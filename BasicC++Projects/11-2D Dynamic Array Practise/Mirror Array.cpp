//W. Mirror Array
#include <iostream>
using namespace std;

void fast()
{
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);
}

void insert2DArr(long long**arr,int r,int c)
{

     for(int i=0;i<r;i++)
    {
            for(int j=0;j<c;j++)
            {
               cin>>arr[i][j];
            }
    }
}
void MirorArr(long long**arr,int r,int c)
{
     for(int i=0;i<r;i++)
    {
            for(int j=c-1;j>=0;j--)
            {
               cout<<arr[i][j]<<" ";
            }cout<<endl;
    }
}
int main()
{
    fast();
int r,c;
cin>>r>>c;
long long**arr;//
arr=new long long*[r];//
 for(int i=0;i<r;i++)//
    arr[i]=new long long[c];
insert2DArr(arr,r,c);
MirorArr(arr,r,c);

delete[]arr;
arr=nullptr;
    return 0;
}