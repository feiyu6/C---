//������Ϊ������1.1p
//��������wasd���Ʒ��򣬿ո����塣 
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <graphics.h>

#define s 19 //�������̴�С

int math[s][s] = {};//���̼����ж�ʤ������
int x = 9, y = 9,m,n;//������ڴ� 
int player;//�ڰ����� 
int time[s*s];//�������õĲ�����������
void un(int x, int y);//ȥ����� 
void draw(int x, int y);//���Ϲ�� 
void print(int x, int y);//��ʾ��ǰ����״��  ˢ�¿� 
void start();//��ʼ���溯�� 
void game();//˫�˶�սģʽ���� 
void zairu();//��������
void cundang(int two, int three);//�浵����
void und(int x, int y);
void wgame();
int check(int x, int y);//�ж�ʤ������ 
int wcheck(int x, int y);

int main()
{

	initgraph(800, 800);
	loadimage(NULL, "jzg.jpg", 800, 800);
	Sleep(1000);

	start();//���뿪ʼ��Ϸ���� 
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


}//��ʼ����д�꿩

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
	player = 1;//1Ϊ��2Ϊ�� 
	int count = 0;//�����Żغ��� 

	for (i = 0; i < 19; i++)
	{
		setlinecolor(BLACK);
		line(40 + i * 40, 40, 40 + i * 40, 760);
		line(40, 40 + 40 * i, 760, 40 + 40 * i);
	}//�����ӣ�����ĺ���
	draw(x, y);//����ƶ�������              

	while (1)//��ʼ����          
	{
		input = _getch();//�õ��������� 
		if (input == ' '&&math[x][y] == 0)//�ո�ɹ����� 
		{
			math[x][y] = player;
			time[count] = x * 19 + y;
			count++;
			print(x, y);
			if (check(x, y))//ʤ���ж� 
			{

				if (player == 1)
					loadimage(NULL, "hq.jpg", 800, 800);
				else
					loadimage(NULL, "bq.jpg", 800, 800);
				getchar();
				break;
			}
			player = 3 - player;//�ڰ����� 
		}
		else
			if (input == ' ')//�ո�����ʧ�� 
			{
				continue;
			}
			else
				if (input == 'a')//���ƶ� 
				{
					un(x, y);//���ԭ��� 
					x = x - 1;
					if (x<0)
						x = 18;
					draw(x, y);//��ʾ�¹�� 
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
										und(m, n);//�����λ�ӵ�ֵ
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
}//��Ϸ���к���д�꿩   

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
}//�����ĺ���д�꿩 

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
}//������ĺ���д�꿩 

void print(int x, int y)
{
	if (player == 1)
		setfillcolor(BLACK);
	else if (player == 2)
		setfillcolor(WHITE);
	fillcircle(40 + 40 * x, 40 + 40 * y, 16);
}//���Ӻ���end

int check(int x, int y)
{
	int a = 1, b = 1, c = 1, d = 1, i;         //aΪ���£�bΪ���ң�cΪ���µ��ϣ�dΪ���ϵ���            
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
}//�þ�����д�꿩 

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
	}//��Ū����
	FILE *d;
	d = fopen("record.out", "rb");
	fread(math[0], sizeof(int), 19 * 19, d);
	fread(time, sizeof(int), 19 * 19, d);//��ȡ����״��
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
	fread(&player, sizeof(int), 1, d);//��ȡִ�ӷ�
	int count;
	fread(&count, sizeof(int), 1, d);//��ȡ�غ���
	fclose(d);
	draw(x, y);

	while (1)//��ʼ����          
	{
		input = _getch();//�õ��������� 
		if (input == ' '&&math[x][y] == 0)//�ո�ɹ����� 
		{
			math[x][y] = player;
			time[count] = x * 19 + y;
			count++;
			print(x, y);
			if (check(x, y))//ʤ���ж� 
			{

				if (player == 1)
					loadimage(NULL, "hq.jpg", 800, 800);
				else
					loadimage(NULL, "bq.jpg", 800, 800);
				getchar();
				break;
			}
			player = 3 - player;//�ڰ����� 
		}
		else
			if (input == ' ')//�ո�����ʧ�� 
			{
				continue;
			}
			else
				if (input == 'a')//���ƶ� 
				{
					un(x, y);//���ԭ��� 
					x = x - 1;
					if (x<0)
						x = 18;
					draw(x, y);//��ʾ�¹�� 
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
										und(m, n);//�����λ�ӵ�ֵ
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
	player = 1;//1Ϊ��2Ϊ�� 
	int count = 0;//�����Żغ��� 

	for (i = 0; i < 19; i++)
	{
		setlinecolor(BLACK);
		line(40 + i * 40, 40, 40 + i * 40, 760);
		line(40, 40 + 40 * i, 760, 40 + 40 * i);
	}//�����ӣ�����ĺ���
	draw(x, y);//����ƶ�������              

	while (1)//��ʼ����          
	{
		input = _getch();//�õ��������� 
		if (input == ' '&&math[x][y] == 0)//�ո�ɹ����� 
		{
			math[x][y] = player;
			count++;
			print(x, y);
			if (wcheck(x, y))
				player = 3 - player;
			player = 3 - player;//�ڰ����� 
		}
		else
			if (input == ' ')//�ո�����ʧ�� 
			{
				continue;
			}
			else
				if (input == 'a')//���ƶ� 
				{
					un(x, y);//���ԭ��� 
					x = x - 1;
					if (x<0)
						x = 18;
					draw(x, y);//��ʾ�¹�� 
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
}//��Ϸ���к���д�꿩 

int wcheck(int x, int y)
{
	int a = 1, b = 1, c = 1, d = 1, i, inx[5], iny[5];         //aΪ���£�bΪ���ң�cΪ���µ��ϣ�dΪ���ϵ���            
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
}//�þ�����д�꿩   und�������ָ����


  
