# Master MakeFile.

# all the object files in one variable.
OBJECT=boot.o main.o system.o utils/string.o drivers/monitor.o

# cross compiler of your choice.
CC=g++

# list of arguments to the compiler.
CFLAGS=-Wall -Wextra -nostdlib -fno-exceptions -fno-rtti -fno-stack-protector -Wno-write-strings

# list of arguments to the nasm compiler. 
AFLAGS=-f elf


all: $(OBJECT) link.ld 
	ld -Tlink.ld -o kernel $(OBJECT)
	cat stage1 stage2 pad kernel >floppy.img
	
main.o: main.cpp
	$(CC) -o main.o -c main.cpp $(CFLAGS)

system.o: system.cpp
	$(CC) -o system.o -c system.cpp $(CFLAGS)

utils/string.o: utils/string.h utils/string.cpp
	$(CC) -o utils/string.o -c utils/string.cpp $(CFLAGS)

drivers/monitor.o: drivers/monitor.h drivers/monitor.cpp
	$(CC) -o drivers/monitor.o -c drivers/monitor.cpp $(CFLAGS)

boot.o: boot.s
	nasm $(AFLAGS) -o boot.o boot.s

clear:
	rm -rf *.o */*.o kernel floppy.img

clean:
	rm -rf *.o */*.o kernel floppy.img
