#include <iostream>
#include <fstream>
using namespace std;
ofstream fout("date.out");

int st[50],suma[50],nrsol=0,n;

void fback(int);
int valid(int);
void tipar(int);

int main()
{
    cout<<"n=";  cin>>n;
    suma[0]=0;
    fback(1);
    fout<<"\nNumarul de solutii = "<<nrsol;
    return 0;
}

void fback(int k)
{
    for(int i=1;i<=n;i++)
    {
        st[k]=i;
        suma[k]=suma[k-1]+st[k];   // i = st[k]
        if(valid(k))
        {
            if(suma[k]==n)
                tipar(k);
            if(k<n)
                fback(k+1);
        }
    }
}

int valid(int k)
{
    if(k>1 && st[k]<st[k-1])
        return 0;
    return 1;
}

void tipar(int k)
{
    nrsol++;
    fout<<n<<"=";
    for(int i=1;i<k;i++)
        fout<<st[i]<<"+";
    fout<<st[k];
    fout<<"\n";
}
