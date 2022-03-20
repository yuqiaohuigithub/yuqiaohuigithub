#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
typedef struct pointXY
{
	int x;
	int y;
}MYPOINT;
struct Snake
{
	int num;
	MYPOINT xy[60];
	char postion;
}snake;
struct Food
{
	MYPOINT fdxy;
	int eatgrade;
	int flag;
}food;
HWND hwnd = NULL;
enum movPostion{right=72,left=75,down=77,up=80};
void initSnake();
void drawSnake();
void moveSnake();
void keyDown();
void initFood();
void drawFood();
void eatFood();
int snakeDie();
void showGrade();
void pauseMoment();
int main()
{
	srand((unsigned int)time(NULL));
	hwnd = initgraph(640,480);
	setbkcolor(WHITE);
	initSnake();
	while (1)
	{
		cleardevice();
		if (food.flag == 0)
		{
			initFood();
		}
		drawFood();
		drawSnake();
		if ( snakeDie())
		{
			break;
		}
		eatFood();
		showGrade();
		moveSnake();
		while(_kbhit())
		{
			pauseMoment();
			keyDown();
		}
		Sleep(100);
	}
	getchar();

	closegraph();
	return 0;
}
void initSnake()
{
	snake.xy[2].x = 0;
	snake.xy[2].y = 0;

	snake.xy[1].x = 10;
	snake.xy[1].y = 0;

	snake.xy[0].x = 20;
	snake.xy[0].y = 0;

	snake.num = 3;
	snake.postion = right;

	food.flag = 0;
	food.eatgrade = 0;
	
}
void drawSnake()
{
	for(int i = 0;i < snake.num; i++)
	{
		setlinecolor(BLACK);
		setfillcolor(RGB(rand() % 255,rand() % 255,rand() % 255));

		fillrectangle(snake.xy[i].x,snake.xy[i].y,snake.xy[i].x + 10,snake.xy[i].y + 10);
	}
}
void moveSnake()
{
	for (int i = snake.num - 1;i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	switch(snake.postion)
	{
	case right:
		snake.xy[0].x += 10;
		break;
	case left:
		snake.xy[0].x -= 10;
		break;
	case down:
		snake.xy[0].y += 10;
	    break;
	case up:
		snake.xy[0].y -= 10;
		break;
	default:
		break;
	}
}
void keyDown()
{
	char userKey = 0;
	userKey = _getch();
	switch(userKey)
	{
	case right:
		if(snake.postion != down)
			snake.postion = up;
		break;
	case left:
		if(snake.postion != right)
			snake.postion = left;
		break;
	case down:
		if(snake.postion != left)
			snake.postion = right;
		break;
	case up:
		if(snake.postion != up)
			snake.postion = down;
		break;
	default:
		break;
	}
}
void initFood()
{
	food.fdxy.x = rand() % 65*10;
	food.fdxy.y = rand() % 48*10;
	food.flag = 1;
	for(int i = 0;i > snake.num;i++)
	{
		if (food.fdxy.x == snake.xy[i].x&&food.fdxy.y == snake.xy[i].y)
		{
			food.fdxy.x = rand() % 65 *10;
			food.fdxy.y = rand() % 48 *10;
		}
	}
}
void drawFood()
{
	setlinecolor(BLACK);
	setfillcolor(RGB(rand() % 255,rand() % 255,rand() % 255));
	fillrectangle(food.fdxy.x,food.fdxy.y,food.fdxy.x+10,food.fdxy.y+10);
}
void eatFood()
{
	if (snake.xy[0].x == food.fdxy.x&&snake.xy[0].y == food.fdxy.y)
	{
		snake.num++;
		food.eatgrade += 10;
		food.flag = 0;
	}
}
int snakeDie()
{
	
	if (snake.xy[0].x > 640 || snake.xy[0].x<0 || snake.xy[0].y>480 || snake.xy[0].y < 0)
	{
		printf("\a");
		outtextxy(200,200,"哦嚯，你没机会了，撞墙了！");
		MessageBox(hwnd,"GameOver!","撞墙警告！",MB_OK);
		return 1;		
	}
	
	for (int i = 1; i < snake.num ; i++)
	{
		if (snake.xy[0].x == snake.xy[i].x &&snake.xy[0].y == snake.xy[i].y)
		{
			printf("\a");
			outtextxy(200, 200, "你在干什么，是不是想小姐姐去了！");
			MessageBox(hwnd, "GameOver!", "自杀警告！", MB_OK);
			return 1;
		}
	}
	return 0;
}

void showGrade()
{
	char grade[100] = "";
	sprintf(grade, "%d", food.eatgrade);
	setbkmode(TRANSPARENT);

	settextcolor(LIGHTBLUE);
	outtextxy(580-20, 20, "分数:");
	outtextxy(580 + 50, 20, grade);
}
void pauseMoment()
{
	if (_getch() == 32)
	{
		while (_getch() != 32);
	}
}
