#include<iostream>
#include<stdio.h>
#include<list>
#include<string.h>
#include<stdlib.h>
#include"scan.h"

using namespace std;
//extern Tk *getTokens(char *nome);
Tk* tokens;
list<Tk*> simbolos;
list<Tk*> pReservadas;
list<Tk*> listId;
int contId;

void analiseLexica();
void loadPr();
void loadId();

/////*********************************
// * Nome: main
// * desc:
// * returno:
// ********************************/
int main(int argc, char *argv[])
{
    contId = 0;
    char nome[50] = "mdc.c";
    //Tk* tokens = getTokens(nome);

    if (argc == 2)
    {
        strcpy (nome, argv[1]);
    }else
    {
        printf("Digite o nome do arquivo:");
        scanf("%s", &nome);
    }

    tokens = getTokens(nome);
    exibeTk(tokens);
    analiseLexica();
    listId.clear();

    return 0;
}

void analiseLexica(){
    Tk *list;
    //list <Tk*>::iterator it;

   //for(it = simbolos.front(); it !=NULL; it++){
   //}

   for(list = tokens; list != NULL; list++){

   }
}

//os outros sao iguais esta palavras reservadas, mas terão outros tokens na matriz char
void loadPr(){
    char nome[][15]={"int","char","float","double","short","long"};
    Tk *l;

    for(int i=0; i<6; i++)
    {
        l = (Tk*) malloc(sizeof(Tk));
        l->nome = (char*)malloc(sizeof(char)*strlen(nome[0]));
        strcpy(l->nome, nome[i]);
        l->id = contId;
        contId++;
        pReservadas;

    }
}

void loadId(){
    char nome[][15]={"int","char","float","double","short","long"};
    Tk *l;

    for(int i=0; i<6; i++)
    {
        l = (Tk*) malloc(sizeof(Tk));
        l->nome = (char*)malloc(sizeof(char)*strlen(nome[0]));
        strcpy(l->nome, nome[i]);
        l->id = contId;
        contId++;
        listId.push_front(l);
        pReservadas;

    }
}
