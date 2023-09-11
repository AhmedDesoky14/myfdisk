.PHONY: all clean install

all: myfdisk

clean:
	@rm -f *.o myfdisk
	@echo all clean

install:
	@sudo cp myfdisk /usr/bin
	@echo installed successfully 

%.o: %.c
	@gcc -o $@ -c $<

main.o: main.c functions.h structures.h
	@gcc -o main.o -c main.c

myfdisk: main.o functions.o
	@gcc -o myfdisk main.o functions.o

