#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

int x=700,y=350,X=50,Y=30,food=4,in=0,z=2,snake[100][2],speed=20,flag=0,foodx,foody,score=0;
int upperx=foodx+20;
int lowerx=foodx-20;
int uppery=foody+15;
int lowery=foody-15;

int screenWidth=1535,screenHeight=860;

void game_start();

using namespace std;

void splash_screen()
{

	initwindow(screenWidth, screenHeight, "",-3 , -3);
	rectangle(0, 0, screenWidth, screenHeight);
	floodfill(200,200,WHITE);
    //PlaySound("sound.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC | SND_LOOP);

	setbkcolor(WHITE);
	setcolor(RED);
	settextstyle(BOLD_FONT,HORIZ_DIR,10);

	outtextxy(570,370,"Snake");
	delay(2000);
	settextstyle(3,HORIZ_DIR,1);
	int i;
	char b[]="Press Enter key to continue";
    char d[100];
    char c;

    for(i=0;b[i]!='\0';i++)
    {
        d[i]=b[i];
        d[i+1]='\0';
        outtextxy(640,800, d);
        Sleep(50);
    }
    c=(char)getch();
    delay(100);
	cleardevice();

}
void environment1()
{
    rectangle(30,20,1505,750);
    for(int i=0;i<=5;i++)
        rectangle(30+i,20+i,1505-i,750-i);
}
void environment2()
{
    for(int j=0;j<=5;j++)
        rectangle(30+j,760+j,600-j,840-j);

}
void update_tail()
{
    int i;
    for(i=food;i>=0;i--)
    {
        snake[i+1][0]=snake[i][0];
        snake[i+1][1]=snake[i][1];
    }
}
void get_food()
{

    foodx=rand() % ((1490) - 40 + 1) + 40;
    foody=rand() % ((725) - 30 + 1) + 30;

    if(foodx%5 >5)
        foodx=foodx-foodx%5;
    if(foody%5 >5)
        foody=foody-foody%5;
}
void move()
{
    int i;
    switch(z)
    {
        case 1: snake[0][1]=snake[0][1]-Y;
                break;
        case 2: snake[0][0]=snake[0][0]+X;
                break;
        case 3: snake[0][1]=snake[0][1]+Y;
                break;
        case 4: snake[0][0]=snake[0][0]-X;
                break;
    }
    outtextxy(snake[food+1][0], snake[food+1][1], " ");
    outtextxy(snake[1][0], snake[1][1],"o");
    update_tail();
    delay(speed);
}
void updatesnake(char c)
{
    switch(c)
    {
        case 'w' :  if(z!=3)
                        z=1;
                    break;
        case 'd' : if(z!=4)
                        z=2;
                   break;
        case 's' : if(z!=1)
                        z=3;
                   break;
        case 'a' : if(z!=2)
                        z=4;
                   break;
    }
}
int snake_hit()
{
    upperx=foodx+20;
    lowerx=foodx-20;
    uppery=foody+15;
    lowery=foody-15;

    for(int i=2;i<=food;i++)
    {
        if(snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1])
        {
            flag=1;
            break;
        }
    }
    int z;
    if(snake[0][0] <= upperx && snake[0][0] >= lowerx && snake[0][1] <= uppery && snake[0][1] >= lowery)
    {
        PlaySound("Eat.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
        outtextxy(foodx, foody, " ");
        food++;
        score++;
        get_food();
        speed = speed - 1;
    }
    if(snake[0][0] <= 30 || snake[0][0] >= 1500 || snake[0][1] <= 15 || snake[0][1] >= 740)
    {
        flag=1;
    }
}
void restart_game()
{
    cleardevice();
    x=700;y=350;X=25;Y=30;food=4;in=0;z=2;speed=200;flag=0;foodx;foody;score=0;
    upperx=foodx+20;
    lowerx=foodx-20;
    uppery=foody+15;
    lowery=foody-15;
    snake[0][0]=700;
    snake[0][1]=350;

    screenWidth=1535;screenHeight=860;
    game_start();
}
int game_over()
{
    cleardevice();
    settextstyle(BOLD_FONT,HORIZ_DIR,10);

    PlaySound("Game Over.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);

	outtextxy(450,300,"GAME OVER");

	settextstyle(BOLD_FONT,HORIZ_DIR,4);
	char d[10];
	sprintf(d,"Your score is:- %d",score);

	outtextxy(600,500,d);
    settextstyle(EUROPEAN_FONT,HORIZ_DIR,1);
	outtextxy(565, 800, "Press enter to play again or esc to exit");
	char c;
	int valid=0;
	while(valid==0)
	{
	    c=(char)getch();
        int a=(int)c;
        if(a == 27)
            valid=1;
        else if(a == 13)
            restart_game();
	}
}
void game_start()
{
    //environment1();
    environment2();
    char c;
    setcolor(RED);
    get_food();
    int a,b;
    char d[10];
    while (flag == 0)
    {
        settextstyle(BOLD_FONT,HORIZ_DIR,5 );
        move();
        if(kbhit())
        {
            c=(char)getch();
            updatesnake(c);
        }
        snake_hit();
        settextstyle(BOLD_FONT,HORIZ_DIR, 5);
        outtextxy(foodx , foody, "@");
        sprintf(d," Score :- %d", score);
        outtextxy(40, 780, d);
        environment1();

    }
    int choice;
    game_over();
    closegraph();
}
int main()
{
    srand(time(NULL));
    snake[0][0]=x;
    snake[0][1]=y;
    splash_screen();
    game_start();
    return 0;
}
