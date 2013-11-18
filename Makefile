all: compila executa

compila:
	gcc -c cli_teste.c
	gcc cli_teste.c -o cliente
server:
	gcc -c ser_teste.c
	gcc ser_teste.o -o servidor
	./servidor 9930
executa:
	./cliente 127.0.0.1 9930 query Joseph

