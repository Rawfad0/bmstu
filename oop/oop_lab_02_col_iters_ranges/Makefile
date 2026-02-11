CC = g++
COMPILE_FLAGS = -std=c++20 -Wall -Werror -g

.PHONY: all clean
all: app.exe

run: app.exe
	./$^

app.exe: main.cpp
	$(CC) $(COMPILE_FLAGS) $^ -o $@

out/%.o: %.cpp
	mkdir -p out
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@

clean:
	rm -rf out/ app.exe