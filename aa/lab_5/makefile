# Команды
RM = rm
MKDIR = mkdir -p

# Компилятор
CC := gcc

# Опции компиляции
CFLAGS := -std=c++20 -Wall -Werror -Wextra -Wpedantic -Wvla -Wfloat-equal -Wfloat-conversion

# Файловая структура
SRC_DIR := src/
OUT_DIR := out/
INC_DIR := inc/
# HTMLS_DIR := htmls/
# RECIPES_DIR := recipes/

HPPS := $(INC_DIR)task.hpp $(INC_DIR)mtqueue.hpp $(INC_DIR)logger.hpp
# $(OUT_DIR)task.o $(OUT_DIR)mtqueue.o $(OUT_DIR)logger.o
OBJS := $(OUT_DIR)task.o $(OUT_DIR)mtqueue.o $(OUT_DIR)logger.o

#
# Основной сценарий
#
run : directories app.exe
	./app.exe
#

# Созание исполняемого файла
app.exe : $(OUT_DIR)main.o $(HPPS) 
	$(CC) $< -o $@ -lstdc++ -lsqlite3

# Создание выходной директории
directories : ${OUT_DIR}
${OUT_DIR} :
	${MKDIR} ${OUT_DIR}

${RECIPES_DIR} :
	$(MKDIR) ${RECIPES_DIR}

# Шаблонные правила Pattern rules
out/%.o : $(SRC_DIR)%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

# Очистка
.PHONY : clean
clean :
	$(RM) $(OUT_DIR)*.o *.exe

