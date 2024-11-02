# Команды
RM := rm -r
MKDIR := mkdir -p
# Компилятор
CC := gcc
# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror -Wextra -lm
# Опции для фреймворка check
CHECK_FLAGS := -lcheck -lpthread -lrt
# Опции утилиты valgrind
VALGRIND_FLAGS := -q --leak-check=full
# Файловая структура
SRC_DIR := src/
OUT_DIR := out/
INC_DIR := inc/
UNIT_TESTS_DIR := unit_tests/
# Объектные файлы библиотек
OBJLIBS := $(OUT_DIR)arr_lib.o
# Объектные файлы для модульного тестирования
UNITS := $(OUT_DIR)check_arr.o
# Для динамических библиотек
export LD_LIBRARY_PATH := LD_LIBRARY_PATH:$(OUT_DIR)

# Основной сценарий
all : directories $(OUT_DIR)libarr.so

# Модульное тестирование
unit : directories unit_tests.exe
	valgrind $(VALGRIND_FLAGS) ./unit_tests.exe

# Исполняемый файл модульного тестирования
unit_tests.exe : directories $(OUT_DIR)libarr.so $(UNITS)
	$(CC) $(UNITS) -g -L$(OUT_DIR) -larr -o $@ $(CHECK_FLAGS) -lm

# Сборка динамической библиотеки
$(OUT_DIR)libarr.so : $(OBJLIBS)
	$(CC) -o $@ -shared $^

# Создание выходной директории
directories : $(OUT_DIR)
$(OUT_DIR) :
	$(MKDIR) $(OUT_DIR)

# Шаблонные правила Pattern rules
# Компиляция для динамических библиотек
out/%_lib.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -g -fPIC -c $< -I $(INC_DIR)  -o $@ 

out/check_%.o : $(UNIT_TESTS_DIR)check_%.c
	$(CC) $(CFLAGS) -g -c $< -I $(INC_DIR) -o $@

# Очистка
.PHONY : clean
clean :
	$(RM) $(OUT_DIR) *.exe
