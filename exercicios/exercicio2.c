#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 4
#define M 4
#define h 1/3.0
#define TOL 1e-9

double func()
{
    return 0;
}

void contorno(double **w)
{	int i, j;
	double x = 1, y = 0;

	for( i = 0; i < N; i++ )
	{	w[i][0] = 2* log(x);
		w[i][M-1] = log( x*x + 1);
		x += h;
	}

	for( i = 0; i < M; i++ )
	{	w[0][i] = log( y*y + 1);
		w[N-1][i] = log( y*y + 4);
		y += h;
	}
}

double edp( double **w, double **aux )
{	int i, j;
	double eps, a = 0;

	for( i = 1; i < N-1; i++ )
	{	for( j = 1; j < M; j++ )
		{	if( aux[i][j] == 0 )
			{	eps = w[i][j];
				w[i][j] = ( w[i-1][j] + w[i+1][j] + w[i][j-1] + w[i][j+1] -h*h* func())/ 4.0;
				eps = fabs( eps - w[i][j] );
				if( eps > a )
					a = eps;
			}
		}
	}
	return a;
}

void imprimeMatriz(double **w, int n, int m)
{
    FILE *arq = fopen("dados_12.1ex2.txt","w");
    int i, j;

	//printf("Matriz calculada\n");
	for(i = 0; i < n; i++)
	{
		for( j = 0; j < m; j++)
        {
            printf("%lf\t ",w[i][j]);
            fprintf(arq,"%lf\t ",w[i][j]);
        }

        fprintf(arq,"\n");
		puts("");
	}

	fclose(arq);
}

void main()
{	double	**w, **aux;
	int  i, j;

	aux = malloc( N* sizeof(double*));
	for( i = 0; i < M; i++ )
    {
        aux[i] = malloc( M* sizeof(double));

    }

	w = malloc( N* sizeof(double*));
	for( i = 0; i < M; i++ )
    {
        w[i] = malloc( M* sizeof(double));
    }


	contorno(w);
	//mascara
	for( i = 0; i < N; i++ )
	{	aux[i][0] = 1;
		aux[i][M-1] = 1;
	}
	for( i = 0; i < M; i++ )
	{	aux[0][i] = 1;
		aux[N-1][i] = 1;
	}

	while( edp(w, aux) > TOL );

	imprimeMatriz(w,N,M);
}


