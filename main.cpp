#include "main.h"
memory_type memory[100];

int main( int argc, char *argv[])
{
    ifstream inFile;
    string start_add,A = "00",B = "00",H = "00",L = "00",D = "00",E = "00",C = "00",M = "0000";
    int line_no[20]={-1};
    for(int k=0; k<65535 ; k++)
        stack[k].DATA = "\0";
    cout<<"\n---------------------------------------------WELCOME TO 8085 EMULATOR--------------------------------------------------\n";
    cout<<"\nEnter the starting address:\t"<<endl;
    if(argc == 1)
        getline(cin, start_add);
    else if(argc == 2 || argc == 3)
    {
        inFile.open(argv[1]);
        if (!inFile)
        {
            cerr << "Unable to open file....!!!";
            exit(0);
        }
        getline(inFile,start_add);
        cout<<start_add<<endl;
    }
    int check = check_start_address(start_add);
    if(check == 0)
    {
        cout<<"START ADDRESSING ERROR....!!! ";
        return 0;
    }
    memory[0].address = start_add;
    string pc = start_add ,instruction,gdb;
    int i=0;
    set_byte(argc, argv,inFile);
    do
    {
        cout<<memory[i].index_status<<" "<<memory[i].address<<" "<<memory[i].mnemonic<<endl;
        i++;
        memory[i-1].debugger_status = false;

    }while(memory[i-1].mnemonic.substr(0,3) != "HLT");

    int status;
    if(argc == 3)
    {
        if(string(argv[2]) != "debugger")
        {
           cerr << "Invalid argument (debugger)....!!!" << endl;
           exit(0);
        }
        status = 1;
        if( status == 1 )
        {
            int n;
            cout<<"Enter number of breakpoints. "<<endl;
            cin>>n;
            if(n != 0)
            {
                cout<<"Enter space separated breakpoints. "<<endl;
                for(i=0;i<n;i++)
                    cin>>line_no[i];
                for(i=0; i<n; i++)
                {
                    int index = line_no[i];
                    memory[index - 1].debugger_status = true;
                }
            }
        }
    }
    bool run=false, quit=false , step=false;
    i=0;
    do
    {
        if(argc == 3)
        {

            if(step == true || (memory[i].debugger_status == true && status == 1))
            {
               run = false;
               if(run == false && quit == false)
                    {
                        label1 :
                        cout<<" Enter debugger option : "<<endl;
                        cin>>gdb;
                        if(gdb.substr(0,3) == "run" || gdb.substr(0,1) == "r" )
                        {
                            run = true;
                            step = false;
                        }
                        else if(gdb.substr(0,4) == "help" )
                        {
                            help();
                            goto label1;
                            step = false;
                        }
                        else if(gdb.substr(0,5) == "print" || gdb.substr(0,1) == "p" )
                        {
                            step = false;
                            char choice;
                            string content;
                            do
                            {
                                cin>>content;
                                if(content.length() == 1)
                                {
                                    if(content == "A")
                                    {
                                        cout<<"A = ";
                                        A=set_precision(A);cout<<A<<endl;
                                    }
                                    else if(content == "B")
                                    {
                                        cout<<"B = ";
                                        B=set_precision(B);cout<<B<<endl;
                                    }
                                    else if(content == "C")
                                    {
                                        cout<<"C = ";
                                        C=set_precision(C);cout<<C<<endl;
                                    }
                                    else if(content == "D")
                                    {
                                        cout<<"D = ";
                                        D=set_precision(D);cout<<D<<endl;
                                    }
                                    else if(content == "E")
                                    {
                                        cout<<"E = ";
                                        E=set_precision(E);cout<<E<<endl;
                                    }
                                    else if(content == "H")
                                    {
                                        cout<<"H = ";
                                        H=set_precision(H);cout<<H<<endl;
                                    }
                                    else if(content == "L")
                                    {
                                        cout<<"L = ";
                                        L=set_precision(L);cout<<L<<endl;
                                    }
                                    else if(content == "M")
                                    {
                                        M=set_precision(stack[hex_to_dec(H+L)].DATA);cout<<M<<endl;
                                    }
                                }
                                else if( content.length() == 4)
                                {
                                    cout<<content<<" = ";
                                    string content1=set_precision(stack[hex_to_dec(content)].DATA); cout<<content1<<endl;
                                }
                                else
                                {
                                    cout<<"SYNTAX ERROR....!!!"<<endl;
                                       return 0;
                                }

                                cout << "Do you want to print more ? Enter register/address(y/n)\t";
                                cin>>choice;
                                if(choice != 'y' && choice != 'n')
                                {
                                    cout<<"Wrong choice "<<endl;
                                    goto label1;
                                }
                                if(choice == 'n')
                                goto label1;
                            }while( choice == 'y' );

                    }
                        else if( gdb.substr(0,4) == "quit" || gdb.substr(0,1) == "q")
                            quit = true;
                        else if( gdb.substr(0,4) == "step" || gdb.substr(0,1) == "s")
                            step = true;
                        else
                        {
                            cout<<"Cannot identify debugger option. Input again ->\n";
                            goto label1;
                        }
                    }
                }
            }
        int x = 0 , l = 0;
        instruction = search(pc,i);
        cout<<"->"<<instruction<<endl;
        if(instruction[0] == 'L' && instruction[1] == 'H' && instruction[2] == 'L' && instruction[3] == 'D' && instruction[4] == ' ')
        {
            if(instruction.length() != 9)
            {
               cout<<" LHLD OPERAND ERROR....!!! "<<endl; return 0;
            }
            x = check_address_limit(instruction.substr(5,4));
            if(x==1)
            {
                cout<<"LHLD OPERAND ERROR....!!! "<<endl; return 0;
            }
            LHLD(L,H,instruction.substr(5,4));
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,4)));
        }
        else if(  instruction[0] == 'S' && instruction[1] == 'H' && instruction[2] == 'L' && instruction[3] == 'D' && instruction[4] == ' ' )
        {
            if(instruction.length() != 9)
            {
               cout<<" SHLD OPERAND ERROR....!!! "<<endl; return 0;
            }
            x = check_address_limit(instruction.substr(5,4));
            if(x==1)
                cout<<"SHLD OPERAND ERROR....!!! "<<endl; return 0;
            SHLD(L,H,instruction.substr(5,4));
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,4)));
        }
        else if( instruction[0] == 'L' && instruction[1] == 'D' && instruction[2] == 'A' && instruction[3] == 'X' && instruction[4] == ' ' )
        {
            if(instruction.length() != 6)
            {
               cout<<" LDAX OPERAND ERROR....!!! "<<endl; return 0;
            }
            if( instruction.substr(5,1)=="H")
                LDAX(A,H,L);
            else if( instruction.substr(5,1)=="B")
                LDAX(A,B,C);
            else if( instruction.substr(5,1)=="D")
                LDAX(A,D,E);
            else
            {
                cout<<"LDAX OPERAND ERROR....!!! "<<endl; return 0;
            }
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,4)));
        }
        else if( instruction[0] == 'S' && instruction[1] == 'T' && instruction[2] == 'A' && instruction[3] == 'X' && instruction[4] == ' ' )
        {
            if(instruction.length() != 6)
            {
               cout<<" STAX OPERAND ERROR....!!! "<<endl; return 0;
            }
            if( instruction.substr(5,1)=="H")
                STAX(A,H,L);
            else if( instruction.substr(5,1)=="B")
                STAX(A,B,C);
            else if( instruction.substr(5,1)=="D")
                STAX(A,D,E);
            else
            {
                cout<<"STAX OPERAND ERROR....!!! "<<endl; return 0;
            }
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,4)));
        }
        else if( instruction[0] == 'X' && instruction[1] == 'C' && instruction[2] == 'H' && instruction[3] == 'G' && instruction[4] == ' ' )
        {
             if(instruction.length() != 4)
            {
               cout<<" XCHG OPERAND ERROR....!!! "<<endl; return 0;
            }
            XCHG(H,L,D,E);
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,4)));
        }
        else if(  instruction[0] == 'L' && instruction[1] == 'D' && instruction[2] == 'A' && instruction[3] == ' ')
        {
             if(instruction.length() != 8)
            {
               cout<<" LDA OPERAND ERROR....!!! "<<endl; return 0;
            }
            x = check_address_limit(instruction.substr(4,4));
            if(x==1)
            {
                cout<<"LDA OPERAND ERROR....!!! "<<endl; return 0;
            }
            LDA(A,instruction.substr(4,4));
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }
        else if( instruction[0] == 'J' && instruction[1] == 'M' &&  instruction[2] == 'P' && instruction[3] == ' ' )
        {
            if(instruction.length() != 8)
            {
               cout<<" JMP OPERAND ERROR....!!! "<<endl; return 0;
            }
            x = check_address_limit(instruction.substr(4,4));
            if(x==1)
            {
                cout<<"JMP OPERAND ERROR....!!! "<<endl; return 0;
            }
            int f = 0,j = 0;
            do
            {
                if(memory[j].address == instruction.substr(4,4) )
                {
                    f = 1;
                    break;
                }
                j++;
            }while(memory[j-1].mnemonic.substr(0,3) != "HLT");

            if( f == 0)
            {
                cout<< "JMP OPERAND ERROR....!!! "<<endl; return 0;
            }
            pc = instruction.substr(4,4);
        }
        else if(  instruction[0] == 'M' && instruction[1] == 'V' && instruction[2] == 'I' && instruction[3] == ' ' && instruction[5]  == ' ' )
        {
            if(instruction.length() != 8)
            {
                cout<<" MVI OPERAND ERROR....!!! "<<endl; return 0;
            }
            if("A" == instruction.substr(4,1))
                MVI(A,instruction.substr(6,2));
            else if("B" == instruction.substr(4,1))
                MVI(B,instruction.substr(6,2));
            else if("C" == instruction.substr(4,1))
                MVI(C,instruction.substr(6,2));
            else if("D" == instruction.substr(4,1))
                MVI(D,instruction.substr(6,2));
            else if("E" == instruction.substr(4,1))
                MVI(E,instruction.substr(6,2));
            else if("H" == instruction.substr(4,1))
                MVI(H,instruction.substr(6,2));
            else if("L" == instruction.substr(4,1))
                MVI(L,instruction.substr(6,2));
            else if("M" == instruction.substr(4,1))
            {
                 string s = H + L;
                M = stack[hex_to_dec(s)].DATA;
                MVI(M,instruction.substr(6,2));
            }
            else
            {
                cout<<" MVI OPERAND ERROR....!!! "<<endl; return 0;
            }
            x = check_data_limit(instruction.substr(6,2));
            if(x==1)
            {
                cout<<"MVI OPERAND ERROR....!!! "<<endl; return 0;
            }
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }

        else if( instruction[0] == 'J' && instruction[1] == 'N' && instruction[2] == 'C' && instruction[3] == ' ')
        {
            if(instruction.length() != 8)
            {
               cout<<" JNC OPERAND ERROR....!!! "<<endl; return 0;
            }
            x = check_address_limit(instruction.substr(4,4));
            if(x == 1)
            {
                cout<<"JNC OPERAND ERROR....!!! "<<endl; return 0;
            }
            int f = 0,j=0;
            do
            {
                if(memory[j].address == instruction.substr(4,4) )
                {
                    f = 1;
                    break;
                }
                j++;
            }while(memory[j-1].mnemonic != "HLT");

            if( f == 0)
            {
                 cout<< "JNC OPERAND ERROR....!!! "<<endl; return 0;
            }
            if(CF == 0)
                 pc = instruction.substr(4,4);
            else
                pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }
        else if( instruction[0] == 'J' && instruction[1] == 'C' && instruction[2] == ' ')
        {
            if(instruction.length() != 7)
            {
               cout<<" JC OPERAND ERROR....!!! "<<endl; return 0;
            }
            x = check_address_limit(instruction.substr(3,4));
            if(x == 1)
            {
                cout<<"JC OPERAND ERROR....!!! "<<endl; return 0;
            }
            int f=0,j=0;
            do
            {
                if(memory[j].address == instruction.substr(3,4) )
                {
                    f = 1;
                    break;
                }
                j++;
            }while(memory[j-1].mnemonic != "HLT");

            if( f == 0)
            {
                 cout<< "JC OPERAND ERROR....!!! "<<endl; return 0;
            }

              if(CF == 1)
                 pc = instruction.substr(3,4);
            else
                 pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,2)));
        }
        else if( instruction[0] == 'J' && instruction[1] == 'N' && instruction[2] == 'Z' && instruction[3] == ' ' )
        {

            if(instruction.length() != 8)
            {
               cout<<" JNZ OPERAND ERROR....!!! "<<endl; return 0;
            }
            x = check_address_limit(instruction.substr(4,4));
            if(x == 1)
            {
                cout<<"JNZ OPERAND ERROR....!!! "<<endl; return 0;
            }
            int f = 0,j=0;
            do
            {
                if(memory[j].address == instruction.substr(4,4) )
                {
                    f = 1;
                    break;
                }
                j++;
            }while(memory[j-1].mnemonic != "HLT");

            if( f == 0)
            {
                 cout<< "JNZ OPERAND ERROR....!!! "<<endl; return 0;
            }
            if(ZF == 0)
            {
                 pc = instruction.substr(4,4);
            }
            else
            {
                pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
            }
        }
        else if( instruction[0] == 'J' && instruction[1] == 'Z' && instruction[2] == ' ')
        {
            if(instruction.length() != 7)
            {
               cout<<" JZ OPERAND ERROR....!!! "<<endl; return 0;
            }
            x = check_address_limit(instruction.substr(3,4));
            if(x == 1)
            {
                cout<<"JZ OPERAND ERROR....!!! "<<endl; return 0;
            }
            int f = 0,j=0;
            do
            {
                if(memory[j].address == instruction.substr(3,4) )
                {
                    f = 1;
                    break;
                }
                j++;
            }while(memory[j-1].mnemonic != "HLT");

            if( f == 0)
            {
                  cout<< "JZ OPERAND ERROR....!!! "<<endl; return 0;
            }
            if(ZF == 1)
            {
                 pc = instruction.substr(3,4);
            }
            else
            {
                   pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,2)));
            }
         }

        else if(  instruction[0] == 'A' && instruction[1] == 'D' && instruction[2] == 'D' && instruction[3] == ' ' )
        {
            if(instruction.length() != 5)
            {
                cout<<" ADD OPERAND ERROR....!!! "<<endl; return 0;
            }
            if("A" == instruction.substr(4,1))
            {
                ADD(A,A);
            }
            else if("B" == instruction.substr(4,1))
            {
               ADD(A,B);
            }
            else if("C" == instruction.substr(4,1))
            {
               ADD(A,C);
            }
            else if("D" == instruction.substr(4,1))
            {
                ADD(A,D);
            }
            else if("E" == instruction.substr(4,1))
            {
                ADD(A,E);
            }
            else if("H" == instruction.substr(4,1))
            {
                 ADD(A,H);
            }
            else if("L" == instruction.substr(4,1))
            {
                ADD(A,L);
            }
            else if("M" == instruction.substr(4,1))
            {
                string s = H + L;
                M = stack[hex_to_dec(s)].DATA;
                ADD(A,M);
            }
            else
            {
                cout<<" ADD OPERAND ERROR....!!! "<<endl; return 0;
            }
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }

        else if( instruction[0] == 'S' && instruction[1] == 'U' && instruction[2] == 'B' && instruction[3] == ' ')
        {
            l=0;
            l = instruction.length();
            if(l!=5)
            {
                cout<<" SUB OPERAND ERROR....!!! "<<endl; return 0;
            }
            if("A" == instruction.substr(4,1))
            {
                SUB(A,A);
            }
            else if("B" == instruction.substr(4,1))
            {
               SUB(A,B);
            }
            else if("C" == instruction.substr(4,1))
            {
               SUB(A,C);
            }
            else if("D" == instruction.substr(4,1))
            {
                SUB(A,D);
            }
            else if("E" == instruction.substr(4,1))
            {
                SUB(A,E);
            }
            else if("H" == instruction.substr(4,1))
            {
                 SUB(A,H);
            }
            else if("L" == instruction.substr(4,1))
            {
                SUB(A,L);
            }
             else if("M" == instruction.substr(4,1))
            {
                string s = H + L;
                M = stack[hex_to_dec(s)].DATA;
                SUB(A,M);
            }
            else
            {
                cout<<" SUB OPERAND ERROR....!!! "<<endl; return 0;
            }
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }
        else if(  instruction[0] == 'D' && instruction[1] == 'A' && instruction[2] == 'D' && instruction[3] == ' ')
        {
            l=instruction.length();
            if(l!=5)
            {
                cout<<" DAD OPERAND ERROR....!!! "<<endl; return 0;
            }
            if(instruction.substr(4,1) == "D")
            {
                 DAD(H,L,D,E);
            }
            else if(instruction.substr(4,1) == "B")
            {
                 DAD(H,L,B,C);
            }
                pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }
        else if( instruction[0] == 'M' && instruction[1] == 'O' && instruction[2] == 'V' && instruction[3] == ' ')
        {
                if(instruction.substr(0,7) == "MOV A,C")
                    MOV(A, C);
                else if(instruction.substr(0,7) == "MOV A,B")
                    MOV(A, B);
                else if(instruction.substr(0,7) == "MOV A,D")
                    MOV(A, D);
                else if(instruction.substr(0,7) == "MOV A,E")
                    MOV(A, E);
                else if(instruction.substr(0,7) == "MOV A,H")
                    MOV(A, H);
                else if(instruction.substr(0,7) == "MOV A,L")
                    MOV(A, L);
                else if(instruction.substr(0,7) == "MOV B,A")
                    MOV(B, A);
                else if(instruction.substr(0,7) == "MOV B,C")
                    MOV(B, C);
                else if(instruction.substr(0,7) == "MOV B,D")
                    MOV(B, D);
                else if(instruction.substr(0,7) == "MOV B,E")
                    MOV(B, E);
                else if(instruction.substr(0,7) == "MOV B,H")
                    MOV(B, H);
                else if(instruction.substr(0,7) == "MOV B,L")
                    MOV(B, L);
                else if(instruction.substr(0,7) == "MOV C,A")
                    MOV(C, A);
                else if(instruction.substr(0,7) == "MOV C,B")
                    MOV(C, B);
                else if(instruction.substr(0,7) == "MOV C,D")
                    MOV(C, D);
                else if(instruction.substr(0,7) == "MOV C,E")
                    MOV(C, E);
                else if(instruction.substr(0,7) == "MOV C,H")
                    MOV(C, H);
                else if(instruction.substr(0,7) == "MOV C,L")
                    MOV(C, L);
                else if(instruction.substr(0,7) == "MOV D,A")
                    MOV(D, A);
                else if(instruction.substr(0,7) == "MOV D,B")
                    MOV(D, B);
                else if(instruction.substr(0,7) == "MOV D,C")
                    MOV(D ,C);
                else if(instruction.substr(0,7) == "MOV D,E")
                    MOV(D, E);
                else if(instruction.substr(0,7) == "MOV D,H")
                    MOV(D, H);
                else if(instruction.substr(0,7) == "MOV D,L")
                    MOV(D, L);
                else if(instruction.substr(0,7) == "MOV E,A")
                    MOV(E, A);
                else if(instruction.substr(0,7) == "MOV E,B")
                    MOV(E, B);
                else if(instruction.substr(0,7) == "MOV E,C")
                    MOV(E, C);
                else if(instruction.substr(0,7) == "MOV E,D")
                    MOV(E, D);
                else if(instruction.substr(0,7) == "MOV E,H")
                    MOV(E, H);
                else if(instruction.substr(0,7) == "MOV E,L")
                    MOV(E, L);
                else if(instruction.substr(0,7) == "MOV H,A")
                    MOV(H, A);
                else if(instruction.substr(0,7) == "MOV H,B")
                    MOV(H, B);
                else if(instruction.substr(0,7) == "MOV H,C")
                    MOV(H, C);
                else if(instruction.substr(0,7) == "MOV H,D")
                    MOV(H, D);
                else if(instruction.substr(0,7) == "MOV H,E")
                    MOV(H, E);
                else if(instruction.substr(0,7) == "MOV H,L")
                    MOV(H, L);
                else if(instruction.substr(0,7) == "MOV L,A")
                    MOV(L, A);
                else if(instruction.substr(0,7) == "MOV L,B")
                    MOV(L, B);
                else if(instruction.substr(0,7) == "MOV L,C")
                    MOV(L, C);                                          //
                else if(instruction.substr(0,7) == "MOV L,D")
                    MOV(L, D);
                else if(instruction.substr(0,7) == "MOV L,E")
                    MOV(L, E);
                else if(instruction.substr(0,7) == "MOV L,H")
                    MOV(L, H);
                else if(instruction.substr(0,7) == "MOV M,A")
                {
                     string s = H + L;
                     stack[hex_to_dec(s)].DATA = A;
                }
                 else if(instruction.substr(0,7) == "MOV M,B")
                {
                     string s = H + L;
                     stack[hex_to_dec(s)].DATA = B;
                }
                 else if(instruction.substr(0,7) == "MOV M,C")
                {
                     string s = H + L;
                     stack[hex_to_dec(s)].DATA = C;
                }
                 else if(instruction.substr(0,7) == "MOV M,D")
                {
                     string s = H + L;
                     stack[hex_to_dec(s)].DATA = D;
                }
                 else if(instruction.substr(0,7) == "MOV M,E")
                {
                     string s = H + L;
                     stack[hex_to_dec(s)].DATA = E;
                }
                 else if(instruction.substr(0,7) == "MOV M,H")
                {
                     string s = H + L;
                     stack[hex_to_dec(s)].DATA = H ;
                }
                 else if(instruction.substr(0,7) == "MOV M,L")
                {
                     string s = H + L;
                     stack[hex_to_dec(s)].DATA = L;
                }
                 else if(instruction.substr(0,7) == "MOV A,M")
                {
                     string s = H + L;
                     A = stack[hex_to_dec(s)].DATA;
                }
                 else if(instruction.substr(0,7) == "MOV B,M")
                {
                     string s = H + L;
                     B = stack[hex_to_dec(s)].DATA;
                }
                 else if(instruction.substr(0,7) == "MOV C,M")
                {
                     string s = H + L;
                     C = stack[hex_to_dec(s)].DATA;
                }
                 else if(instruction.substr(0,7) == "MOV D,M")
                {
                     string s = H + L;
                     D = stack[hex_to_dec(s)].DATA;
                }
                 else if(instruction.substr(0,7) == "MOV E,M")
                {
                     string s = H + L;
                     E = stack[hex_to_dec(s)].DATA;
                }
                 else if(instruction.substr(0,7) == "MOV H,M")
                {
                     string s = H + L;
                     H = stack[hex_to_dec(s)].DATA;
                }
                 else if(instruction.substr(0,7) == "MOV L,M")
                {
                     string s = H + L;
                     L = stack[hex_to_dec(s)].DATA;
                }
                else
                {
                    cout<<" MOV OPERAND ERROR....!!! "<<endl; return 0;
                }

                pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }
        else if(  instruction[0] == 'S' && instruction[1] == 'T' && instruction[2] == 'A' && instruction[3] == ' ')
        {
                 l=instruction.length();
                 if(l!=8)
                 {
                    cout<<" STA OPERAND ERROR....!!! "<<endl; return 0;
                 }
                 x = check_address_limit(instruction.substr(4,4));
                 if(x == 1)
                 {
                    cout<<"STA OPERAND ERROR....!!! "<<endl; return 0;
                 }
                 STA(A,instruction.substr(4,4));
                 pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }

        else if(instruction[0] == 'L' && instruction[1] == 'X' && instruction[2] == 'I' && instruction[3] == ' ' && instruction[5] == ' '  )
        {
            l=instruction.length();
            if(l != 10)
            {
                cout<<" LXI OPERAND ERROR....!!! "<<endl; return 0;
            }
            if( instruction.substr(4,1) == "H" )
            {
                LXI( instruction.substr(6,4),H,L );
            }
            else if( instruction.substr(4,1) == "D" )
            {
                LXI( instruction.substr(6,4),D,E );
            }
            else if( instruction.substr(4,1) == "B" )
            {
                LXI( instruction.substr(6,4),B,C );
            }
            else
            {
                cout<<"LXI OPERAND ERROR....!!! "<<endl; return 0;
            }
            x = check_address_limit(instruction.substr(6,4));
            if( x == 1 )
            {
                cout<<"LXI OPERAND ERROR....!!! "<<endl; return 0;
            }
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }

        else if( instruction[0] == 'I' && instruction[1] == 'N' && instruction[2] == 'R' && instruction[3] == ' ' )
        {
            if(instruction.substr(0,5) == "INR A")
                INR(A);
            else if(instruction.substr(0,5) == "INR B")
                INR(B);
            else if(instruction.substr(0,5) == "INR C")
                INR(C);
            else if(instruction.substr(0,5) == "INR D")
                INR(D);
            else if(instruction.substr(0,5) == "INR E")
                INR(E);
            else if(instruction.substr(0,5) == "INR H")
                INR(H);
            else if(instruction.substr(0,5) == "INR L")
                INR(L);
            else if(instruction.substr(0,5) == "INR M" )
            {
                string s = H + L;
                M = stack[hex_to_dec(s)].DATA;
                INR(M);
            }
            else
            {
                cout<<"INR OPERAND ERROR....!!! "<<endl; return 0;
            }
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }
         else if( instruction[0] == 'D' && instruction[1] == 'C' && instruction[2] == 'R' && instruction[3] == ' ')
        {
            if(instruction.substr(0,5) == "DCR A")
                DCR(A);
            else if(instruction.substr(0,5) == "DCR B")
                DCR(B);
            else if(instruction.substr(0,5) == "DCR C")
                DCR(C);
            else if(instruction.substr(0,5) == "DCR D")
                DCR(D);
            else if(instruction.substr(0,5) == "DCR E")
                DCR(E);
            else if(instruction.substr(0,5) == "DCR H")
                DCR(H);
            else if(instruction.substr(0,5) == "DCR L")
                DCR(L);
            else if(instruction.substr(0,5) == "DCR M" )
            {
                string s = H + L;
                M = stack[hex_to_dec(s)].DATA;
                DCR(M);
            }
            else
            {
                cout<<"DCR OPERAND ERROR....!!! "<<endl; return 0;
            }
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }
        else if( instruction[0] == 'I' && instruction[1] == 'N' && instruction[2] == 'X' && instruction[3] == ' ')
        {

            if(instruction.substr(0,5) == "INX B")
                INX(B,C);
            else if(instruction.substr(0,5) == "INX D")
                INX(D,E);
            else if(instruction.substr(0,5) == "INX H")
                INX(H,L);
            else
            {
                cout<<" INX OPERAND ERROR....!!! "<<endl; return 0;
            }

            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }
        else if( instruction[0] == 'D' && instruction[1] == 'C' && instruction[2] == 'X' && instruction[3] == ' ')
        {

            if(instruction.substr(0,5) == "DCX B")
                DCX(B,C);
            else if(instruction.substr(0,5) == "DCX D")
                DCX(D,E);
            else if(instruction.substr(0,5)== "DCX H")
                DCX(H,L);
            else
            {
                cout<<"DCX OPERAND ERROR....!!! "<<endl; return 0;
            }

            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }
        else if( instruction[0] == 'S' && instruction[1] == 'U' && instruction[2] == 'I' && instruction[3] == ' ')
        {
            l=instruction.length();
            if(l!=6)
            {
                cout<<" SUI OPERAND ERROR....!!! "<<endl; return 0;
            }
            SUB( A, instruction.substr(4,2));
            x = check_data_limit(instruction.substr(4,2));
            if(x == 1)
            {
                cout<<"SUI OPERAND ERROR....!!! "<<endl; return 0;
            }
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }
        else if( instruction[0] == 'A' && instruction[1] == 'D' && instruction[2] == 'I' && instruction[3] == ' ')
        {
            l=instruction.length();
            if(l!=6)
            {
                cout<<" ADI OPERAND ERROR....!!! "<<endl; return 0;
            }
            ADD( A, instruction.substr(4,2));
            x = check_data_limit(instruction.substr(4,2));
            if(x == 1)
            {
                cout<<"ADI OPERAND ERROR....!!! "<<endl; return 0;
            }
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }
         else if( instruction[0] == 'C' && instruction[1] == 'M' && instruction[2] == 'P' && instruction[3] == ' ')
        {
            if(instruction == "CMP B")
                CMP(A,B);
            else if(instruction == "CMP C")
                CMP(A,C);
            else if(instruction == "CMP D")
                CMP(A,D);
            else if(instruction == "CMP E")
                CMP(A,E);
            else if(instruction == "CMP H")
                CMP(A,H);
            else if(instruction == "CMP L")
                CMP(A,L);
            else if(instruction == "CMP M")
            {
                string s = H + L;
                M = stack[hex_to_dec(s)].DATA;
                CMP(A,M);
            }
            else
            {
                cout<<"CMP OPERAND ERROR....!!! "<<endl; return 0;
            }
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }
        else if( instruction[0] == 'C' && instruction[1] == 'M' && instruction[2] == 'A' && instruction[3] == ' ')
        {
            l=instruction.length();
            if(l!=6)
            {
                cout<<" CMA OPERAND ERROR....!!! "<<endl; return 0;
                return 0;
            }
            CMA(A);
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }
        else if( instruction[0] == 'S' && instruction[1] == 'E' && instruction[2] == 'T' && instruction[3] == ' ' && instruction[8] == ' ')
        {
            l = instruction.length();
            if(l!=11)
            {
                cout<<" SET OPERAND ERROR....!!! "<<endl; return 0;
                return 0;
            }
            SET( instruction.substr(4,4),instruction.substr(9,2));
            x = check_address_limit(instruction.substr(4,4));
            if(x == 1)
            {
                cout<<"SET OPERAND(ADDRESS) ERROR....!!! "<<endl; return 0;
            }
            x = 0;
            x = check_data_limit(instruction.substr(9,2));
            if(x == 1)
            {
                cout<<"SET OPERAND(DATA) ERROR....!!! "<<endl; return 0;
            }
            pc = dec_to_hex(hex_to_dec(pc) + Return_bytes(instruction.substr(0,3)));
        }
        else if( instruction[0] == 'H' && instruction[1] == 'L' && instruction[2] == 'T')
        {

        }
        else
        {
            cout<<"Mnemonic Error....!!! "<<endl; return 0;
        }
    }while(instruction.substr(0,3) != "HLT" );

   cout << "\n--------REGISTER VALUES-------- "<<endl;
   cout << "A =";
   A=set_precision(A); cout<<A<<endl;
   cout << "B =";
   B=set_precision(B); cout<<B<<endl;
   cout << "C =";
   C=set_precision(C); cout<<C<<endl;
   cout << "D =";
   D=set_precision(D); cout<<D<<endl;
   cout << "E =";
   E=set_precision(E); cout<<E<<endl;
   cout << "H =";
   H=set_precision(H); cout<<H<<endl;
   cout << "L =";
   L=set_precision(L); cout<<L<<endl;

   cout << "\n\n---------USED MEMORY LOCATIONS---------- "<<endl;
   int f=0;
   for( i=0 ; i< 65535 ; i++)
   {
       if( stack[i].DATA != "\0")
       {
            f=1;
            string stack_data=stack[i].DATA;
            cout << dec_to_hex(i) << "=" ;
            stack_data = set_precision(stack_data);
            cout<<stack_data<<endl;
       }
   }
   if(f==0)
    cout<<"No memory locations used";
    cout << "\n\n----------FLAGS------------ "<<endl;
    show_FLAG(CF,ZF,SF,PF);
    inFile.close();
}
