#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include <ctype.h>
#include "scan.h"

// variaveis globais
int linha;
int coluna;
char look;
char token[256];
int ntoken;

// funcoes locais
FILE *abreArq(char *nome);
void nextChar(FILE *p);
void scan(FILE *P);
void skipWhite(FILE *p);
void skipString(FILE *p);
void newLine(FILE *p);
void getWord(FILE *p);
void getNum(FILE *p);
void getOp(FILE *p);
void skipComment(FILE *p);
void getOp(FILE *p);
int isOp(char c);
void getNum(FILE *p);

Tk *TkList = NULL;

/***********************************************
 * Nome: getTokens
 * desc: obtem todos os tokens do arquivo nome
 * returno: ponteiro para a lista de tokens
 ***********************************************/
Tk* getTokens(char *nome)
{
    Tk *elemento = NULL;
    FILE *p;
    char c;

    p = abreArq(nome);

    linha = 1;
    ntoken = 0;
    nextChar(p);

    do{
        scan(p);

        //instanciar struct
        //inserir na lista

        Tk* item = (Tk*) malloc(sizeof(Tk));
        item->prox = NULL;
        item->linha = linha;
        item->nome = (char*)malloc(strlen(token) * sizeof(char));

        strcpy(item->nome, token);

        insereTk(item);

    } while(look != EOF);

    return TkList;
}

/*********************************
 * Nome: scan
 * desc: verifica cada caracter de um FILE
 * returno: null
 ********************************/
void scan(FILE *p)
{
    // How to Preencher o  structo
    //

    memset(token, 0, 256);
    char aux;

    // PROXIMA LINHA
    newLine(p);

    // PULAR BRANCO
    skipWhite(p);

    // PULAR STRING
    if(look == 34){
        skipString(p);
    }else{
        // PEGAR PALAVRA
        if((look > 64 && look < 91) || (look > 96 && look < 123)){
            getWord(p);
        }else{
            // PEGAR NUMERO
            if((look > 48 && look < 58)){
                getNum(p);
            }else{
                getOp(p);
            }
        }
    }




    // PEGANDO P PROXIMO CARACTERE
    //nextChar(p);
}

/*********************************
 * Nome: abreArq
 * desc: abre o arquivo .c no formato string e salva em in
 * returno: FILE in
 ********************************/
FILE *abreArq(char *nome)
{
    char *var;
    FILE *in;

    var = strstr(nome,".c");
    if(var == NULL) // O ARQUIVO NAO TEM EXTENSAO
    {
        printf("Arquivo : %s invalido!\n",nome);
        exit(1); // cada erro sera tratado com uma sa�da diferente de 0.
    }
    in = fopen(nome,"r");
    if(in == NULL)
    {
        printf("Nao foi possivel abrir o arquivo %s \n",nome);
        exit(3);
    }
    return in;
}

/*********************************
 * Nome: insereTk
 * desc:
 * returno: void
 ********************************/
void insereTk(Tk *TkElemento)
{
    Tk *ptr;

    if(TkList == NULL)
        TkList = TkElemento;
    else{

        for(ptr = TkList; ptr->prox != NULL; ptr = ptr->prox);

        ptr->prox = TkElemento;
    }
}

/*********************************
 * Nome: exibeTk
 * desc:
 * returno: void
 ********************************/
void exibeTk(Tk *TkList)
{
    Tk *ptr;

    int li = 0;

    for(ptr = TkList; ptr->prox != NULL; ptr = ptr->prox){
        if(ptr->linha != li){
            li = ptr->linha;
            printf("\nLINHA %d: ", li);
            printf("%s ", ptr->nome);
        }else{

            printf("%s", ptr->nome);
            printf(" ");
        }
    }

    printf("\n\n");
    printf("Total de linhas: %d\n", linha - 1);
    printf("Total de tokens: %d\n", ntoken);

}

/*********************************
 * Nome: removeTk
 * desc:
 * returno: void
 ********************************/
void liberaTk(Tk *TkList)
{
    Tk *T,*ptr;
}

/*********************************
 * Nome: buscaTk
 * desc:
 * returno: void
 ********************************/
void removeTk(Tk *TkList, int chave)
{

}

/*********************************
 * Nome: nextChar
 * desc:
 * returno:
 ********************************/
void nextChar(FILE *p)
{
    if(look != EOF) // EOF(End Of File)
    {
        look = getc(p);
    }
}

/*********************************
 * Nome: removeSpace
 * desc:
 * returno:
 ********************************/
void skipWhite(FILE *p)
{
    while (look == ' ' || look == '\t'){
        nextChar(p);
    }
}

/*********************************
 * Nome: skipString
 * desc:
 * returno:
 ********************************/
void skipString(FILE *p)
{
    int i = 1;
    token[0] = look;

    nextChar(p);

    while(look != 34 && i < 253){
        token[i] = look;
        nextChar(p);

        i++;
    }

    nextChar(p);

    if(i < 253){
        token[i] = '\"';
        token[i + 1] = '\0';
    }else{
        token[i] = '\0';
    }


}

/*********************************
 * Nome: newLine
 * desc:
 * returno:
 ********************************/
void newLine(FILE *p)
{
    while(look == '\n' || look == 13)
    {
        if(look == '\n'){
            linha++;
        }

        look = getc(p);
    }
}

/*********************************
 * Nome: skipComment
 * desc:
 * returno:
 ********************************/
void skipComment(FILE *p, int isSingleLine)
{
    std::string doubleOperator = "";
    char aux = look;
    nextChar(p);

    doubleOperator += aux;
    doubleOperator += look;

    while((isSingleLine == 1 && aux != '\n') || (isSingleLine == 0 && doubleOperator != "*/")){
        aux = look;
        nextChar(p);

        doubleOperator = "";
        doubleOperator += aux;
        doubleOperator += look;

        //printf("%c", aux);
        //printf("%c", look);
    }
}

/*********************************
 * Nome: getNum
 * desc:
 * returno:
 ********************************/
void getNum(FILE *p)
{
    int i = 0;

    do{
        token[i] = look;
        nextChar(p);
        i++;
    }while(look > 48 && look < 58 && i < 256);

    token[i] = '\0';
    ntoken++;
}

/*********************************
 * Nome: getWord
 * desc: salva uma palavra na variavel token[256]
 * returno:
 ********************************/
void getWord(FILE *p)
{
    int i = 0;

    do{
        token[i] = look;
        nextChar(p);
        i++;
    }while((look > 64 && look < 91) || (look > 96 && look < 123) && i < 256);

    token[i] = '\0';
    ntoken++;
}

/*********************************
 * Nome: getOp
 * desc: printa o caractere
 * returno:
 ********************************/
void getOp(FILE *p)
{
    int i = 0;

    do{
        token[i] = look;
        nextChar(p);
        i++;
    }while(isOp(look) == 1);

    token[i] = '\0';
    ntoken++;
}

/*********************************
 * Nome: isOp
 * desc:
 * returno: 1 - Se é caractere especial / 0 - se não é
 ********************************/
int isOp(char c)
{
    return (strchr("#,.+-*/<>:=!{}()", c) != NULL); //Returns a pointer to the first occurrence of character in the C string str.
}

