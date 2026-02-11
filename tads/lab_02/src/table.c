#include "table.h"

/**
 * @brief Проверка даты
 * 
 * @param date строка даты в формате DD.MM.YYYY
 * @return int результат (0 - если корректная дата)
 */
int is_date_valid(char date[])
{
    // Перевод строки даты в числа
    int day = 10*(date[0] - '0') + (date[1] - '0');
    int month = 10*(date[3] - '0') + (date[4] - '0');
    int year = 1000*(date[6] - '0') + 100*(date[7] - '0') + 10*(date[8] - '0') + (date[9] - '0');

    int days[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};    // Массив для проверки количества дней

    // Простая универсальная проверка
    if (day == 0 || day > 31 || month == 0 || month > 12)
        return RC_INCORRECT_DATE;

    // Проверка количества дней в  конкретном месяце
    if (day > days[month - 1])
        return RC_INCORRECT_DATE;

    // Проверка високосных годов
    if (month == 2 && year % 400 == 0 && day > 29)
        return RC_INCORRECT_DATE;
    if (month == 2 && year % 100 == 0 && day > 28)
        return RC_INCORRECT_DATE;
    if (month == 2 && year % 4 == 0 && day > 29)
        return RC_INCORRECT_DATE;

    return RC_OK;
}

/**
 * @brief Проверка полей
 * 
 * @param fields поля записи
 * @return int код возврата
 */
int check_fields(char fields[TABLE_FIELDS][MAX_FIELD_LEN+1])
{
    int is_correct_address_type = 0;
    regex_t regex;
    // Проверка фиксированных полей студента
    for (size_t i = 0; i < TABLE_FIELDS - ADDRESS_FIELDS; i++)
    {
        regcomp(&regex, masks[i], REG_EXTENDED);
        if (regexec(&regex, fields[i], 0, NULL, 0) == REG_NOMATCH)
        {
            printf("OK3\n");
            printf("Введенное поле '%s' не прошло проверку. Поле должно иметь вид '%s'.\n", fields[i], masks[i]);
            return RC_INCORRECT_FIELD;
        }
        if (i == 6 && is_date_valid(fields[i]) != 0)
            return RC_INCORRECT_DATE;
    }
    // Проверка полей адреса студента
    for (size_t i = 0; i < ADDRESS_TYPES; i++)
        if (strcmp(addresses[i], fields[TABLE_FIELDS-ADDRESS_FIELDS]) == 0)
        {
            for (size_t j = 0; j < ADDRESS_FIELDS - 1; j++)
            {
                regcomp(&regex, masks_address_types_with_blanks[i][j], REG_EXTENDED);
                if (regexec(&regex, fields[TABLE_FIELDS-ADDRESS_FIELDS+j+1], 0, NULL, 0) == REG_NOMATCH)
                {
                    printf("Введенное поле '%s' не прошло проверку. Поле должно иметь вид '%s'.\n", 
                        fields[TABLE_FIELDS-ADDRESS_FIELDS+j+1], masks_address_types_with_blanks[i][j]);
                    return RC_INCORRECT_FIELD;
                }
            }
            is_correct_address_type = 1;
        }
    if (!is_correct_address_type)
        return RC_INCORRECT_ADDRESS_TYPE;
    return RC_OK;
}

/**
 * @brief Перевод массива строк в стуктуру студента
 * 
 * @param fields массив строк
 * @return student_t структура студента
 */
student_t fields_to_student(char fields[TABLE_FIELDS][MAX_FIELD_LEN+1])
{
    student_t stud;
    // Перевод статических полей
    strcpy(stud.last_name, fields[0]);
    strcpy(stud.first_name, fields[1]);
    strcpy(stud.group, fields[2]);
    stud.gender = fields[3][0];
    strcpy(stud.age, fields[4]);
    strcpy(stud.gpa, fields[5]);
    strcpy(stud.enrollment_date, fields[6]);
    strcpy(stud.address_type, fields[7]);
    // Перевод вариативных полей
    if (strcmp(ADDRESS_TYPE_HOUSE, fields[7]) == 0)
    {
        strcpy(stud.address.house.street, fields[8]);
        strcpy(stud.address.house.house_num, fields[9]);
        strcpy(stud.address.house.flat_num, fields[10]);
    }
    else if (strcmp(ADDRESS_TYPE_DORMITORY, fields[7]) == 0)
    {
        strcpy(stud.address.dormitory.dorm_num, fields[9]);
        strcpy(stud.address.dormitory.room_num, fields[10]);
    }
    else if (strcmp(ADDRESS_TYPE_RENTAL_PLACE, fields[7]) == 0)
    {
        strcpy(stud.address.rent.street, fields[8]);
        strcpy(stud.address.rent.house_num, fields[9]);
        strcpy(stud.address.rent.flat_num, fields[10]);
        strcpy(stud.address.rent.cost, fields[11]);
    }
    return stud;
}

/**
 * @brief Запись строк записи в структуру студента с проверкой корректности строк  
 * 
 * @param fields массив строк
 * @param student указатель на структуру студента
 * @return int код возврата
 */
int process_student(char fields[TABLE_FIELDS][MAX_FIELD_LEN+1], student_t *student)
{
    int rc = 0;
    // Проверка введенных полей
    if ((rc = check_fields(fields)))
    {
        printf("Введенные данные не соответствуют формату входных данных.\n");
        printf("Некорректная запись: '%s %s %s %s %s %s %s %s %s %s %s %s'\n", \
            fields[0], fields[1], fields[2], fields[3], fields[4], fields[5], \
            fields[6], fields[7], fields[8], fields[9], fields[10], fields[11]);
        return rc;
    }
    *student = fields_to_student(fields);   // Перевод полей в структуру студента
    return RC_OK;
}

/**
 * @brief Чтение таблицы из файла
 * 
 * @param file_name имя файла
 * @param students таблица студентов
 * @return int код возврата
 */
int read_table(char *file_name, student_table_t *students)
{
    FILE *f;
    char fields[TABLE_FIELDS][MAX_FIELD_LEN+1];
    int rc = RC_OK;

    students->n = 0;    // Количество записей
    if (!(f = fopen(file_name, "r")))
        return RC_INCORRECT_FILE;
    // Чтение из файла, проверка считанной записи и запись в таблицу
    while (!feof(f) && rc == 0 && students->n < MAX_TABLE_LEN)
        if (!(rc = read_record(f, fields)))
            if (!(rc = process_student(fields, &(students->table[students->n]))))
                (students->n)++;
    fclose(f);
    if (rc)
        students->n = 0;
    return rc;
}

/**
 * @brief Вывод таблицы студентов
 * 
 * @param students таблица студентов
 */
void print_table(student_table_t students)
{
    // Шапка таблицы
    print_table_header();
    // Таблица
    if (students.n == 0)
        printf("В таблице нет записей.\n");
    for (size_t i = 0; i < students.n; i++)
        printf("|%*zu", PADDING_4, i + 1), print_record(students.table[i]);
}

/**
 * @brief Запрашивает field_name, длиной n. Записывает в field и проверяет mask
 * 
 * @param field строка для записи
 * @param n размер поля
 * @param field_name название поля
 * @param mask маска регулярного выражения
 * @return int код возврата
 */
int get_field(char field[], size_t n, char field_name[], char mask[])
{
    int rc = RC_OK;
    printf("Введите %s студента: ", field_name);    // Приглашение к вводу
    if ((rc = get_input(&field[0], n + 1)))
        return rc;
    if (field[strlen(field) - 1] == '\n')
        field[strlen(field) - 1] = '\0';            // Удаление символа переноса строки

    // Проверка введенного поля с помощью регулярного выражение
    regex_t regex;
    regcomp(&regex, mask, REG_EXTENDED);
    if (regexec(&regex, field, 0, NULL, 0) == REG_NOMATCH)
    {
        printf("Введенное поле %s '%s' не прошло проверку. Поле должно иметь вид '%s'.\n", 
            field_name, field, mask);
        return RC_INCORRECT_FIELD;
    }
    
    return RC_OK;
}

/**
 * @brief Поиск студентов определенного года поступления и живущих в съемном жилье
 * 
 * @param students таблица студентов
 * @return int код возврата
 */
int print_filtered_table(student_table_t students)
{
    char selected_year[DATE_LEN+1];
    char mask[] = MASK_YEAR;
    size_t counter = 0;
    int rc = RC_OK;
    
    // Ввод года
    printf("Введите %s студента: ", "enrollment year");
    if ((rc = get_input(&selected_year[6], YEAR_LEN + 1)))
        return rc;
    if (selected_year[6+strlen(&selected_year[6]) - 1] == '\n')
        selected_year[6+strlen(&selected_year[6]) - 1] = '\0';

    // Проверка года
    regex_t regex;
    regcomp(&regex, mask, REG_EXTENDED);
    if (regexec(&regex, &selected_year[6], 0, NULL, 0) == REG_NOMATCH)
    {
        printf("Введенное поле %s '%s' не прошло проверку. Поле должно иметь вид '%s'.\n", 
            "enrollment year",  &selected_year[6], mask);
        return RC_INCORRECT_FIELD;
    }

    // Вывод подходящих студентов
    print_table_header();
    for (size_t i = 0; i < students.n; i++)
        if (!(strcmp(&selected_year[6], &students.table[i].enrollment_date[6])) && 
            !(strcmp(ADDRESS_TYPE_RENTAL_PLACE, students.table[i].address_type)))
            printf("|%*zu", PADDING_4, i + 1), print_record(students.table[i]), counter++;
    if (counter == 0)
        printf("В таблице не найдено подходящих записей.\n");
    return rc;
}

/**
 * @brief Добавить запись в таблицу
 * 
 * @param table таблица
 * @return int код возврата
 */
int add_record(student_table_t *table)
{
    int is_correct_address_type = 0;
    // Проверка таблицы на заполненность
    if (table->n == MAX_TABLE_LEN)
        return RC_TABLE_IS_FULL;
    table->n++;
    student_t student;
    int rc = RC_OK;

    // Массив указателей на фиксированные поля структуры студента
    char *fields[TABLE_FIELDS - ADDRESS_FIELDS + 1] = {
        &student.last_name[0], &student.first_name[0], &student.group[0], &student.gender, 
        &student.age[0], &student.gpa[0], &student.enrollment_date[0], &student.address_type[0]};
    // Массив указателей на вариативные поля структуры студента
    char *fields_address_types[ADDRESS_TYPES][ADDRESS_FIELDS - 1] = {
        {&student.address.house.street[0], &student.address.house.house_num[0], 
            &student.address.house.flat_num[0]},
        {&student.address.dormitory.dorm_num[0], &student.address.dormitory.room_num[0]},
        {&student.address.rent.street[0], &student.address.rent.house_num[0], 
            &student.address.rent.flat_num[0], &student.address.rent.cost[0]}};
    // Заполенение фиксированных полей структуры студента
    for (size_t i = 0; i < TABLE_FIELDS - ADDRESS_FIELDS + 1; i++)
    {
        if ((rc = get_field(fields[i], field_sizes[i], field_names[i], masks[i])))
            return rc;
        if (i == 6 && is_date_valid(fields[i]) != 0)
            return RC_INCORRECT_DATE;
    }
    // Заполенение вариативных полей структуры студента
    for (size_t i = 0; i < ADDRESS_TYPES; i++)
        if (strcmp(addresses[i], student.address_type) == 0)
        {
            for (size_t j = 0; j < address_types_fields[i]; j++)
                if ((rc = get_field(fields_address_types[i][j], field_sizes_address_types[i][j], 
                    fields_names_address_types[i][j], masks_address_types[i][j])))
                    return rc;
            is_correct_address_type = 1;
        }
    if (!is_correct_address_type)
        return RC_INCORRECT_ADDRESS_TYPE;
    table->table[table->n - 1] = student;
    printf("Запись успешно добавлена.\n");
    return RC_OK;
}

/**
 * @brief Удалить студента с введенной фамилией из таблицы
 * 
 * @param table таблица
 * @return int код возврата
 */
int del_record(student_table_t *students)
{
    if (students->n == 0)
    {
        printf("В таблице нет записей, удаление невозможно.\n");
        return RC_OK;
    }
    char selected_last_name[LAST_NAME_LEN+1];
    char mask[] = MASK_LAST_NAME;
    int rc = RC_OK;
    // Получение фамилии
    if ((rc = get_field(selected_last_name, LAST_NAME_LEN, "last name", mask)))
        return rc;
    // Поиск
    size_t i = 0;
    for (i = 0; i < students->n && strcmp(selected_last_name, students->table[i].last_name); i++)
        ;
    // Проверка
    if (strcmp(selected_last_name, students->table[i].last_name))
    {
        printf("В таблице нет подходящих записей. %s\n", students->table[i].last_name);
        return RC_OK;
    }
    // Удаление (сдвиг следующих записей таблицы влево)
    for (size_t j = i; j < students->n - 1; j++)
        students->table[j] = students->table[j + 1];
    students->n--;
    printf("Удаление записи №%zu с фамилией '%s' завершено.\n", i + 1, selected_last_name);
    return RC_OK;
}

/**
 * @brief Удалить всех студентов с введенной фамилией из таблицы
 * 
 * @param table таблица
 * @return int код возврата
 */
int del_records(student_table_t *students)
{
    if (students->n == 0)
    {
        printf("В таблице нет записей, удаление невозможно.\n");
        return RC_OK;
    }
    char selected_last_name[LAST_NAME_LEN+1];
    char mask[] = MASK_LAST_NAME;
    size_t counter = 0;
    int rc = RC_OK;
    // Получение фамилии
    if ((rc = get_field(selected_last_name, LAST_NAME_LEN, "last name", mask)))
        return rc;
    // Удаление (сдвиг записей таблицы влево на количество удаленных записей)
    for (size_t i = 0; i < students->n; i++)
        if (!strcmp(selected_last_name, students->table[i].last_name))
            counter++;
        else
            students->table[i - counter] = students->table[i];
    if (counter == 0)
        printf("В таблице нет подходящих записей.");
    else
        printf("Удаление %zu записей с фамилией '%s' завершено.\n", counter, selected_last_name);
    students->n -= counter;     // Снижение количества записей
    return RC_OK;
}

/**
 * @brief Функция сравнения двух студентов в таблице ключей по фамилии
 * 
 * @param p указатель на первого студента
 * @param q указатель на второго студента
 * @return int результат
 */
int compare_student_last_names(const void *p, const void *q)
{
    return strcmp(((student_t *)p)->last_name, ((student_t *)q)->last_name);
}

/**
 * @brief Функция сравнения двух студентов по фамилии
 * 
 * @param p указатель на первого студента
 * @param q указатель на второго студента
 * @return int результат
 */
int compare_student_key_last_names(const void *p, const void *q)
{
    return strcmp(((student_key_t *)p)->last_name, ((student_key_t *)q)->last_name);
}

/**
 * @brief Заполнение таблицы ключей
 * 
 * @param table таблица
 * @param key_table таблица ключей
 */
void fill_student_key_table(student_table_t table, student_key_table_t *key_table)
{
    key_table->n = table.n; // Количество элементов
    for (size_t i = 0; i < table.n; i++)
        strcpy(key_table->key_table[i].last_name, table.table[i].last_name), key_table->key_table[i].index = i;
}

/**
 * @brief Вывод табилцы ключей
 * 
 * @param key_table таблица ключей
 */
void print_key_table(student_key_table_t key_table)
{
    // Шапка таблицы
    print_key_table_header();
    // Таблица
    if (key_table.n == 0)
        printf("В таблице ключей нет записей.\n");
    for (size_t i = 0; i < key_table.n; i++)
        printf("|%*zu", PADDING_4, i + 1), print_key_record(key_table.key_table[i]);
}

/**
 * @brief Вывод 
 * 
 * @param key_table таблица ключей
 */
void sort_key_table_and_print(student_key_table_t *key_table)
{
    binary_insertion_sort(key_table, key_table->n, sizeof(key_table->key_table[0]), compare_student_key_last_names);
    print_key_table(*key_table);
}

/**
 * @brief Вывод отсортированной таблицы
 * 
 * @param table таблица
 */
void print_sorted_table(student_table_t *table)
{
    binary_insertion_sort(table, table->n, sizeof(table->table[0]), compare_student_last_names);
    print_table(*table);
}

/**
 * @brief Вывод отсортированной таблицы используя таблицу ключей
 * 
 * @param table таблица
 * @param key_table таблица ключей
 */
void print_table_using_sorted_key_table(student_table_t table, student_key_table_t *key_table)
{
    print_table_header();   // Шапка таблицы
    if (table.n == 0)
        printf("В таблице нет записей.\n");
    else
    {
        // Сортировка таблицы ключей
        binary_insertion_sort(key_table, key_table->n, sizeof(key_table->key_table[0]), compare_student_key_last_names);
        // Вывод таблицы, где индекс элемента берется по порядку из отсортированной таблицы ключей
        for (size_t i = 0; i < key_table->n; i++)
            printf("|%*zu", PADDING_4, i + 1), print_record(table.table[key_table->key_table[i].index]);
    }
}

// Функция для сортировки таблицы (передача структуры по значению, чтобы не менять исходную таблицу)
double table_insertion_sort(student_table_t table)
{
    struct timeval tb, te;

    gettimeofday(&tb, NULL);
    insertion_sort(&table, table.n, sizeof(table.table[0]), compare_student_last_names);
    gettimeofday(&te, NULL);

    return te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;
}

// Функция для сортировки таблицы ключей (передача структуры по значению, чтобы не менять исходную таблицу)
double table_key_insertion_sort(student_key_table_t key_table)
{
    struct timeval tb, te;

    gettimeofday(&tb, NULL);
    insertion_sort(&key_table, key_table.n, sizeof(key_table.key_table[0]), compare_student_key_last_names);
    gettimeofday(&te, NULL);

    return te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;
}

// Функция для сортировки таблицы (передача структуры по значению, чтобы не менять исходную таблицу)
double table_binary_insertion_sort(student_table_t table)
{
    struct timeval tb, te;

    gettimeofday(&tb, NULL);
    binary_insertion_sort(&table, table.n, sizeof(table.table[0]), compare_student_last_names);
    gettimeofday(&te, NULL);

    return te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;
}

// Функция для сортировки таблицы ключей(передача структуры по значению, чтобы не менять исходную таблицу)
double table_key_binary_insertion_sort(student_key_table_t key_table)
{
    struct timeval tb, te;

    gettimeofday(&tb, NULL);
    binary_insertion_sort(&key_table, key_table.n, sizeof(key_table.key_table[0]), compare_student_key_last_names);
    gettimeofday(&te, NULL);

    return te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;
}


/**
 * @brief Сравнение функций сортировок и отсутствие/наличие таблицы ключей
 * 
 * @param filename имя файла
 * @return int код возврата
 */
int compare(char *filename)
{
    int rc = 0;

    // Время сортировок
    double sort1_table = 0;
    double sort1_table_key = 0;
    double sort2_table = 0;
    double sort2_table_key = 0;

    // Инициализация таблиц
    student_table_t table = { 0 };
    student_key_table_t key_table = { 0 };
    if ((rc = read_table(filename, &table)))
        return rc;
    fill_student_key_table(table, &key_table);

    // Сортировка таблицы вставками
    for (size_t i = 0; i < SORT_REPEAT; i++)
        sort1_table += table_insertion_sort(table);
    
    // Сортировка таблицы ключей вставками
    for (size_t i = 0; i < SORT_REPEAT; i++)
        sort1_table_key += table_key_insertion_sort(key_table);

    // Сортировка таблицы вставками с бинарным поиском
    for (size_t i = 0; i < SORT_REPEAT; i++)
        sort2_table += table_binary_insertion_sort(table);

    // Сортировка таблицы ключей вставками с бинарным поиском
    for (size_t i = 0; i < SORT_REPEAT; i++)
        sort2_table_key += table_key_binary_insertion_sort(key_table);

    // Вывод таблицей
    printf("%.*s\n", 61, BLANKSx150);
    printf("%s%-*u|%-*s|%-*s|%-*s \n", "Sort time comparison, s, N=", 8, SORT_REPEAT, 12, "Table", 12, "Table key", 12, "%%");
    printf("%.*s+%.*s\n", 35, BLANKSx150, 12+12+1, BLANKSx150);
    printf("%-*s|%*lf|%*lf|%.*lf%%\n", 35, "Insertion sort", 12, sort1_table, 12, sort1_table_key, 3, sort1_table / sort1_table_key * 100 - 100);
    printf("%-*s|%*lf|%*lf|%.*lf%%\n", 35, "Insertion sort with binary search", 12, sort2_table, 12, sort2_table_key, 3, sort2_table / sort2_table_key * 100 - 100);
    printf("%-*s| % .*lf%%  | % .*lf%%\n", 35, "%%", 3, sort1_table / sort2_table *100 - 100, 3, sort1_table_key / sort2_table_key * 100 - 100);
    return RC_OK;
}

/**
 * @brief Перевод структуры студента в массив строк
 * 
 * @param stud структура студента
 * @param fields массив строк
 */
void student_to_str(student_t stud, char fields[TABLE_FIELDS][MAX_FIELD_LEN+1])
{
    // Перевод статических полей
    strcpy(fields[0], stud.last_name);
    strcpy(fields[1], stud.first_name);
    strcpy(fields[2], stud.group);
    fields[3][0] = stud.gender;
    strcpy(fields[4], stud.age);
    strcpy(fields[5], stud.gpa);
    strcpy(fields[6], stud.enrollment_date);
    strcpy(fields[7], stud.address_type);
    // Перевод вариативных полей
    if (strcmp(ADDRESS_TYPE_HOUSE, fields[7]) == 0)
    {
        strcpy(fields[8], stud.address.house.street);
        strcpy(fields[9], stud.address.house.house_num);
        strcpy(fields[10], stud.address.house.flat_num);
        strcpy(fields[11], "-");
    }
    else if (strcmp(ADDRESS_TYPE_DORMITORY, fields[7]) == 0)
    {
        strcpy(fields[8], "-");
        strcpy(fields[9], stud.address.dormitory.dorm_num);
        strcpy(fields[10], stud.address.dormitory.room_num);
        strcpy(fields[11], "-");
    }
    else if (strcmp(ADDRESS_TYPE_RENTAL_PLACE, fields[7]) == 0)
    {
        strcpy(fields[8], stud.address.rent.street);
        strcpy(fields[9], stud.address.rent.house_num);
        strcpy(fields[10], stud.address.rent.flat_num);
        strcpy(fields[11], stud.address.rent.cost);
    }
}

/**
 * @brief Запись таблицы в файл
 * 
 * @param filename имя файла
 * @param table таблица
 * @return int код возврата
 */
int write_table(char *file_name, student_table_t table)
{
    FILE *f;
    char fields[TABLE_FIELDS][MAX_FIELD_LEN+1];
    int rc = 0;

    if (!(f = fopen(file_name, "w")))
        return RC_INCORRECT_FILE;
    for (size_t i = 0; i < table.n; i++)
    {
        student_to_str(table.table[i], fields);                                     // Перевод структуры студента в список строк
        fprintf(f, "%s %s %s %c %s %s %s %s %s %s %s %s\n", \
            fields[0], fields[1], fields[2], fields[3][0], fields[4], fields[5], \
            fields[6], fields[7], fields[8], fields[9], fields[10], fields[11]);    // Запись массива строк (как одну строку) в файл-таблицу
    }
    fclose(f);
    return rc;
}