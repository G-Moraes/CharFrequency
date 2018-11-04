#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charFreq.h"



int main(){

	FILE* arquivo = criaDefault();

	Conteudo* fugo = getContent(arquivo);

	imprimeConteudo(fugo);

	char* vetor = codificar(fugo);

	decodificar(arquivo, vetor);

	return 0;
}

FILE* fileCreate(){


	FILE* arquivo;

	if ((arquivo = fopen("arquivo.txt", "w+b")) == NULL){
		
		printf("Erro ao abrir arquivo!\n\n");
		exit(1);
	}

	return arquivo;
}

FILE* fileOpen(){

	FILE* arquivo;

	if ((arquivo = fopen("arquivo.txt", "r+b")) == NULL){

		printf("Erro ao abrir arquivo! É provável que o arquivo 'arquivo.txt' não exista.\n\n");
		exit(1);
	}

	return arquivo;
}

int lenght(char* string){
	
	int i, tamanho = 0;

	for(i = 0; string[i] != '\0'; i++){

		tamanho++;
	}

	return tamanho;
}

void imprimeConteudo(Conteudo* c){

	int i; 

	printf("Tamanho do texto: %d\n\n", c->tamString);
	printf("String: %s\n\n", c->string);
	printf("Quantidade de elementos: %d\n\n", c->tamAlfabeto);

	for(i = 0; i < c->tamAlfabeto; i++){
		
		printf("Linha %d: %s", i + 1, c->matAlfabeto[i]);
		printf("Quantidade de elementos da linha %d: %d\n\n", i +1, c->vetorTamColunas[i] - 1);
	}
}

Conteudo* getContent(FILE* arquivo){

	Conteudo* giorno = (Conteudo*) malloc(sizeof(Conteudo));

	int auxInt1, auxInt2, i, j;
	char neutro;
	char auxChar;
	char* auxString;
	char** auxMatrix;

	int* vetor; 

	//leio e armazeno o primeiro elemento (tamanho da string) e preencho na struct de retorno
	fread(&auxInt1, sizeof(int), 1, arquivo);
	giorno->tamString = auxInt1;
	
	//seto o tamanho do texto e atualizo o tamanho do atributo da struct de retorno
	auxString = (char*) malloc(sizeof(char) * auxInt1);
	giorno->string = (char*) malloc(sizeof(char) * auxInt1);

	//quebra de linha
	fread(&neutro, sizeof(char), 1, arquivo);

	//leio o texto
	fread(auxString, sizeof(char*) * auxInt1, 1, arquivo);

	//copio da variável para a struct de retorno
	strcpy(giorno->string, auxString);
 
	//quebra de linha
	fread(&neutro, sizeof(char), 1, arquivo);

	//leio e armazeno o terceiro elemento (quantidade de elementos de códigos) e preencho na struct de retorno
	fread(&auxInt2, sizeof(int), 1, arquivo);
	giorno->tamAlfabeto = auxInt2;

	vetor = (int*) malloc(sizeof(int) * auxInt2);

	vetor = crazyDiamond(arquivo);
	giorno->vetorTamColunas = (int*) malloc(sizeof(int) * auxInt2);

	for(i = 0; i < auxInt2; i++){

		giorno->vetorTamColunas[i] = vetor[i];
	}

	fseek(arquivo, (sizeof(int) + sizeof(char) + (sizeof(char* ) * auxInt1) + sizeof(char) + sizeof(int)), SEEK_SET);

	//seto a matriz de retorno pra ter o tamanho certo
	giorno->matAlfabeto = (char**) malloc(sizeof(char*) * auxInt2);
	auxMatrix = (char**) malloc(sizeof(char*) * auxInt2);

	for(i = 0; i < auxInt2; i++){

		giorno->matAlfabeto[i] = (char*) malloc(sizeof(char) * auxInt1);
		auxMatrix[i] = (char*) malloc(sizeof(char) * auxInt1);
	}

	//quebra de linha
	fread(&neutro, sizeof(char), 1, arquivo);

	for(i = 0; i < auxInt2; i++){

		for(j = 0; j < vetor[i]; j++){

			fread(&giorno->matAlfabeto[i][j], sizeof(char), 1, arquivo);
			//printf("%c", giorno->matAlfabeto[i][j]);
		}
	}

	rewind(arquivo);

	return giorno;
}

char* codificar(Conteudo* c){
 
 	int i, j, k, indexString = 0;
 	char* stringRetorno;
 	char** auxString;

 	auxString = (char**) malloc(sizeof(char*) * c->tamAlfabeto);

	for(i = 0; i < c->tamAlfabeto; i++){

		auxString[i] = (char*) malloc(sizeof(char) * c->vetorTamColunas[i]);

		for(j = 0; j < c->vetorTamColunas[i] - 1; j++){

			auxString[i][j] = c->matAlfabeto[i][j];
			//printf("%c", auxString[i][j]);
		}

		//printf("\n");
	}

	stringRetorno = (char*) malloc(sizeof(char) * (c->tamString * i * j));

	printf("String a ser codificada: '%s'\n", c->string);

	printf("String codificada: ");

	for(i = 0; i < c->tamString; i++){

		//printf("entrei aq 1\n");
		
		for(j = 0; j < c->tamAlfabeto; j++){

			//printf("entrei aq 2\n");
			
			if(c->string[i] == auxString[j][0]){

				//printf("entrei aq 3\n");
				
				for(k = 2; k < c->vetorTamColunas[j] - 1; k++){

					stringRetorno[indexString] = auxString[j][k];
					indexString++;
					printf("%c", auxString[j][k]);
				}
			}
		}
	}

	printf("\n");

	return stringRetorno;
}

void decodificar(FILE* arquivo, char* string){

	int i, j, k, contador = 0;
	int x = lenght(string);
	char* stringDecodificada; 
	
	Conteudo* abacchio = getContent(arquivo);

	stringDecodificada = (char*) malloc(sizeof(char) * x);

	//printf("%d\n", abacchio->tamAlfabeto);

	printf("String decodificada: '");

	
	printf("'\n");
}

FILE* criaDefault(){

	int n = 5, i, j;
	char test[] = "DCCACADEACCCCCBCEBBBD";
	int x = lenght(test);
	char linha = '\n';
	char auxChar;
	char* auxString = (char*) malloc(sizeof(char) * x);
	char espaco = ' ';

	char** matriz = (char**) malloc(sizeof(char*) * 5);

	for(i = 0; i < 5; i++){

		matriz[i] = (char*) malloc(sizeof(char) * x);
	}

	matriz[0] = "A00";
	matriz[1] = "B0100";
	matriz[2] = "C0101";
	matriz[3] = "D011";
	matriz[4] = "E1";

	FILE* arquivo = fileCreate();

	fwrite(&x, sizeof(int), 1, arquivo);
	fwrite(&linha, sizeof(char), 1, arquivo);
	fwrite(test, sizeof(char*) * x, 1, arquivo);
	fwrite(&linha, sizeof(char), 1, arquivo);
	fwrite(&n, sizeof(int), 1, arquivo);
	fwrite(&linha, sizeof(char), 1, arquivo);

	for(i = 0; i < n; i++){

		auxChar = matriz[i][0];
		fwrite(&auxChar, sizeof(char), 1, arquivo);
		fwrite(&espaco, sizeof(char), 1, arquivo);

		//printf("linha %d, coluna 0: %c\n", i, auxChar);

		for(j = 1; matriz[i][j] != '\0'; j++){

			auxChar = matriz[i][j];
			//printf("linha %d, coluna %d: %c\n", i, j, auxChar);
			fwrite(&auxChar, sizeof(char), 1, arquivo);
		}
		
		//printf("\n");
		auxString[j] = '\0';
		fwrite(&linha, sizeof(char), 1, arquivo);
	}

	rewind(arquivo);
	return arquivo;
}

void imprimeArquivo(FILE* arquivo){

	char auxChar;
	char* auxString;
	int auxInt;
	int* tamanhoLinhas;

	rewind(arquivo);

	fread(&auxInt, sizeof(int), 1, arquivo); //tamanho do texto
	printf("%d", auxInt);
	fread(&auxChar, sizeof(char), 1, arquivo); //quebra de linha
	printf("%c", auxChar);

	auxString = (char*) malloc(sizeof(char) * auxInt);

	fread(auxString, sizeof(char*) * auxInt, 1, arquivo); //texto do arquivo
	printf("%s", auxString);
	fread(&auxChar, sizeof(char), 1, arquivo); //quebra de linha
	printf("%c", auxChar);
	fread(&auxInt, sizeof(int), 1, arquivo); //tamanho da matriz de elementos
	printf("%d", auxInt);

	tamanhoLinhas = (int*) malloc(sizeof(int) * auxInt);

	fread(&auxChar, sizeof(char), 1, arquivo); //quebra de linha
	printf("%c", auxChar);
	
	int valor = 0;
	int indice = 0;

	while(!feof(arquivo)){
		
		
		fread(&auxChar, sizeof(char), 1, arquivo); //texto da matriz
		printf("%c", auxChar);
	}

	//printf("Fim da impressão.\n\n");
	rewind(arquivo);
}

int* crazyDiamond(FILE* arquivo){

	char auxChar;
	char* auxString;
	int auxInt;
	int* tamanhoLinhas;

	rewind(arquivo);

	fread(&auxInt, sizeof(int), 1, arquivo); //tamanho do texto
	fread(&auxChar, sizeof(char), 1, arquivo); //quebra de linha

	auxString = (char*) malloc(sizeof(char) * auxInt);

	fread(auxString, sizeof(char*) * auxInt, 1, arquivo); //texto do arquivo
	fread(&auxChar, sizeof(char), 1, arquivo); //quebra de linha
	fread(&auxInt, sizeof(int), 1, arquivo); //tamanho da matriz de elementos

	tamanhoLinhas = (int*) malloc(sizeof(int) * auxInt);

	fread(&auxChar, sizeof(char), 1, arquivo); //quebra de linha
	
	int valor = 0;
	int indice = 0;

	while(!feof(arquivo)){
		
		fread(&auxChar, sizeof(char), 1, arquivo); //texto da matriz
		valor++;
		
		if(auxChar == '\n'){

			tamanhoLinhas[indice] = valor;
			valor = 0;
			indice++;
		}
	}

	rewind(arquivo);

	return tamanhoLinhas;
}