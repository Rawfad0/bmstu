# Сборка командой make

# Команды
RM = rm
MKDIR = mkdir -p

# Компилятор
CC := gcc

# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror -Wextra -Wpedantic

# Файловая структура
SRC_DIR := src/
OUT_DIR := out/
INC_DIR := inc/

# Общие объектные файлы
OBJS := $(OUT_DIR)io.o $(OUT_DIR)table.o $(OUT_DIR)arrays.o $(OUT_DIR)sorts.o

# Заголовочные файлы
HEADERS := $(INC_DIR)consts.h $(INC_DIR)structs.h $(INC_DIR)io.h $(INC_DIR)table.h $(INC_DIR)arrays.h $(INC_DIR)sorts.h

#
# Основной сценарий
#
all : directories headers app.exe
#

# Созание исполняемого файла
app.exe : $(OBJS) $(OUT_DIR)main.o
	$(CC) $^ -o $@


# Создание выходной директории
directories : ${OUT_DIR}
${OUT_DIR} :
	${MKDIR} ${OUT_DIR}

# Проверка наличия заголовочных файлов
headers : $(HEADERS)

# Шаблонные правила Pattern rules
out/%.o : $(SRC_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -g -c -o $@ $< -I $(INC_DIR)

# # Функциональное тестирование
# func : func_tests/scripts/func_tests.sh
# 	./$<

# Очистка
.PHONY : clean
clean :
	$(RM) $(OUT_DIR)*.o *.exe
