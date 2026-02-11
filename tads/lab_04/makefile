# Сборка командой make

# Команды
RM = rm
MKDIR = mkdir -p

# Компилятор
CC := gcc

# Опции компиляции
CFLAGS := -std=gnu99 -Wall -Werror -Wextra -Wpedantic

# Файловая структура
SRC_DIR := src/
OUT_DIR := out/
INC_DIR := inc/

# Общие объектные файлы
OBJS := $(OUT_DIR)freed_mem_arr.o $(OUT_DIR)linked_list_stack.o \
	$(OUT_DIR)static_array_stack.o $(OUT_DIR)da_stack.o \
	$(OUT_DIR)ui.o $(OUT_DIR)palindrome.o $(OUT_DIR)compare.o

# # Заголовочные файлы
# HEADERS := $(INC_DIR)consts.h $(INC_DIR)io.h $(INC_DIR)matrix.h $(INC_DIR)arrays.h 

#
# Основной сценарий
#
all : directories app.exe
#

# Созание исполняемого файла
app.exe : $(OBJS) $(OUT_DIR)main.o
	$(CC) $^ -o $@


# Создание выходной директории
directories : ${OUT_DIR}
${OUT_DIR} :
	${MKDIR} ${OUT_DIR}

# # Проверка наличия заголовочных файлов
# headers : $(HEADERS)

# Шаблонные правила Pattern rules
out/%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -g3 -c -o $@ $< -I $(INC_DIR)

# # Функциональное тестирование
# func : func_tests/scripts/func_tests.sh
# 	./$<

# Очистка
.PHONY : clean
clean :
	$(RM) $(OUT_DIR)*.o *.exe
