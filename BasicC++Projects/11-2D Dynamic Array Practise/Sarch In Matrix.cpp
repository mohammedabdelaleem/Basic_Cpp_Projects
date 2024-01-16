//S. Search In Matrix
#include <iostream>
using namespace std;

void insert2DArr(int**arr,int r,int c)
{

     for(int i=0;i<r;i++)
    {
            for(int j=0;j<c;j++)
            {
              //  cout<<"Enter element at position "<<i<<j<<" then press Enter ";
             //cin>>*(*(arr+i)+c);
               cin>>arr[i][j];
            }
    }
}

void print2DArr(int**arr,int r,int c)
{
      for(int i=0;i<r;i++)
    {
            for(int j=0;j<c;j++)
            {
         //  cout<<(*(*(arr+i)+c));
                cout<<arr[i][j]<<" ";
            }cout<<endl;
    }
}

//vector<int>linearSearch(int **arr,int r,int c,int target)
bool linearSearch(int **arr,int r,int c,int target)
{
    bool f=false;
       for(int i=0;i<r;i++)
    {
            for(int j=0;j<c;j++)
            {
         if(arr[i][j]==target)
           {
               f=true;
               return f;
           }
           // return {i,j};
            }
    }
    return f;
    //return {-1,-1};
}


int main()
{
int row=2,colomn=3;
//cout<<"Enter dimintions of 2D array: ";
cin>>row>>colomn;
int**arr=new int*[row];
 for(int i=0;i<row;i++)
    {
        arr[i]=new int[colomn];
    }
insert2DArr(arr,row,colomn);

int target;
cin>>target;
bool f=linearSearch(arr, row, colomn, target);
if(f)
    cout<<"will not take number\n";
else
    cout<<"will take number\n";



system("pause");
    return 0;
}

