#include<iostream>
#include<stdio.h>
#include<string.h>
#include"scan.h"

//using namespace std;
//extern Tk *getTokens(char *nome);

/////*********************************
// * Nome: main
// * desc:
// * returno:
// ********************************/
int main(int argc, char *argv[])
{
    char nome[50] = "mdc.c";
    //Tk* tokens = getTokens(nome);

    if (argc == 2)
    {
        strcpy (nome, argv[1]);
    }else
    {
        //printf("Digite o nome do arquivo:");
        //scanf("%s", &nome);
    }

    Tk* tokens = getTokens(nome);
    exibeTk(tokens);

    return 0;
}
