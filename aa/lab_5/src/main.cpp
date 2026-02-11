#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <fstream>
#include <regex>
#include <chrono>
#include <atomic>
#include <filesystem>
#include <iomanip>

#include <sqlite3.h>
// #include <codecvt>

#include "task.hpp"
#include "mtqueue.hpp"
#include "logger.hpp"


using namespace std;
atomic<bool> finished; // Условие завершения для циклов в потоках


const string dir = "./recipes";
// Queues
Queue<StringTask> rq;   // Очередь для чтения (элементы содержат имя файла)
Queue<StringTask> pq;   // Очередь для обработки (элементы содержат содержимое файла)
Queue<RecipeTask> wq;   // Очередь для записи (элементы содержат данные о рецепте)
Queue<Task> fq;         // Очередь для завершения
// Logger
Logger logger("./log.txt");
// DataBase
sqlite3 *create_db(const char *db_name) {
    sqlite3 *db;
    if (sqlite3_open(db_name, &db))
        throw runtime_error("ERROR: cant create table" + string(sqlite3_errmsg(db)));

    const char *create_table = R"(
        create table if not exists recipes (
            id integer primary key,
            issue_id integer,
            url text,
            title text,
            ingredients text,
            steps text
        );
    )";
    char *error_message = nullptr;
    int rc = sqlite3_exec(db, create_table, nullptr, nullptr, &error_message);

    if (rc != SQLITE_OK) {
        string err_msg(error_message);
        sqlite3_free(error_message);
        sqlite3_close(db);
        throw runtime_error("ERROR: cant create table" + err_msg);
    }
    return db;
}

void insert_recipe_into_db(sqlite3 *db, const RecipeTask &recipe) {
    string ingredients_str;
    for (const auto &ingredient : recipe.get_ingredients())
        ingredients_str += ingredient[0] + "(" + ingredient[1] + " " + ingredient[2] + ")|";
    if (!ingredients_str.empty())
        ingredients_str.pop_back();

    string steps_str;
    for (const auto &step : recipe.get_steps())
        steps_str += step + " ";
    if (!steps_str.empty())
        steps_str.pop_back();

    string url = recipe.get_url();
    string title = recipe.get_title();
    string img_url = recipe.get_img_url();
    string sql = "INSERT INTO recipes (id, issue_id, url, title, ingredients, steps) VALUES (?, ?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, recipe.get_task_index());
    sqlite3_bind_int(stmt, 2, 9227);
    sqlite3_bind_text(stmt, 3, url.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, ingredients_str.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, steps_str.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, img_url.c_str(), -1, SQLITE_STATIC);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// Stages
void read() 
{
    while (!finished.load()) {
        if (!rq.is_empty()) {
            StringTask task = rq.pop();
            ssize_t task_index = task.get_task_index();
            if (task_index == -1) {
                pq.push(StringTask());
                continue;
            }

            task.stop_wait(0);
            task.start_work(0);
            logger.log(to_string(task_index) + " reading begin");

            ifstream file(task.get_data());
            // file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));
            stringstream wss;
            wss << file.rdbuf();        // Чтение в поток
            task.set_data(wss.str());   // Передача потока для следующей задачи (Переиспользование задачи для следующей очереди)
            file.close();

            task.stop_work(0);
            task.start_wait(1);
            pq.push(task);
            logger.log(to_string(task_index) + " reading end");
        }
    }
}

void parse() {
    while (!finished.load()) {
        if (!pq.is_empty()) {
            StringTask task = pq.pop();
            ssize_t task_index = task.get_task_index();
            if (task_index == -1) {
                wq.push(RecipeTask());
                continue;
            }

            task.stop_wait(1);
            task.start_work(1);
            logger.log(to_string(task_index) + " processing begin");
            
            RecipeTask recipe_task(task, task.get_data());
            
            task.stop_work(1);
            task.start_wait(2);
            wq.push(recipe_task);
            logger.log(to_string(task_index) + " processing end");
        }
    }
}

void write() {
    sqlite3 *db = create_db("recipes.db");
    while (!finished.load()) {
        if (!wq.is_empty()) {
            RecipeTask task = wq.pop();
            ssize_t task_index = task.get_task_index();
            if (task_index == -1) {
                fq.push(StringTask());
                continue;
            }

            task.stop_wait(2);
            task.start_work(2);
            logger.log(to_string(task_index) + " writing begin");

            insert_recipe_into_db(db, task);

            task.stop_work(2);
            Task final_task(task);
            fq.push(final_task);
            logger.log(to_string(task_index) + " writing end");
        }
    }
    sqlite3_close(db);
}


int main()
{
    vector<string> file_names;
    if (filesystem::exists(dir) && filesystem::is_directory(dir)) {
        for (const auto& entry : filesystem::directory_iterator(dir))
            if (filesystem::is_regular_file(entry.status()))
                file_names.push_back(entry.path().filename().string());
    } else
        throw runtime_error("ERROR: cant open dir: " + dir);

    for (size_t i = 0; i < file_names.size(); ++i) {
        StringTask task(dir + "/" + file_names[i], i + 1);
        task.start_wait(0);
        rq.push(task);
    }
    rq.push(StringTask());

    thread reader_thread(&read);
    thread parcer_thread(&parse);
    thread writer_thread(&write);


    size_t count = 0;
    array<clock_t, 3> wait_time;
    array<clock_t, 3> work_time;

    for (size_t i = 0; i < 3; ++i) {
        wait_time[i] = 0;
        work_time[i] = 0;
    }

    while (true) {
        if (!fq.is_empty()) {
            Task task = fq.pop();
            if (task.get_task_index() == -1) {
	            finished.store(true);
                break;
            }
            ++count;
            for (size_t i = 0; i < 3; ++i) {
                wait_time[i] += task.get_wait_time()[i];
                work_time[i] += task.get_work_time()[i];
            }
        }
    }
    
    reader_thread.join();
    parcer_thread.join();
    writer_thread.join();
    
    ofstream last_log("final_log.txt");

    for (size_t i = 0; i < 3; ++i) {
        last_log << "Work time in " << i + 1 << " " << work_time[i] * 1000 / count / CLOCKS_PER_SEC << endl;
        last_log << "Wait time in " << i + 1 << " " << wait_time[i] * 1000 / count / CLOCKS_PER_SEC << endl;
    }

    return 0;
}
