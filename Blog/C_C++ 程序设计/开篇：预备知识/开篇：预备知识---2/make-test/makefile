custom1.o:
		gcc -c custom1.c -o custom1.o
hello.exe: custom1.o custom2.o
		gcc hello.c custom1.o custom2.o -o hello.exe
custom2.o:
		gcc -c custom2.c -o custom2.o