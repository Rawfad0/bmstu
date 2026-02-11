#include "f.h"

void strreverse(char* begin, char* end)
{
	char aux;
	while(end>begin)
		aux=*end, *end--=*begin, *begin++=aux;
}

/**
 * Ansi C "itoa" based on Kernighan & Ritchie's "Ansi C":
 */	
void itoa(int value, char* str, int base)
{
	static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char* wstr=str;
	int sign;

	// Validate base
	if (base < 2 || base > 35)
    {
        *wstr='\0';
        return;
    }
	// Take care of sign
	if ((sign=value) < 0)
        value = -value;
	// Conversion. Number is reversed.
	do 
        *wstr++ = num[value%base];
    while(value/=base);
	if (sign<0) 
        *wstr++='-';
	*wstr='\0';
	// Reverse string
	strreverse(str,wstr-1);
}

/**
 * @brief Сдвиг цифр мантиссы влево
 * 
 * @param arr массив цифр мантиссы
 * @param n длина массива
 * @param shift сдвиг
 */
void shift_to_left(int8_t *arr, size_t n, size_t shift)
{
    for (size_t i = 0; i < n; i++)
    if (i < n - shift)
        arr[i] = arr[i + shift];
    else
        arr[i] = 0;
}

/**
 * @brief Подсчет конечных нулей
 * 
 * @param arr массив цифр мантиссы
 * @param n длина массива 
 * @return int количество нулей после числа
 */
int count_zeros(int8_t *arr, size_t n)
{
    int zero_counter = 0;
    for (size_t i = 0; arr[i] == 0 && i < n; i++)
        zero_counter++;
    return zero_counter;
}
 
/**
 * @brief Подсчет значащих цифр в мантиссе
 * 
 * @param arr массив цифр мантиссы
 * @param n длина массива 
 * @return int количество цифр
 */
int count_digits(int8_t *arr, size_t n)
{
    int digit_counter = n;
    for (size_t i = n - 1; arr[i] == 0; i--)
        digit_counter--;
    return digit_counter;
}

/**
 * @brief Округление
 * 
 * @param arr массив цифр мантиссы
 * @param n длина массива 
 */
void round_mantiss(int8_t *arr, size_t n)
{
    int counter = count_digits(arr, n);
    for (size_t i = 0; i < counter; i++)
    {
        arr[i + 1] += arr[i] / 10;
        arr[i] = arr[i] % 10;
    }
}

int str_to_real_num(char *real_num_str, real_num *real_num)
{
    char *ptr = real_num_str;   // Адрес первого элемента строки
    int i = 0;                  // Счетчик количетсва цифр в мантиссе
    int exp_diff = 0;           // Изменение порядка за счет перевода действительного числа в целое
    int is_exp_neg = 0;         // Отрицателен ли порядок
    // Обработка знака
    if (*ptr == '-')
    {
        real_num->mantiss_sign = -1;
        ptr++;
    }
    else if (*ptr == '+')
        ptr++;
    // Обработка целой части
    while (*ptr != 'e' && *ptr != 'E' && *ptr != '.' && *ptr != '\0')
    {
        real_num->mantiss_digits[MANTISS_SIZE - 1 - i] = *ptr - '0';
        i++;
        ptr++;
        if (i > MANTISS_SIZE)
        {
            printf("Ошибка размера мантиссы\n");
            return MANTISS_SIZE_ERROR;
        }
    }
    // Обработка остальной части (дробной и порядка)
    switch (*ptr)
    {
        case '.':
            ptr++;
            while (*ptr != 'e' && *ptr != 'E' && *ptr != '\0')
            {
                real_num->mantiss_digits[MANTISS_SIZE - 1 - i] = *ptr - '0';
                i++;
                ptr++;
                exp_diff--;
                if (i > MANTISS_SIZE)
                {
                    printf("Ошибка размера мантиссы\n");
                    return MANTISS_SIZE_ERROR;
                }
            }
            if ((*ptr != 'e') && (*ptr != 'E'))
                break;
        case 'e':
        case 'E':
            ptr++;
            if (*ptr == '-')
            {
                is_exp_neg = 1;
                ptr++;
            }
            else if (*ptr == '+')
                ptr++;
            
            int pw = strlen(ptr);
            while (*ptr != '\0')
            {
                real_num->exp += (*ptr - '0') * (int)pow(10, pw-- - 1);
                ptr++;
            }
            break;
    }

    // Знак порядка
    if (is_exp_neg)
        real_num->exp *= -1;
    // Проверка переполнения экспоненты
    if (abs(real_num->exp) > EXP_MAX)
    {
        printf("Ошибка: порядок превысил допустимое значение в 5 знаков.\n");
        return EXP_SIZE_ERROR;
    }
    
    real_num->exp += exp_diff;
    // Сдвиг влево
    shift_to_left(real_num->mantiss_digits, MANTISS_SIZE, MANTISS_SIZE - i);
    return OK;
}

int str_to_int_num(char *integer_num_str, int_num *integer_num)
{
    char *ptr = integer_num_str;
    int i = 0;
    // Знак
    if (*ptr == '-')
    {
        integer_num->sign = -1;
        ptr++;
    }
    else if (*ptr == '+')
        ptr++;

    i = 0;
    while (*ptr != '\0')
    {
        if (i > INT_SIZE - 1)
        {
            printf("Ошибка размера мантиссы\n");
            return MANTISS_SIZE_ERROR;
        }
        integer_num->digits[INT_SIZE - 1 - i] = *ptr - '0';
        i++;
        ptr++;
    }
    // Сдвиг влево
    shift_to_left(integer_num->digits, INT_SIZE, INT_SIZE - i);
    return OK;
}

int res_to_str(calc_num res_num, char *res_num_str)
{
    char *ptr = res_num_str;
    int count = count_digits(res_num.mantiss_digits, CALC_MANTISS_SIZE);
    int rc = 0;

    // Знак
    if (res_num.mantiss_sign >= 0)
        *ptr = '+';
    else
        *ptr = '-';
    ptr++;
    // Начало нормализованного вида
    *(ptr++) = '0';
    *(ptr++) = '.';
    // Мантисса
    for (int i = count - 1; i >= 0; i--)
    {
        *ptr = res_num.mantiss_digits[i] + '0'; 
        ptr++;
    }
    // Обозначение экспоненты
    *ptr = 'E';
    ptr++;
    // Знак экспоненты
    if (res_num.exp >= 0)
        *ptr = '+';
    else
        *ptr = '-';
    ptr++;
    // Экспонента
    itoa(abs(res_num.exp), ptr, 10);

    return rc;
}

int calculate(real_num real_num, int_num integer_num, calc_num *res_num)
{
    int rc = 0;

    // Умножение
    for (int i = 0; i < MANTISS_SIZE; i++)
        for (int j = 0, rest = 0; j < INT_SIZE || rest; j++)
        {
            int cur = res_num->mantiss_digits[i + j] + real_num.mantiss_digits[i] * (j < INT_SIZE ? integer_num.digits[j] : 0) + rest;
            res_num->mantiss_digits[i + j] = cur % 10;
            rest = cur / 10;
        }

    // Знак мантиссы
    res_num->mantiss_sign = real_num.mantiss_sign * integer_num.sign;
    // Экспонента
    res_num->exp = real_num.exp;

    // Проверка на ноль
    int counter = count_zeros(res_num->mantiss_digits, CALC_MANTISS_SIZE);
    if (counter == CALC_MANTISS_SIZE)
    {
        printf("0 (нуль) непредставим в нормализованном виде.\n\n");
        return ZERO_ERROR;
    }

    // Округление
    counter = count_digits(res_num->mantiss_digits, CALC_MANTISS_SIZE);
    if (counter >= RES_SIZE)
    {
        if (res_num->mantiss_digits[counter - RES_SIZE] >= 5)
            res_num->mantiss_digits[counter - RES_SIZE + 1]++;   // округление ив большую сторону
        shift_to_left(res_num->mantiss_digits, CALC_MANTISS_SIZE, counter - RES_SIZE + 1);
        res_num->exp += counter - RES_SIZE + 1;
        round_mantiss(res_num->mantiss_digits, CALC_MANTISS_SIZE);
    }
    // Перевод конечных нулей в экспоненту
    counter = count_zeros(res_num->mantiss_digits, CALC_MANTISS_SIZE);
    shift_to_left(res_num->mantiss_digits, CALC_MANTISS_SIZE, counter);
    res_num->exp += counter;

    // Подсчет значащих цифр в мантиссе и добавление в экспоненту
    counter = count_digits(res_num->mantiss_digits, CALC_MANTISS_SIZE);
    res_num->exp += counter;

    // Проверка на переполнение порядка
    if (abs(res_num->exp) > EXP_MAX)
    {
        printf("Ошибка: Произошло переполнение порядка.\n");
        return EXP_SIZE_ERROR;
    }

    return rc;
}
