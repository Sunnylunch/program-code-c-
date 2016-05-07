#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void chess_board(char arr[3][3])
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 3; i++)
	{
		printf(" %c | %c | %c \n", arr[i][0], arr[i][1], arr[i][2]);
		if (i<2)
			printf("---|---|---\n");
	}
}


int success_or_failure(char arr[3][3])
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 3; i++)
	{
		if ((arr[i][0] == arr[i][1]) && (arr[i][j] == arr[i][2]))
		{
			if (arr[i][0] == '#')
				return 1;
			else if (arr[i][0] == '0')
				return -1;
		}
	}
	
	
	
	for (j = 0; j < 3; j++)
	{
		if ((arr[0][j] == arr[1][j]) && (arr[1][j] == arr[2][j]))
		{
			if (arr[0][j] == '#')
				return 1;
			else if (arr[0][j] == '0')
				return -1;
		}
	}
	
	
	if ((arr[0][0] == arr[1][1]) && (arr[0][0] == arr[2][2]))
	{
		if (arr[1][1] == '#')
			return 1;
		else if (arr[1][1] == '0')
			return -1;
	}
	if ((arr[0][2] == arr[1][1]) && (arr[0][2] == arr[2][0]))
	{
		if (arr[1][1] == '#')
			return 1;
		else if (arr[1][1] == '0')
			return -1;
	}
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (arr[i][j] == ' ')
			return 0;
		}
	}
	return -2;
}



int user_game(char arr[3][3])
{
	int x = 0;
	int y = 0;
	while (1)
	{
		printf("please user input:(x, y) ");
		scanf("%d%d", &x, &y);
		printf("\n");
		if ((x<1 && x>3) || (y<1 && y>3))
		{
		    printf("地址无效，请重新输入\n");
			break;
        }
		if (arr[x - 1][y - 1] == ' ')
		{
			arr[x - 1][y - 1] = '#';
			break;
		}
		printf("地址无效，请重新输入\n");
	}
	chess_board(arr);
	int ret=success_or_failure(arr);
	return ret;
}



int computer_game(char arr[3][3])
{
	printf("computer input:\n\n");
	int x = 0;
	int y = 0;
	while (1)
	{
		srand((unsigned)time(NULL));
		x = rand() % 3;
		srand((unsigned)time(NULL));
	    y = rand() % 3;
		if (arr[x][y] == ' ')
			break;
	}
	arr[x][y]= '0';
	chess_board(arr);
	int ret=success_or_failure(arr);
	return ret;
}




int main()
{
	printf("***************************\n");
	printf("***************************\n");
	printf("*******             *******\n");
	printf("*******1.go   0.exit*******\n");
	printf("*******             *******\n");
	printf("***************************\n");
	printf("***************************\n\n\n");
	char arr[3][3];
	while (1)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				arr[i][j] = ' ';
			}
		}
		int count = 0;
		printf("\nplease choice:1 or 0 : ");
		scanf("%d", &count);
		if (count == 0)
		{
			exit(EXIT_FAILURE);
		}
		else if (count == 1)
		{
			printf("\n****游戏开始****\n\n");
			while (1)
			{
				int n1 = user_game(arr);
				{
					if (n1 == 1)
					{
						printf("****恭喜玩家赢了****\n");
						break;
					}
				}
				int n2 = computer_game(arr);
				{
					if (n2 == -1)
					{
						printf("****电脑赢了****\n");
						break;
					}
				}
				if ((n1 == -2) || (n2 == -2))
				{
					printf("*****平局******\n");
					break;
				}
			}
		}
		printf("再来一局\n\n");
	}
	return 0;
}
