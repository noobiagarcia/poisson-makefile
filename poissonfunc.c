#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "poisson.h"
#include "time.h"

//#define l 900 //Qt linhas
//#define c 900 //Qt colunas
#define MAX 1e+10 //Numero máximo de iterações
#define TOl 1e-13 //Tolerância do erro
#define h  1e-4 //Tamanho do passo x
#define k  1e-4 //Tamanho do passo y

void condcontorno(double **u, double **aux, int l, int c) //Inicializando as condições de contorno
{	
	int i, y1, y2; 
	double y, t;
	
	for(i=c-c/8; i<=c+c/8; i++) //condição dos "is" marca o tamanho dos passos na malha
	{   
	    t = i*(8*M_PI/l);
	    //printf("\n%lf \t i = %d\n", t, i);
	    y = 0.125*l*sin(t); //equação da onda
	    y1= (int) y + l/2;
	    y2= (int) -1*y + l/2;
	    //printf("y = %lf, y1 = %d\n", y, y1);
	    //printf("--------------");
	    u[y1][i+c/2] = -1;
	    u[y2][i+c/2] = -1;
		aux[y1][i+c/2] = -1;
		aux[y2][i+c/2] = -1;
	}
	
	for(i=0; i<c/10; i++)
	{
	    u[c/10][i+c/10] = 1;
	    u[i+c/10][c/10] = 1;
	    u[c-c/10][(9*c/10)-i] = 1;
	    u[(9*c/10)-i][c-c/10] = 1;
		aux[c/10][i+c/10] = 1;
	    aux[i+c/10][c/10] = 1;
	    aux[c-c/10][(9*c/10)-i] = 1;
	    aux[(9*c/10)-i][c-c/10] = 1;
	}
}
double mtdffin(double **w, double **mt_aux, int l, int c)
{	
	int i, j, x = 0.5*l, y = 0.5*c; 
	double  df, err = 0, r;
	
	for(i=1;i<l-1;i++)
	{	for(j=1;j<c-1;j++)
		{	
			df = w[i][j]; //Salvando o valor atual da matriz no ponto [i][j]
			
			if(mt_aux[i][j] == 0) 
			{	
				w[i][j] = (-h*h + w[i+1][j] + w[i-1][j] + w[i][j-1] + w[i][j+1])/(4.0); //Formula encontrada para calcular os pontos pelo metodo das diferenças finitas.
					
				df = fabs(df - w[i][j]); //calculando o erro
			}
		}
	}
	if(df > err) //Verificando se o erro é menor que o anterior.
	{
		err = df;
	}
	
	return err;
}
void salvasol(double **w, int l, int c) //Salvando a solução no arquivo.
{	
	FILE *fp;
	int i, j;
	
	fp = fopen("matriz_solucao.dat", "w");
	
	for(i=0;i<l;i++)
	{	
		for(j=0;j<c;j++)
		{
			fprintf(fp, "%lf\t", w[i][j]);
		}	
		
		fprintf(fp,"\n");
	}
	
 fclose(fp);
}
