#include <iostream>
#include <windows.h>

using namespace std;

char Player='X';
char Matrix[3][3]= {'1','2','3','4','5','6','7','8','9'};

//a first basic function
void Drow()
{
    system("cls");// clean screen after any operation we do.
    cout<<" -------\n";
    for(int r=0; r<3; r++)
    {
        cout<<"| ";
        for(int c=0; c<3; c++)
        {
            cout<<Matrix[r][c]<<" ";
        }
        cout<<"|";
        cout<<endl;
    }
    cout<<" -------\n";
}

void Input()
{
    int pos;
    cout<<"Enter Your Position ("<<Player<<")\n";
    cin>>pos;
    for(int r=0; r<3; r++)
    {
        for(int c=0; c<3; c++)
        {
            if(Matrix[r][c]==pos+'0')
            {
                Matrix[r][c]=Player;
                break;
            }
        }
    }
    if(Player=='X')
        Player='O';
    else
        Player='X';
}
char CheckWinner()
{
    int x=0;
    int o=0;
    int counter=0;
    for(int r=0; r<3; r++)
    {
        for(int c=0; c<3; c++)
        {
            if(Matrix[r][c]=='X')
                x++;
            if(Matrix[r][c]=='O')
                o++;
            if(x==3)
                return 'X';
            if(o==3)
                return 'O';
        }
        x=0;
        o=0;
    }
    //-------------
    for(int c=0; c<3; c++)
    {
        for(int r=0; r<3; r++)
        {
            if(Matrix[r][c]=='X')
                x++;
            if(Matrix[r][c]=='O')
                o++;
            if(x==3)
                return 'X';
            if(o==3)
                return 'O';
        }
        x=0;
        o=0;
    }
    //------------
    if(Matrix[0][0]=='X' && Matrix[1][1]=='X' && Matrix[2][2]=='X')
        return 'X';
    if(Matrix[0][0]=='O' && Matrix[1][1]=='O' && Matrix[2][2]=='O')
        return 'O';
    //-----------
    if(Matrix[0][2]=='X' && Matrix[1][1]=='X' && Matrix[2][0]=='X')
        return 'X';
    if(Matrix[0][2]=='O' && Matrix[1][1]=='O' && Matrix[2][0]=='O')
        return 'O';
    //------------
    for(int r=0; r<3; r++)
    {
        for(int c=0; c<3; c++)
        {
            if(Matrix[r][c]!='X' && Matrix[r][c]!='O')
                counter++;
        }
    }
    if(counter==0)
        return '=';

    return '*'; // to check whether the Game continue
}

int main()
{
    while (CheckWinner() == '*')
    {
        Drow();
        Input();
        CheckWinner();
    }
    Drow();
    if (CheckWinner() == 'X')
        cout << "\nThe Winner Is Player X\n";
    if (CheckWinner() == '0')
        cout << "\nThe Winner Is Player O\n";
    if (CheckWinner() == '=')
        cout <<"\nNo Winner\n";

    return 0;
}
