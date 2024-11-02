# Команды
RM = rm
MKDIR = mkdir -p

# Компилятор
CC := gcc

# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror -Wextra -Wpedantic

# Опции для фреймворка check
CHECK_FLAGS := -lcheck -lpthread -lrt

# Файловая структура
SRC_DIR := src/
OUT_DIR := out/
INC_DIR := inc/
UNIT_TESTS_DIR := unit_tests/

# Общие объектные файлы
OBJS := $(OUT_DIR)matrix.o $(OUT_DIR)io.o

HDS := $(INC_DIR)matrix.h $(INC_DIR)io.h $(INC_DIR)consts.h

# Объектные файлы для модульного тестирования
UNITS := $(OUT_DIR)check_matrix.o

#
# Основной сценарий
#
all : directories headers app.exe
#

# Созание исполняемого файла
app.exe : directories $(OBJS) $(OUT_DIR)main.o
	$(CC) $(OBJS) $(OUT_DIR)main.o -o $@


# Исполняемый файл модульного тестирования
unit_tests.exe : directories $(UNITS) $(OBJS)
	$(CC) $(UNITS) $(OBJS) -g -o $@ $(CHECK_FLAGS)

# Заголовочные файлы
headers : ${HDS}

# Создание выходной директории
directories : ${OUT_DIR}
${OUT_DIR} :
	${MKDIR} ${OUT_DIR}

# Шаблонные правила Pattern rules
out/%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -g -c $< -o $@ -I $(INC_DIR)

out/check_%.o : unit_tests/check_%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INC_DIR)

# Функциональное тестирование
func : func_tests/scripts/func_tests.sh
	./$<

# Очистка
.PHONY : clean
clean :
	$(RM) $(OUT_DIR)*.o *.exe
