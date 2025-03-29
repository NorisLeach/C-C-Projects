#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");

const int di[]={-1,-1,-1,0,1,1,1,0};
const int dj[]={-1,0,1,1,1,0,-1,-1};

int m,n,a[20][20],traseu[20][20];
int xs,ys,xb,yb;
int nrsol;

void citire()
{
    fin>>m>>n;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            fin>>a[i][j];
    fin>>xs>>ys;
    fin>>xb>>yb;
}

void tipar()
{
    nrsol++;
    fout<<"\nSolutia nr. "<<nrsol<<"\n";
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
            fout<<setw(3)<<traseu[i][j];
        fout<<"\n";
    }
}

int valid(int inou,int jnou)
{
    if(traseu[inou][jnou]!=0)
        return 0;
    if(inou<1 || inou>m || jnou<1 || jnou>n)
        return 0;
    if(a[inou][jnou]!=0)
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
        if(valid(inou,jnou)==1)
        {
            traseu[inou][jnou]=pas;
            if(inou==xb && jnou==yb)
                tipar();
            else
                fback(inou,jnou,pas+1);
            traseu[inou][jnou]=0;
        }
    }
}

int main()
{
    citire();
    tipar();
    traseu[xs][ys]=1;
    fback(xs,ys,2);
    return 0;
}
