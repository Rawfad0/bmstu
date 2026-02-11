#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <thread>
#include <mutex>
#include <fstream>
#include <curl/curl.h>
#include <regex>
#include <chrono>

#include <filesystem>
#include <iomanip>


#define RC_OK 0
#define RC_INCORRECT_INPUT 1

using namespace std;

string site_link = "https://www.patee.ru";

// regex link_regex(R"(<a class="c" href=\"([\s\S]*?)\">[\s\S]*?</a>)");
regex link_regex(R"(="c" href=\"([\s\S]*?)\">[\s\S]*?</a>)");
// regex recipe_regex(R"(class="body"[\s\S]*?<p>([\s\S]*?)</p>)");
regex recipe_regex(R"(><p>([\s\S]*?)</p>)");


size_t page_counter = 0;
set<string> uniq_hrefs;
queue<string> hrefs;
size_t n_threads = 1;
mutex mtx;


// CURL
size_t write_callback(void *contents, size_t size, size_t nmemb, std::string *userp)
{
    size_t total_size = size * nmemb;
    userp->append(static_cast<const char *>(contents), total_size);
    return total_size;
}

string get_html_from_link(const string &link)
{
    CURL* curl;
    curl = curl_easy_init();
    std::string readBuffer;
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "ERROR: curl" << curl_easy_strerror(res) << std::endl;
            readBuffer.clear();
        }
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}


// Extraction
string get_recipe(string html)
{
    string result = "";
    sregex_iterator iter(html.begin(), html.end(), recipe_regex);
    sregex_iterator end;

    while (iter != end) {
        result += (*iter)[1].str() + "\n";
        ++iter;
    }
    return result;
}

vector<string> get_links(string html)
{
    vector<string> matches;
    sregex_iterator iter(html.begin(), html.end(), link_regex);
    sregex_iterator end;

    while (iter != end)
    {
        matches.push_back((*iter)[1].str());
        ++iter;
    }
    
    return matches;
}


// Proccessing
string clean_recipe(string recipe)
{
    string ldquo = "&ldquo;";
    while(true)
    {
        size_t start = recipe.find(ldquo);
        if (start == string::npos)
            break;
        recipe.replace(start, ldquo.length(), "\"");
    }

    string rdquo = "&rdquo;";
    while(true)
    {
        size_t start = recipe.find(rdquo);
        if (start == string::npos)
            break;
        recipe.replace(start, rdquo.length(), "\"");
    }

    return recipe;
}

string get_html_from_file(string path)
{
    string result;
    string line;

    ifstream in(path);
    if (in.is_open())
        while (getline(in, line))
            result += line + '\n';
    in.close();
    return result;
}

void write_recipe(string recipe, string id)
{
    string result;

    ofstream out;
    out.open("./recipes/" + id);
    if (out.is_open())
        out << recipe << endl;
    out.close();
}

void process_recipe(string html, string link)
{
    size_t i = link.find("=");                      // =123
    if (i == string::npos)
        return;                                     // Страница не "рецептурная"
    string id = link.substr(i + 1, link.size() - i);// id страницы
    string recipe = get_recipe(html);               // Достать сам рецепт из html
    recipe = clean_recipe(recipe);                  // Замена кавычек и т.д.
    write_recipe(recipe, id);                       // Запись
}

void process_links(string html)
{
    vector<string> links = get_links(html);
    for (auto &link: links)
    {
        link = site_link + link;
        // cout << "New link: " <<link << endl;
        if (!uniq_hrefs.contains(link))
            hrefs.push(link);
        uniq_hrefs.insert(link);
    }
}

void process_links_mt(string html)
{
    vector<string> links = get_links(html);
    lock_guard<mutex> lock(mtx);
    for (auto &link: links)
    {
        link = site_link + link;
        // cout << "New link: " <<link << endl;
        if (!uniq_hrefs.contains(link))
            hrefs.push(link);
        uniq_hrefs.insert(link);
    }
}

void singlethread_processing()
{
    for (; page_counter > 0; page_counter--)
    {
        string link = hrefs.front();
        hrefs.pop();
        cout << "Left:" << page_counter << "; Cur link: "<< link << endl;
        string html = get_html_from_link(link); // html по ссылке 
        process_recipe(html, link);   // Парсинг рецептов и запись в файл
        process_links(html);          // Парсинг ссылок и помещение новых в очередь
    }
}

string get_link_from_queue_mp()
{
    lock_guard<mutex> lock(mtx);
    if (page_counter == 0)
        return "";
    else if (hrefs.empty())
        return "";
    else
    {
        string link = hrefs.front();
        hrefs.pop();
        page_counter--;
        cout << "Left:" << page_counter << "; Cur link: " << link << endl;
        return link;
    }
}

size_t get_page_counter_mp()
{
    lock_guard<mutex> lock(mtx);
    return page_counter;
}

// void mt_get_links(string link)
// {
//     string html = get_html_from_link(link); 
//     vector<string> links = get_links(html);
//     lock_guard<mutex> lock(mtx);
//     for (auto &link: links)
//     {
//         link = site_link + link;
//         // cout << "New link: " <<link << endl;
//         if (!uniq_hrefs.contains(link))
//             hrefs.push(link);
//         uniq_hrefs.insert(link);
//     }
// }

// void mt_get_recipes(string link)
// {
//     string html = get_html_from_link(link);         // html по ссылке
//     size_t i = link.find("=");                      // =123
//     if (i == string::npos)
//         return;                                     // Страница не "рецептурная"
//     string id = link.substr(i + 1, link.size() - i);// id страницы
//     string recipe = get_recipe(html);               // Достать сам рецепт из html
//     recipe = clean_recipe(recipe);                  // Замена кавычек и т.д.
//     write_recipe(recipe, id);                       // Запись
// }

void wait_threads(vector<thread> &threads)
{
    for (auto &th : threads)
        if (th.joinable())
            th.join();
    threads.clear();
}

// void multithread_processing()
// {
//     std::vector<std::thread> threads;
//     chrono::time_point<chrono::steady_clock> t1 = chrono::steady_clock::now();   
//     while (hrefs.size() < page_counter)
//     {
//         string link = hrefs.front();    // Берем ссылку из очереди
//         hrefs.pop();                    // Удаляем её из очереди
//         threads.emplace_back(&mt_get_links, link);
//         if (hrefs.size() == 0 || threads.size() == n_threads)
//             wait_threads(threads);
//     }
//     wait_threads(threads);
//     chrono::time_point<chrono::steady_clock> t2 = chrono::steady_clock::now();
//     while (page_counter > 0)
//     {
//         string link = hrefs.front();    // Берем ссылку из очереди
//         hrefs.pop();                    // Удаляем её из очереди
//         page_counter--;                 // Уменьшаем количество оставшихся для обработки страниц
//         threads.emplace_back(&mt_get_recipes, link);
//         if (hrefs.size() == 0 || threads.size() == n_threads)
//             wait_threads(threads);
//     }
//     chrono::time_point<chrono::steady_clock> t3 = chrono::steady_clock::now();
//     cout << "queue size: " << hrefs.size() << " Page counter: "<< page_counter << endl;
//     cout << "time links  : " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << endl;
//     cout << "time recipes: " << chrono::duration_cast<chrono::milliseconds>(t3 - t2).count() << endl;
//     cout << "time total  : " << chrono::duration_cast<chrono::milliseconds>(t3 - t1).count() << endl;
// }

void mt_process()
{
    string link = get_link_from_queue_mp();
    if (!link.empty())
    {
        string html = get_html_from_link(link); // html по ссылке 
        process_recipe(html, link);     // Парсинг рецептов и запись в файл
        process_links_mt(html);         // Парсинг рецептов и помещение новых в очередь
    }
}

void multithread_processing()
{
    std::vector<std::thread> threads;

    while(get_page_counter_mp() > 0)
    {
        threads.emplace_back(&mt_process);
        if (hrefs.size() == 0 || threads.size() == n_threads)
            wait_threads(threads);
    }
    wait_threads(threads);
}

int main()
{
    int rc = RC_OK;

    // // Замеры времени
    // size_t _page_counter = 100;
    // size_t reps = 5;
    // cout << "page_counter = " << _page_counter << "; reps = " << reps << endl;
    // for (size_t i = 64; i > 1; i/=2)
    // {
    //     n_threads = i;
    //     double time = 0;
    //     cout << n_threads << ": ";
    //     for (size_t j = 0; j < reps; j++)
    //     {
    //         // Очистка
    //         page_counter = _page_counter; 
    //         uniq_hrefs.clear();
    //         hrefs = {};
    //         // Начальное заполнение
    //         hrefs.push(site_link);          // Начальную страницу в очередь
    //         uniq_hrefs.insert(site_link);   // Начальную страницу в множество
    //         // Замер выполнения
    //         chrono::time_point<chrono::steady_clock> tb = chrono::steady_clock::now();
    //         multithread_processing();
    //         chrono::time_point<chrono::steady_clock> te = chrono::steady_clock::now();
    //         time += chrono::duration_cast<chrono::milliseconds>(te - tb).count();
    //     }
    //     cout << time / reps << endl;
    // }
    // n_threads = 1;
    // double time = 0;
    // cout << n_threads << ": ";
    // for (size_t j = 0; j < reps; j++)
    // {
    //     // Очистка
    //     page_counter = _page_counter; 
    //     uniq_hrefs.clear();
    //     hrefs = {};
    //     // Начальное заполнение
    //     hrefs.push(site_link);          // Начальную страницу в очередь
    //     uniq_hrefs.insert(site_link);   // Начальную страницу в множество
    //     // Замер выполнения
    //     chrono::time_point<chrono::steady_clock> tb = chrono::steady_clock::now();
    //     multithread_processing();
    //     chrono::time_point<chrono::steady_clock> te = chrono::steady_clock::now();
    //     time += chrono::duration_cast<chrono::milliseconds>(te - tb).count();
    // }
    // cout << time / reps << endl;

    // cout << "Введите ссылку на сайт"
    // cin >> site_link;
    // cout << site_link;

    hrefs.push(site_link);          // Начальную страницу в очередь
    uniq_hrefs.insert(site_link);   // Начальную страницу в множество

    cout << "Введите количество обрабатываемых страниц: ";
    if ((!(cin >> page_counter) || page_counter == 0))
    {
        cout << "Введено некорректное число страниц (0)!";
        rc = RC_INCORRECT_INPUT;
    }
    else if (cout << "Введите количество потоков: " && (!(cin >> n_threads) || n_threads == 0))
    {
        cout << "Введено некорректное число потоков (0)!";
        rc = RC_INCORRECT_INPUT;
    }
    else 
    {
        if (n_threads == 1)
            singlethread_processing();
        else
            multithread_processing();
    }
    return rc;
}