_MAKE_OUT_DIR_ := $(shell mkdir -p out)
_MAKE_ASM_DIR_ := $(shell mkdir -p assembly)
_MAKE_DISASM_DIR_ := $(shell mkdir -p disassembly)

.PHONY: 1_2 1_1 1_3 math 2 run assembly disassembly clean

1_1: 1.cpp
	g++ 1.cpp -m80387 -O0 -o 1_1.exe
	./1_1.exe
1_2: 1.cpp
	g++ 1.cpp -mno-80387 -O0 -o 1_2.exe
	./1_2.exe
1_3: 1.cpp
	g++ 1.cpp -masm=intel -DASM -O0 -o 1_3.exe
	./1_3.exe

math: 1_1 1_2 1_3

2: 2.cpp
	g++ 2.cpp -masm=intel -o 2.exe -lm
	./2.exe

3: 3.cpp
	g++ 3.cpp -masm=intel -c -o 3.o -lm
	g++ 3.o -o 3.exe
	./3.exe

3_1: 3_1.cpp
	g++ 3_1.cpp -masm=intel -c -o 3_1.o -lm
	nasm -f win64 root.asm -o root.o
	g++ 3_1.o root.o -o 3_1.exe
	./3_1.exe

run: math 2

# Посмотреть ассемблерный код можно 2 способами:
assembly:
	g++ -S 1.cpp -mno-80387 -O0 -o assembly/1_2.s
	g++ -S 1.cpp -m80387 -O0 -o assembly/1_1.s
	g++ -S 1.cpp -masm=intel -DASM -O0 -o assembly/1_3.s
	g++ -S 2.cpp -masm=intel -o assembly/2.s

disassembly:
	g++ -c 1.cpp -mno-80387 -O0 -o out/1_2.o
	g++ -c 1.cpp -m80387 -O0 -o out/1_1.o
	g++ -c 1.cpp -masm=intel -DASM -O0 -o out/1_3.o
	g++ -c 2.cpp -masm=intel -o out/2.o
	objdump -M intel-mnemonic -d out/1_2.o  > disassembly/1_2.txt
	objdump -M intel-mnemonic -d out/1_1.o  > disassembly/1_1.txt
	objdump -M intel-mnemonic -d out/1_3.o  > disassembly/1_3.txt
	objdump -M intel-mnemonic -d out/2.o  > disassembly/2.txt

clean:
	rm -rf out/* assembly/* disassembly/* *.exe *.o