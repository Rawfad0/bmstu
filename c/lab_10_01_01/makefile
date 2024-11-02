# Команды
RM = rm
MKDIR = mkdir -p

# Компилятор
CC := gcc

# Опции компиляции
CFLAGS := -std=gnu99 -Wall -Werror -Wextra -Wpedantic -Wimplicit-function-declaration

# Опции для фреймворка check
CHECK_FLAGS := -lcheck -lpthread -lrt

# Опции утилиты valgrind
VALGRIND_FLAGS := -q --leak-check=full

# Файловая структура
SRC_DIR := src/
OUT_DIR := out/
INC_DIR := inc/
UNIT_TESTS_DIR := unit_tests/

# Общие объектные файлы
OBJS := $(OUT_DIR)film.o $(OUT_DIR)list.o

# Объектные файлы для модульного тестирования
UNITS := $(OUT_DIR)check_main.o


# Основной сценарий
all : directories app.exe

# Функциональное тестирование
func : func_tests/scripts/func_tests.sh app.exe 
	./$<

# Модульное тестирование
unit : directories unit_tests.exe
	valgrind $(VALGRIND_FLAGS) ./unit_tests.exe

# Созание исполняемого файла
app.exe : directories $(OBJS) $(OUT_DIR)main.o
	$(CC) $(OBJS) $(OUT_DIR)main.o -g -o $@

# Исполняемый файл модульного тестирования
unit_tests.exe : directories $(UNITS) $(OBJS)
	$(CC) $(UNITS) $(OBJS) -g -o $@ $(CHECK_FLAGS)

# Создание выходной директории
directories : ${OUT_DIR}
${OUT_DIR} :
	${MKDIR} ${OUT_DIR}

# Создание объектного файла main.o
out/main.o : $(SRC_DIR)main.c
	$(CC) $(CFLAGS) -g -c -o $@ $< -I $(INC_DIR)

# Шаблонные правила Pattern rules
out/%.o : $(SRC_DIR)%.c $(INC_DIR)%.h
	$(CC) $(CFLAGS) -g -c -o $@ $< -I $(INC_DIR)

out/check_%.o : unit_tests/check_%.c
	$(CC) $(CFLAGS) -g -c -o $@ $< -I $(INC_DIR)

# Очистка
.PHONY : clean
clean :
	$(RM) $(OUT_DIR)*.o *.exe
