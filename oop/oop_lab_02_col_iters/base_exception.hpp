#include <ctime>
#include <string>
#include "base_exception.h"

BaseException::BaseException(const time_t time_info,
                                         const char* file_info, 
                                         const size_t line_info,
                                         const char* errmsg)
{
    strcpy(_errmsg, "");
    strcat(_errmsg, "\nTime: ");
    char *str_time = ctime(&time_info);
    strcat(_errmsg, str_time);
    strcat(_errmsg, "File: ");
    strcat(_errmsg, file_info);
    char str_line[10] = "\0";
    strcat(str_line, std::to_string(line_info).c_str());
    strcat(_errmsg, "\nLine: ");
    strcat(_errmsg, str_line);
    strcat(_errmsg, "\nError message: ");
    strcat(_errmsg, errmsg);
}