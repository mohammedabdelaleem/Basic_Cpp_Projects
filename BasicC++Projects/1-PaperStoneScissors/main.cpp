/*  for(;;)cout<<"الحمد لله\n";  */
#include <iostream> //cin ,cout
#include <stdlib.h>//srand
#include <time.h> //time
#include <windows.h> // Sleep
#include <cstdlib>  // cls

using namespace std;

// paper>stone , stone>scissors , scissors>paper
enum enGameChoice {Stone=1, Paper=2, Scissors=3};
enum enWinner {Player1=1, Computer=2, Draw=3};

struct stRoundInfo
{
    short RoundNumber=0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResult
{
    short NumberOfRounds=0;
    short  Player1WinTimes;
    short  ComputerWinTimes;
    short  DrawTimes;
    enWinner GameWinner;
    string WinnerName="";
};

void moveCursor(int row, int col){/////////////
  cout << "\033[" << row << ";" << col << "H"; //33 Escape character
}

inline void load(int time)
{
    moveCursor(25,48);
    cout << "\t--->Loading";
    for( int i = 0 ; i < time ; i++ )
    {
        if( (i+1) != time )
        {
            Sleep(250);//250*10^3sec
            cout << ".";
        }
        else
        {
            Sleep(250);
            cout << ":-)";
            Sleep(350);
        }
    }
     system("cls");
}

void ResetNormalBkColor()
{
    system("cls");
    system("Color 0f");
}

short RandomNumber(short From,short To)
{
    //function To Generate Random Number
    return (rand() %(To-From+1) + 1);
}

short ReadHowManyRounds()
{
    short GameRounds=1;
    do
    {
        cout<<"How Many Rounds 1 To 10 : ";
        cin>>GameRounds;
    }
    while(GameRounds<1 || GameRounds>10);
    return GameRounds;
}

enGameChoice ReadPlayer1Choice()
{
    short Player1Choice=1;
    do
    {
        cout<<"Your Choice: [1]Stone    [2]Paper    [3]Scissors ? ";
        cin>>Player1Choice;
    }
    while(Player1Choice<1 || Player1Choice>3);

    return (enGameChoice)Player1Choice;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice) RandomNumber(1,3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if(RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    //when Computer Win
    switch(RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone :
        if(RoundInfo.ComputerChoice == enGameChoice::Paper)
            return enWinner::Computer;

    case enGameChoice::Scissors :
        if(RoundInfo.ComputerChoice == enGameChoice::Stone)
            return enWinner::Computer;

    case enGameChoice::Paper :
        if(RoundInfo.ComputerChoice == enGameChoice::Scissors)
            return enWinner::Computer;
    }
    //if You reach here ,then Player1 is Win
    return enWinner::Player1;
}

string WinnerName(enWinner Winner)
{
    string arrWinnerNames[3]= {"Player1", "Computer","No Winner"};
    return arrWinnerNames[Winner-1]; //0_index
}

string ChoiceName(enGameChoice Choice)
{
    string arrChoiceName[3]= {"Stone","Paper","Scissors"};
    return arrChoiceName[Choice-1];
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch(Winner)
    {
    case enWinner::Player1 :
        system("Color 2f");//Green Bk Color
        break;

    case enWinner::Computer :
        system("Color 4f");//Red Bk Color
        cout<<"\a";
        break;

    case enWinner::Draw :
        system("Color 6f");//Yellow Bk Color
        break;
    }
}

string Tab(short NumberOfTabs)
{
    string t="";
    for(short i=1;i<=NumberOfTabs;i++)
        t+="\t";

    return t;
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
    cout<<"\n\n"<<Tab(3)<<"--------------Round["<<RoundInfo.RoundNumber<<"]-----------\n\n";
    cout<<Tab(3)<<"Player1 Choice  : "<<ChoiceName(RoundInfo.Player1Choice)<<endl;
    cout<<Tab(3)<<"Computer Choice : "<<ChoiceName(RoundInfo.ComputerChoice)<<endl;
    cout<<Tab(3)<<"Round Winner    : ["<<RoundInfo.WinnerName<<"]\n";
    cout<<"\n"<<Tab(3)<<"---------------------------------\n\n";

    SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short Player1WinTimes,short ComputerWinTimes)
{
    if(Player1WinTimes>ComputerWinTimes)
        return enWinner::Player1;

    else if(Player1WinTimes<ComputerWinTimes)
        return enWinner::Computer;

    return enWinner::Draw;
}

stGameResult FillGameResults(short NumberOfRounds,short Player1WinTimes,short ComputerWinTimes,short DrawTimes)
{
    stGameResult GameResults;

    GameResults.NumberOfRounds=NumberOfRounds;
    GameResults.Player1WinTimes=Player1WinTimes;
    GameResults.ComputerWinTimes=ComputerWinTimes;
    GameResults.DrawTimes=DrawTimes;
    GameResults.GameWinner=WhoWonTheGame(Player1WinTimes,ComputerWinTimes);
    GameResults.WinnerName=WinnerName(GameResults.GameWinner);

    return GameResults;
}

stGameResult PlayGame(short NumberOfRounds)
{
    load(7);
    stRoundInfo RoundInfo;
    short Player1WinTimes=0, ComputerWinTimes=0,DrawTimes=0;

    for(short GameRound=1 ; GameRound<=NumberOfRounds ; GameRound++)
    {
        cout<<"\nRound ["<<GameRound<<"] Begins:"<<Tab(2)<<"Total Rounds["<<NumberOfRounds<<"]\n";
        cout<<"-------------------------------------------------------\n";
        RoundInfo.RoundNumber=GameRound;
        RoundInfo.Player1Choice=ReadPlayer1Choice();
        RoundInfo.ComputerChoice=GetComputerChoice();
        RoundInfo.Winner=WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName=WinnerName(RoundInfo.Winner);

        //Increase Win/Draw
        if(RoundInfo.Winner==enWinner::Player1)
            Player1WinTimes++;
        else if(RoundInfo.Winner==enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResult(RoundInfo);
        load(10);
        ResetNormalBkColor();
    }

    return FillGameResults(NumberOfRounds,Player1WinTimes,ComputerWinTimes,DrawTimes);
}

void ResetScreen()
{
    system("cls");
    system("Color 0f");
}

void ShowGameOverScreen()
{
    cout<<Tab(2)<<"-------------------------------------------------\n\n";
    cout<<Tab(2)<<"               +++ G a m e  O v e r +++           \n\n ";
    cout<<Tab(2)<<"-------------------------------------------------\n\n";
}

void ShowFinalGameResult(stGameResult GameResult)
{
    cout<<Tab(2)<<"-----------[Game Results]--------------------\n\n";
    cout<<Tab(2)<<"Game Rounds        : "<<GameResult.NumberOfRounds<<endl;
    cout<<Tab(2)<<"Player1 Won Times  : "<<GameResult.Player1WinTimes<<endl;
    cout<<Tab(2)<<"Computer Won Times : "<<GameResult.ComputerWinTimes<<endl;
    cout<<Tab(2)<<"Draw Times         : "<<GameResult.DrawTimes<<endl;
    cout<<Tab(2)<<"Final Winner       : "<<GameResult.WinnerName<<endl;
    cout<<Tab(2)<<"----------------------------------------------\n\n";

    SetWinnerScreenColor(GameResult.GameWinner);
}

void StartGame()
{
    char PLayAgain='N';
    do
    {
        ResetScreen();
        stGameResult GameResult=PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResult(GameResult);

        cout<<endl<<Tab(3)<<"Do You Want To Play Again[Y/N]?: ";
        cin>>PLayAgain;
       cout<<endl<<endl;

       if(PLayAgain=='Y' || PLayAgain=='y')load(7);
    }
    while(PLayAgain=='Y' || PLayAgain=='y');
}

using namespace std;

int main()
{
    //seeds random number generator,called only once
    srand((unsigned)time(NULL));

    StartGame();
    return 0;
}










/*
colors Bk Text
0 = Black
1 = Blue
2 = Green
3 = Aqua
4 = Red
5 = Purple
6 = Yellow
7 = White
8 = Gray
9 = Light Blue
A = Light Green
B = Light Aqua
C = Light Red
D = Light Purple
E = Light Yellow
F = Bright White
*/
