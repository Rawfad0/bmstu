#ifndef TASK_HPP
#define TASK_HPP

#include <array>
#include <string>
#include <sys/types.h>
#include <vector>
#include <sstream>
#include <iostream>

class Task
{
public:
    // explicit Task(ssize_t task_index = -1);
    explicit Task(ssize_t task_index): _task_index(task_index) {};

    virtual ~Task() {};

    ssize_t get_task_index() const {return _task_index;};
    std::array<clock_t, 3> get_wait_time() const {return wait_time;}
    std::array<clock_t, 3> get_work_time() const {return work_time;}

    void start_wait(size_t queue_ind) {wait_time[queue_ind] = clock();}
    void stop_wait(size_t queue_ind) {wait_time[queue_ind] = clock() - wait_time[queue_ind];}

    void start_work(size_t queue_ind) {work_time[queue_ind] = clock();}
    void stop_work(size_t queue_ind) {work_time[queue_ind] = clock() - work_time[queue_ind];}

    std::array<clock_t, 3> wait_time;
    std::array<clock_t, 3> work_time;
private:
    ssize_t _task_index;

};

class RecipeTask;

class StringTask : public Task {
public:
    explicit StringTask(ssize_t task_index = -1): Task(task_index) {};
    StringTask(const std::string &data, ssize_t task_index = -1): Task(task_index), _data(data) {};

    std::string get_data() const {return _data;}
    void set_data(const std::string &str) {_data = str;}

private:
    std::string _data;
};


class RecipeTask : public Task {
public:
    explicit RecipeTask(ssize_t task_index = -1): Task(task_index) {}
    RecipeTask(const StringTask &string_task, const std::string &recipe_data): Task(string_task) {parse(recipe_data);};
    RecipeTask(const std::string &recipe_data, ssize_t task_index = -1): Task(task_index) {parse(recipe_data);};

    std::string get_url() const {return _url;}
    std::string get_title() const {return _title;}
    std::vector<std::array<std::string, 3>> get_ingredients() const {return _ingredients;}
    std::vector<std::string> get_steps() const {return _steps;}
    std::string get_img_url() const {return _img_url;}

private:

    void parse_ingredients(std::istringstream &iss) {
        std::string str_n;
        int n;
        std::getline(iss, str_n);
        try{
            n = stoi(str_n);
        }
        catch(std::exception &err)
        {
            std::cout << "ERROR ingredients " << str_n << err.what() << std::endl;
        }
        // std::string str_n;
        // std::getline(iss, str_n);
        // cout << str_n << std::endl;
        // const int n = std::stoi(str_n);
        std::string name, unit, quantity;
        for (int i = 0; i < n; i++) {
            std::getline(iss, name, ';');
            std::getline(iss, unit, ';');
            std::getline(iss, quantity);
            _ingredients.push_back({name, unit, quantity});
            // std::cout << name + " " + unit + " " + quantity << std::endl;
        }
    }

    void parse_steps(std::istringstream &iss) {
        // std::string str_n;
        // std::getline(iss, str_n);
        // cout << str_n << std::endl;
        // const int n = std::stoi(str_n);
        std::string str_n;
        int n;
        std::getline(iss, str_n);
        // std::cout << str_n << std::endl;
        try{
            n = stoi(str_n);
        }
        catch(std::exception &err)
        {
            std::cout << "ERROR steps " << str_n << err.what() << std::endl;
        }
        std::string step;
        for (int i = 0; i < n; i++) {
            std::getline(iss, step);
            _steps.push_back(step);
        }
    }

    void parse(const std::string &recipe) {
        std::istringstream iss(recipe);
        std::getline(iss, _url);
        std::getline(iss, _title);
        std::getline(iss, _img_url);
        parse_ingredients(iss);
        parse_steps(iss);
    }

    std::string _url;
    std::string _title;
    std::string _img_url;
    std::vector<std::array<std::string, 3>> _ingredients;
    std::vector<std::string> _steps;
 };

#endif // TASK_HPP
