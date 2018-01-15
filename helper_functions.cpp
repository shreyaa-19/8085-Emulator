#include "helper_functions.h"

int CF=0,ZF=0,PF=0,AF=0,SF=0;
stack_type stack[65535];

int hex_to_dec(string hex)
{
    unsigned long result = 0;
    for (int i=0; i<hex.length(); i++) {
        if (hex[i]>=48 && hex[i]<=57)
        {
            result += (hex[i]-48)*pow(16,hex.length()-i-1);
        } else if (hex[i]>=65 && hex[i]<=70) {
            result += (hex[i]-55)*pow(16,hex.length( )-i-1);
        } else if (hex[i]>=97 && hex[i]<=102) {
            result += (hex[i]-87)*pow(16,hex.length()-i-1);
        }
    }
    return result;
}

string Return_inst(string str)
{
    string word;
    stringstream iss(str);
    iss >> word;
    return word;
}

string set_precision( string s)
{
    if(s == "0")
        return "00";
    else if( s == "1")
        return "01";
    else if( s == "2")
         return "02";
    else if( s == "3")
         return "03";
    else if( s == "4")
         return "04";
    else if( s == "5")
         return "05";
    else if( s == "6")
         return "06";
    else if( s == "7")
         return "07";
    else if( s == "8")
         return "08";
    else if( s == "9")
         return "09";
    else if( s == "A")
        return "0A";
    else if( s == "B")
         return "0B";
    else if( s == "C")
         return "0C";
    else if( s == "D")
         return "0D";
    else if( s == "E")
         return "0E";
    else if( s == "F")
         return "0F";
    else
        return s;
}
int check_start_address(string start_add)
{
    int l = start_add.length();
    if(l != 4)
        return 0;
    else
    {
        for(int i=0;i<l;i++)
        {
            if(!((start_add[i] >= 48 && start_add[i] <= 57) || ( start_add[i] >= 65 && start_add[i] <= 70)))
            {
               return 0;
            }
        }
        return 1;
    }
}

int Return_bytes(string inst)
{
    if(inst == "MOV"||inst == "ADD"||inst == "CMA"||inst == "HLT"||inst == "SUB"||inst=="LDAX"||inst=="STAX"||inst=="XCHG"||inst=="DAD"||inst == "INX"||inst=="INR"||inst=="DCR"||inst=="DCX"||inst=="CMP")
        return 1;
    else if(inst == "ADI" ||inst == "MVI"||inst=="SUI")
        return 2;
    else if(inst == "SET")
        return 4;
    else
        return 3;
}

string dec_to_hex(int decimal)
{
    char hexDigits[] = "0123456789ABCDEF";
    char hexadecimal[40];
    int index, remaindar;
    index = 0;
    while(decimal != 0) {
        remaindar = decimal % 16;
        hexadecimal[index] = hexDigits[remaindar];
        decimal /= 16;
        index++;
    }
    hexadecimal[index]='\0';
    return strrev(hexadecimal);
}

int str_to_i(string str)
{
    stringstream convert_stoi(str);
    int x = 0;
    convert_stoi >> x;
    return(x);
}
string i_to_str(int i)
{
    stringstream convert_itos;
    convert_itos << i;
    string s;
    s=convert_itos.str();
    return(s);
}

int dec_to_bin(int n)
{
    int binaryNumber = 0;
    int remainder, i = 1;

    while (n!=0)
    {
        remainder = n%2;
         n /= 2;
        binaryNumber += remainder*i;
        i *= 10;
    }
    return binaryNumber;
}

void show_FLAG(int CF,int ZF,int SF,int PF)
{
    cout<<"Carry Flag= "<<CF<<endl;
    cout<<"Zero Flag= "<<ZF<<endl;
    cout<<"Sign Flag= "<<SF<<endl;
    cout<<"Parity Flag= "<<PF<<endl;
    cout<<"Auxiliary Flag= "<<AF<<endl;
}

bool CarryFlag(string result)
{
    int res=hex_to_dec(result);
    if(res>255)
        return true;
    else
        return false;
}

bool ParityFlag(int result)
{
    int res=dec_to_bin(result);
    string str=dec_to_hex(res);
    int length=str.length();
    int i,c=0;
    for(i=length-1 ; i>=(length-8) ; i--)
    {
        if(str[i]=='1')
        {
            c++;
        }
    }
    if(c%2==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool SignFlag(int result)
{
    string str=dec_to_hex(result);
    if(str[0]=='-')
        return true;
    else
        return false;
}

int check_data_limit(string address)
{
    int i=str_to_i(address);
    if(i<0 || i>255)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_address_limit(string address)
{
    int i=str_to_i(address);
    if(i<0 || i>65535)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

string search( string pc,int &i )
{
    int j=0;
    while(memory[j].address != pc)
    {
        j++;
    }
    i = j;
    if((memory[j].address != pc))
        cout<<"ADDRESS ASSIGNMENT ERROR!\n";
    else
    {
        return memory[j].mnemonic;
    }
}

void help()
{
    cout<<" 1. break or b `line no`:- It will set break point on given line number."<<endl;
    cout<<"2. run or r :- Run the program until it ends or breakpoint is encountered.\n"<<endl;
    cout<<"3. step or s :- It will run the program one instruction at a time."<<endl;
    cout<<"4. print or p:- It prints the value of register or memory location."<<endl;
    cout<<"5. quit or q:- quits the debugger."<<endl;
    cout<<"6. help:- will show all the commands of debugger."<<endl;
}

std::string trim(char str[100])
{
    for(int i = 99; i >= 0; i--)
    {
        if(str[i] == ' ' || str[i] == '\0' || str[i] == (char)(10))
            str[i] = '\0';
        else
            break;
    }

    return string(str);
}

void set_byte(int argc , char *argv[],ifstream &inFile)
{
    string instruction;
    int i = 0;
    do
    {
        char buffer[100];
        int tempAdd;
        memory[i].index_status = i+1;

        if(argc == 1)
        {
             for(int j = 0; j < 100; j++)
                buffer[j] = ' ';
            cin.getline(buffer,99);
        }
        else if(argc == 2 || argc == 3)
        {
            for(int j = 0; j < 100; j++)
                buffer[j] = ' ';
            inFile.getline(buffer,99);
        }
        instruction = trim(buffer);
        if( instruction[0] == 'L' && instruction[1] == 'D' && instruction[2] == 'A' && instruction[3] == 'X' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'S' && instruction[1] == 'T' && instruction[2] == 'A' && instruction[3] == 'X' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
         else if( instruction[0] == 'L' && instruction[1] == 'H' && instruction[2] == 'L' && instruction[3] == 'D' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+3;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'S' && instruction[1] == 'H' && instruction[2] == 'L' && instruction[3] == 'D' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+3;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'X' && instruction[1] == 'C' && instruction[2] == 'H' && instruction[3] == 'G' )
        {
         tempAdd = (hex_to_dec(memory[i].address))+1;
         memory[i+1].address = dec_to_hex(tempAdd);
          memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'J'  && instruction[1] == 'M' && instruction[2] == 'P' )
         {
             tempAdd = (hex_to_dec(memory[i].address))+3;
             memory[i+1].address = dec_to_hex(tempAdd);
              memory[i].mnemonic = instruction;
         }
        else if( instruction[0] == 'L' && instruction[1] == 'D' && instruction[2] == 'A' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+3;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'S' && instruction[1] == 'T' && instruction[2] == 'A' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+3;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'M' && instruction[1] == 'O' && instruction[2] == 'V' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }

        else if( instruction[0] == 'L' && instruction[1] == 'X' && instruction[2] == 'I' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+3;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'M' && instruction[1] == 'V' && instruction[2] == 'I' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+2;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }

        else if( instruction[0] == 'S' && instruction[1] == 'T' && instruction[2] == 'A' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+3;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'I' && instruction[1] == 'N' && instruction[2] == 'R' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'D' && instruction[1] == 'C' && instruction[2] == 'R' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'I' && instruction[1] == 'N' && instruction[2] == 'X' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'D' && instruction[1] == 'C' && instruction[2] == 'X' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
          else if( instruction[0] == 'S' && instruction[1] == 'U' && instruction[2] == 'B' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'A' && instruction[1] == 'D' && instruction[2] == 'D' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'A' && instruction[1] == 'D' && instruction[2] == 'I' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'S' && instruction[1] == 'U' && instruction[2] == 'I' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'C' && instruction[1] == 'M' && instruction[2] == 'A' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'C' && instruction[1] == 'M' && instruction[2] == 'P' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'D' && instruction[1] == 'A' && instruction[2] == 'D' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
             memory[i].mnemonic = instruction;
        }
        else if( instruction[0] == 'H' && instruction[1] == 'L' && instruction[2] == 'T' )
        {
             tempAdd = (hex_to_dec(memory[i].address))+1;
             memory[i+1].address = dec_to_hex(tempAdd);
              memory[i].mnemonic = instruction;
         }

         else if( instruction[0] == 'J' && instruction[1] == 'N' && instruction[2] == 'C' )
         {
             tempAdd = (hex_to_dec(memory[i].address))+3;
             memory[i+1].address = dec_to_hex(tempAdd);
              memory[i].mnemonic = instruction;
         }
           else if( instruction[0] == 'J' && instruction[1] == 'C' )
         {
             tempAdd = (hex_to_dec(memory[i].address))+3;
             memory[i+1].address = dec_to_hex(tempAdd);
              memory[i].mnemonic = instruction;
         }
          else if( instruction[0] == 'J' && instruction[1] == 'N' && instruction[2] == 'Z' )
         {
             tempAdd = (hex_to_dec(memory[i].address))+3;
             memory[i+1].address = dec_to_hex(tempAdd);
              memory[i].mnemonic = instruction;
         }
          else if( instruction[0] == 'S' && instruction[1] == 'E' && instruction[2] == 'T' )
         {
             tempAdd = (hex_to_dec(memory[i].address))+4;
             memory[i+1].address = dec_to_hex(tempAdd);

              memory[i].mnemonic = instruction;
         }
           else if( instruction[0] == 'J' && instruction[1] == 'Z' )
         {
             tempAdd = (hex_to_dec(memory[i].address))+3;
             memory[i+1].address = dec_to_hex(tempAdd);
              memory[i].mnemonic = instruction;
         }
         i++;
    }while(instruction.substr(0,3)!="HLT");
}

