/**
* Модуль содержащий структуру "object" и неоходимые структуре значения
*/

#ifndef __STRUCTS__H__
#define __STRUCTS__H__

#define NAME_MAX 25

struct object
{
    char name[NAME_MAX+1];
    double mass;
    double volume;
};

#endif
