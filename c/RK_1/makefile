
app.exe : io.o matrix3.o main.o
	gcc -std=c99 -Wall -Werror -o $@ $^
	
%.o : %.c
	gcc -std=c99 -Wall -Werror -c -g $^