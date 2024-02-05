#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "poisson.h"
#include "time.h"

//#define l 900 //Qt linhas
//#define c 900 //Qt colunas
#define MAX 1e+10 //Numero máximo de iterações
#define TOl 1e-6 //Tolerância do erro
#define h  1e-4 //Tamanho do passo x
#define k  1e-4 //Tamanho do passo y

int main(int argc, char **argv)
{	
	double **M, **Maux, er = 1, tempo;
	int i, j, cont, l, c;
	clock_t tini, tfim;
	
	tini = clock();
	
	l = atoi(argv[1]);
	c = atoi(argv[2]);

	M = (double**)malloc(l*sizeof(double*)); //matriz principal.
	for(i=0;i<l;i++)
		M[i] = (double*)malloc(c*sizeof(double*));

	
	Maux = (double**)malloc(l*sizeof(double*)); //matriz auxiliar.
	for(i=0;i<l;i++)	
		Maux[i] = (double*)malloc(c*sizeof(double*));
	
	for(i=0;i<l;i++) //iniciandos as matrizes com zeros
	{
		for(j=0;j<c;j++)
		{
			M[i][j] = 0;
			Maux[i][j] = 0;
		}
	}
	
	condcontorno(M, Maux, l, c); //Aplicando as condições de contorno.

	for(cont = 1; er>TOl && cont<MAX; cont++) //Aplicando o metodo
	{	
		er = mtdffin(M, Maux, l, c);
		//printf("\nPasso: %d\n %.22lf\n", cont, er); 
	}
	
	salvasol(M, l, c); //Salvando a solução
	tfim = clock();
	
	tempo = (double)(tfim - tini)/CLOCKS_PER_SEC;
	printf("tempo = %lf segundos\n", tempo);

 return 0;
}
