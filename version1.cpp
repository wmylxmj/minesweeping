#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

#define m_max 100
#define n_max 100

typedef struct{
	unsigned int m;
	unsigned int n;
	char array[m_max][n_max];
}Matrix;

Matrix matrix_saolei;

void CreatMatrixZero(Matrix *matrix, unsigned int m, unsigned int n)
{
	unsigned int i = 0,j = 0;
	matrix->m = m;
	matrix->n = n;
	for(i=0; i<m; i++)
	{
		for(j=0; j<n; j++)
		{
			matrix->array[i][j]=0;
			printf("0 ");
		}
		printf("\n");
	}
	printf("\n");
}

void PlaceBombs(Matrix *matrix, unsigned int num_bomb)
{
	unsigned int i;
	unsigned int m_point, n_point;
	unsigned int max_num_bomb = 0;
	max_num_bomb = matrix->m * matrix->n;
	if(max_num_bomb >= num_bomb)
	{
		for(i=1;i<=num_bomb;i++) 
		{
			//0 to m-1
			m_point = rand()%matrix->m;
			n_point = rand()%matrix->n;
			if(matrix->array[m_point][n_point]!='*')
			{
				matrix->array[m_point][n_point]='*';
			}
			else
			{
				//retry
				i = i - 1;
			}
		}
	}
	else
	{
		printf("The number of bombs is error!\n");
	}
}

bool ArrangeJudge(Matrix *matrix, unsigned int i, unsigned int j)
{
	if(i>=0 && i<matrix->m && j>=0 && j<matrix->n)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ComputeBombs(Matrix *matrix)
{
	unsigned int i = 0,j = 0;
	char result = 0;
	for(i=0; i<matrix->m; i++)
	{
		for(j=0; j<matrix->n; j++)
		{
			if(matrix->array[i][j]!='*')
			{
				if(ArrangeJudge(matrix, i-1, j-1) && matrix->array[i-1][j-1]=='*')result++;
				if(ArrangeJudge(matrix, i, j-1) && matrix->array[i][j-1]=='*')result++;
				if(ArrangeJudge(matrix, i+1, j-1) && matrix->array[i+1][j-1]=='*')result++;
				if(ArrangeJudge(matrix, i-1, j) && matrix->array[i-1][j]=='*')result++;
				if(ArrangeJudge(matrix, i+1, j) && matrix->array[i+1][j]=='*')result++;
				if(ArrangeJudge(matrix, i-1, j-1) && matrix->array[i-1][j+1]=='*')result++;
				if(ArrangeJudge(matrix, i, j) && matrix->array[i][j+1]=='*')result++;
				if(ArrangeJudge(matrix, i+1, j+1) && matrix->array[i+1][j+1]=='*')result++;
				matrix->array[i][j] = result;
			}
			result = 0;
		}
	}
}

void DisplayTheSaoleiTable(Matrix *matrix)
{
	unsigned int i = 0,j = 0;
	for(i=0; i<matrix->m; i++)
	{
		for(j=0; j<matrix->n; j++)
		{
			if(matrix->array[i][j]=='*')
			{
				printf("%c ", matrix->array[i][j]);
			}
			else
			{
				printf("%c ", matrix->array[i][j]+0x30);
			}
		}
		printf("\n");
	}
	printf("\n");
}


void main(void)
{
	CreatMatrixZero(&matrix_saolei, 30, 30);
	PlaceBombs(&matrix_saolei, 100);
	DisplayTheSaoleiTable(&matrix_saolei);
	ComputeBombs(&matrix_saolei);
	DisplayTheSaoleiTable(&matrix_saolei);
}
