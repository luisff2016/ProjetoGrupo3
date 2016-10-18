#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <string.h>

//Limites das Variaveis
#define MAX 1000        //Quantidade Maxima de Contatos
#define tNome 31        //Quantidade Maxima de Caracteres do Nome
#define tSnome 31       //Quantidade Maxima de Caracteres do Sobrenome
#define tFone 20        //Quantidade Maxima de Caracteres do Telefone
#define tEmail 61       //Quantidade Maxiam de Caracteres do Email


/* PROJETO DE PROGRAMAÇÃO IMPERATIVA */
/*  -Luis Fernando Feitosa.
    -Wendhio Thalison Neres dos Santos.
    -Rodrigo Oliveira Santos. */

/*definindo variavel para registro */

int total;
typedef struct{
int ordem;
char nome[tNome]; /* nao pode ser vazio*/
char sobrenome[tSnome];
char telefone[3][tFone]; /* modelo: '+01 (23) 45678 9012' */
char email[3][tEmail]; /* 'modelo_usu.1234567890abcdefghijklmnopqrstuvwxyz@local.aaa.bb' */
} TCONTATO;
TCONTATO fone;
TCONTATO agenda[MAX];

/* funcoes auxiliares*/
void menu();
int addMenu();
void adicionaContato();
int buscaContato();
void dadosContato();
void gravaContato(int i);
void veAgenda();


void leContato();
void veContato(int i);
void apagaContato();
void atualizaContato();
void encNome();
int tamNome(int i);
void ordenacao();

/* funcao principal*/
int main(){
    setlocale(LC_ALL, "portuguese");
    addMenu();
    return 0;
}

/* exibe menu de opcoes */
void menu(){
printf("\t============================================\n");
printf("\t\t\t AGENDA TELEFONICA \t\t\n");
printf("\t============================================\n");
printf ("\t1. Adicionar contato \n");
printf ("\t2. Apagar contato \n");
printf ("\t3. Atualizar contato \n");
printf ("\t4. Ver todos os contatos da agenda \n");
printf ("\t\t0. Sair do programa\n");
}

/* Menu de seleção */
int addMenu(){
    int opcao;
    do {
        system("cls");
        menu();
        printf("\nDigite a opção desejada do MENU\n\n");
        scanf("%d", &opcao);
        switch (opcao){
            case 0: break;
            case 1: adicionaContato(); break;
            case 2: apagaContato(); break;
            case 3: atualizaContato(); break;
            case 4: veAgenda(); break;
            default:{
                system("cls");
                printf("\n DIGITE UMA OPCAO VALIDA!\n\n");
                } break;
            }
    } while(opcao != 0);
    return 0;
}

void adicionaContato(){
    fone.nome[0]='\0';
    setbuf(stdin, NULL);
    system("cls");
    do {
        printf("Digite o primeiro nome:\n");
        gets(fone.nome);
    } while(fone.nome[0]=='\0' || fone.nome[0]=='\n');
    fone.sobrenome[0]='\0';
    setbuf(stdin, NULL);
    do {
        printf("Digite o sobrenome:\n");
        gets(fone.sobrenome);
    } while(fone.sobrenome[0]=='\0' || fone.sobrenome[0]=='\n');
    int i = buscaContato();
    if ( i != -1 ) {
        system("cls");
        printf("\nContato já registrado\n\n");
        printf("(pressione qualquer tecla)\n\n");
        getch(); }
    else if (total == MAX){
        system("cls");
        printf("\nNúmero máximo de contatos ultrapassado\n\n");
        printf("(pressione qualquer tecla)\n\n");
        getch(); }
    else {
        dadosContato();
        gravaContato(total);
        system("cls");
        printf("\nContato registrado com sucesso\n\n");
        printf("(pressione qualquer tecla)\n\n");
        getch();
        }
}

/* confere se a matricula ja foi registrada*/
int buscaContato(){
    int i;
    for (i=0; i<total ; i++)
    if (strcmp(agenda[i].nome, fone.nome) == 0 && strcmp(agenda[i].sobrenome, fone.sobrenome) == 0)
        return i;
    return -1;
}

void dadosContato(){
    int i;
    for (i=0; i<3; i++){
        printf("\nDigite o telefone %d: \n", i+1 );
        gets(fone.telefone[i]); }
    for (i=0; i<3; i++){
        printf("\nDigite o email %d: \n", i+1 );
        gets(fone.email[i]);
    }
}

void gravaContato(int i){
    agenda[total] = fone;
    total++;
}


void veContato(int i){
        register int j;
        //printf("\nOrdem: %d . ", agenda[i].ordem);
        printf("\nNome: %s ", agenda[i].nome);
        printf("\nSobrenome: %s\n", agenda[i].sobrenome);
        for (j=0; j<3; j++)
            printf("Fone %d: %s  \n", j+1, agenda[i].telefone[j]);
        for (j=0; j<3; j++)
            printf("Email %d: %s \n", j+1, agenda[i].email[j]);
        printf("(pressione qualquer tecla)\n\n");
        getch();
}



void veAgenda(){
    int i;
    for (i=0 ; i<total ; i++)
        veContato(i);
    system("cls");
    printf("\nTodos os contatos foram mostrados.\n\n");
    printf("(pressione qualquer tecla)\n\n");
    getch();
}

void apagaContato(){
    int j;
    buscaContato();
    printf("\nQual contato deseja apagar:\n\n");
    scanf("%d", &fone.ordem);
    agenda[j]=agenda[total-1];
    total--;
    system("cls");
    printf("\ncontato apagado \n\n\n");
    system("cls");
    printf("\ncontato nao existe\n\n\n");
}

void atualizaContato(){
    int i, checkalt=0;
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin);
    gets(fone.nome);
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin);
    gets(fone.sobrenome);
    for (i=0; i<total ; i++){
        if (strcmp(agenda[i].nome, fone.nome) == 0 && strcmp(agenda[i].sobrenome, fone.sobrenome) == 0) {
            dadosContato();
            agenda[i]=fone;
            checkalt++;
            }
        }
    if(checkalt==0){
        system("cls");
        printf("\nEsse contato não existe.\n\n");
        printf("(pressione qualquer tecla)\n\n");
        getch();
    }
    else {
        system("cls");
        printf("\nContato alterado com sucesso.\n\n");
        printf("(pressione qualquer tecla)\n\n");
        getch();
    }
}

/*void verMatAluno(){
    int i = buscaContato();
    printf("\n Qual matricula deseja visualisar?\n");
    scanf("%d", &fone.ordem);

    if ( i != -1 )
        {
        for (i=0; i<total ; i++)
            {
            if (agenda[i].nome == fone.nome) {
                veContato(i);
                system("cls");
                printf("\nRegistro visualizado.\n\n\n"); }
            }
        }
    else { system("cls");
        printf("\n Registro inexistente\n\n\n"); }
}*/


/* Rotina de ordenação */
/*
void ordenacao(){
    int i,j;
    for(i = 1; i<total; i++)
        for (j = 0; j<total-1 ; j++)
            if (strcmp(agenda.nome[j],agenda.nome[j+1]) > 0)
            {
                strcpy(fone,agenda[j]);
                strcpy(agenda.nome[j],agenda.nome[j+1]);
                strcpy(agenda.nome[j+1],fone);
            }
    printf("Imprimindo os nomes ordenados\n");
    for(i = 0; i < qtd;++i)
        printf("%s\n",nomes[i]);
}
*/

/*void verMedia(){
    int i = buscaEstudante(est);
    printf("\n Digite a matrícula do aluno.\n");
    scanf("%d", &est.cpf);

    if ( i != -1 )
        {
        for (i=0; i<codCadastro; i++)
            {
            if (aluno[i].cpf == est.cpf){
                system("cls");
                printf("\nMEDIA DO ALUNO %s: %.2f\n\n\n", aluno[i].nome, aluno[i].media); }
            }
        }
    else { system("cls");
        printf("\n Registro inexistente\n\n\n"); }
}*/

/*void ordemMedia(){
    int i,h;
    for (i=0; i<codCadastro-1; i++)
    {
        for (h=0; h<codCadastro-1-i ; h++)
        {
            if (aluno[h].media>aluno[h+1].media)
            {
                est=aluno[h+1];
                aluno[h+1]=aluno[h];
                aluno[h]=est;
            }
        }
    }
}*/

/*void maiorMedia(){
    int i = codCadastro-1;
    ordemMedia();

    system("cls");
    printf ("\nAluno %s tem a maior media: %.2f \n\n\n", aluno[i].nome, aluno[i].media);
}

void menorMedia(){
    ordemMedia();
    system("cls");
    printf ("\nAluno %s tem a menor media: %.2f \n\n\n", aluno[0].nome, aluno[0].media);
}*/

/*void encNome(){
    int i, tamStr, check=0;
    printf("\n Digite nome do aluno:\n");
    fflush(stdin);
    gets(fone.nome);
    tamStr=strlen(fone.nome);
    for (i=0; i<total ; i++)
    {
        if(memcmp(fone.nome, agenda[i].nome, tamStr)==0){
            veContato(i);
            check++;
        }
    }
    if(check==0){
        system("cls");
        printf("\nRegistro inexistente.\n\n\n"); }
    else {
        system("cls");
        printf("\nRegistro visualizado com sucesso.\n\n\n");
    }
}*/

/*int tamNome(int i){
    int j=0;
    while (agenda[i].nome[j] != '\0')
        j++;
    return j;
}*/

/*
void verMediaOrdem(){
    ordemMedia();
    verTodos();
}
*/

/*
char* temp = (char*) malloc(50*sizeof(char));
nomes = (char**) malloc(qtd*sizeof(char*));
    for(i=0 ; i<total ; ++i){
        printf("Entre com nome %i : ", i );
        scanf("%s", agenda.nome[i]);
        printf("\n");
    }
*/
