#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");
const int di[]={-2,-1,1,2,2,1,-1,-2};
const int dj[]={1,2,2,1,-1,-2,-2,-1};

int n,a[20][20],traseu[20][20];
int i_rege,j_rege,i_cal,j_cal;
int nrsol;
int pasmin=401, pasmax=0;

void citire()
{
    fin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            fin>>a[i][j];
    fin>>i_cal>>j_cal;
    fin>>i_rege>>j_rege;
}

void tipar(int pas)
{
    int i,j;
    nrsol++;
    fout<<"\nSolutia nr."<<nrsol<<"\n";
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            fout<<traseu[i][j]<<" ";
        fout<<"\n";
    }
    fout<<"\n\n\n";
    if(pas<pasmin)
        pasmin=pas;
    if(pas>pasmax)
        pasmax=pas;
}

int valid(int inou,int jnou)
{
    if(inou<1 || inou>n || jnou<1 || jnou>n)
        return 0;
    if(a[inou][jnou]==1)
        return 0;
    if(traseu[inou][jnou]!=0)
        return 0;
    return 1;
}

int amSolutie(int i,int j)
{
    if(traseu[i_rege][j_rege]==0)
        return 0;
    int inou,jnou,k;
    for(k=0;k<=7;k++)
    {
        inou=i+di[k];
        jnou=j+dj[k];
        if(inou==i_cal && jnou==j_cal)
            return 1;
    }
    return 0;
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
            if(amSolutie(inou,jnou))
                tipar(pas);
            else
                fback(inou,jnou,pas+1);
            traseu[inou][jnou]=0;

        }
    }
}


int main()
{
    citire();
    traseu[i_cal][j_cal]=1;
    fback(i_cal,j_cal,2);
    fout<<"Nr minim de pasi: "<<pasmin+1;
    fout<<endl;
    fout<<"Nr maxim de pasi: "<<pasmax+1;
    return 0;
}
