#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
struct Tipo_Elemento{
      char *user;
      char *dns[5000];
      char *ip[5000]; 
      int idCount;
      struct Tipo_Elemento *proximo;
      struct Tipo_Elemento *anterior;
};  

//Estrutura de lista duplamente encadeada para representar a memória física.
typedef struct Tipo_Lista{
	int tamanho;
	struct Tipo_Elemento *fim, *inicio;	
}Tipo_Lista;

//Função para inicializar uma lista.
Tipo_Lista *Lista_Vazia();

//Função para inserir um elemento na lista.
void Insere_Lista(Tipo_Lista *L,char *ip ,  char *dns ,  char *user);

//Função que retorna um elemento da lista, caso ele exista.
struct Tipo_Elemento *Busca_Elemento(Tipo_Lista *L, char *alvo);

//Função para deletar um elemento da lista.
void Elimina_Elemento(Tipo_Lista *L, struct Tipo_Elemento * ponteiro_alvo);
 
//Função para desalocar uma lista alocada.
void Desaloca_Lista(Tipo_Lista *L);

//Função para imprimir uma lista.
void Imprime_Lista(Tipo_Lista *L);
 


#include "struc_usuario.c"