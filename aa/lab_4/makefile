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
RECIPES_DIR := recipes/

#
# Основной сценарий
#
run : directories app.exe
	./app.exe
#

# Созание исполняемого файла
app.exe : directories $(OUT_DIR)main.o
	$(CC) $(OUT_DIR)main.o -o $@ -lcurl -lstdc++

# Создание выходной директории
directories : ${OUT_DIR} ${RECIPES_DIR}
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

