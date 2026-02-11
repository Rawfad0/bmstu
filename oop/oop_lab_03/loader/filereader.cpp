#include "filereader.h"


FileReader::FileReader() {}

FileReader::FileReader(const std::string& filename)
{
    this->filename = filename;
}

void FileReader::open()
{
    if (this->is_open())
    {
        throw std::exception();
    }
    this->file = fopen(this->filename.c_str(), "r");

    if (!this->is_open())
    {
        throw std::exception();
    }
}

void FileReader::close()
{
    if (!this->is_open())
    {
        throw std::exception();
    }
    fclose(this->file);
    this->file = nullptr;
}

bool FileReader::is_open()
{
    return this->file != nullptr;
}

double FileReader::read()
{
    if (!this->is_open())
    {
        throw std::exception();
    }

    double x;

    fscanf(this->file, "%lf", &x);

    return x;
}
