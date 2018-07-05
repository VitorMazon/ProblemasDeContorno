/*
 * DifFinita.c
 * 
 * Copyright 2018 Vitor <vitor@vitor-mazon>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

/*EDO (ñ linear)
	y"(x)= y'(x)+2*y(x)+cos(x)
	  	  |      | 	     |
	     p(x)   q(x)    r(x)
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double p(double x){
	return 1;
}

double q(double x) {
	return 2;
}

double r(double x) {
	return cos(x);
}

void imprime(double **N, int x, int y){
	int i, j;
	for(i=0;i<x;i++) {
		for(j=0;j<y;j++) { 
			printf("%5.3lf\t",N[i][j]);
		}	  
		puts("");
	}
}

void pivoteamento(double **M, int dim) {
	int i, j, r, a, col, pivo;
	double lamb, aux, max;
	i=j=0;
	for(j=0; j<dim-1; j++) {
		//Acha o maior valor da coluna e o faz de pivo
		max=fabs(M[j][j]);
		pivo=j;
		for(a=j; a<=dim-1; a++) {
			if(fabs(M[a][j]) > max) {
				pivo = a;
				max = fabs(M[a][j]);
			}
		}
		//Troca as linhas para o novo pivo
		for(col=0; col<=dim; col++) {
			aux=M[j][col];
			M[j][col]=M[pivo][col];
			M[pivo][col]=aux;
		}
		//Triangulariza a matriz adjacente
		for(i=j+1; i<=dim-1; i++) {
			lamb=M[i][j]/M[j][j];
			for(r=j; r<=dim; r++)
				M[i][r] = M[i][r] - (lamb)*M[j][r];
		}
	}
}

void subsreversa(double **M, double *raizes, int dim) {
	int i, j;
	double a;
	for(i=dim-1; i>=0; i--) {
		a=0;
		for(j=i+1; j<dim; j++)
			a += M[i][j]*raizes[j];
		raizes[i] = (M[i][dim]-a)/(M[i][i]);
		//*n=*n+1;  operações
	}
}

void resultados(double *r, int n, double yi, double yf, double a, double h) {
	int i;
	double x=a;
	
	printf("%lf\t%lf\n", x, yi);
	for(i=0; i<n; i++){
		x+=h;
		printf("%lf\t%lf\n", x, r[i]);
	}
	x+=h;
	printf("%lf\t%lf\n", x, yf);
}

int main(int argc, char **argv) {
	int N, i, j;
	double h, x;
	double **M, *raizes;
	double a=0, b=0.5*M_PI;
	double yi=-0.3, yf=-0.1;
	
	N=atof(argv[1]);
	
	h=(b-a)/(N+1);
	x=a;
	
	M=malloc(N*sizeof(double *));
	for(i=0; i<N; i++)
		M[i]=(double *)malloc((N+1)*sizeof(double *));
		
	for(i=0; i<N; i++) {
		x+=h;
		
		for(j=0; j<=N; j++){
			
			M[i][j]=0.;
			
			if(i==j)
				M[i][j]=2+pow(h,2)*q(x);
			
			if(j==i-1)
				M[i][j]=-1-0.5*h*p(x);
			
			if(j==i+1)
				M[i][j]=-1+0.5*h*p(x);
			
			if(j==N){
				M[i][j]=-pow(h,2)*r(x);
				
				if(i==0)
					M[i][j]=-pow(h,2)*r(x)+(1+0.5*h*p(x))*yi;
				if(i==N-1)
					M[i][j]=-pow(h,2)*r(x)+(1-0.5*h*p(x))*yf;	
			}				
		}
	}
	
	pivoteamento(M,N);
	raizes = malloc(N*sizeof(double));
	subsreversa(M,raizes,N);
	resultados(raizes,N,yi,yf,a,h);
	return 0;
}

