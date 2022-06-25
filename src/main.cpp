#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

#define mainfunc int main(int argc, char** argv)
#define sBuff malloc

void finish(FILE* file,char* source,int e){
  free(source);
  fclose(file);
  if(e>=0) exit(e);
}

int interpret(FILE* source, int memLen)
{
    int ptrindex = 0, codeIndex; 
    char tape[memLen];
    fseek(source,0,SEEK_END);
    int source_len = ftell(source);
    char* code=(char*) sBuff(source_len);
    rewind(source);
    memset(tape, '\0', memLen);



    for(int a=0; a<source_len; a++)
        code[a] = fgetc(source);
    while(codeIndex < source_len)
    {
        char c = code[codeIndex]; 
        switch(c)
        {
            case '+':
                if(tape[ptrindex] + 1 >= 127) 
                    tape[ptrindex] = 0;
                else
                    tape[ptrindex]++;
                break;
            case '-':
                if(tape[ptrindex] - 1 <= -1)
                    tape[ptrindex] = 126;
                else
                    tape[ptrindex]--;
                break;
            case '.':
                fprintf(stdout,"%c", tape[ptrindex]);
                break;
            case ',':
                tape[ptrindex] = fgetc(stdin); 
                break;
            case '>':
                ptrindex++; 
                break;
            case '<':                
                ptrindex--;
                break;
            case '[':
                if (!tape[ptrindex]){
                        int open=1;
                        while(open){
                            if(++codeIndex==source_len) finish(source,code,0);
                            if(code[codeIndex]=='[') open++;
                            if(code[codeIndex]==']') open--;
                        }
                }
                break;
            case ']':
                if (tape[ptrindex]){
                        int close=1;
                        while(close){
                            if(--codeIndex==-1) finish(source,code,0);
                            if(code[codeIndex]=='[') close--;
                            if(code[codeIndex]==']') close++;
                        }
                }
                break;
            default:
                break;
        }
        codeIndex++;
    }
    finish(source, code, -1);
    free(tape);
    return 0;
}



mainfunc{
    if(argc !=3)
    {   
        fprintf(stderr, "Usage: [File] [memLen]\n");
        exit(1);
    }
    FILE *source = fopen(argv[1], "r");
    if(!source){
        fprintf(stderr,"File not found or could not be open, please check if the filename is right\n");
        exit(1);
    }
    interpret(source, atoi(argv[2])); 
}


