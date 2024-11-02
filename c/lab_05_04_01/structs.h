/**
* Модуль содержащий константы
*/

#ifndef __STRUCTS__H__
#define __STRUCTS__H__

#include <stdint.h>

#define LAST_NAME_MAX 25
#define FIRST_NAME_MAX 10
#define GRADES_NUMBER 4

struct student
{
    char last_name[LAST_NAME_MAX+1];
    char first_name[FIRST_NAME_MAX+1];
    uint32_t grades[GRADES_NUMBER];
};

#endif
