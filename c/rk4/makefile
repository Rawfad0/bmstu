app.exe : main.o stack.o
	gcc -std=gnu99 main.o stack.o -o app.exe
	
main.o : main.c
	gcc -std=gnu99 -c main.c -o main.o

stack.o : stack.c stack.h
	gcc -std=gnu99 -c stack.c -o stack.o
