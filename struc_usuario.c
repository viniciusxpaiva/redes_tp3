Tipo_Lista *Lista_Vazia(){
	Tipo_Lista *L;
	L = (Tipo_Lista *) malloc( sizeof(Tipo_Lista) );
	L->tamanho = 0;
	L->fim = NULL;
	L->inicio = NULL;
	return L;
}

struct Tipo_Elemento *iniciaElemento(){
	struct Tipo_Elemento *x;	
	x = ( struct Tipo_Elemento *) malloc ( sizeof (struct Tipo_Elemento) );
	x->idCount = 1; 
	x->user = (char*)malloc( sizeof(char) * 500);
	x->dns[ x->idCount ] = (char*)malloc(sizeof(char) * 500);
	x->ip[ x->idCount ] = (char*)malloc(sizeof(char) * 500);
	return x;
}

void insereValores( struct Tipo_Elemento *x  , char *ip , char *dns){ 
	x->idCount++;  
	printf("%d\n", x->idCount );    
	x->dns[ x->idCount ] = (char*)malloc(sizeof(char) * 500);
	x->ip[ x->idCount ] = (char*)malloc(sizeof(char) * 500);
    strcpy( x->dns[ x->idCount ] , dns );      
    strcpy( x->ip[ x->idCount ] , ip );
}
//Função que insere um elemento na lista.
void Insere_Lista(Tipo_Lista *L,char *ip ,  char *dns ,  char *user){
	struct Tipo_Elemento *x;	
	x = iniciaElemento();

	if (L->inicio == NULL)
	{
		L->inicio = x;                            //A função cria um elemento auxiliar concatena esse elemento
		L->fim = x;                               //na lista, verificando caso a lista esteja vazia.
		x->proximo = NULL;	
	}
	else {
		x->proximo = L->inicio;
		L->inicio->anterior=x;
		L->inicio=x; 
	}
	x->anterior = NULL;       
 
	strcpy( x->user , user );      
    strcpy( x->dns[ x->idCount ], dns );      
    strcpy( x->ip[ x->idCount ] , ip );

    L->tamanho++;                                 //Tamanho da lista também é incrementado.

}


//Função que busca um elemento na lista.
struct Tipo_Elemento *Busca_Elemento(Tipo_Lista *L, char *alvo){
    struct Tipo_Elemento *aux;     
    aux = L->inicio;
    
    while (aux != NULL){    
        if ( strcmp( alvo , aux->user) == 0 )     //ou no caso onde o elemento não esteja na lista.
			return (aux);
		aux = aux->proximo;   
    }                               //O retorno será um ponteiro, se o elemento existir, o ponteiro encontrado será retornado,
    return NULL;                    //mas se o elemento não existir, retornamos NULL. 
}                                   



//Função que elimina um elemento da lista, testando cada caso onde o elementou (ou nó), possa estar.
void Elimina_Elemento(Tipo_Lista *L, struct Tipo_Elemento * ponteiro_alvo){  
    if (ponteiro_alvo->anterior == NULL && ponteiro_alvo->proximo == NULL) {
        L->fim = NULL;
        L->inicio = NULL;
    }else if (ponteiro_alvo->anterior == NULL) {    //O elemento é o primeiro nó
        L->inicio = ponteiro_alvo->proximo;
        ponteiro_alvo->proximo->anterior = NULL;
    }else if (ponteiro_alvo->proximo == NULL) {     //O elemento é o ultimo nó
        L->fim = ponteiro_alvo->anterior;
        ponteiro_alvo->anterior->proximo = NULL;
    }else{
        ponteiro_alvo->anterior->proximo = ponteiro_alvo->proximo;
        ponteiro_alvo->proximo->anterior = ponteiro_alvo->anterior;
    }
    L->tamanho--;
    free(ponteiro_alvo);
} 



//Função para desalocar uma lista.
void Desaloca_Lista(Tipo_Lista *L) {
  struct Tipo_Elemento *tmp, *aux;
  tmp = L->inicio;
  while (tmp != NULL) {             //O laço percorre todos nós da lista, desalocando cada um deles.
    aux = tmp->proximo;
    free(tmp);
    tmp = aux;
  }
  free(L);
}

//Função para imprimir uma lista
void Imprime_Lista(Tipo_Lista *L){
  struct Tipo_Elemento * tmp, * aux;
  tmp = L->inicio;
  printf("T=%d |   ", L->tamanho);
  while (tmp != NULL) {
    aux = tmp->proximo;
    printf("%s %d\n", tmp->user ,tmp->idCount);
    tmp = aux;
  }
}

