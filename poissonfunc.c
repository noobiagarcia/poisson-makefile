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

void condcontorno(double **u, double **aux, int l, int c) //Inicializando as condições de contorno
{
	int i, y1, y2;
	double y, t;

	for(i=c-(c*0.125); i<=c+(c*0.125); i++) //condição dos "is" marca o tamanho dos passos na malha
	{
	    t = i*(8*M_PI/l);
	    //printf("\n%lf \t i = %d\n", t, i);
	    y = 0.125*l*sin(t); //equação da onda
	    y1= (int) y + (l*0.5);
	    y2= (int) -1*y + (l*0.5);
	    //printf("y = %lf, y1 = %d\n", y, y1);
	    //printf("--------------");
	    u[y1][i+(c*0.5)] = -1;
	    u[y2][i+(c*0.5)] = -1;
		aux[y1][i+(c*0.5)] = -1;
		aux[y2][i+(c*0.5)] = -1;
	}
	for(i=0; i<(c*0.1); i++)
	{
	    u[c*0.1][i+c*0.1] = 1;
	    u[i+(c*0.1)][c*0.1] = 1;
	    u[c-(c*0.1)][(9*c*0.1)-i] = 1;
	    u[(9*c*0.1)-i][c-(c*0.1)] = 1;
		 aux[c*0.1][i+c*0.1] = 1;
	    aux[i+c*0.1][c*0.1] = 1;
	    aux[c-c*0.1][(9*c*0.1)-i] = 1;
	    aux[(9*c*0.1)-i][c-c*0.1] = 1;
	}
}
double mtdffin(double **w, double **mt_aux, int l, int c)
{
	int i, j, x = 0.5*l, y = 0.5*c;
	double  df, err = 0, r;

	for(i=1;i<l-1;i++)
	{	for(j=1;j<c-1;j++)
		{
			df = w[i][j];
			if(mt_aux[i][j] == 0)
			{
				w[i][j] = ( (-h*h + w[i+1][j] + w[i-1][j] + w[i][j-1] + w[i][j+1]) )*(0.25); //metodo das diferenças finitas.
				df = fabs(df - w[i][j]);
			}
		}
	}
	if(df > err) //Verificando o erro 
		err = df;

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
			fprintf(fp, "%lf\t", w[i][j]);

		fprintf(fp,"\n");
	}
 fclose(fp);
}
