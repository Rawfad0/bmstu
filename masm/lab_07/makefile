32bit:
	make asm32
	g++ -m32 -masm=intel main_32bit.cpp -c main_32bit.o
	g++ -m32 main_32bit.o mystrcpy_32.o -o app.exe

64bit:
	make asm64
	g++ -masm=intel main_64bit.cpp -c main_64bit.o
	g++ main_64bit.o mystrcpy_64.o -o app.exe

run:
	./app.exe

clean:
	rm -rf *.exe *.o

asm32:
	nasm -f elf32 -o mystrcpy_32.o mystrcpy_32.asm

asm64:
	nasm -f elf64 -o mystrcpy_64.o mystrcpy_64.asm