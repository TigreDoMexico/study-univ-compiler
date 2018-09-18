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
void newLine(FILE *p);
void getWord(FILE *p);
void getNum(FILE *p);
void getOp(FILE *p);
void skipComment(FILE *p);
void getOp(FILE *p);
int isOp(char c);
void getNum(FILE *p);

/***********************************************
 * Nome: getTokens
 * desc: obtem todos os tokens do arquivo nome
 * returno: ponteiro para a lista de tokens
 ***********************************************/
Tk *getTokens(char *nome)
{
    Tk *TkList = NULL, *elemento = NULL;
    FILE *p;
    char c;

    p = abreArq(nome);

    linha = 1;
    ntoken = 0;
    nextChar(p);
    printf("LINHA %d - ", linha);

    do{
        scan(p);

        //instanciar struct
        //inserir na lista

            Tk* item = (Tk*) malloc(sizeof(Tk));
            item->prox = NULL;
            item->linha = linha;
            item->nome = (char) malloc(sizeof()*strlen(token));

            strcpy(item->nome, token);

            insereTk(*Tk, *item);

        if(token[0] != '\0')
            printf("%s ", token);

    } while(look != EOF);

    printf("\n");
    printf("Total de linhas: %d\n", linha);
    printf("Total de tokens: %d\n", ntoken);


    return TkList;
}

/*********************************
 * Nome: scan
 * desc: verifica cada caracter de um FILE
 * returno: null
 ********************************/
void scan(FILE *p)
{
    //char look
    // look = fgetc(p);
    //printf("%c", look);
    //if(look >47 && look <58) // se é numero
    //{
            // getNum();
    //}else if (look >64 && < 91 || look > 96 && <123)
    //{
            //getName();
    //}else
        //isopr();



    // How to Preencher o  structo
    //





    memset(token, 0, 256);
    char aux;

    if(look == '\n' || look == '\0'){
        newLine(p);
        //nextChar(p);
        printf("\n");
        printf("LINHA %d - ", linha);

    }else{

        if(look == ' ' || look == '\t')
            skipWhite(p);

        if(look >= '0' && look <= '9'){
            getNum(p);
        }else{
            if(isOp(look) == 0)
                getWord(p);
            else
                getOp(p);
        }
    }

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
    if(var ==NULL) // O ARQUIVO N�O TEM EXTEN��O
    {
        printf("Arquivo : %s invalido!\n",nome);
        exit(1); // cada erro ser� tratado com uma sa�da diferente de 0.
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
void insereTk(Tk *TkList, Tk *TkElemento)
{
    Tk *ptr;




}

/*********************************
 * Nome: exibeTk
 * desc:
 * returno: void
 ********************************/
void exibeTk(Tk *TkList)
{
    Tk *ptr;

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
        printf("%c ", look);
        nextChar(p);
    }

}

/*********************************
 * Nome: newLine
 * desc:
 * returno:
 ********************************/
void newLine(FILE *p)
{


    do{
        look = getc(p);
    }while(look == '\n' || look == '\0');


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
    printf("%c ", look);
    ntoken++;
    nextChar(p);
}

/*********************************
 * Nome: getString
 * desc:
 * returno:
 ********************************/
void getString(FILE *p)
{
    while(look != '"'){
        printf("%c", look);
        nextChar(p);
    }

    printf("%c ", look);
    nextChar(p);
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
    }while(look != ' ' && look != '\n' && isOp(look) == 0 && i < 256);



    if(look == '\n')
        linha++;



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
    char aux = look;
    std::string doubleOperator = "";
    std::string operators[17] = {"!=", "==", ">=", "<=", "+=", "-=", "*=", "/=", "%=", "||", "&&", "<<", ">>", "::", "++", "--", "**"};

    nextChar(p);

    if(look == '\n')
        linha++;

    if(aux == '"'){
        getString(p);
    }else{
        if(aux == '/' && (look == '/' || look == '*')){
            skipComment(p, look == '/');
        }else{
            if(isOp(look) == 0){
                printf("%c ", aux);
                ntoken++;
            }else{
                int hasAny = 0;

                doubleOperator += aux;
                doubleOperator += look;

                for(i = 0; i < 16; i++){
                    if(operators[i] == doubleOperator){
                        hasAny = 1;
                        break;
                    }
                }

                if(hasAny == 1){
                    ntoken++;
                    printf("%c", aux);
                    printf("%c ", look);
                }
            }
        }
    }
}

/*********************************
 * Nome: isOp
 * desc:
 * returno: 1 - Se é caractere especial / 0 - se não é
 ********************************/
int isOp(char c)
{
    return (strchr("#,.+-*/<>:=!", c) != NULL); //Returns a pointer to the first occurrence of character in the C string str.
}

