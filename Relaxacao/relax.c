/*
 * relax.c
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

void condContorno(double **M, int xdim, int ydim) {
	int i, j;
	
	for(i=0; i<xdim; i++) {
		M[i][0]=0;
		M[i][ydim-1]=200;
	}
	
	for(j=0; j<ydim; j++) {
		M[0][j]=200;
		M[xdim-1][j]=0;
	}	
	return;
}

int relax(double **M, int xdim, int ydim, int h) {
	int i, j, cont=0, vi;
	int x, y;
	double var=0., aux;
	
	x=xdim-1;
	y=ydim-1;
	
	while(var!=h) {
		var=0.;
		for(i=1; i<x; i++) {
			for(j=1; j<y; j++) {
				M[i][j]=(M[i-1][j]+M[i+1][j]+M[i][j-1]+M[i][j+1])/4;
				if(cont==0) {
					aux=M[i][j];
					vi=i;
				}
				if(cont==1) {
					var=aux;
				}
				var=M[i][j];
			}
		}
		cont++;
	}
	return cont;
}

void imprime(double **N, int x, int y){
	int i, j;
	for(i=0;i<x;i++) {
		for(j=0;j<y;j++) { 
			printf("%5.2lf\t",N[i][j]);
		}	  
		puts("");
	}
}

int main(int argc, char **argv) {
	int xdim, ydim, it, i;
	double **L;
	
	err=atof(argv[1]);
	xdim=22;
	ydim=22;
	
	L=malloc(xdim*sizeof(double *));
	for(i=0; i<xdim; i++)
		L[i]=(double *)malloc(ydim*sizeof(double *));
		
	condContorno(L, xdim, ydim);
	it=relax(L, xdim, ydim, err);
	imprime(L, xdim, ydim);
	printf("# %d iterações", it);
	return 0;
}

