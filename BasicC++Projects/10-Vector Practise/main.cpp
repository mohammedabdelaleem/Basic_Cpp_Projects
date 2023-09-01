#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#define itn int
using namespace std;

bool CompareRight(int A, int B)
{
    return A<B;
}

vector<int>v{-45,54,0,9,-450,87,-10000,0,0,12,-87877,54541255,1200000};

void InterFace();

int main()
{
    InterFace();

    return 0;
}

void InterFace()
{
    int choice1,counter,value,key,idx,start,_end,new_size;

    char choice2;
    do
    {
        do
        {
            system("cls");
            cout<<"Vector Application in C++\n\n";
            cout<<"1-Adds an element x to the vector A at the end\n"<<
                "2-Adds an element x to the vector\n"<<
                "3-Erase An Element From the Back\n"<<
                "4-Erase An Element by index\n"<<
                "5-Erase From To\n"<<
                "6-Clear Vector\n"<<
                "7-Sorts the vector in an ascending order\n"<<
                "8-Sorts the vector in a descending order\n"<<
                "9-Reverses the vector \n"<<
                "10-Find Max Value\n"
                "11-Find Min Element\n"
                "12-prints the size of the vector\n"<<
                "13-prints the capacity of the vector\n"<<
                "14-prints space separated values of the vector\n"<<
                "15-Searching For Value\n"<<
                "16-Resize\n"
                "17-Print Min Max Elements\n"
                "18-Print The First Element In The Vector\n"
                "19-Print The Last Element In The Vector\n"
                "0-Exit\n\n";
            cout<<"Enter Your Choice:  ";
            cin>>choice1;
        }
        while((choice1<0 || choice1>16));

        switch(choice1)
        {
        case 0 :
            return ;
        case 1 :
            cout<<"How Many Times do you do that ? :  ";
            cin>>counter;
            for(auto i=1; i<=counter; i++)
            {
                cout<<"Enter value Number "<<i<<" : ";
                cin>>value;
                v.push_back(value);
            }
            cout<<"Addition Successfully\n";
            break;

        //////////////////////////////////////////////
        case 2 :
            cout<<"Enter An Index ";
            cin>>idx;
            cout<<"Enter Your Value : ";
            cin>>value;
            v.insert(v.begin()+idx,value);//insert || emplace(the best)
            break;
        ////////////////////////////////

        case 3 :
            v.pop_back();
            break;

        //////////////////
        case 4 :
            cout<<"Enter by Index ";
            cin>>idx;
            v.erase(v.begin()+idx);
            break;

        //////////////////
        case 5 :
            cout<<"Enter the Start: ";
            cin>>start;
            cout<<"Enter the End: ";
            cin>>_end;
            //assert(start>=0 && start<v.size());
            //  assert(_end>=0 && _end<v.size());
            v.erase(v.begin()+start,v.begin()+_end);
            break;
//////////////////////

        case 6 :
            v.clear();
            break;
/////////////////

        case 7 :
            sort(v.begin(),v.end(),CompareRight);
            cout<<"Ascending Order Sorting Successfully\n";
            break;
        ///////////////

        case 8 :
            sort(v.rbegin(),v.rend(),CompareRight);
            cout<<"Descending Order Sorting Successfully\n";
            break;

        ////////////////
        case 9 :
            reverse(v.begin(),v.end());
            cout<<"Reversing Successfully\n";
            break;
        ////////////////////

        case 10 :
            cout<<"Max Element : "<<*max_element(v.begin(),v.end())<<endl;
            break;
/////////////////////

        case 11 :
            cout<<"Min Element : "<<*min_element(v.begin(),v.end())<<endl;
            break;
/////////////////////////////

        case 12 :
            cout<<"Vector's Size : "<<v.size()<<endl;
            break;
//////////////////////

        case 13 :
            cout<<"Vector's Capacity : "<<v.capacity()<<endl;
            break;
//////////////////////

        case 14 :
            if(v.empty())
            {
                cout<<"EMPTY\n\a";
            }
            else
            {
                for(auto item:v)
                    cout<<item<<" ";
                cout<<endl;
            }

            break;
/////////////////////////////

        case 15 :
        {
            cout<<"Enter The Key : ";
            cin>>key;
            auto it=v.begin();
            it = find(v.begin(),v.end(),key);
            it!=v.end()?cout<<key<<" Found in Position "<<it-v.begin()<<endl: cout<<"Not Found\n\a";
            break;
        }
///////////////////////////

        case 16 :
        {
            cout<<"Enter The New size : ";
            cin>>new_size;
            v.resize(new_size);
            v.shrink_to_fit();
            break;
        }

        case 17 :
           {
            auto Pair = minmax_element(v.begin(),v.end());
            cout<<"Min Element = "<<*Pair.first<<"\tMax Element = "<<*Pair.second<<endl;
            break;
           }

        case 18 :
            cout<<"The First Element = "<<v.front()<<endl;
            break;

            case 19 :
            cout<<"The Last Element = "<<v.back()<<endl;
            break;

        }

        cout<<"Repeat Again [Y/N] ?? ";
        cin>>choice2;
    }
    while(choice2=='Y' || choice2=='y');
}