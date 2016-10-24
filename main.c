#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <string.h>

/*Limites das Variaveis*/
#define TAM_MAX 1000       /*Quantidade maxima de Contatos*/
#define TAM_NOME 31        /*Quantidade maxima de Caracteres do Nome*/
#define TAM_SOBRENOME 31   /*Quantidade maxima de Caracteres do Sobrenome*/
#define TAM_FONE 20        /*Quantidade maxima de Caracteres do Telefone*/
#define TAM_EMAIL 61       /*Quantidade maxima de Caracteres do Email*/


/* PROJETO DE PROGRAMAÇÃO IMPERATIVA */
/*  -Luis Fernando Feitosa.
    -Wendhio Thalison Neres dos Santos.
    -Rodrigo Oliveira Santos. */

/*definindo variavel para registro */
typedef struct{
int ordem;
char nome[TAM_NOME]; /* nao pode ser vazio*/
char sobrenome[TAM_SOBRENOME];
char telefone[3][TAM_FONE]; /* modelo: '+01 (23) 45678 9012' */
char email[3][TAM_EMAIL]; /* 'modelo_usu.1234567890abcdefghijklmnopqrstuvwxyz@local.aaa.bb' */
} TCONTATO;
TCONTATO fone;
TCONTATO agenda[TAM_MAX];

int total=0;
FILE* agendadados;
FILE* ncontatos;

/* funcoes auxiliares*/
void Menu();
int AddMenu();
void AdicionaContato();
int BuscaContato();
void DadosContato();
void GravaContato(int i);
void VerAgenda();
void SalvarDados();
void CarregarDados();
void LerContato();
void VerContato(int i);
void EncNomeSobrenome();
void EncNome();
void EncSobrenome();
void ApagaContato();
void AtualizaContato();
int TamNome(int i);
void Ordenacao();

/* funcao principal*/
int main(){
    setlocale(LC_ALL, "portuguese");
    CarregarDados();
    AddMenu();
    SalvarDados();
    /*Além de ser executado aqui ao fim do programa, também é executado na função 'addMenu'
    salvando os dados sempre que o programa volta para o menu, evitando perda de dados
    no caso do usuario fechar o programa de forma inadequada.*/
    return 0;
}

/* exibe menu de opcoes */
void Menu(){
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
int AddMenu(){
    int opcao;
    do {
        system("cls");
        Menu();
        printf("\nDigite a opção desejada do MENU\n\n");
        scanf("%d", &opcao);
        switch (opcao){
            case 0: break;
            case 1: AdicionaContato(); break;
            case 2: ApagaContato(); break;
            case 3: AtualizaContato(); break;
            case 4: VerAgenda(); break;
            case 5: EncNomeSobrenome(); break;
            case 6: EncNome(); break;
            case 7: EncSobrenome(); break;
            default:{
                system("cls");
                printf("\n DIGITE UMA OPCAO VALIDA!\n\n");
                } break;
            }
            SalvarDados(); /*Executa aqui, pra evitar que dados se percam, no caso do programa ser fechado de forma inadequada.*/
    } while(opcao != 0);
    return 0;
}

/* Lê nome e sobrenome, e, se não forem repetidos, lê e grava os outros dados */
void AdicionaContato(){
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
    int i = BuscaContato();
    if ( i != -1 ) {
        system("cls");
        printf("\nContato já registrado\n\n");
        printf("(pressione qualquer tecla)\n\n");
        getch(); }
    else if (total == TAM_MAX){
        system("cls");
        printf("\nNúmero máximo de contatos ultrapassado\n\n");
        printf("(pressione qualquer tecla)\n\n");
        getch(); }
    else {
        DadosContato();
        GravaContato(total);
        system("cls");
        printf("\nContato registrado com sucesso\n\n");
        printf("(pressione qualquer tecla)\n\n");
        getch();
        }
}

/* Lê os demais dados */
void DadosContato(){
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
void GravaContato(int i){
    agenda[total] = fone;
    total++;
}

/* confere se o contato ja foi registrada*/
int BuscaContato(){
    int i;
    for (i=0; i<total ; i++)
    if (strcmp(agenda[i].nome, fone.nome) == 0 && strcmp(agenda[i].sobrenome, fone.sobrenome) == 0)
        return i;
    return -1;
}

/* Imprime um contato */
void VerContato(int i){
        register int j;
        /*printf("\nOrdem: %d . ", agenda[i].ordem);*/
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
void VerAgenda(){
    int i;
    for (i=0 ; i<total ; i++)
        VerContato(i);
    system("cls");
    printf("\nTodos os contatos foram mostrados.\n\n");
    printf("(pressione qualquer tecla)\n\n");
    getch();
}

/* Busca por um contato especifico*/
void EncNomeSobrenome(){
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin);
    gets(fone.nome);
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin);
    gets(fone.sobrenome);
    int i=BuscaContato();
    if(i==-1){
        system("cls");
        printf("Nenhum contato encontrado!!");
        printf("\n(Pressione qualquer tecla)\n\n");
        getch();
    } else
        VerContato(i);
}

/* Mostra todos os contatos com o mesmo nome */
void EncNome(){
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin);
    gets(fone.nome);
    int i;
    for (i=0 ; i<total ; i++){
        if (strcmp(agenda[i].nome, fone.nome) == 0)
            VerContato(i);
    }
    system("cls");
    printf("\nTodos os contatos de nome: '%s' foram mostrados.\n\n", fone.nome);
    printf("(pressione qualquer tecla)\n\n");
    getch();
}

/* Mostra todos os contatos com o mesmo sobrenome */
void EncSobrenome(){
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin);
    gets(fone.sobrenome);
    int i;
    for (i=0 ; i<total ; i++){
        if (strcmp(agenda[i].sobrenome, fone.sobrenome) == 0)
            VerContato(i);
    }
    system("cls");
    printf("\nTodos os contatos de sobrenome: '%s' foram mostrados.\n\n", fone.sobrenome);
    printf("(pressione qualquer tecla)\n\n");
    getch();
}

/* Apaga um contato */
void ApagaContato(){
    printf("\nDigite o primeiro nome do contato que deseja apagar:\n");
    fflush(stdin);
    gets(fone.nome);
    printf("\nDigite o sobrenome do contato que deseja apagar:\n");
    fflush(stdin);
    gets(fone.sobrenome);
    int i = BuscaContato();
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
void AtualizaContato(){
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin);
    gets(fone.nome);
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin);
    gets(fone.sobrenome);
    int i, checkalt=0;
    for (i=0; i<total ; i++){
        if (strcmp(agenda[i].nome, fone.nome) == 0 && strcmp(agenda[i].sobrenome, fone.sobrenome) == 0) {
            DadosContato();
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
void SalvarDados(){
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
void CarregarDados(){
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
void Ordenacao(){
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
