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
    //char nome[100];

    //printf("Digite o nome do arquivo:");
    //scanf("%s", &nome);

    //Tk* tokens = getTokens(nome);

    Tk* tokens = getTokens("mdc.c");

    return 0;
}
