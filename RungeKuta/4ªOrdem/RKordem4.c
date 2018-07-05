/*
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

//y'=1+(t-y)², 2<=t<=3, y(2)=1, com N=10pontos

#include <stdio.h>
#include <math.h>

double f(double t, double y){
	return (1+pow((t-y),2));
}

double RungeKuta(double t, double y, double h){
	double k1, k2, k3, k4;
	
	k1=f(t,y);
	k2=f(t+0.5*h,y+0.5*h*k1);
	k3=f(t+0.5*h,y+0.5*h*k2);
	k4=f(t+h,y+h*k3);
	
	printf("%lf\t%lf\n", t, y); //printf antes de calcular y
	
	y=y+(h/6)*(k1+2*k2+2*k3+k4);
	
	return y;
}

int main(int argc, char **argv) {
	int N=10;
	double t, h, y;
	double a=2, b=3;
	
	h=(b-a)/N;
	y=1;
	
	for(t=2; t<=3; t+=h){
		y=RungeKuta(t,y,h);
	}
	
	return 0;
}
