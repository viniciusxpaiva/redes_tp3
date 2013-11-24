all: cliente servidor

cliente:
	gcc -c cli_teste.c
	gcc cli_teste.c -o cliente
servidor:
	gcc -c ser_teste.c
	gcc ser_teste.o -o servidor