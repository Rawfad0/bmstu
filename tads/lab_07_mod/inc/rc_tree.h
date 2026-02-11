#ifndef RC_TREE_H__
#define RC_TREE_H__

typedef enum error
{
    /// При выполнении действия ошибок не возникло
    BIN_TREE_OK = 0,
    /// При вызове функции указаны неверные параметры
    BIN_TREE_INVALID_PARAM, 
    /// При выполнении действия возникли ошибки при работе с памятью 
    BIN_TREE_MEM,
    /// Не найдено значение по указанному ключу
    BIN_TREE_NOT_FOUND
} bt_rc_t;

#endif
