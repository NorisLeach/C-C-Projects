#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");

int n,a[20][20],traseu[20][20];
int x0,y0;
int nrsol;

const int di[]={-2,-1,1,2,2,1,-1,-2};
const int dj[]={1,2,2,1,-1,-2,-2,-1};

void tipar()
{
    nrsol++;
    fout<<"\nSolutia nr. "<<nrsol<<"\n";
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            fout<<setw(3)<<traseu[i][j];
        fout<<"\n";
    }
}

int valid(int inou,int jnou)
{
    if(inou<1 || inou>n || jnou<1 || jnou>n)
        return 0;
    if(traseu[inou][jnou]!=0)
        return 0;
    return 1;
}

void fback(int i,int j,int pas)
{
    int inou,jnou,k;
    for(k=0;k<=7;k++)
    {
        inou=i+di[k];
        jnou=j+dj[k];
        if(valid(inou,jnou))
        {
            traseu[inou][jnou]=pas;
            if(pas==n*n)
                tipar();
            else
                fback(inou,jnou,pas+1);
            traseu[inou][jnou]=0;
        }
    }
}

int main()
{
    fin>>n>>x0>>y0;
    traseu[x0][y0]=1;
    fback(x0,y0,2);

    return 0;
}
