#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charFreq.h"

int main(){

	FILE* arquivo = criaDefault();

	Conteudo* fugo = getContent(arquivo);

	//imprimeArquivo(arquivo);

	//imprimeConteudo(fugo);

	//char* vetor = codificar(fugo);

	//decodificar(arquivo, vetor);

	return 0;
}

FILE* fileCreate(){


	FILE* arquivo;

	if ((arquivo = fopen("arquivo.txt", "w+")) == NULL){
		
		printf("Erro ao abrir arquivo!\n\n");
		exit(1);
	}

	return arquivo;
}

FILE* fileOpen(){

	FILE* arquivo;

	if ((arquivo = fopen("arquivo.txt", "r+")) == NULL){

		printf("Erro ao abrir arquivo! É provável que o arquivo 'arquivo.txt' não exista.\n\n");
		exit(1);
	}

	return arquivo;
}

void imprimeConteudo(Conteudo* c){

	int i; 

	printf("Tamanho do texto: %d\n\n", c->tamString);
	printf("String: %s\n\n", c->string);
	printf("Quantidade de elementos: %d\n\n", c->tamAlfabeto);

	for(i = 0; i < c->tamAlfabeto; i++){
		
		printf("Linha %d: %s", i + 1, c->matAlfabeto[i]);
		printf("tamanho da String %d que substitui %c: %d\n\n", i +1, c->matAlfabeto[i][0], c->vetorTamColunas[i] - 3);
	}
}

Conteudo* getContent(FILE* arquivo){

	Conteudo* giorno = (Conteudo*) malloc(sizeof(Conteudo));

	arquivo = fileOpen();

	int auxInt1, auxInt2, i, j;
	int* vetor; 
	char neutro;
	char auxChar;
	char* auxString;
	char auxConcat[1], strFinal[1], espaco[1];
	char** auxMatrix;

	rewind(arquivo);

	espaco[0] = ' ';

	//leio e armazeno o primeiro elemento (tamanho da string) e preencho na struct de retorno
	//fread(&auxInt1, sizeof(int), 1, arquivo);
	fscanf(arquivo, "%d", &auxInt1);
	giorno->tamString = auxInt1;
	printf("Tamando da string a ser codificada: %d\n", auxInt1);

	//seto o tamanho do texto e atualizo o tamanho do atributo da struct de retorno
	auxString = (char*) malloc(sizeof(char) * auxInt1);
	giorno->string = (char*) malloc(sizeof(char) * auxInt1);

	//quebra de linha
	fgetc(arquivo);

	//leio o texto
	//fread(auxString, sizeof(char*) * auxInt1, 1, arquivo);
	fscanf(arquivo, "%s", auxString);
	printf("String a ser codificada: %s\n", auxString);

	//copio da variável para a struct de retorno
	strcpy(giorno->string, auxString);
 
	//quebra de linha
	//fread(&neutro, sizeof(char), 1, arquivo);
	fgetc(arquivo);

	//leio e armazeno o terceiro elemento (quantidade de elementos de códigos) e preencho na struct de retorno
	//fread(&auxInt2, sizeof(int), 1, arquivo);
	fscanf(arquivo, "%d", &auxInt2);
	printf("tamanho da matriz: %d\n", auxInt2);
	giorno->tamAlfabeto = auxInt2;

	vetor = (int*) malloc(sizeof(int) * auxInt2);

	vetor = setarTamanhoVetor(arquivo);

	giorno->vetorTamColunas = (int*) malloc(sizeof(int) * auxInt2);

	for(i = 0; i < auxInt2; i++){

		giorno->vetorTamColunas[i] = vetor[i];
	}

	//fseek(arquivo, (sizeof(char) + sizeof(char) + (sizeof(char*) * auxInt1) + sizeof(char) + sizeof(char)), SEEK_SET);

	fseek(arquivo, (sizeof(int) + sizeof(char*) * auxInt1) + sizeof(int), SEEK_SET);

	//seto a matriz de retorno pra ter o tamanho certo
	giorno->matAlfabeto = (char**) malloc(sizeof(char*) * auxInt2);
	auxMatrix = (char**) malloc(sizeof(char*) * auxInt2);

	for(i = 0; i < auxInt2; i++){

		giorno->matAlfabeto[i] = (char*) malloc(sizeof(char) * auxInt1);
		auxMatrix[i] = (char*) malloc(sizeof(char) * auxInt1);
	}

	//quebra de linha
	//fread(&neutro, sizeof(char), 1, arquivo);
	fgetc(arquivo);

	/*for(i = 0; i < auxInt2; i++){
		for(j = 0; j < vetor[i]; j++){
			//fread(&giorno->matAlfabeto[i][j], sizeof(char), 1, arquivo);
			//printf("%c", giorno->matAlfabeto[i][j]);
			fscanf(arquivo, "%c", &giorno->matAlfabeto[i][j]);
		}
	}*/

	/*for(i = 0; i < auxInt2; i++){

		fscanf(arquivo, "%s", giorno->matAlfabeto[i]);
		printf("string da linha %d é: %s\n", i + 1, giorno->matAlfabeto[i]);
		fgetc(arquivo);
	}*/

	i = 0;

	while(fscanf(arquivo, "%c", &auxConcat[0]) != EOF){
		
		printf("entrei aq\n");
		//fread(&auxChar, sizeof(char), 1, arquivo); //texto da matriz
		fscanf(arquivo, "%s", auxString);
		strcpy(strFinal, auxConcat);
		strcat(strFinal, espaco);
		strcat(strFinal, auxString);
		printf("String da linha %d é :%s\n", i + 1, strFinal);
		fgetc(arquivo);
		i++;
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

	printf("String codificada: '");

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

	printf("'\n");	

	return stringRetorno;
}

char* decodificar(FILE* arquivo, char* string){

	int i, j, k, contador = 0;
	int x = strlen(string);
	char* stringDecodificada; 
	
	Conteudo* abacchio = getContent(arquivo);

	stringDecodificada = (char*) malloc(sizeof(char) * x);

	printf("String decodificada: '");

	int controle = 0;

	for(i = 0; i < x; i++){

		for(j = 0; j < abacchio->tamAlfabeto; j++){

			for(k = 0; k < abacchio->vetorTamColunas[j] - 3; k++){
				
				if(abacchio->matAlfabeto[j][k + 2] != string[i + k]){

					break;
				}
				
				else if(k  == abacchio->vetorTamColunas[j] - 4){
					
					stringDecodificada[i] = abacchio->matAlfabeto[j][0];
					printf("%c", abacchio->matAlfabeto[j][0]);
					i = i + k;
					controle = 1;
				} 
			}

			if(controle == 1){
			
				controle = 0;
				break;
			}
		}	
	}

	printf("'\n");

	return stringDecodificada;
}

FILE* criaDefault(){

	int n = 5, i, j;
	char test[] = "DCCACADEACCCCCBCEBBBD";
	int x =	strlen(test);
	char linha = '\n';
	char auxChar;
	char* auxString = (char*) malloc(sizeof(char) * x);
	char espaco = ' ';

	char** matriz = (char**) malloc(sizeof(char*) * 5);

	for(i = 0; i < 5; i++){

		matriz[i] = (char*) malloc(sizeof(char) * x);
	}

	matriz[0] = "A 00";
	matriz[1] = "B 0100";
	matriz[2] = "C 0101";
	matriz[3] = "D 011";
	matriz[4] = "E 1";

	FILE* arquivo = fileCreate();

	fprintf(arquivo, "%d\n%s\n%d\n", x, test, n);

	//fwrite(&x, sizeof(int), 1, arquivo);
	
	//fprintf(arquivo, "%d\n", x);
	
	//fwrite(&linha, sizeof(char), 1, arquivo);
	//fprintf(arquivo, "%c", linha);
	//fwrite(test, sizeof(char*) * x, 1, arquivo);
	
	//fprintf(arquivo, "%s\n", test);
	
	//fwrite(&linha, sizeof(char), 1, arquivo);
	//fprintf(arquivo, "%c", linha);
	//fwrite(&n, sizeof(int), 1, arquivo);
	
	//fprintf(arquivo, "%d\n", n);
	
	//fwrite(&linha, sizeof(char), 1, arquivo);
	//fprintf(arquivo, "%c", linha);

	for(i = 0; i < n; i++){

		fprintf(arquivo, "%s\n", matriz[i]);
	}

	/*for(i = 0; i < n; i++){

		auxChar = matriz[i][0];
		//fwrite(&auxChar, sizeof(char), 1, arquivo);
		fprintf(arquivo, "%c ", auxChar);
		//fwrite(&espaco, sizeof(char), 1, arquivo);
		//fprintf(arquivo, "%c", espaco);
		//printf("linha %d, coluna 0: %c\n", i, auxChar);

		for(j = 1; matriz[i][j] != '\0'; j++){

			auxChar = matriz[i][j];
			//printf("linha %d, coluna %d: %c\n", i, j, auxChar);
			//fwrite(&auxChar, sizeof(char), 1, arquivo);
			fprintf(arquivo, "%c", auxChar);
		}
		
		//printf("\n");
		//auxString[j] = '\0';
		//fwrite(&linha, sizeof(char), 1, arquivo);
		fprintf(arquivo, "%c", linha);
	}*/

	rewind(arquivo);
	return arquivo;
}

void imprimeArquivo(FILE* arquivo){

	char auxChar;
	char* auxString;
	int auxInt1, auxInt2;
	int* tamanhoLinhas;

	rewind(arquivo);

	//fread(&auxInt, sizeof(int), 1, arquivo); //tamanho do texto
	
	fscanf(arquivo, "%d", &auxInt1);
	printf("%d\n", auxInt1);
	fgetc(arquivo);
	
	//fread(&auxChar, sizeof(char), 1, arquivo); //quebra de linha
	//printf("%c", auxChar);

	auxString = (char*) malloc(sizeof(char) * auxInt1);

	//fread(auxString, sizeof(char*) * auxInt, 1, arquivo); //texto do arquivo
	fscanf(arquivo, "%s", auxString);
	printf("%s\n", auxString);

	//fread(&auxChar, sizeof(char), 1, arquivo); //quebra de linha
	//printf("%c", auxChar);
	fgetc(arquivo);
	
	//fread(&auxInt, sizeof(int), 1, arquivo); //tamanho da matriz de elementos
	fscanf(arquivo, "%d", &auxInt2);
	//printf("%d\n", auxInt2);

	tamanhoLinhas = (int*) malloc(sizeof(int) * auxInt2);

	//fread(&auxChar, sizeof(char), 1, arquivo); //quebra de linha
	fgetc(arquivo);
	//printf("%c\n", auxChar);
	
	int valor = 0;
	int indice = 0;

	while(fscanf(arquivo, "%c", &auxChar) != EOF){
		
		//fread(&auxChar, sizeof(char), 1, arquivo); //texto da matriz
		fscanf(arquivo, "%s", auxString);
		printf("%c ", auxChar);
		printf("%s\n", auxString);
		fgetc(arquivo);
	}

	printf("Fim da impressão.\n");
	rewind(arquivo);
}

int* setarTamanhoVetor(FILE* arquivo){

	char auxChar;
	char* auxString;
	int auxInt;
	int* tamanhoLinhas;

	rewind(arquivo);

	//fread(&auxInt, sizeof(int), 1, arquivo); //tamanho do texto
	fscanf(arquivo, "%d", &auxInt);
	//fread(&auxChar, sizeof(char), 1, arquivo); //quebra de linha

	fgetc(arquivo);

	auxString = (char*) malloc(sizeof(char) * auxInt);

	//fread(auxString, sizeof(char*) * auxInt, 1, arquivo); //texto do arquivo
	fscanf(arquivo, "%s", auxString);

	//fread(&auxChar, sizeof(char), 1, arquivo); //quebra de linha
	fgetc(arquivo);

	//fread(&auxInt, sizeof(int), 1, arquivo); //tamanho da matriz de elementos
	fscanf(arquivo, "%d", &auxInt);

	tamanhoLinhas = (int*) malloc(sizeof(int) * auxInt);

	//fread(&auxChar, sizeof(char), 1, arquivo); //quebra de linha
	fgetc(arquivo);

	int valor = 0;
	int indice = 0;

	//printf("%d\n", auxInt);

	while(fscanf(arquivo, "%c", &auxChar) != EOF){
		
		//fread(&auxChar, sizeof(char), 1, arquivo); //texto da matriz
		fscanf(arquivo, "%s", auxString);
		valor = strlen(auxString);
		//printf("A string %d tem tamanho: %d.\n", indice + 1, valor);
		//printf("%c ", auxChar);
		//printf("%s\n", auxString);
		fgetc(arquivo);
		tamanhoLinhas[indice] = valor;
		indice++;
	}

	printf("\n");
	/*while(indice < auxInt){

		//fread(&auxChar, sizeof(char), 1, arquivo); //texto da matriz
		fscanf(arquivo, "%s", auxString);
		//fgetc(arquivo);
		valor = strlen(auxString);
		printf("string %d tem tamanho %d\n", indice + 1, valor);
		tamanhoLinhas[indice] = valor;
		indice++;
	}*/

	rewind(arquivo);

	return tamanhoLinhas;
}