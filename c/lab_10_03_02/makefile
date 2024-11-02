# Команды
RM = rm
MKDIR = mkdir -p

# Компилятор
CC := gcc

# Опции компиляции
CFLAGS := -std=gnu99 -Wall -Werror -Wextra -Wpedantic

# Опции для фреймворка check
CHECK_FLAGS := -lcheck -lpthread -lrt

# Опции утилиты valgrind
VALGRIND_FLAGS := -q --leak-check=full

# Общие объектные файлы
OBJS := associative_array_impl_2.o

# Объектные файлы для модульного тестирования
UNITS := check_main.o

# Основной сценарий
all : unit

# Модульное тестирование
unit : unit_tests.exe
	valgrind $(VALGRIND_FLAGS) ./unit_tests.exe

# Исполняемый файл модульного тестирования
unit_tests.exe : $(UNITS) $(OBJS)
	$(CC) $(UNITS) $(OBJS) -g -o $@ $(CHECK_FLAGS)

# Шаблонные правила Pattern rules
out/%.o : %.c %.h
	$(CC) $(CFLAGS) -g -c $< -o $@

out/check_%.o : unit_tests/check_%.c
	$(CC) $(CFLAGS) -g -c $< -o $@

# Очистка
.PHONY : clean
clean :
	$(RM) $(OUT_DIR)*.o *.exe
