TASK1 := task1
TASK2 := task2
TASK3 := task3

task1:
	g++ -std=c++20 -masm=intel -m80387 -mno-sse $(TASK1).cpp -c $(TASK1).o -O0
	g++ -std=c++20 $(TASK1).o -o app.exe

task2:
	g++ -std=c++20 -masm=intel -m80387 $(TASK2).cpp -c $(TASK2).o -O0
	g++ -std=c++20 $(TASK2).o -o app.exe

task3:
	make root
	g++ -std=c++20 -masm=intel -m80387 $(TASK3).cpp -c $(TASK3).o -O0
	g++ -std=c++20 $(TASK3).o root.o -o app.exe

run:
	./app.exe

clean:
	rm -rf *.exe *.o

root:
	nasm -f elf64 -o root.o root.asm

task1_asm:
	make task1
	g++ -std=c++20 -masm=intel -m80387 $(TASK1).cpp -S $(TASK1).s -O0