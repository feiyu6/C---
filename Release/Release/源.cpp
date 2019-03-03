//本程序为五子棋1.1p
//操作方法wasd控制方向，空格下棋。 
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <graphics.h>

#define s 19 //定义棋盘大小

int math[s][s] = {};//棋盘计算判定胜负所用
int x = 9, y = 9,m,n;//光标所在处 
int player;//黑白轮流 
int time[s*s];//悔棋所用的步数计算数组
void un(int x, int y);//去除光标 
void draw(int x, int y);//表上光标 
void print(int x, int y);//显示当前棋盘状况  刷新咯 
void start();//开始界面函数 
void game();//双人对战模式函数 
void zairu();//读档函数
void cundang(int two, int three);//存档函数
void und(int x, int y);
void wgame();
int check(int x, int y);//判定胜负函数 
int wcheck(int x, int y);

int main()
{

	initgraph(800, 800);
	loadimage(NULL, "jzg.jpg", 800, 800);
	Sleep(1000);

	start();//载入开始游戏界面 
	while (1)
	{
		start();
	}
}

void start()
{
	loadimage(NULL, "xz.jpg", 800, 800);

	char a;
	do
	{
		a = _getch();
		if (a == '1')
			game();
		else
			if (a == '2')
			{
				zairu();
			}
			else
				if (a == '3')
					wgame();
				else if(a== '4')
					exit(0);
	} while (a != '1'&&a != '2'&&a != '3'&&a != '4');


}//开始界面写完咯

void game()
{
	setbkcolor(YELLOW);
	cleardevice();
	setfillcolor(BLACK);
	x = 9;
	y = 9;
	int input;
	int i, j;
	for (i = 0; i<19; i++)
		for (j = 0; j < 19; j++)
		{
			math[i][j] = 0;
			time[i * 19 + j] = -1;
		}
	player = 1;//1为黑2为白 
	int count = 0;//记载着回合数 

	for (i = 0; i < 19; i++)
	{
		setlinecolor(BLACK);
		line(40 + i * 40, 40, 40 + i * 40, 760);
		line(40, 40 + 40 * i, 760, 40 + 40 * i);
	}//画格子，经典的黑线
	draw(x, y);//光标移动到中心              

	while (1)//开始下棋          
	{
		input = _getch();//得到键盘输入 
		if (input == ' '&&math[x][y] == 0)//空格成功落子 
		{
			math[x][y] = player;
			time[count] = x * 19 + y;
			count++;
			print(x, y);
			if (check(x, y))//胜利判断 
			{

				if (player == 1)
					loadimage(NULL, "hq.jpg", 800, 800);
				else
					loadimage(NULL, "bq.jpg", 800, 800);
				getchar();
				break;
			}
			player = 3 - player;//黑白轮流 
		}
		else
			if (input == ' ')//空格落子失败 
			{
				continue;
			}
			else
				if (input == 'a')//上移动 
				{
					un(x, y);//清除原光标 
					x = x - 1;
					if (x<0)
						x = 18;
					draw(x, y);//显示新光标 
				}
				else
					if (input == 'd')
					{
						un(x, y);
						x = x + 1;
						if (x>18)
							x = 0;
						draw(x, y);
					}
					else
						if (input == 'w')
						{
							un(x, y);
							y = y - 1;
							if (y<0)
								y = 18;
							draw(x, y);
						}
						else
							if (input == 's')
							{
								un(x, y);
								y = y + 1;
								if (y>18)
									y = 0;
								draw(x, y);
							}
							else
								if (input == 'j')
								{
									cundang(player, count);
								}
								else
									if (input == 'h'&&count)
									{
										m = time[count - 1] / 19;
										n = time[count - 1] % 19;
										time[count - 1] = -1;
										und(m, n);//清除该位子的值
										player = 3 - player;
										count = count - 1;
									}
								else
								{
									continue;
								}
		if (count == 19 * 19)//666 
		{
			loadimage(NULL, "pj.jpg", 800, 800);
			getchar();
			break;
		}
	}
}//游戏进行函数写完咯   

void draw(int x, int y)
{
	if (player == 1)
		setfillcolor(BLACK);
	else if (player == 2)
		setfillcolor(WHITE);
	int pts1[] = { 40 * x + 20, 40 * y + 20,  40 * x + 36, 40 * y + 20,  40 * x + 20, 40 * y + 36 };
	solidpolygon((POINT*)pts1, 3);
	int pts2[] = { 40 * x + 20, 40 * y + 60,  40 * x + 20, 40 * y + 44,  40 * x + 36, 40 * y + 60 };
	solidpolygon((POINT*)pts2, 3);
	int pts3[] = { 40 * x + 60, 40 * y + 20,  40 * x + 44, 40 * y + 20,  40 * x + 60, 40 * y + 36 };
	solidpolygon((POINT*)pts3, 3);
	int pts4[] = { 40 * x + 60, 40 * y + 60,  40 * x + 60, 40 * y + 44,  40 * x + 44, 40 * y + 60 };
	solidpolygon((POINT*)pts4, 3);
}//画光标的函数写完咯 

void un(int x, int y)
{
	int pts1[] = { 40 * x + 20, 40 * y + 20,  40 * x + 36, 40 * y + 20,  40 * x + 20, 40 * y + 36 };
	clearpolygon((POINT*)pts1, 3);
	int pts2[] = { 40 * x + 20, 40 * y + 60,  40 * x + 20, 40 * y + 44,  40 * x + 36, 40 * y + 60 };
	clearpolygon((POINT*)pts2, 3);
	int pts3[] = { 40 * x + 60, 40 * y + 20,  40 * x + 44, 40 * y + 20,  40 * x + 60, 40 * y + 36 };
	clearpolygon((POINT*)pts3, 3);
	int pts4[] = { 40 * x + 60, 40 * y + 60,  40 * x + 60, 40 * y + 44,  40 * x + 44, 40 * y + 60 };
	clearpolygon((POINT*)pts4, 3);
}//清除光标的函数写完咯 

void print(int x, int y)
{
	if (player == 1)
		setfillcolor(BLACK);
	else if (player == 2)
		setfillcolor(WHITE);
	fillcircle(40 + 40 * x, 40 + 40 * y, 16);
}//画子函数end

int check(int x, int y)
{
	int a = 1, b = 1, c = 1, d = 1, i;         //a为上下，b为左右，c为从下到上，d为从上到下            
	for (i = 1; i<5; i++)
	{
		if (y + i<s&&math[x][y + i] == player)
			a++;
		else
			break;
	}
	for (i = 1; i<5; i++)
	{
		if (y - i >= 0 && math[x][y - i] == player)
			a++;
		else
			break;
	}
	if (a >= 5)
		return 1;
	for (i = 1; i<5; i++)
	{
		if (x + i<s&&math[x + i][y] == player)
			b++;
		else
			break;
	}
	for (i = 1; i<5; i++)
	{
		if (x - i >= 0 && math[x - i][y] == player)
			b++;
		else
			break;
	}
	if (b >= 5)
		return 1;

	for (i = 1; i<5; i++)
	{
		if (x + i<s&&y + i<s&&math[x + i][y + i] == player)
			c++;
		else
			break;
	}
	for (i = 1; i<5; i++)
	{
		if (x - i >= 0 && y - i >= 0 && math[x - i][y - i] == player)
			c++;
		else
			break;
	}
	if (c >= 5)
		return 1;
	for (i = 1; i<5; i++)
	{
		if (x + i<s&&y - i >= 0 && math[x + i][y - i] == player)
			d++;
		else
			break;
	}
	for (i = 1; i<5; i++)
	{
		if (x - i >= 0 && y + i<s&&math[x - i][y + i] == player)
			d++;
		else
			break;
	}
	if (d >= 5)
		return 1;
	return 0;
}//裁决函数写完咯 

void cundang(int two, int three)
{
	FILE *d;
	d = fopen("record.out", "wb");
	fwrite(math[0], sizeof(int), 19 * 19, d);
	fwrite(time, sizeof(int), 19 * 19, d);
	fwrite(&two, sizeof(int), 1, d);
	fwrite(&three, sizeof(int), 1, d);
	fclose(d);
}

void zairu()
{
	setbkcolor(YELLOW);
	cleardevice();
	setfillcolor(BLACK);
	int i, j;
	for (i = 0; i < 19; i++)
	{
		setlinecolor(BLACK);
		line(40 + i * 40, 40, 40 + i * 40, 760);
		line(40, 40 + 40 * i, 760, 40 + 40 * i);
	}//先弄棋盘
	FILE *d;
	d = fopen("record.out", "rb");
	fread(math[0], sizeof(int), 19 * 19, d);
	fread(time, sizeof(int), 19 * 19, d);//读取棋盘状况
	for (i = 0; i < 19; i++)
	{
		for (j = 0; j < 19; j++)
		{
			player = math[i][j];

			if (player != 0)
			{
				print(i, j);
			}
		}
	}
	x = 9;
	y = 9;
	int input;
	fread(&player, sizeof(int), 1, d);//读取执子方
	int count;
	fread(&count, sizeof(int), 1, d);//读取回合数
	fclose(d);
	draw(x, y);

	while (1)//开始下棋          
	{
		input = _getch();//得到键盘输入 
		if (input == ' '&&math[x][y] == 0)//空格成功落子 
		{
			math[x][y] = player;
			time[count] = x * 19 + y;
			count++;
			print(x, y);
			if (check(x, y))//胜利判断 
			{

				if (player == 1)
					loadimage(NULL, "hq.jpg", 800, 800);
				else
					loadimage(NULL, "bq.jpg", 800, 800);
				getchar();
				break;
			}
			player = 3 - player;//黑白轮流 
		}
		else
			if (input == ' ')//空格落子失败 
			{
				continue;
			}
			else
				if (input == 'a')//上移动 
				{
					un(x, y);//清除原光标 
					x = x - 1;
					if (x<0)
						x = 18;
					draw(x, y);//显示新光标 
				}
				else
					if (input == 'd')
					{
						un(x, y);
						x = x + 1;
						if (x>18)
							x = 0;
						draw(x, y);
					}
					else
						if (input == 'w')
						{
							un(x, y);
							y = y - 1;
							if (y<0)
								y = 18;
							draw(x, y);
						}
						else
							if (input == 's')
							{
								un(x, y);
								y = y + 1;
								if (y>18)
									y = 0;
								draw(x, y);
							}
							else
								if (input == 'j')
								{
									cundang(player, count);
								}
								else
									if (input == 'h'&&count)
									{
										m = time[count - 1] / 19;
										n = time[count - 1] % 19;
										time[count - 1] = -1;
										und(m, n);//清除该位子的值
										player = 3 - player;
										count = count - 1;
									}
								else
								{
									continue;
								}
		if (count == 19 * 19)//666 
		{
			loadimage(NULL, "pj.jpg", 800, 800);
			getchar();
			break;
		}
	}
}

void und(int x, int y)
{
	math[x][y] = 0;
	setbkcolor(YELLOW);
	clearcircle(40 + 40 * x, 40 + 40 * y, 17);
	if (x == 0 && y == 0)
	{
		line(40, 40, 57, 40);
		line(40, 40, 40, 57);
	}
	else
		if (x == 0 && y == 18)
		{
			line(40, 760, 57, 760);
			line(40, 760, 40, 743);
		}
		else
			if (x == 18 && y == 0)
			{
				line(760, 40, 760, 57);
				line(760, 40, 743, 40);
			}
			else
				if (x == 18 && y == 18)
				{
					line(760, 760, 760, 743);
					line(760, 760, 743, 760);
				}
				else
					if (x == 0)
					{
						line(40, 40 + 40 * y, 57, 40 + 40 * y);
						line(40, 57 + 40 * y, 40, 23 + 40 * y);
					}
					else
						if (x == 18)
						{
							line(743, 40 + 40 * y, 760, 40 + 40 * y);
							line(760, 23 + 40 * y, 760, 57 + 40 * y);
						}
						else
							if (y == 0)
							{
								line(40 + 40 * x, 40, 40 + 40 * x, 57);
								line(23 + 40 * x, 40, 57 + 40 * x, 40);
							}
							else
								if (y == 18)
								{
									line(40 * x + 40, 760, 40 * x + 40, 753);
									line(23 + 40 * x, 760, 57 + 40 * x, 760);
								}
								else
								{
									line(40 * x + 40, 23 + 40 * y, 40 * x + 40, 57 + 40 * y);
									line(23 + 40 * x, 40 + 40 * y, 57 + 40 * x, 40 + 40 * y);
								}

}

void wgame()
{
	setbkcolor(YELLOW);
	cleardevice();
	setfillcolor(BLACK);
	x = 9;
	y = 9;
	int input;
	int i, j;
	for (i = 0; i<19; i++)
		for (j = 0; j < 19; j++)
		{
			math[i][j] = 0;
		}
	player = 1;//1为黑2为白 
	int count = 0;//记载着回合数 

	for (i = 0; i < 19; i++)
	{
		setlinecolor(BLACK);
		line(40 + i * 40, 40, 40 + i * 40, 760);
		line(40, 40 + 40 * i, 760, 40 + 40 * i);
	}//画格子，经典的黑线
	draw(x, y);//光标移动到中心              

	while (1)//开始下棋          
	{
		input = _getch();//得到键盘输入 
		if (input == ' '&&math[x][y] == 0)//空格成功落子 
		{
			math[x][y] = player;
			count++;
			print(x, y);
			if (wcheck(x, y))
				player = 3 - player;
			player = 3 - player;//黑白轮流 
		}
		else
			if (input == ' ')//空格落子失败 
			{
				continue;
			}
			else
				if (input == 'a')//上移动 
				{
					un(x, y);//清除原光标 
					x = x - 1;
					if (x<0)
						x = 18;
					draw(x, y);//显示新光标 
				}
				else
					if (input == 'd')
					{
						un(x, y);
						x = x + 1;
						if (x>18)
							x = 0;
						draw(x, y);
					}
					else
						if (input == 'w')
						{
							un(x, y);
							y = y - 1;
							if (y<0)
								y = 18;
							draw(x, y);
						}
						else
							if (input == 's')
							{
								un(x, y);
								y = y + 1;
								if (y>18)
									y = 0;
								draw(x, y);
							}
							else
								if (input == 'j')
								{
									cundang(player, count);
								}
								else
								{
									continue;
								}
		if (count == 19 * 19)//666 
		{
			loadimage(NULL, "pj.jpg", 800, 800);
			getchar();
			break;
		}
	}
}//游戏进行函数写完咯 

int wcheck(int x, int y)
{
	int a = 1, b = 1, c = 1, d = 1, i, inx[5], iny[5];         //a为上下，b为左右，c为从下到上，d为从上到下            
	for (i = 1; i<5; i++)
	{
		if (y + i < s&&math[x][y + i] == player)
		{
			inx[a] = x;
			iny[a] = y + i;
			a++;
		}
		else
			break;
	}
	for (i = 1; i<5; i++)
	{
		if (y - i >= 0 && math[x][y - i] == player)
		{
			inx[a] = x;
			iny[a] = y - i;
			a++;
		}
		else
			break;
	}
	if (a >= 5) {
		for (i = 1; i < 5; i++)
		{
			und(inx[i], iny[i]);
		}
		und(x, y);
		return 1;
	}
	for (i = 1; i<5; i++)
	{
		if (x + i < s&&math[x + i][y] == player)
		{
			inx[b] = x + i;
			iny[b] = y;
			b++;
		}
		else
			break;
	}
	for (i = 1; i<5; i++)
	{
		if (x - i >= 0 && math[x - i][y] == player)
		{
			inx[b] = x - i;
			iny[b] = y;
			b++;
		}
		else
			break;
	}
	if (b >= 5)
	{
		for (i = 1; i < 5; i++)
		{
			und(inx[i], iny[i]);
		}
		und(x, y);
		return 1;
	}

	for (i = 1; i<5; i++)
	{
		if (x + i < s&&y + i < s&&math[x + i][y + i] == player)
		{
			inx[c] = x + i;
			iny[c] = y + i;
			c++;
		}
		else
			break;
	}
	for (i = 1; i<5; i++)
	{
		if (x - i >= 0 && y - i >= 0 && math[x - i][y - i] == player)
		{
			inx[c] = x - i;
			iny[c] = y - i;
			c++;
		}
		else
			break;
	}
	if (c >= 5)
	{
		for (i = 1; i < 5; i++)
		{
			und(inx[i], iny[i]);
		}
		und(x, y);
		return 1;
	}
	for (i = 1; i<5; i++)
	{
		if (x + i < s&&y - i >= 0 && math[x + i][y - i] == player)
		{
			inx[d] = x + i;
			iny[d] = y - i;
			d++;
		}
		else
			break;
	}
	for (i = 1; i<5; i++)
	{
		if (x - i >= 0 && y + i < s&&math[x - i][y + i] == player)
		{
			inx[d] = x - i;
			iny[d] = y + i;
			d++;
		}
		else
			break;
	}
	if (d >= 5)
	{
		for (i = 1; i < 5; i++)
		{
			und(inx[i], iny[i]);
		}
		und(x, y);
		return 1;
	}
	return 0;
}//裁决函数写完咯   und函数清除指定点


  
