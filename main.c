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
void VerOrdenado();
void Ordenar();
void Visualizacao();
void BuscaBinaria();

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
printf ("\t8. Ordenar os contatos\n");
printf ("\t9. Busca Binaria do nome\n");
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
            case 8: VerOrdenado(); break;
            case 9: BuscaBinaria(); break;
            default:{
                system("cls");
                printf("\n DIGITE UMA OPCAO VALIDA!\n\n");
                } break;
            }
            SalvarDados(); /*Executa aqui, pra evitar que dados se percam, no caso do programa ser fechado de forma inadequada.*/
    } while(opcao != 0);
    return 0;
}

/* Permitir ver o resultado */
void Visualizacao(){
    printf("(pressione qualquer tecla)\n\n");
    getch();
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
    if ( BuscaContato() != -1 ) {
        system("cls");
        printf("\nContato já registrado\n\n");
        Visualizacao();
        }
    else if (total == TAM_MAX){
        system("cls");
        printf("\nNúmero máximo de contatos ultrapassado\n\n");
        Visualizacao();
        }
    else {
        DadosContato();
        GravaContato(total);
        system("cls");
        printf("\nContato registrado com sucesso\n\n");
        Visualizacao();
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
void VerContato(int n){
        register int j;
        printf("\nNome: %s Sobrenome: %s\n", agenda[n].nome,agenda[n].sobrenome);
        for (j=0; j<3; j++)
            printf("Fone%d: %s Email%d: %s \n", j+1, agenda[n].telefone[j], j+1, agenda[n].email[j]);
        Visualizacao();
}

/* Imprime todos os contatos */
void VerAgenda(){
    int i;
    for (i=0 ; i<total ; i++)
        VerContato(i);
    system("cls");
    printf("\nTodos os contatos foram mostrados.\n\n");
    Visualizacao();
}

/* Busca por um contato especifico*/
void EncNomeSobrenome(){
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin);
    gets(fone.nome);
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin);
    gets(fone.sobrenome);
    if(BuscaContato()==-1){
        system("cls");
        printf("Nenhum contato encontrado!!");
        Visualizacao();
    } else
        VerContato(BuscaContato());
}

/* Mostra todos os contatos com o mesmo nome */
void EncNome(){
    int i;
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin);
    gets(fone.nome);
    for (i=0 ; i<total ; i++){
        if (strcmp(agenda[i].nome, fone.nome) == 0)
            VerContato(i);
    }
    system("cls");
    printf("\nTodos os contatos de nome: '%s' foram mostrados.\n\n", fone.nome);
    Visualizacao();
}

/* Mostra todos os contatos com o mesmo sobrenome */
void EncSobrenome(){
    int i;
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin);
    gets(fone.sobrenome);
    for (i=0 ; i<total ; i++){
        if (strcmp(agenda[i].sobrenome, fone.sobrenome) == 0)
            VerContato(i);
    }
    system("cls");
    printf("\nTodos os contatos de sobrenome: '%s' foram mostrados.\n\n", fone.sobrenome);
    Visualizacao();
}

/* Apaga um contato */
void ApagaContato(){
    printf("\nDigite o primeiro nome do contato que deseja apagar:\n");
    fflush(stdin);
    gets(fone.nome);
    printf("\nDigite o sobrenome do contato que deseja apagar:\n");
    fflush(stdin);
    gets(fone.sobrenome);
    if ( BuscaContato() != -1 )
    {
        int j;
        for (j=BuscaContato(); j<total; j++)
            agenda[j]=agenda[j+1];
        total--;
        system("cls");
        printf("\n Registro apagado \n\n\n");
        Visualizacao();
    }
    else {
        system("cls");
        printf("\n Contato nao existe\n\n\n");
        Visualizacao();
    }
}

/* Atualiza um contato */
void AtualizaContato(){
    int i, checkalt=0;
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin);
    gets(fone.nome);
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin);
    gets(fone.sobrenome);
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
        Visualizacao();
    }
    else {
        system("cls");
        printf("\nContato alterado com sucesso.\n\n");
        Visualizacao();
    }
}

/* Salva os dados no arquivo */
void SalvarDados(){
    agendadados = fopen("agd.bin", "wb");
    if(agendadados == NULL){
        system("cls");
        printf("Opa!! parece que houve um problema ao tentar salvar os contatos. x.x");
        Visualizacao();
        }
    else
    fwrite(&agenda, sizeof(TCONTATO), total, agendadados);
    fclose(agendadados);
    ncontatos = fopen("nco.bin", "wb");
    if(ncontatos == NULL){
        system("cls");
        printf("Opa!! parece que houve um problema ao tentar salvar os contatos. x.x");
        Visualizacao();
        }
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
            Visualizacao();
            system("cls");
            }
        else
            fread(&agenda, sizeof(TCONTATO), total, agendadados);
            fclose(agendadados);
        }
}

/* Rotina de ordenação */
void VerOrdenado(){
    int i;
    Ordenar();
    printf("\nImprimindo os nomes ordenados\n");
    for(i = 0; i < total;++i)
        printf("%s %s\n", agenda[i].nome,agenda[i].sobrenome);
    Visualizacao();
}

void Ordenar(){
    int j,k;
    for (k=1; k < total ; k++){
        for (j=0; j < total-1 ; j++)
            if (strcmp(agenda[j].nome,agenda[j+1].nome)>0) {
            fone=agenda[j];
            agenda[j]=agenda[j+1];
            agenda[j+1]=fone;
            }
    }
}

/* Busca Binaria do nome */
void BuscaBinaria(){
    int i = total/2;
    Ordenar();
    printf("\nDigite o nome para localizar:\n");
    fflush(stdin);
    gets(fone.nome);
    if (strcmp(agenda[i].nome, fone.nome) == 0)
        i=total/4;
    if (strcmp(agenda[i].nome, fone.nome) >= 0){
        for (; i >= 0 ; i--){
        if (strcmp(agenda[i].nome,fone.nome)==0)
            VerContato(i);
        }
    }
    else {
        for (; i <= total ; i++){
        if (strcmp(agenda[i].nome, fone.nome)==0)
            VerContato(i);
        }
    }
    printf("\nTodos os contatos de nome: '%s' foram mostrados.\n\n", fone.nome);
    Visualizacao();
}
