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

typedef struct{
	char name[20];
	int score;
}Player;

Matrix matrix_saolei;
Matrix matrix_user;

Player players[20];

void CreatMatrixZero(Matrix *matrix, unsigned int m, unsigned int n)
{
	unsigned int i = 0, j = 0;
	if(m_max>=m && n_max>=n)
	{
		matrix->m = m;
		matrix->n = n;
		for(i=0; i<m; i++)
		{
			for(j=0; j<n; j++)
			{
				matrix->array[i][j] = 0;
				printf("0 ");
			}
			printf("\n");
		}
		printf("\n");
	}
	else
	{
		printf("m, n is error!\n");
	}
}

void CreatMatrixUser(Matrix *matrix, unsigned int m, unsigned int n)
{
	unsigned int i = 0, j = 0;
	if(m_max>=m && n_max>=n)
	{
		matrix->m = m;
		matrix->n = n;
		for(i=0; i<m; i++)
		{
			for(j=0; j<n; j++)
			{
				matrix->array[i][j] = '#';
				printf("# ");
			}
			printf("\n");
		}
		printf("\n");
	}
	else
	{
		printf("m, n is error!\n");
	}
}

void PlaceBombs(Matrix *matrix, unsigned int num_bomb, unsigned int x, unsigned int y)
{
	unsigned int i;
	unsigned int m_point, n_point;
	unsigned int max_num_bomb = 0;
	max_num_bomb = matrix->m * matrix->n;
	if(max_num_bomb >= num_bomb)
	{
		for(i=1; i<=num_bomb; i++)
		{
			//0 to m-1
			m_point = rand()%matrix->m;
			n_point = rand()%matrix->n;
			if(matrix->array[m_point][n_point] != '*' && m_point!=x-1 && n_point!=y-1)
			{
				matrix->array[m_point][n_point] = '*';
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
	if(i>=0 && i<matrix->m && j>=0 &&j < matrix->n)
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
	unsigned int i = 0, j = 0;
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
				if(ArrangeJudge(matrix, i-1, j+1) && matrix->array[i-1][j+1]=='*')result++;
				if(ArrangeJudge(matrix, i, j+1) && matrix->array[i][j+1]=='*')result++;
				if(ArrangeJudge(matrix, i+1, j+1) && matrix->array[i+1][j+1]=='*')result++;
				matrix->array[i][j] = result;
			}
			result = 0;
		}
	}
}

void DisplayMatrix(Matrix *matrix)
{
	unsigned int i = 0, j = 0;
	for(i=0; i<matrix->m; i++)
	{
		for(j=0; j<matrix->n; j++)
		{
			if(matrix->array[i][j]=='*' || matrix->array[i][j]=='#' || matrix->array[i][j]=='@')
			{
				printf("%c ", matrix->array[i][j]);
			}
			else
			{
				printf("%d ", matrix->array[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

void ShowZeroArround(Matrix *matrix_saolei, Matrix *matrix_user, unsigned int i, unsigned int j)
{
	unsigned int now_i, now_j;
	matrix_user->array[i][j] = 0;
	//1
	now_i = i; now_j = j-1;
	if(ArrangeJudge(matrix_saolei, now_i, now_j) && matrix_saolei->array[now_i][now_j]==0 && matrix_user->array[now_i][now_j]!=0)
	{
		matrix_user->array[now_i][now_j] = 0;
		ShowZeroArround(matrix_saolei, matrix_user, now_i, now_j);
	}
	else if(ArrangeJudge(matrix_saolei, now_i, now_j) && matrix_saolei->array[now_i][now_j]!=0 && matrix_saolei->array[now_i][now_j]!='*')
	{
		matrix_user->array[now_i][now_j] = matrix_saolei->array[now_i][now_j];
	}
	//2
	now_i = i-1; now_j = j;
	if(ArrangeJudge(matrix_saolei, now_i, now_j) && matrix_saolei->array[now_i][now_j]==0 && matrix_user->array[now_i][now_j]!=0)
	{
		matrix_user->array[now_i][now_j] = 0;
		ShowZeroArround(matrix_saolei, matrix_user, now_i, now_j);
	}
	else if(ArrangeJudge(matrix_saolei, now_i, now_j) && matrix_saolei->array[now_i][now_j]!=0 && matrix_saolei->array[now_i][now_j]!='*')
	{
		matrix_user->array[now_i][now_j] = matrix_saolei->array[now_i][now_j];
	}
	//3
	now_i = i+1; now_j = j;
	if(ArrangeJudge(matrix_saolei, now_i, now_j) && matrix_saolei->array[now_i][now_j]==0 && matrix_user->array[now_i][now_j]!=0)
	{
		matrix_user->array[now_i][now_j] = 0;
		ShowZeroArround(matrix_saolei, matrix_user, now_i, now_j);
	}
	else if(ArrangeJudge(matrix_saolei, now_i, now_j) && matrix_saolei->array[now_i][now_j]!=0 && matrix_saolei->array[now_i][now_j]!='*')
	{
		matrix_user->array[now_i][now_j] = matrix_saolei->array[now_i][now_j];
	}
	//4
	now_i = i; now_j = j+1;
	if(ArrangeJudge(matrix_saolei, now_i, now_j) && matrix_saolei->array[now_i][now_j]==0 && matrix_user->array[now_i][now_j]!=0)
	{
		matrix_user->array[now_i][now_j] = 0;
		ShowZeroArround(matrix_saolei, matrix_user, now_i, now_j);
	}
	else if(ArrangeJudge(matrix_saolei, now_i, now_j) && matrix_saolei->array[now_i][now_j]!=0 && matrix_saolei->array[now_i][now_j]!='*')
	{
		matrix_user->array[now_i][now_j] = matrix_saolei->array[now_i][now_j];
	}
}

bool JudgeBombs(Matrix *matrix_saolei, Matrix *matrix_user, unsigned int x, unsigned int y, int judge)
{
	if(matrix_saolei->array[x-1][y-1] == '*')
	{
		if(judge == 0)
		{
			printf("Game Over !\n");
			DisplayMatrix(matrix_saolei);
			return false;
		}
		else if(judge == 1)
		{
			matrix_user->array[x-1][y-1] = '@';
		}
	}
	else if(matrix_saolei->array[x-1][y-1] != '*')
	{
		if(judge == 0)
		{
			if(matrix_saolei->array[x-1][y-1] != 0)
			{
				matrix_user->array[x-1][y-1] = matrix_saolei->array[x-1][y-1];
			}
			else if(matrix_saolei->array[x-1][y-1] == 0)
			{
				ShowZeroArround(matrix_saolei, matrix_user, x-1, y-1);
			}
		}
		else if(judge == 1)
		{
			matrix_user->array[x-1][y-1] = '@';
		}
	}
	return true;
}

bool JudgeWin(Matrix *matrix_saolei, Matrix *matrix_user)
{
	unsigned int i = 0, j = 0;
	for(i=0; i<matrix_saolei->m; i++)
	{
		for(j=0; j<matrix_saolei->n; j++)
		{
			if(matrix_saolei->array[i][j]=='*')
			{
				if(matrix_user->array[i][j]!='@')
				{
					return false;
				}
			}
		}
	}
	return true;
}

void main(void)
{
	unsigned int x, y;
	unsigned int m, n;
	unsigned int num_bombs;
	bool win_flag = true;
	int play_flag = 1;
	int judge;
	int i = 1;
	while(play_flag==1)
	{
		printf("Please input the area of m, n and the number of bombs:\n");
		scanf("%d%d%d", &m, &n, &num_bombs);
		while(num_bombs > m*n*0.75)
		{
			printf("Bombs is too much!\n");
			printf("Please input the area of m, n and the number of bombs:\n");
			scanf("%d%d%d", &m, &n, &num_bombs);
		}
		CreatMatrixZero(&matrix_saolei, m, n);
		CreatMatrixUser(&matrix_user, m, n);
		printf("Please input x y and judge:\n");
		scanf("%d%d%d", &x, &y, &judge);
		PlaceBombs(&matrix_saolei, num_bombs, x, y);
		ComputeBombs(&matrix_saolei);
		JudgeBombs(&matrix_saolei, &matrix_user, x, y, judge);
		DisplayMatrix(&matrix_user);
		while(!JudgeWin(&matrix_saolei, &matrix_user))
		{
			printf("Please input x y and judge:\n");
			scanf("%d%d%d", &x, &y, &judge);
			while(x>m || y>m || (judge!=0&&judge!=1))
			{
				printf("Input error !\n");
				printf("Please input x y and judge:\n");
				scanf("%d%d%d", &x, &y, &judge);
			}
			i=1;
			if(!JudgeBombs(&matrix_saolei, &matrix_user, x, y, judge))
			{
				win_flag = false;
				break;
			}
			if(i)
			{
				DisplayMatrix(&matrix_user);
			}
			i=0;
		}
		if(win_flag)
		{
			printf("You Win !\n");
		}
		printf("Play again ?\n");
		printf("1.yes 2.no\n");
		scanf("%d", &play_flag);
	}
}
