#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double ** matrix_alloc(int n){
	int i;
	double **matrix = (double **)malloc(n * sizeof(double*));
	for(i = 0; i < n; i++){
		matrix[i] = (double *)malloc(n * sizeof(double));
	}
	return matrix;
}
void matrix_free(double ** minor){
	int i;
	for (i=0; i<sqrt(sizeof(minor)/8); i++){
		free(minor[i]);
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

	minor = matrix_alloc(n-1);

	for(i=0;i<n;i++)
	{
		if (matrix[0][i] == 0){
			sum+=0;
		}
		else{
			sum+=sign*matrix[0][i]*det(minor,n-1);
			sign = -sign;
		}
	}

	matrix_free(minor);

	return sum;
}

int main(){
	double** minor;
	FILE * pFile;
	int size = 0, i,j;
  pFile = fopen ("matrix.dat","r");
  if (pFile!=NULL)
  {
		fscanf(pFile, "%d", &size);
		printf("Wielkosc -> %d\n", size);
		minor = matrix_alloc(size);
		for(i=0;i<size;i++){
			for(j=0;j<size;j++){
				fscanf(pFile, "%lf", &minor[i][j]);
			}
		}
		for(i=0;i<size;i++){
			for(j=0;j<size;j++){
				printf("%.2f ", minor[i][j]);
			}
			printf("\n");
		}
		printf("%.2f",det(minor, size));
		matrix_free(minor);
    fclose (pFile);
  }
	else{
		printf("Nie mozna otworzyc pliku");
	}

	return 0;
}
