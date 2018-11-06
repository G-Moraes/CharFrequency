#ifndef charFreq_H
#define charFreq_H

#include <stdio.h>
#include <stdlib.h>

typedef struct conteudo{

	int tamString;
	char* string;
	int tamAlfabeto;
	char** matAlfabeto;
	int* vetorTamColunas;
} Conteudo;

FILE* fileCreate();
FILE* fileOpen();
void imprimeConteudo(Conteudo* c);
Conteudo* getContent(FILE* arquivo);
char* codificar(Conteudo* c);
char* decodificar(FILE* arquivo, char* string);
FILE* criaDefault();
void imprimeArquivo(FILE* arquivo);
int* setarTamanhoVetor(FILE* arquivo);

#endif
