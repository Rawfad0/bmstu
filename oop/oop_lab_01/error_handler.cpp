#include "error_handler.h"

void error_handler(const rc_t &error)
{
    const char *error_message = NULL;
    
    switch (error)
    {
        case RC_UNDEFINED_ACTION:
            error_message = "Неизвестное действие.";
            break;
        case RC_FILE_OPEN_ERROR:
            error_message = "Не удалось открыть файл.";
            break;
        case RC_FILE_READ_ERROR:
            error_message = "Не удалось прочитать файл.";
            break;
        case RC_FILE_WRITE_ERROR:
            error_message = "При записи файла были даны некорректные данные.";
            break;
        case RC_MEMORY_ALLOCATION_ERROR:
            error_message = "Не удалось выделить память.";
            break;
        case RC_FIGURE_NOT_LOADED:
            error_message = "Фигура не загружена.";
            break;
        case RC_INCORRECT_POINTS:
            error_message = "Некорректный массив точек.";
            break;
        case RC_INCORRECT_EDGES:
            error_message = "Некорректный массив ребер.";
            break;
        case RC_INCORRECT_FIGURE:
            error_message = "Некорректная фигура.";
            break;
        case RC_POINTS_SIZE_ERROR:
            error_message = "Кол-во точек в файле должно быть больше нуля.";
            break;
        case RC_EDGES_SIZE_ERROR:
            error_message = "Кол-во ребер в файле должно быть больше нуля.";
            break;
        case RC_SCALE_COEFF_ERROR:
            error_message = "Коэффициенты масштабирования не должны равняться нулю.";
            break;
        case RC_INCORRECT_SCENE:
            error_message = "При попытке нарисовать, фигуру произошла ошибка.";
            break;
        default:
            error_message = "Неизвестная ошибка.";
    };
    QMessageBox::critical(NULL, "Ошибка!", error_message);
}
