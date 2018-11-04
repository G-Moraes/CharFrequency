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
//Conteudo* geraValores(FILE* texto);
int lenght(char* string);
void imprimeConteudo(Conteudo* c);
Conteudo* getContent(FILE* arquivo);
char* codificar(Conteudo* c);
void decodificar(FILE* arquivo, char* string);
FILE* criaDefault();
void imprimeArquivo(FILE* arquivo);
int* crazyDiamond(FILE* arquivo);

#endif