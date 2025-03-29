#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

int a[20][20],traseu[20][20],suma[30];
int m,n,iinit,jinit,ifinal,jfinal;
int nrsol;
int MatriceMaxim[20][20],sMaxim;


const int di[]={-1,-1,-1,0,1,1,1,0};
const int dj[]={-1,0,1,1,1,0,-1,-1};

void citire()
{
    fin>>m>>n;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            fin>>a[i][j];
    fin>>iinit>>jinit;
    fin>>ifinal>>jfinal;
}

void determinareMaxim(int pas)
{
    int i,j;
    if(suma[pas]>sMaxim)
    {
        sMaxim=suma[pas];
        for(i=1;i<=m;i++)
            for(j=1;j<=n;j++)
                MatriceMaxim[i][j]=traseu[i][j];
    }
}

int valid(int inou,int jnou,int i,int j)
{
    if(inou<1 || inou>m || jnou<1 || jnou>n)
        return 0;
    if(traseu[inou][jnou]!=0)
        return 0;
    if(a[inou][jnou]<a[i][j])
        return 0;
    return 1;
}

void tipar(int t[20][20])
{
   int i,j;
   nrsol++;
   fout<<"\nSolutia nr. "<<nrsol<<" cu suma maxima:"<<sMaxim<<"\n";
   for(i=1;i<=m;i++)
   {
        for(j=1;j<=n;j++)
            fout<<setw(4)<<t[i][j]<<" ";
        fout<<endl;
   }

}

void fback(int i,int j,int pas)
{
    int inou,jnou,k;
    for(k=0;k<=7;k++)
    {
        inou=i+di[k];
        jnou=j+dj[k];
        if(valid(inou,jnou,i,j))
        {
            traseu[inou][jnou]=pas;
            suma[pas]=suma[pas-1]+a[inou][jnou]-a[i][j];
            if(inou==ifinal && jnou==jfinal)
                determinareMaxim(pas);
            else
                fback(inou,jnou,pas+1);
            traseu[inou][jnou]=0;
        }
    }
}

int main()
{
    int pas;
    citire();
    traseu[iinit][jinit]=1;
    suma[1]=0;
    fback(iinit,jinit,2);
    tipar(MatriceMaxim);
    return 0;
}
