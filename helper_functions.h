#include<iostream>
#include<sstream>
#include<math.h>
#include<string>
#include<cstring>
#include<iomanip>
#include<stdio.h>
#include <fstream>
#include<algorithm>

#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_

using namespace std;

typedef struct memo
{
    string address;
    string mnemonic;
    bool debugger_status;
    int index_status;
}memory_type;

extern memory_type memory[100];

extern int CF,ZF,PF,AF,SF;

typedef struct memory_space
{
    string DATA;
}stack_type;

extern stack_type stack[65535];

int hex_to_dec(string hex);
string Return_inst(string str);
string set_precision( string s);
int Return_bytes(string inst);
string dec_to_hex(int decimal);
int str_to_i(string str);
string i_to_str(int i);
int dec_to_bin(int n);
void show_FLAG(int CF,int ZF,int SF,int PF);
bool CarryFlag(string result);
bool ParityFlag(int result);
bool ZeroFlag(string str);
bool SignFlag(int result);
int check_data_limit(string address);
int check_address_limit(string address);
void help();
string search( string pc,int &i );
int check_start_address(string start_add);
void set_byte(int argc, char *argv[],ifstream &inFile);
#endif // HELPER_FUNCTIONS_H_
