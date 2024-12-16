all: test clean

ASM=nasm
ASMFLAGS=-f elf64

%.o: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

main: lib.o dict.o main.o
	ld -o main main.o lib.o dict.o

test: main
	python3 test.py

.PHONY: clean
clean:
	rm *.o
	rm main

