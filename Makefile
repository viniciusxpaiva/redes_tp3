all: compila executa

compila:
	gcc -c cli_teste.c
	gcc cli_teste.c -o executavel
server:
	gcc -c ser_teste.c
	gcc ser_teste.o -o servidor
	./servidor
executa:
	./executavel 

