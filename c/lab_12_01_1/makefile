# Команды
RM := rm -r
MKDIR := mkdir -p

# Компилятор
CC := gcc

# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror -Wextra

# Опции для фреймворка check
CHECK_FLAGS := -lcheck -lpthread -lrt

# Опции утилиты valgrind
VALGRIND_FLAGS := -q --leak-check=full

# Файловая структура
SRC_DIR := src/
OUT_DIR := out/
INC_DIR := inc/
UNIT_TESTS_DIR := unit_tests/

# Объектные файлы библиотек (статической и динамической)
OBJLIBS := $(OUT_DIR)io_lib.o $(OUT_DIR)key_lib.o $(OUT_DIR)mysort_lib.o
OBJDLIBS := $(OUT_DIR)io_dlib.o $(OUT_DIR)key_dlib.o $(OUT_DIR)mysort_dlib.o

# Для динамических библиотек
export LD_LIBRARY_PATH := LD_LIBRARY_PATH:$(OUT_DIR)

# Объектные файлы для модульного тестирования
UNITS := $(OUT_DIR)check_mysort.o


# Основной сценарий
all : directories app_s.exe app_dl1.exe app_dl2.exe
# app_s.exe - исполняемый файл с использованием статической библиотеки
# app_dl1.exe - исполняемый файл с использованием динамической библиотеки и динамической компоновки
# app_dl2.exe - исполняемый файл с использованием динамичесой библиотеки и динамической загрузки

# Модульное тестирование
unit : directories unit_tests.exe
	valgrind $(VALGRIND_FLAGS) ./unit_tests.exe

# Созание исполняемых файлов
app_s.exe : directories $(OUT_DIR)libarr.a $(OUT_DIR)main.o
	$(CC) $(OUT_DIR)main.o -L$(OUT_DIR) -larr -o $@

app_dl1.exe : directories $(OUT_DIR)libarr.so $(OUT_DIR)main.o
	$(CC) $(OUT_DIR)main.o -L$(OUT_DIR) -larr -o $@

app_dl2.exe : directories $(OUT_DIR)libarr.so $(OUT_DIR)main_dl.o
	$(CC) $(OUT_DIR)main_dl.o -ldl -o $@

# Исполняемый файл модульного тестирования
unit_tests.exe : directories $(OUT_DIR)libarr.so $(UNITS)
	$(CC) $(UNITS) -g -L$(OUT_DIR) -larr -o $@ $(CHECK_FLAGS)

# Сборка статической библиотеки
$(OUT_DIR)libarr.a : $(OBJLIBS)
	ar cr $@ $^
	ranlib $@
	
# Сборка динамической библиотеки
$(OUT_DIR)libarr.so : $(OBJDLIBS)
	$(CC) -o $@ -shared $^

# Создание выходной директории
directories : $(OUT_DIR)
$(OUT_DIR) :
	$(MKDIR) $(OUT_DIR)

# Шаблонные правила Pattern rules
# Компиляция
out/%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -g -c $< -I $(INC_DIR) -o $@

out/check_%.o : $(UNIT_TESTS_DIR)check_%.c
	$(CC) $(CFLAGS) -g -c $< -I $(INC_DIR) -o $@

#Компиляция объектных файлов статических бибилотек
out/%_lib.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -g -c $< -I $(INC_DIR) -o $@

# Компиляция для динамических библиотек
out/%_dlib.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -g -fPIC -c $< -I $(INC_DIR) -o $@


# Функциональное тестирование
func : func_tests/scripts/func_tests.sh app_s.exe app_dl1.exe app_dl2.exe
	./$< app_s.exe
	./$< app_dl1.exe
	./$< app_dl2.exe

# Очистка
.PHONY : all unit clean func directories
clean :
	$(RM) $(OUT_DIR) *.exe
