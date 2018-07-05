/*	Método Shooting Linear 
 * (Para funções com condição inicial e final, sem derivada da
 *  função inicial)
 * 
 * ShootingLinear.c
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
 * Obs.: Duas equações diferentes para resolver por Runge-Kuta, então 
 * são 4 funções pra duas equações de 2º grau.
 * 	Neste caso são apenas 3 funções pois a primeira função é igual para
 * as duas equações.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 2  //nº de equações
typedef double(*sistfunc)();

//Função "z"
double f(double t, double y[]){
	return y[1];
}

double f1(double t, double y[]){
	return y[1]+2*y[0]+cos(t);
}

double f2(double t, double y[]){
	return y[1]+2*y[0];
}

double rk(sistfunc func[], double y[], double t, double h){
	int i;
	double k1[N], k2[N], k3[N], k4[N], aux[N];
	
	//Valores de k's para cada função (equação)
	for(i=0; i<N; i++)
		k1[i]=func[i](t,y);
	
	for(i=0; i<N; i++)
		aux[i]=y[i]+0.5*h*k1[i];
	for(i=0; i<N; i++)
		k2[i]=func[i](t+0.5*h,aux);
	
	for(i=0; i<N; i++)
		aux[i]=y[i]+0.5*h*k2[i];
	for(i=0; i<N; i++)
		k3[i]=func[i](t+0.5*h,aux);
	
	for(i=0; i<N; i++)
		aux[i]=y[i]+h*k3[i];
	for(i=0; i<N; i++)
		k4[i]=func[i](t+h,aux);
	
	for(i=0; i<N; i++)
		y[i]=y[i]+(h/6)*(k1[i]+2*k2[i]+2*k3[i]+k4[i]);
		
	return y[0];
}

double* shootingLinear(double y1[], double y2[], double beta, int P){
	int i;
	double *v;
	
	v=(double *)malloc(P*sizeof(double *));
	
	for(i=0; i<P; i++)
		v[i]=y1[i]+((beta-y1[P-1])/y2[P-1])*y2[i];
	
	return v;
}

void main(int argc, char **argv) {
	int P, i;
	double t, h, y1[N], y2[N], *res1, *res2, *sol;
	double a=0, b=0.5*M_PI;
	double beta=-0.1;
	sistfunc equacoes1[N]={f,f1};
	sistfunc equacoes2[N]={f,f2};
	
	P=atof(argv[1]);
	
	res1=(double *)malloc(P*sizeof(double *));
	res2=(double *)malloc(P*sizeof(double *));
	
	h=(b-a)/P;

	y1[0]=-0.3;
	y1[1]=0;

	y2[0]=0;
	y2[1]=1;
	
	res1[0]=y1[0];
	res2[0]=y2[0];
	
	i=1; //indice de inicio na segunda posição do vetor res[]
	for(t=a+h; t<=b; t+=h) {
		res1[i]=rk(equacoes1,y1,t,h);
		res2[i]=rk(equacoes2,y2,t,h);
		i++;
	}
	
	sol=shootingLinear(res1,res2,beta,P);
	
	t=a;
	for(i=0; i<P; i++){
		printf("%lf\t%lf\n", t, sol[i]);
		t+=h;
	}
}
