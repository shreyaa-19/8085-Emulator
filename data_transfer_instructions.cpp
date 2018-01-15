#include "helper_functions.h"

void MOV(string &reg1, string reg2)
{
    reg1 = reg2;
}

void SET(string address,string data)
{
    stack[hex_to_dec(address)].DATA=data;
}

void LDAX(string &A, string B, string C)
{
    string add1=B;
    string add2=C;
    string add = add1 + add2;
    if( stack[hex_to_dec(add)].DATA == "\0")
    {
          cout<<"ERROR LDAX,NO DATA FOUND!! "<<endl;
    }
    if(hex_to_dec(add)>=0 && hex_to_dec(add)<65535)
    {
            A=stack[hex_to_dec(add)].DATA;
    }
    else
            cout<<"ERROR!!";
}

void STAX(string &A, string B, string C)
{
    string add1=B;
    string add2=C;
    string add = add1 + add2;
    if(hex_to_dec(add)>=0 && hex_to_dec(add)<65535)
        stack[hex_to_dec(add)].DATA=A;
    else
        cout<<"ERROR!!";
}

void XCHG(string &H, string &L, string &D, string &E)
{
    string temp;
    temp = H;
    H = D;
    D = temp;
    temp = L;
    L = E;
    E = temp;
}

void SHLD(string &L,string &H,string address)
{
    int d=hex_to_dec(address);
    stack[d].DATA=L;
    d=d+1;
    stack[d].DATA=H;
}

void MVI(string  &reg1, string data)
{
    reg1 = data;
}

void LDA(string &A, string address)
{
    A = stack[hex_to_dec(address)].DATA;
}

void LHLD(string &L,string &H,string address)
{
    if(stack[hex_to_dec(address)].DATA == "\0" || stack[hex_to_dec(address)+1].DATA == "\0")
    {
        cout<<"ERROR LHLD,NO DATA FOUND!! "<<endl;
    }
    L=stack[hex_to_dec(address)].DATA;
    int d=hex_to_dec(address);
    d=d+1;
    string data=dec_to_hex(d);
    H=stack[hex_to_dec(data)].DATA;
}

void LXI( string location , string &h, string &l)
{
    h = location.substr(0,2);
    l = location.substr(2,2);
}

void STA(string &A,string address)
{
    int add=hex_to_dec(address);
    stack[add].DATA=A;
}

