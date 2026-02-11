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

regex link_regex(R"(="c" href=\"([\s\S]*?)\">[\s\S]*?</a>)");
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
    out.open("./htmls/" + id);
    if (out.is_open())
        out << recipe << endl;
    out.close();
}

void process_recipe(string html, string link)
{
    while(true)
    {
        size_t start = link.find("/");
        if (start == string::npos)
            break;
        link.replace(start, 1, "_");
    }
    write_recipe(html, link);                       // Запись
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

void wait_threads(vector<thread> &threads)
{
    for (auto &th : threads)
        if (th.joinable())
            th.join();
    threads.clear();
}

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