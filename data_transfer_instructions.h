#include "helper_functions.h"

void MOV(string &reg1, string reg2);
void LDAX(string &A, string B, string C);
void STAX(string &A, string B, string C);
void XCHG(string &H, string &L, string &D, string &E);
void SHLD(string &L,string &H,string address);
void MVI(string  &reg1, string data);
void LDA(string &A, string address);
void LHLD(string &L,string &H,string address);
void LXI( string location , string &h, string &l);
void STA(string &A,string address);
void SET(string address,string data);
