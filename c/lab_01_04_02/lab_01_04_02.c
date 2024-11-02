/*!
 * \file
 * \brief Задача 4
 *
 * 2. С клавиатуры задаётся время в секундах. Перевести в часы, минуты, секунды и вывести на экран.
 */

#include <stdio.h>

#define SECONDS_IN_MINUTE 60
#define MINUTES_IN_HOUR 60

/*!
 * \brief Переводит секунды в часы, минуты, секунды
 *
 * Данная функция запрашивает значение времени в секундах,
 * которое является целым числом seconds,
 * и выводит на экран значения часов, минут, секунд,
 * которые являются целыми числами hours, minutes, seconds.
 */
int main(void)
{
    int seconds, minutes, hours;
    printf("Введите количество секунд: ");
    scanf("%d", &seconds);

    hours = seconds / (SECONDS_IN_MINUTE * MINUTES_IN_HOUR);
    seconds %= (SECONDS_IN_MINUTE * MINUTES_IN_HOUR);
    minutes = seconds / SECONDS_IN_MINUTE;
    seconds %= SECONDS_IN_MINUTE;

    printf("Количество часов: %d\n", hours);
    printf("Количество минут: %d\n", minutes);
    printf("Количество секунд: %d\n", seconds);
    return 0;
}