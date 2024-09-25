all : Peterson01

Peterson01 : osLab11_peterson01.o osLab11_peterson.o 
	gcc -o Peterson01 osLab11_peterson01.o osLab11_peterson.o

Peterson01.o : osLab11_peterson01.c
	gcc -c osLab11_peterson01.c

peterson.o : osLab11_peterson.c
	gcc -c osLab11_peterson.c

clean :
	rm - rf *.o Peterson01