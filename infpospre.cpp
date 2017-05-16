#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct Node{
	 char caractere;
	 struct Node *prox;
};
typedef struct Node node;

int tam;
static int MAX = 100;

int menu(node *pilhaExpressao);
int vazia(node *pilha);
void inicia(node *pilha);
void opcao(node *pilhaExpressao, int op);
void exibe(node *pilha);
void libera(node *pilha);
void push(node *pilha, char elemento);
node *pop(node *pilha);
node *aloca(char elemento);
char *infixaParaPosfixa(node *pilhaExpressao);
void inserirExpressao(node *pilhaExpressao);
void validaExpressao(char *expressao);

int main(int argc, char *argv[])
{
	 int opt;
	 char *expressao;
	 char chr;
	 
	 node *pilhaExpressao = (node *) malloc(sizeof(node)); // Pilha respons�vel por carregar a express�o
	 
	 if(!pilhaExpressao){
		  printf("Erro ao alocar memoria.\n");
		  exit(1);
	 }else{
	 	  inicia(pilhaExpressao);
	 	  
     if(argc != 2)  // N�o foi utilizado linha de comando
			inserirExpressao(pilhaExpressao);
	 else{ // Valida express�o e insere na pilha
	 		expressao = argv[1];
			
			validaExpressao(expressao);
			
	 		while(chr = *expressao++)
	 			push(pilhaExpressao, chr);
	 	 }
	 	 // Express�o ok, chama menu
	 do{
		  opt = menu(pilhaExpressao);
		  opcao(pilhaExpressao,opt);
	 }while(opt);
	
	 free(pilhaExpressao);
	 
	 return 0;
	 }
}

/*
	Insere uma nova express�o na pilha
*/
void inserirExpressao(node *pilhaExpressao){
	char expressao[MAX];
	char chr;
	int i;
	size_t strSize = 0;
	memset(expressao, 0, MAX);
	
	if(!vazia(pilhaExpressao)){
		libera(pilhaExpressao);
		inicia(pilhaExpressao);
	}

	do{
		fflush(stdin);
		printf("Digite uma expressao com ate 100 caracteres: ");
		fgets(expressao, MAX, stdin);
	}while(strlen(expressao) < 3);
	
	
	validaExpressao(expressao);
	
	strSize = strlen(expressao); 
	printf("\nNova expressao %s", expressao);
	printf("tamanho: %i", strSize);
	system("pause");
	
	for(i = 0; i < strSize; i++)
		push(pilhaExpressao, expressao[i]); // -2 temporario, para retirar o \n
	
}

/*
	Retira espa�os e parenteses de express�es
*/
void validaExpressao(char *expressao){
	char *p2 = expressao;
	
	// Remover \n, \t, (, ) e espa�os
    while(*expressao != '\0') {
        if(*expressao != '\t' && *expressao != '\n' & *expressao != '(' & *expressao != ')' & *expressao != ' ') {
            *p2++ = *expressao++;
        } else {
            ++expressao;
        }
    }
    *p2 = '\0';
}

void inicia(node *PILHA) // Inicia a pilha e o contador
{
	 PILHA->prox = NULL;
	 tam=0;
}

int menu(node *pilhaExpressao)
{
	 int opt;
	 
	 system("cls");
	 
	 printf("\nExpressao utilizada: ");
	 exibe(pilhaExpressao);
	 printf(" tamanho da pilha: %i \n\n", tam);
	 
	 printf("Escolha a opcao\n");
     printf("1. Zerar PILHA\n");
	 printf("2. POP\n");
	 printf("3 - Infixa para posfixa\n");
	 printf("4 - Nova expressao\n");
	 printf("0. Sair\n");
	 printf("Opcao: "); 
	 
	 scanf("%d", &opt);
	
	 return opt;
}



void opcao(node *pilhaExpressao, int op)
{
	 node *tmp;
	 
	 switch(op){
		  case 0:
		   		libera(pilhaExpressao);
		   break;
		
		  case 1:
			   libera(pilhaExpressao);
			   inicia(pilhaExpressao);
		   break;
		
		  case 2:
			   tmp = pop(pilhaExpressao);
			   if(tmp != NULL)
				   printf("Retirado: %3c\n\n", tmp->caractere);
				   
			   system("pause");
		   break;
		   
		  case 3:
		  		printf("%s", infixaParaPosfixa(pilhaExpressao));
		  		system("pause");
		   break;
	      case 4:
	      		inserirExpressao(pilhaExpressao);
	       break;
		  default:
		   		printf("Comando invalido\n\n");
	 }
}
/*
	A fun��o a seguir realiza a convers�o de uma express�o em pilha para posfixa
	e retorna o ponteiro da string
	
	Argumentos: 
		- pilha contendo a express�o
*/
char *infixaParaPosfixa(node *pilhaExpressao){
	
	return 0;
}

int vazia(node *PILHA)
{
	 if(PILHA->prox == NULL) // Se o pr�ximo n� da pilha estiver NULL, a pilha est� vazia
	  return 1;
	 else
	  return 0;
}

void exibe(node *PILHA) // Exibe o conte�do da pilha
{
	 if(vazia(PILHA)){
	  	printf("PILHA vazia!");
	  return ;
	 }
	
	 node *tmp; // Ponteiro tempor�rio 
	 tmp = PILHA->prox; // Recebe o primeiro n�
	 
	 while( tmp != NULL){   // Enquanto o pr�ximo n� n�o for NULL, ainda existem elementos
	  printf("%1c ", tmp->caractere);
	  tmp = tmp->prox;     // tmp aponta para prox da pilha, onde o prox possui o prox para o outro n� at� encontrar NULL
	  					// tmp->prox = prox->prox = prox->prox = NULL; (tr�s n�s)
	 }
	/*
	 int count;
	 for(count=0 ; count < tam ; count++)
	  printf("  ^  ");
	 printf("\nOrdem:");
	 for(count=0 ; count < tam ; count++)
	  printf("%5d", count+1);
	
	
	 printf("\n\n"); */
}

void libera(node *PILHA)
{
	 if(!vazia(PILHA)){
		  node *proxNode, *atual;
		  atual = PILHA->prox;
	  while(atual != NULL){ // Dando free nos n�s at� encontrar NULL
     	   proxNode = atual->prox;
		   free(atual);
	 	   atual = proxNode;
	  }
	 }
}


node *aloca(char elemento) // Alocar novo n� na pilha
{
	 node *novo=(node *) malloc(sizeof(node));
	 
	 if(!novo){
		  printf("Erro ao alocar memoria.\n");
		  exit(1);
	 }else{
		  novo->caractere = elemento;
	  	  return novo;
	 }
}

void push(node *PILHA, char elemento)
{
	 node *novo = aloca(elemento); // aloca novo n�, pergunta qual elemento adicionar
	 novo->prox = NULL; // Inicia o proximo como NULL
	
	 if(vazia(PILHA))
	  	PILHA->prox = novo; // Se a pilha estiver vazia, o ponteiro proximo continuar� NULL
	 else{
	  	node *tmp = PILHA->prox;  // Aponta para o pr�ximo elemento, PILHA->prox possui o endere�o do topo da pilha
	
	  while(tmp->prox != NULL) // Enquanto o pr�ximo elemento n�o for NULL 
	   	tmp = tmp->prox; // o ponteiro temporario ir� recebendo o pr�ximo n�
	
	  	tmp->prox = novo; // Quando alcancar o ponteiro com o valor NULL, o endere�o do novo n� ser� colocado no prox 
	 }
	 tam++;
}


node *pop(node *PILHA)
{
	 if(PILHA->prox == NULL){
		  printf("Pilha nao contem elementos.\n");
		  return NULL;
	 }else{
	  node *ultimo = PILHA->prox, *penultimo = PILHA;
	
	  while(ultimo->prox != NULL){
		   penultimo = ultimo;
		   ultimo = ultimo->prox;
	  }
	
	  penultimo->prox = NULL;
	  tam--;
	  return ultimo;
	 }
}

