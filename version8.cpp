 #include<stdio.h> 
 #include<math.h> 
 #include<time.h> 
 #include<stdlib.h> 
 #include<string.h> 
  
//矩阵最大100*100
 #define m_max 100 
 #define n_max 100 
  
//排行榜最大人数
 #define max_players 5  
  
//矩阵结构体
 typedef struct{ 
 	unsigned int m; 
 	unsigned int n; 
 	char array[m_max][n_max]; 
 }Matrix; 
  
 //玩家结构体
 typedef struct{ 
 	char name[20]; 
 	int time; 
 }Player; 
  
 //任务枚举
 enum assignment{
	menu,
	show_score,
	play_saolei,
	guess_number,
	exit_system
 };

 //显示给计算机看的矩阵
 Matrix matrix_saolei; 

 //显示给玩家看的矩阵
 Matrix matrix_user; 
  

 Player players[20]; 
  

//创建m*n大小的零矩阵
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
  
 //创建m*n显示给玩家看的矩阵
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
  
 //部雷
 /*
	matrix: 矩阵
	num_bomb: 雷数
	x: 初始位置横坐标
	y: 初始位置纵坐标
 */
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
  
 //判断位置（i，j）是否在矩阵中
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
  
 //计算每个点周围的雷数
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
  
 //显示扫雷矩阵
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
  
 //显示周围的安全地形
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
 
 //对玩家输入的x，y坐标和判断进行数据处理
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
 			if(matrix_user->array[x-1][y-1]=='#')  
 			{ 
 				matrix_user->array[x-1][y-1] = '@'; 
 			} 
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
 			if(matrix_user->array[x-1][y-1]=='#')  
 			{ 
 				matrix_user->array[x-1][y-1] = '@'; 
 			} 
 		} 
 	} 
 	return true; 
 } 
  
 //判断是否游戏结束
 bool JudgeWin(Matrix *matrix_saolei, Matrix *matrix_user) 
 { 
 	unsigned int i = 0, j = 0; 
	bool result=true;
 	for(i=0; i<matrix_saolei->m; i++) 
 	{ 
 		for(j=0; j<matrix_saolei->n; j++) 
 		{ 
 			if(matrix_saolei->array[i][j]=='*') 
 			{ 
 				if(matrix_user->array[i][j]!='@') 
 				{ 
 					result = false; 
 				} 
 			} 
			if(matrix_saolei->array[i][j]!='*') 
			{
				if(matrix_user->array[i][j]=='@' || matrix_user->array[i][j]=='#') 
				{
					result = false;
				}
			}
 		} 
 	} 
 	return result; 
 } 
  
 //主函数
 void main(void) 
 { 
	int mode=0;
 	unsigned int x, y; 
 	unsigned int m, n; 
 	unsigned int num_bombs; 
 	bool win_flag = true; 
 	int play_flag = 1; 
 	int judge; 
 	int i = 1; 
 	char name[20]; 
 	time_t start_time, end_time; 
 	int player = 0; 
 	int index = 0; 
 	int min_time_index; 
 	int max_time_index; 
 	int num; 
	int read_index = 0;
	int char_index = 0;
	int now_task = menu;
	char back_flag;
	int guess_number_max;
	int guess_number_min;
	int number_guess;
	int answer;
	int number_guess_play_again;
	bool guess_true = false;
	//读入排行榜
	FILE *fp;
	fp = fopen("score.txt", "r+");
	while(!fp)
	{
		printf("you build a new file!\n");
		fp = fopen("score.txt", "w+");
	}
	while(!feof(fp))
	{
		fgetc(fp);
		fgetc(fp);
		fgetc(fp);
		fgetc(fp);
		fgetc(fp);
		for(char_index=0;char_index<10;char_index++)
		{
			fscanf(fp, "%c", &players[read_index].name[char_index]);
		}		
		fscanf(fp, "%d", &players[read_index].time);
		fgetc(fp);
		if(players[read_index].time!=0)
		{
			read_index ++;
			player++;
		}
	}
	fclose(fp);
	while(1)
	{
		//显示排行榜任务
		if(now_task == show_score)
		{
			system("cls");
			for(num = 0; num<=max_players - 1;num++) 
 			{ 
				printf("number: %5d, name = %-10s, time = %ds\n", num+1, players[num].name, players[num].time); 
 			} 
			printf("input any key to back.\n");
			fflush(stdin);
			scanf("%c", &back_flag);
			now_task = menu;
		}
		//玩扫雷任务
 		if(now_task == play_saolei) 
		{ 
			system("cls");
			printf("Please input your name:\n"); 
			fflush(stdin); 
			gets(name);
			while(strlen(name)>10 || strlen(name)<=1)
			{
				printf("your name is too long or too short!\n");
				fflush(stdin);
				gets(name);
			}
 			printf("your name is: %s\n", name); 
 			printf("Please input the area of m, n and the number of bombs:\n"); 
 			scanf("%d%d%d", &m, &n, &num_bombs); 
 			while(num_bombs > m*n*0.75 || num_bombs == 0) 
 			{ 
				fflush(stdin);
 				printf("Bombs is too much or there is no bomb!\n"); 
 				printf("Please input the area of m, n and the number of bombs:\n"); 
 				scanf("%d%d%d", &m, &n, &num_bombs); 
 			} 
 			CreatMatrixZero(&matrix_saolei, m, n); 
			system("cls");
 			CreatMatrixUser(&matrix_user, m, n); 
 			printf("Please input x y and judge:\n"); 
			fflush(stdin);
 			scanf("%d%d%d", &x, &y, &judge); 
			while(x>m || y>n || (judge!=0&&judge!=1)) 
			{
				fflush(stdin);
				printf("Input error !\n"); 
				printf("Please input x y and judge:\n"); 
				scanf("%d%d%d", &x, &y, &judge); 
			}
 			PlaceBombs(&matrix_saolei, num_bombs, x, y); 
 			ComputeBombs(&matrix_saolei); 
 			time(&start_time); 
 			printf("start time = %ds\n", start_time); 
 			JudgeBombs(&matrix_saolei, &matrix_user, x, y, judge); 
			system("cls");
 			DisplayMatrix(&matrix_user); 
 			while(!JudgeWin(&matrix_saolei, &matrix_user)) 
 			{ 
 				printf("Please input x y and judge:\n"); 
 				scanf("%d%d%d", &x, &y, &judge); 
 				while(x>m || y>n || (judge!=0&&judge!=1)) 
 				{ 
					fflush(stdin);
 					printf("Input error !\n"); 
 					printf("Please input x y and judge:\n"); 
 					scanf("%d%d%d", &x, &y, &judge); 
 				} 
 				i=1; 
 				if(!JudgeBombs(&matrix_saolei, &matrix_user, x, y, judge)) 
 				{ 
					//loss
 					win_flag = false; 
 					break; 
 				} 
				//只显示一次用户矩阵
 				if(i) 
 				{ 
					system("cls");
 					DisplayMatrix(&matrix_user); 
 				} 
 				i=0; 
 			} 
			//如果赢了
 			if(win_flag) 
 			{ 
 				printf("You Win !\n"); 
 				time(&end_time); 
 				printf("end time = %ds\n", end_time); 
 				strcpy(players[player].name, name); 
 				players[player].time = end_time - start_time; 
 				printf("time = %ds\n", end_time - start_time); 
 				player ++; 
				//排序
				//如果排行榜满了
 				if(player == max_players + 1) 
 				{ 
					//用时最长的被踢出排行榜
 			  		player = max_players; 
 					//fimd time max 
 					max_time_index = 0; 
 					for(index=0;index<=max_players;index++) 
 					{ 
 						if(players[index].time>players[max_time_index].time) 
 						{ 
 							max_time_index = index; 
 						} 
 					} 
 					//copy the last player's data to the max time's player 
 					strcpy(players[max_time_index].name, players[max_players].name); 
 					players[max_time_index].time = players[max_players].time; 
					//排名
 					for(num = 0; num<=max_players - 1;num++) 
 					{ 
 						min_time_index = num; 
 				 
 						for(index=num;index<=max_players - 1;index++) 
 						{ 
 							if(players[index].time<players[min_time_index].time) 
 					  		{ 
 								min_time_index = index; 
 							} 
 						} 
 						strcpy(players[max_players].name, players[num].name); 
 						players[max_players].time = players[num].time; 
 						strcpy(players[num].name, players[min_time_index].name); 
 						players[num].time = players[min_time_index].time; 
 						strcpy(players[min_time_index].name, players[max_players].name); 
 						players[min_time_index].time = players[max_players].time; 
 					 } 
 				} 
				//如果排行榜没满
 				else 
 				{ 
 					for(num = 0; num<=player - 1; num++) 
 					{ 
 						min_time_index = num; 
 				 
 						for(index=num;index<=player - 1;index++) 
 						{ 
 							if(players[index].time<players[min_time_index].time) 
 				  			{ 
 								min_time_index = index; 
 							} 
 						} 
 						strcpy(players[player].name, players[num].name); 
 						players[player].time = players[num].time; 
 						strcpy(players[num].name, players[min_time_index].name); 
 						players[num].time = players[min_time_index].time; 
 						strcpy(players[min_time_index].name, players[player].name); 
 						players[min_time_index].time = players[player].time; 
 					} 
 					strcpy(players[player].name, ""); 
 					players[player].time = 0; 
 				} 
				//写入文件
				fp = fopen("score.txt", "w+");
 				for(num = 0; num<=max_players - 1;num++) 
 				{ 
 					//printf("number: %5d, name = %-10s, time = %ds\n", num+1, players[num].name, players[num].time); 
					fprintf(fp, "%-5d%-10s\t%d\n", num+1, players[num].name, players[num].time);
 				} 
				fclose(fp);
 			} 
 			printf("Play again ?\n"); 
 			printf("1.yes 2.no\n"); 
 			scanf("%d", &play_flag); 
 			printf("\n"); 
			if(play_flag==1)
			{
				now_task = play_saolei;
			}
			else
			{
				now_task = menu;
			}
 		} 
		//主菜单任务
		if(now_task == menu)
		{
			system("cls");
			printf("meun:\n");
			printf("1.play\n");
			printf("2.score\n");
			printf("3.ai guess number\n");
			printf("4.exit\n");
			scanf("%d", &mode);
			switch(mode)
			{
			case 1:
				now_task = play_saolei;
				break;
			case 2:
				now_task = show_score;
				break;
			case 3:
				now_task = guess_number;
				break;
			case 4:
				now_task = exit_system;
				break;
			}
		}
		if(now_task == exit_system)
		{
			exit(0);
		}
		//猜数字任务
		if(now_task == guess_number)
		{
			system("cls");
			fflush(stdin);
			printf("please input the range of number,max,min\n");
			scanf("%d%d",&guess_number_max, &guess_number_min);
			while(guess_number_max<=guess_number_min)
			{
				printf("input error! max < min\n");
				fflush(stdin);
				scanf("%d%d",&guess_number_max, &guess_number_min);
			}
			while(!guess_true)
			{
				if(guess_number_max==guess_number_min)
				{
					number_guess = guess_number_max;
				}
				else
				{
					number_guess = rand()%(guess_number_max-guess_number_min)+guess_number_min;
				}
				printf("I guess the number is %d\n", number_guess);
				printf("samll or big or true?\n");
				printf("1.small, 2.big, 3.true\n");
				fflush(stdin);
				scanf("%d",&answer);
				switch(answer)
				{
				case 1:
					guess_number_min = number_guess + 1;
					break;
				case 2:
					guess_number_max = number_guess - 1;
					break;
				case 3:
					guess_true= true;
					break;
				}
				if(guess_number_max < guess_number_min)
				{
					printf("Error! Fuck you !\n");
					break;
				}
			}
			guess_true = false;
			printf("play again?\n");
			fflush(stdin);
			printf("1.yes, 2.no\n");
			scanf("%d",&number_guess_play_again);
			if(number_guess_play_again==2)
			{
				now_task = menu;
			}
		}
	}
 } 
