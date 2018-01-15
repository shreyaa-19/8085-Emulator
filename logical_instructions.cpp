#include "logical_instructions.h"

void CMP( string &A,string &reg)
{
    if( hex_to_dec(A) < hex_to_dec(reg) )
    {
        CF=1;
        SF=0;
        ZF=0;
    }
    else if( hex_to_dec(A) > hex_to_dec(reg) )
    {
        CF=0;
        SF=0;
        ZF=0;
    }
    else if( hex_to_dec(A) == hex_to_dec(reg) )
    {
        CF=0;
        SF=0;
        ZF=1;
    }
}

void CMA(string &s)
{
    int b[100]={0},sum=0,n=0;
    int l=s.length();
    for(int i=0;i<l;i++)
    {
        if(s[i]>64 &&s[i]<71)
             n=s[i]-55;
        else
            n=s[i]-48;
        int k=4*(i+1);
        while(n!=1 && n!=0)
        {
            b[--k]=n%2;
            n=n/2;
        }
        b[--k]=n;
    }
    for(int i=0;i<l*2;i++)
    {
        int tmp=b[i];
        b[i]=b[(l*4)-1-i];
        b[(l*4)-1-i]=tmp;
    }
    for(int j=0;j<l*4;j++)
    {
        if(b[j]==1)
            b[j]=0;
        else
            b[j]=1;
    }
    for(int j=0;j<l*4;j++)
    {

            if(b[j]==1)
                sum+=pow(2,j);
    }
    s = dec_to_hex(sum);
}
