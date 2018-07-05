/*Runge-Kuta para EDO de ordem mais alta
 * 
 * RK.c
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

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 2  //nº de equações
typedef double(*sistfunc)();

//Função de z
double f(double t, double y[]){
	return y[1];
}

//Função de z'
double g(double t, double y[]){
	return 3*y[1]-2*y[0]+6*exp(-t);
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

void main(int argc, char **argv) {
	int P=10;
	double t, h, y[N], yt;
	double a=0, b=1;
	sistfunc equacoes[N]={f,g};
	
	h=(b-a)/P;
	y[0]=2;
	y[1]=2;
	
	yt=y[0];
	
	for(t=a; t<=b; t+=h){
		printf("%lf\t%lf\n", t, yt);
		
		yt=rk(equacoes,y,t,h);
	}
}
