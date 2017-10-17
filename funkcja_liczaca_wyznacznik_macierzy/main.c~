#include <stdio.h>
#include <stdlib.h>

int matrix_alloc(int n){
	int **matrix = (int **)malloc(n * sizeof(int*));
	for(int i = 0; i < n; i++){
		matrix[i] = (int *)malloc(n * sizeof(int));
	}
}
int matrix_free(double ** minor){
	while(*minor++){
		free(minor);	
	}
	free(minor);
}

double det(double ** matrix, int n)
{
	double** minor;
	double sum=0.0;
	double sign=1.0;
	int i;

	/* rozpatrz przypadki szczególne */
	if(n==1){
		return matrix[0][0];
	}
	if(n==2){
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}

	minor=matrix_alloc(n-1);

	for(i=0;i<n;i++)
	{
		/* skopiuj odp. podmacierz do minor */
		...

		/* wylicz wyznacznik podmiacierzy */
		sum+=sign*matrix[0][i]*det(minor,n-1);
		sign = -sign;
	};

	matrix_free(minor);

	return sum;
}	

int main(){
	
	return 0;
}
