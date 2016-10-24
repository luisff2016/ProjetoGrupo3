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

typedef struct{
int ordem;
char nome[tNome]; /* nao pode ser vazio*/
char sobrenome[tSnome];
char telefone[3][tFone]; /* modelo: '+01 (23) 45678 9012' */
char email[3][tEmail]; /* 'modelo_usu.1234567890abcdefghijklmnopqrstuvwxyz@local.aaa.bb' */
} TCONTATO;
TCONTATO fone;
TCONTATO agenda[MAX];

int total=0;
FILE* agendadados;
FILE* ncontatos;

/* funcoes auxiliares*/
void menu();
int addMenu();
void adicionaContato();
int buscaContato();
void dadosContato();
void gravaContato(int i);
void veAgenda();
void salvarDados();
void carregarDados();


void leContato();
void veContato(int i);
void encNomeSobrenome();
void encNome();
void encSobrenome();
void apagaContato();
void atualizaContato();
int tamNome(int i);
void ordenacao();

/* funcao principal*/
int main(){
    setlocale(LC_ALL, "portuguese");
    carregarDados();
    addMenu();
    salvarDados();      // Além de ser executado aqui ao fim do programa, também é executado na função 'addMenu'
    return 0;           // salvando os dados sempre que o programa volta para o menu, evitando perda de dados
}                       // no caso do usuario fechar o programa de forma inadequada.

/* exibe menu de opcoes */
void menu(){
printf("\t============================================\n");
printf("\t\t\t AGENDA TELEFONICA \t\t\n");
printf("\t============================================\n");
printf ("\t1. Adicionar contato \n");
printf ("\t2. Apagar contato \n");
printf ("\t3. Atualizar contato \n");
printf ("\t4. Ver todos os contatos da agenda \n");
printf ("\t5. Procurar um contato espefico(Nome e Sobrenome) \n");
printf ("\t6. Mostrar todos os contatos com o mesmo nome \n");
printf ("\t7. Mostrar todos os contatos com o mesmo sobrenome \n");
printf ("\t\t0. Sair do programa e salvar os contatos\n");
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
            case 5: encNomeSobrenome(); break;
            case 6: encNome(); break;
            case 7: encSobrenome(); break;
            default:{
                system("cls");
                printf("\n DIGITE UMA OPCAO VALIDA!\n\n");
                } break;
            }
            salvarDados(); // Executa aqui, pra evitar que dados se percam, no caso do programa ser fechado de forma inadequada.
    } while(opcao != 0);
    return 0;
}

/* Lê nome e sobrenome, e, se não forem repetidos, lê e grava os outros dados */
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

/* Lê os demais dados */
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

/* Grava a leitura feita, na agenda*/
void gravaContato(int i){
    agenda[total] = fone;
    total++;
}

/* confere se o contato ja foi registrada*/
int buscaContato(){
    int i;
    for (i=0; i<total ; i++)
    if (strcmp(agenda[i].nome, fone.nome) == 0 && strcmp(agenda[i].sobrenome, fone.sobrenome) == 0)
        return i;
    return -1;
}

/* Imprime um contato */
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

/* Imprime todos os contatos */
void veAgenda(){
    int i;
    for (i=0 ; i<total ; i++)
        veContato(i);
    system("cls");
    printf("\nTodos os contatos foram mostrados.\n\n");
    printf("(pressione qualquer tecla)\n\n");
    getch();
}

/* Busca por um contato especifico*/
void encNomeSobrenome(){
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin);
    gets(fone.nome);
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin);
    gets(fone.sobrenome);
    int i=buscaContato();
    if(i==-1){
        system("cls");
        printf("Nenhum contato encontrado!!");
        printf("\n(Pressione qualquer tecla)\n\n");
        getch();
    } else
        veContato(i);
}

/* Mostra todos os contatos com o mesmo nome */
void encNome(){
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin);
    gets(fone.nome);
    int i;
    for (i=0 ; i<total ; i++){
        if (strcmp(agenda[i].nome, fone.nome) == 0)
            veContato(i);
    }
    system("cls");
    printf("\nTodos os contatos de nome: '%s' foram mostrados.\n\n", fone.nome);
    printf("(pressione qualquer tecla)\n\n");
    getch();
}

/* Mostra todos os contatos com o mesmo sobrenome */
void encSobrenome(){
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin);
    gets(fone.sobrenome);
    int i;
    for (i=0 ; i<total ; i++){
        if (strcmp(agenda[i].sobrenome, fone.sobrenome) == 0)
            veContato(i);
    }
    system("cls");
    printf("\nTodos os contatos de sobrenome: '%s' foram mostrados.\n\n", fone.sobrenome);
    printf("(pressione qualquer tecla)\n\n");
    getch();
}

/* Apaga um contato */
void apagaContato(){
    printf("\nDigite o primeiro nome do contato que deseja apagar:\n");
    fflush(stdin);
    gets(fone.nome);
    printf("\nDigite o sobrenome do contato que deseja apagar:\n");
    fflush(stdin);
    gets(fone.sobrenome);
    int i = buscaContato();
    if ( i != -1 )
    {
        int j;
        for (j=i; j<total; j++)
            agenda[j]=agenda[j+1];
        total--;
        system("cls");
        printf("\n Registro apagado \n\n\n");
        printf("(pressione qualquer tecla)\n\n");
        getch();
    }
    else { system("cls");
           printf("\n Contato nao existe\n\n\n");
           printf("(pressione qualquer tecla)\n\n");
            getch(); }
}

/* Atualiza um contato */
void atualizaContato(){
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin);
    gets(fone.nome);
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin);
    gets(fone.sobrenome);
    int i, checkalt=0;
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

/* Salva os dados no arquivo */
void salvarDados(){
    agendadados = fopen("agd.bin", "wb");
    if(agendadados == NULL){
        system("cls");
        printf("Opa!! parece que houve um problema ao tentar salvar os contatos. x.x");
        printf("\n(Pressione qualquer tecla)");
        getch(); }
    else
    fwrite(&agenda, sizeof(TCONTATO), total, agendadados);
    fclose(agendadados);

    ncontatos = fopen("nco.bin", "wb");
    if(ncontatos == NULL){
        system("cls");
        printf("Opa!! parece que houve um problema ao tentar salvar os contatos. x.x");
        printf("\n(Pressione qualquer tecla)");
        getch(); }
    else
    fprintf(ncontatos, "%d", total);
    fclose(ncontatos);
}

/* Carrega os contatos a partir do arquivo*/
void carregarDados(){
    ncontatos = fopen("nco.bin", "rb");
    if(ncontatos != NULL)
        fscanf(ncontatos, "%d", &total);
    fclose(ncontatos);

    if(total!=0) {
        agendadados = fopen("agd.bin", "rb");
        if(agendadados == NULL){
            printf("Opa!! parece que houve um problema ao tentar carregar os contatos. x.x");
            printf("\n(Pressione qualquer tecla)");
            getch();
            system("cls"); }
        else
            fread(&agenda, sizeof(TCONTATO), total, agendadados);
        fclose(agendadados); }
}

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

/*
char* temp = (char*) malloc(50*sizeof(char));
nomes = (char**) malloc(qtd*sizeof(char*));
    for(i=0 ; i<total ; ++i){
        printf("Entre com nome %i : ", i );
        scanf("%s", agenda.nome[i]);
        printf("\n");
    }
*/
