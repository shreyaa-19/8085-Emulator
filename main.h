#include "arithemetic_instructions.h"
#include "helper_functions.h"
#include "data_transfer_instructions.h"
#include "logical_instructions.h"

void help();
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

