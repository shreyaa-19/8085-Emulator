#include "arithemetic_instructions.h"

void ADD(string &A,string value)
{
    int v1=hex_to_dec(A);
    int v2=hex_to_dec(value);
    int sum=v1+v2;
    A=dec_to_hex(sum);
    if(A == "00")
        ZF = 1;
    else
        ZF=0;
    if(CarryFlag(A))
        CF=1;
    else
        CF=0;
    if(SignFlag(hex_to_dec(A)))
        SF=1;
    else
        SF=0;
    if(ParityFlag(hex_to_dec(A)))
        PF=1;
    else
        PF=0;

    if(CF==1)
        A=A.substr(1,4);
}

void SUB(string &A,string value)
{
    int sum;
    int v1=hex_to_dec(A);
    int v2=hex_to_dec(value);
    if(v1>v2)
    {
        sum=v1-v2;
        if(SignFlag(hex_to_dec(A)))
            SF=1;
        else
            SF=0;

        if(CarryFlag(A))
            CF=1;
        else
            CF=0;
    }
    else
    {
         sum=v2-v1;
         SF=1;
         CF=1;
    }
    if(sum == 0)
    {
        A = "00";
        CF = 0;
    }
    else
    {
         A=dec_to_hex(sum);
    }
    if(ParityFlag(hex_to_dec(A)))
        PF=1;
    else
        PF=0;

    if(A == "00")
        ZF = 1;
    else
        ZF=0;
}


void DAD(string &H,string &L,string &D,string &E)
{
    string HL_DATA = H + L;
    string DE_DATA = D + E;
    int add = hex_to_dec(HL_DATA) + hex_to_dec(DE_DATA);
    string dad = dec_to_hex(add);

    if(dad.length() == 3)
    {
        dad = "0" + dad;
    }
    else if(dad.length() == 2)
    {
        dad = "00" + dad;
    }
    else if(dad.length() == 1)
    {
        dad = "000" + dad;
    }
    if(dad.length() == 5)
    {
        dad = dad.substr(1,4);
        H = dad.substr(0,2);
        L = dad.substr(2,2);
        CF=1;
    }
    else
    {
        H = dad.substr(0,2);
        L = dad.substr(2,2);
        CF=0;
    }
    if(SignFlag(hex_to_dec(dad)))
        SF=1;
    else
        SF=0;
    if(ParityFlag(hex_to_dec(dad)))
        PF=1;
    else
        PF=0;
   if(stack[hex_to_dec(H+L)].DATA == "00")
      ZF = 1;
    else
        ZF=0;
   }

void ADI(string &A , string data)
{
    A = dec_to_hex(hex_to_dec(A) + hex_to_dec(data));
     if(A == "00")
        ZF = 1;
    else
        ZF=0;
}

void SUI(string &A , string data)
{
    A = dec_to_hex(hex_to_dec(A) - hex_to_dec(data));
    if(A == "00")
        ZF = 1;
    else
        ZF=0;
}

void DCX(string &H,string &L)
{
    string add=H+L;
    string data=dec_to_hex(hex_to_dec(add)-1);
    int l=data.length();
    if(l == 1)
    {
        data="000"+data;
    }
    else if(l == 2)
    {
         data="00"+data;
    }
     else if(l == 3)
    {
         data="0"+data;
    }
    L = set_precision(data.substr(2,2));
    H = set_precision(data.substr(0,2));

}

void INX(string &H,string &L)
{
   string add=H+L;
    string data=dec_to_hex(hex_to_dec(add)+1);
    int l=data.length();
     if(l == 1)
    {
        data="000"+data;
    }
    else if(l == 2)
    {
         data="00"+data;
    }
     else if(l == 3)
    {
         data="0"+data;
    }
    H = set_precision(data.substr(0,2));

    L = set_precision(data.substr(2,2));
}

void DCR(string &value)
{
    if(value=="00")
    {
        value="FF";
        SF=1;
    }
    else
    {
        if(hex_to_dec(value)-1 == 0)
            value = "00";
        else
            value=dec_to_hex(hex_to_dec(value) - 1);
        value = set_precision(value);
        if(SignFlag(hex_to_dec(value)))
            SF=1;
        else
            SF=0;
    }
    if(value == "00")
        ZF=1;
    else
        ZF=0;

    if(ParityFlag(hex_to_dec(value)))
        PF=1;
    else
        PF=0;

}

void INR(string &value)
{
    if(value=="FF")
        value="00";
    else
    {
        int temp_A=hex_to_dec(value);
        temp_A=temp_A+1;
        value=dec_to_hex(temp_A);
    }

    if(value == "00")
        ZF=1;
    else
        ZF=0;
    if(SignFlag(hex_to_dec(value)))
        SF=1;
    else
        SF=0;
    if(ParityFlag(hex_to_dec(value)))
        PF=1;
    else
        PF=0;

}
