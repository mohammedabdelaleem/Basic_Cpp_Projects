#include<iostream>
#include <graphics.h>
#include<climits>
#include<queue>
#include<fstream>
#include<typeinfo>
#include<stdlib.h>
#include<string>

using namespace std;

auto color=0;
int Colors[]= {BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY,
        LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, WHITE, LIGHTMAGENTA, YELLOW
};

//path for highScore file in my pc.
char path[]="D:\\University\\Coding\\My projects\\Snake\\highScore.txt";


//Snake Game Components.
const int EMPTY=0;
const int BODY=1;
const int APPLE=2;
const int WALL=3;
const int cell_size=18;

FILE*f;//for storing High Score
int score=0;
int highScore=0;

enum Direction {UP,DOWN,LEFT,RIGHT};
Direction snakeDirection=DOWN;
bool isGameOver=false;

//location for snake
struct location
{
    int r;
    int c;
};

bool isFireStarted;
location fireLcation;
Direction fireDirection;

queue<location>snakeBody;

//imaginary  board for you
int board[35][35] =
{
    {3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
};

void startWindow();
void initSnake();//draw snakeBody using for loop [because i need to push the location
void drawFire(int row,int col);
void eraseFire(int row,int col);
void drawSnakeBody(int row,int col);
void eraseSnakeBody(int row,int col);
void drawApple(int row,int col);
void drawWall(int row,int col);
location getNextfireLocation();
location getNextHead();
void MoveSnakeToNextLocation(location nh);
void printScore();
void MoveAndGrowSnake(location nh);
void generateNextApple();/////////
void GameOver();
void moveSnake();
void drawBoard();
void changeSnakeDirection(char ch);
void  startFire();
void  stopFire();
void  moveFire();
void checkKeyInput();

int main()
{
    startWindow();
    char ch = getch();
    //////////////////
    isGameOver=false;
    initwindow(630,630,"Snake Game");
    initSnake();

    drawBoard();

    int gameTimer=0;
    while(! isGameOver )//Game loop [loop for Ever]
    {

        if(gameTimer==INT_MAX)
            gameTimer=0;

        if(gameTimer%(500000)==0)
            moveFire();

        if(gameTimer%(5000000)==0)
            moveSnake();
        gameTimer++;

        checkKeyInput();
    }

    while(!kbhit());
    closegraph();

    return 0;
}
void initSnake()//draw snakeBody using for loop [because i need to push the location
{
 f=fopen(path,"r");
 fscanf(f,"%d",&highScore);
 fclose(f);

 char _highScore[]="";
 itoa(highScore,_highScore,10);
    //view Score and High Score in window.
    outtextxy(7*cell_size,0*cell_size,"Score:0");
    outtextxy(23.4*cell_size,0*cell_size,"High Score:");/////////
    outtextxy(27.59*cell_size,0*cell_size,_highScore);/////////

    location loc;
    loc.r=2;
    loc.c=10;

    for(int i=0; i<4; i++)
    {
        snakeBody.push(loc);
        board[loc.r][loc.c]=1;//don't forget it
        loc.r=loc.r+1;
    }
}

void drawFire(int row,int col)
{
    int x=col*cell_size;
    int y=row*cell_size;

    setfillstyle(SOLID_FILL,LIGHTCYAN);
    bar(x+2,y+2,x+15,y+15);
}

void eraseFire(int row,int col)
{
    int x=col*cell_size;
    int y=row*cell_size;

    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y,x+18,y+18);
}

void drawSnakeBody(int row,int col)
{
    int x=col*cell_size;
    int y=row*cell_size;

    setfillstyle(SOLID_FILL,Colors[color]);
    bar(x+1,y+1,x+17,y+17);
}

void eraseSnakeBody(int row,int col)
{
    int x=col*cell_size;
    int y=row*cell_size;

    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y,x+18,y+18);
}

void drawApple(int row,int col)
{
    int x=col*cell_size;
    int y=row*cell_size;

    readimagefile("C++.jpg",x+1,y+1,x+16,y+16);
}

void drawWall(int row,int col)
{
    int x=col*cell_size;
    int y=row*cell_size;

    setfillstyle(SOLID_FILL,LIGHTRED);
    bar(x+0,y+0,x+cell_size,y+cell_size);

    setcolor(BLACK);
    setlinestyle(SOLID_LINE,1,NORM_WIDTH);

    line(x+0,y+0,x+18,y+0);//left top right bottom
    line(x+0,y+9,x+18,y+9);
    line(x+0,y+18,x+18,y+18);

    line(x+12,y+0,x+12,y+9);
    line(x+6,y+9,x+6,y+18);
}

location getNextfireLocation()
{
    location nextFireloc = fireLcation;
    switch(snakeDirection)
    {
    case UP:
        nextFireloc.r-=1;
        break;

    case DOWN:
        nextFireloc.r+=1;
        break;

    case LEFT:
        nextFireloc.c-=1;
        break;

    case RIGHT:
        nextFireloc.c+=1;
        break;
    }
    return nextFireloc;
}

location getNextHead()
{
    location head =snakeBody.back();
    switch(snakeDirection)
    {
    case UP:
        head.r-=1;
        break;

    case DOWN:
        head.r+=1;
        break;

    case LEFT:
        head.c-=1;
        break;

    case RIGHT:
        head.c+=1;
        break;
    }
    return head;
}

void MoveSnakeToNextLocation(location nh)
{
    snakeBody.push(nh);
    drawSnakeBody(nh.r,nh.c);
    board[nh.r][nh.c]=1;//update 2D matrix

    location Tail=snakeBody.front();
    snakeBody.pop();
    eraseSnakeBody(Tail.r,Tail.c);
    board[Tail.r][Tail.c]=0;
    /*
    be sure from
    1-queue is Updated.
    2-screen is Updated.
    3-board is Updated.
    */
}

void printScore()
{
   setcolor(WHITE);
   char Score[]="";
   itoa(++score,Score,10);
   outtextxy(9.35*cell_size,0,Score);
}

void printHighScore()
{
   setcolor(WHITE);
   char HighScore[]="";
   itoa(highScore,HighScore,10);
   outtextxy(25*cell_size,0,HighScore);
}

void MoveAndGrowSnake(location nh)
{
    printScore();
    snakeBody.push(nh);
    drawSnakeBody(nh.r,nh.c);
    board[nh.r][nh.c]=1;//update 2D matrix
    color=rand()%14;
   }

void generateNextApple()/////////
{
    int r,c;
    do
    {
        r=rand()%(35-3+1)+3;//r,c belongs to [0,43]
        c=rand()%(35-0+1)+0;
    }
    while(board[r][c]!=EMPTY);
    drawApple(r,c);
    board[r][c]=APPLE;
}

void GameOver()
{
    isGameOver=true;
    ///////////////////////////

    initwindow(630,630,"Game Over");
    setbkcolor(WHITE);
    cleardevice();
    setcolor(RED);

    if(score>highScore)
    {
        highScore=score;
        f=fopen(path,"w") ;
        fprintf(f,"%d",score);
        fclose(f);
    }
    /////////////////////////
    //setcolor(WHITE);
    settextjustify(CENTER_TEXT,CENTER_TEXT);//TO MAKE FONT IN MIDDLE GAME
    settextstyle(TRIPLEX_FONT,HORIZ_DIR,5);//TO GROW THE FONT
    outtextxy(getmaxx()/2,(getmaxy()/2)-100,"GAME OVER");//TO MAKE FONT IN MIDDLE SCREEN

/*///////////////////print highScore under Game Over//////////////////////////
string s=to_string(highScore);
int y;
(s.size()<2 ?  y=11 : y=12);

char _HighScore[s.size()+y]="High Score: ";
for(int i=y ;i<s.size()+y;i++)
{
    _HighScore[i]=s[i-y];
}*/
setcolor(RED);
outtextxy((getmaxx()/2)-50,(getmaxy()/2)+100,"High Score: ");
char _highScore[]="";
itoa(highScore,_highScore,10);
outtextxy(((getmaxx()/2)+205)-40,(getmaxy()/2)+100,_highScore);

    string GameOver="GameOver.wav";
    PlaySound(GameOver.c_str(),NULL,SND_ASYNC);

     Sleep(2000);
    exit(0);
}


void moveSnake()
{
    location nh=getNextHead();
    string sound="appleSound.wav";
    switch(board[nh.r][nh.c])
    {
    case EMPTY:
        MoveSnakeToNextLocation(nh);
        break;

    case APPLE:
        PlaySound(sound.c_str(),NULL,SND_ASYNC);
        MoveAndGrowSnake(nh);
        generateNextApple();
        break;

    case WALL:
    case BODY:
        GameOver();
        break;
    }
}

void drawBoard()
{
    for(int r=0; r<35; r++)
    {
        for(int c=0; c<35; c++)
        {
            switch(board[r][c])
            {
            case EMPTY:
                break;

            case BODY:
                drawSnakeBody(r,c);
                break;

            case APPLE:
                drawApple(r,c);
                break;

            case WALL:
                drawWall(r,c);
                break;
            }
        }
    }
}

void changeSnakeDirection(char ch)
{
    switch(ch)
    {
    case KEY_UP:
        snakeDirection=UP;
        break;
    case KEY_DOWN:
        snakeDirection=DOWN;
        break;
    case KEY_LEFT:
        snakeDirection=LEFT;
        break;
    case KEY_RIGHT:
        snakeDirection=RIGHT;
        break;
    }
}

void  startFire()
{
    isFireStarted=true;
    fireLcation=getNextHead();
    fireDirection=snakeDirection;
    drawFire(fireLcation.r,fireLcation.c);

    string filesound="Fire.wav";
    PlaySound(filesound.c_str(),NULL,SND_ASYNC);
}

void  stopFire()
{
    isFireStarted=false;
    eraseFire(fireLcation.r,fireLcation.c);
}

void  moveFire()
{
    if(isFireStarted)
    {
        location nextFireLocation=getNextfireLocation();
if(nextFireLocation.r <= 1 || nextFireLocation.r >=34 || nextFireLocation.c <= 0 || nextFireLocation.c >=34 || board[nextFireLocation.r][nextFireLocation.c]==APPLE)
        {
            stopFire();
            return ;
        }
        drawFire(nextFireLocation.r,nextFireLocation.c);
        eraseFire(fireLcation.r,fireLcation.c);
        fireLcation = nextFireLocation ;
    }
}

void checkKeyInput()
{
//when we press on any key in keyboard ,it stores in buffer with its cipher and if you wanna know this character there's a built in function called kbhit() for that ,but if the key from arrow family it stores 0 + it's cipher
    char ch;
    if(kbhit())
    {
        ch = getch();
        if(ch==0)
        {
            ch = getch();
            changeSnakeDirection(ch);
        }
        else if(ch==32) //space bar is pressed.
        {
            if(!isFireStarted)
                startFire();
        }
    }
}

void startWindow()
{
    initwindow(630,630,"Snake Game with c++");
    setcolor(LIGHTRED);
    settextjustify(CENTER_TEXT,CENTER_TEXT);//TO MAKE FONT IN MIDDLE GAME
    settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);//TO GROW THE FONT
    outtextxy(getmaxx()/2,(getmaxy()/2)-200,"Eng\ M.Abd Elallem ");
    setcolor(RED);
    outtextxy(getmaxx()/2,getmaxy()/2,"Press Any Key To Start....");
}
