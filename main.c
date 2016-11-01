#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

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

/*27-10-2016, fazer apenas busca por nome. OK*/
/*27-10-2016, apos buscar, navegar Antes e Posterior. OK*/
/*27-10-2016, sugestao: abrir arquivo no inicio e gravar no final. OK*/
/*27-10-2016, nao precisa editar contato. OK*/
/*27-10-2016, sugestao: salvar arquivo ordenado. OK*/
/*27-10-2016, Orientacao do professor: nao declarar variavel auxiliar como global. OK*/
/*foi excluia a variavel TCONTATO fone e em seu lugar sera usada agenda[total] como auxiliar */
/*falta fazer a validacao do telefone e do email */


/*definindo variavel para registro */
typedef struct{
char nome[TAM_NOME];            /* nao pode ser vazio*/
char sobrenome[TAM_SOBRENOME];
char telefone[3][TAM_FONE];     /* modelo: '+01 (23) 45678 9012' */
char email[3][TAM_EMAIL];       /* 'modelo_usu.1234567890abcdefghijklmnopqrstuvwxyz@local.aaa.bb' */
} TCONTATO;
TCONTATO agenda[TAM_MAX];

int total=0;
FILE* agendadados;
FILE* ncontatos;

/* funcoes auxiliares*/

/* exibe menu de opcoes */
void Menu();

/* Menu de seleção */
int AddMenu();

/* Permitir ver o resultado */
void Visualizacao();

/* Lê nome e sobrenome, e, se não forem repetidos, lê e grava os outros dados */
void AdicionaContato();

/* Lê os demais dados */
void DadosContato();

/* Grava a leitura feita, na agenda*/
void GravaContato(int i);

/* confere se o contato ja foi registrada*/
int ExisteContato();

/* Imprime um contato */
void VerContato(int n);

/* Navega para contatos posteriores e anteriores da agenda */
void NavegarAgenda(int i);

/* Visualiza toda a agenda com os contatos ordenados pelo nome */
void VerAgenda();

/* Apaga um contato */
void ApagaContato();

/* Atualiza um contato */
void AtualizaContato();

/* Salva os dados no arquivo */
void SalvarDados();

/* Carrega os contatos a partir do arquivo*/
void CarregarDados();

/* Visualiza contatos ordenados */
void VerOrdenado();

/* Ordena contatos pelo nome */
void Ordenar();

/* Busca Binaria do nome */
void BuscaNomeBinaria();

/* Funcao de busca binaria da agenda */
int BuscaBinaria(int e, int d);

void EncNome();
void EncSobrenome();
void EncNomeSobrenome();
int ValidarEmail();


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
    printf ("\t5. Procurar um contato pelo Nome \n");
    printf ("\t6. Mostrar todos os contatos com o mesmo nome \n");
    printf ("\t7. Mostrar todos os contatos com o mesmo sobrenome \n");
    printf ("\t8. Buscar contato especifico. (Nome e Sobrenome) \n");
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
            case 5: BuscaNomeBinaria(); break;
            case 6: EncNome(); break;
            case 7: EncSobrenome(); break;
            case 8: EncNomeSobrenome(); break;
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
   /* agenda[total].nome=0;*/
    setbuf(stdin, NULL);
    system("cls");
    do {
        printf("Digite o primeiro nome:\n");
        gets(agenda[total].nome);
    } while(agenda[total].nome[0]=='\0' || agenda[total].nome[0]=='\n');
    agenda[total].sobrenome[0]='\0';
    setbuf(stdin, NULL);
    do {
        printf("Digite o sobrenome:\n");
        gets(agenda[total].sobrenome);
    } while(agenda[total].sobrenome[0]=='\0' || agenda[total].sobrenome[0]=='\n');
    if ( ExisteContato() != -1 ) {
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
        Ordenar();      /*manter lista ordenada*/
        printf("\nContato registrado com sucesso\n\n");
        Visualizacao();
        }
}

/* Lê os demais dados */
void DadosContato(){
    int i;
    for (i=0; i<3; i++){
        printf("\nDigite o telefone %d: \n", i+1 );
        gets(agenda[total].telefone[i]); }
    int emailOk;
    for (i=0; i<3; i++){
        do { printf("\nDigite o email %d: \n", i+1 );
             gets(agenda[total].email[i]);
             if( ValidarEmail(i) == 0 )
             {
                printf("\n Email invalido\n");
                emailOk=0;
             }
             else emailOk=1; }
        while (emailOk == 0);
    }
}

/* Grava a leitura feita, na agenda*/
void GravaContato(int i){
       total++;
}

/* confere se o contato ja foi registrada*/
int ExisteContato(){
    int i;
    for (i=0; i<total ; i++)
    if (strcmp(agenda[i].nome, agenda[total].nome) == 0 && strcmp(agenda[i].sobrenome, agenda[total].sobrenome) == 0)
        return i;
    return -1;
}

/* Imprime um contato */
void VerContato(int n){
        register int j;
        if (n>total-1) printf("\nContato nao existe\n");
        printf("\nNome: %s Sobrenome: %s\n", agenda[n].nome,agenda[n].sobrenome);
        for (j=0; j<3; j++)
            printf("Fone%d: %s Email%d: %s \n", j+1, agenda[n].telefone[j], j+1, agenda[n].email[j]);
        getch();
}

void NavegarAgenda(int i){
    char opc='\0';
    do {
        printf("\nDigite (A)nterior, (P)osterior e (F)inalizar busca \n");
        scanf("%c", &opc);
        switch (opc){
            case 'A': case 'a': {
                if (i==0) VerContato(i);
                    else VerContato(--i);}; break;
            case 'P': case 'p': {
                if (i==total-1) VerContato(total-1);
                    else VerContato(++i);}; break;
            default:{
                system("cls");
                printf("\n DIGITE UMA OPCAO VALIDA!\n\n");
                } break;
            }
        } while(opc != 'f' && opc != 'F');
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

/* Apaga um contato */
void ApagaContato(){
    printf("\nDigite o primeiro nome do contato que deseja apagar:\n");
    fflush(stdin);
    gets(agenda[total].nome);
    printf("\nDigite o sobrenome do contato que deseja apagar:\n");
    fflush(stdin);
    gets(agenda[total].sobrenome);
    if ( ExisteContato() != -1 )
    {
        int j;
        for (j=ExisteContato(); j<total; j++)
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
    gets(agenda[total].nome);
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin);
    gets(agenda[total].sobrenome);
    for (i=0; i<total ; i++){
        if (strcmp(agenda[i].nome, agenda[total].nome) == 0 && strcmp(agenda[i].sobrenome, agenda[total].sobrenome) == 0) {
            DadosContato();
            agenda[i]=agenda[total];
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
    agendadados = fopen("agd.txt", "w");
    if(agendadados == NULL){
        system("cls");
        printf("Opa!! parece que houve um problema ao tentar salvar os contatos. x.x");
        Visualizacao();
        }
    else
    fwrite(&agenda, sizeof(TCONTATO), total, agendadados);
    fclose(agendadados);
    ncontatos = fopen("nco.txt", "w");
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
    ncontatos = fopen("nco.txt", "r");
    if(ncontatos != NULL)
        fscanf(ncontatos, "%d", &total);
    fclose(ncontatos);
    if(total!=0) {
        agendadados = fopen("agd.txt", "r");
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
            agenda[total]=agenda[j];
            agenda[j]=agenda[j+1];
            agenda[j+1]=agenda[total];
            }
    }
}

/* Busca Binaria do nome */
void BuscaNomeBinaria(){
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin);
    gets(agenda[total].nome);
    system("cls");
    VerContato( BuscaBinaria( 0, total-1 ));
    NavegarAgenda(BuscaBinaria( 0, total-1 ));
}

int BuscaBinaria(int e, int d){
    int i = (e + d)/2;
    if (strcmp(agenda[total].nome, agenda[i].nome)==0)
        return i;
    if (e >= d)
        return -1;
        else
            if (strcmp(agenda[total].nome, agenda[i].nome)>0)
                return BuscaBinaria( i+1, d );
            else
                return BuscaBinaria( e, i-1 );
}

/* Mostra todos os contatos com o mesmo nome */

void EncNome(){
    int i;
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin);
    gets(agenda[total].nome);
    for (i=0 ; i<total ; i++){
        if (strcmp(agenda[i].nome, agenda[total].nome) == 0)
            VerContato(i);
    }
    system("cls");
    printf("\nTodos os contatos de nome: '%s' foram mostrados.\n\n", agenda[total].nome);
    Visualizacao();
}

/* Mostra todos os contatos com o mesmo sobrenome */

void EncSobrenome(){
    int i;
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin);
    gets(agenda[total].sobrenome);
    for (i=0 ; i<total ; i++){
        if (strcmp(agenda[i].sobrenome, agenda[total].sobrenome) == 0)
            VerContato(i);
    }
    system("cls");
    printf("\nTodos os contatos de sobrenome: '%s' foram mostrados.\n\n", agenda[total].sobrenome);
    Visualizacao();
}

/*Busca por um contato especifico*/

void EncNomeSobrenome(){
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin);
    gets(agenda[total].nome);
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin);
    gets(agenda[total].sobrenome);
    if(ExisteContato()==-1){
        system("cls");
        printf("Nenhum contato encontrado!!");
        Visualizacao();
    } else
        VerContato(ExisteContato());
}

/* Faz a validação do Email */
int ValidarEmail(int i){
    // o Email é valido ja de cara, se for vazio.
    if( strlen(agenda[total].email[i]) == 0 )
        return 1;
    // Invalido se não houver '@'.
    else if( strchr(agenda[total].email[i], '@') == NULL )
        return 0;
     // Contando numero de caracteres antes do '@'
    int nc=0;
    while(agenda[total].email[i][nc] != '@')
        nc++;
    // Passando a primeira parte pra outra string
    char emailPP[TAM_EMAIL];
    strncpy(emailPP,agenda[total].email[i], nc);
    // Invalido se houver qualquer coisa além de letras minusculas nesta parte.
    int j;
    for(j=0; j<nc; j++){
        if(isalpha(emailPP[j])==0 || isupper(emailPP[j]))
            return 0;
    }
    // Passando a ultima parte para outra string
    char emailUP[TAM_EMAIL];
    strcpy(emailUP,agenda[total].email[i]);
    int teup = strlen(emailUP);
    int k;
    for(k=0; k<=nc; k++){
        for(j=0; j<=teup; j++){
            emailUP[j]=emailUP[j+1];
        }
        teup = strlen(emailUP);
    }
    /*Invalido se: Tem algo alem de letras e pontos, tem letras com acentos,
      tem dois pontos juntos, tem ponto no final, não tem ponto algum.*/
    for(j=0; j<teup; j++){
        if(isalpha(emailUP[j])==0 && emailUP[j] != '.'
        || emailUP[j] == '.' && emailUP[j+1] == '.'
        || emailUP[teup-1] == '.'
        || strchr(emailUP, '.') == NULL )
            return 0;
    }
    // Email valido se passar por todos os testes
    return 1;
}

    /*for (i=0; i<3; i++){
        do { printf("\nDigite o email %d: \n", i+1 );
             gets(agenda[total].email[i]);
             if(   strlen(agenda[total].email[i]) != 0
                && strchr(agenda[total].email[i], '@') == NULL)
             {
                printf("\n Email invalido\n");
                emailOk=0;
             }
             else emailOk=1; }
        while (emailOk == 0);

/*    Ordenar();
    printf("\nDigite o nome para localizar:\n");
    fflush(stdin);
    gets(agenda[total].nome);
    while (i>1){
        i = total/2;
        if (strcmp(agenda[i].nome, agenda[total].nome) >= 0){
            for (; i >= 0 ; i--){
                if (strcmp(agenda[i].nome,agenda[total].nome)==0)
                VerContato(i);
                }
            }
        else {
            for (; i <= total ; i++){
        if (strcmp(agenda[i].nome, agenda[total].nome)==0)
            VerContato(i);
            }
        }
    printf("\nTodos os contatos de nome: '%s' foram mostrados.\n\n", agenda[total].nome);
    Visualizacao();



    int PesquisaBinaria (int x, int v[], int e, int d)
{
 int i = (e + d)/2;
 if (v[i] == x)
    return i;
 if (e >= d)
    return -1; // Não foi encontrado
 else
     if (v[i] < x)
        return PesquisaBinaria(x, v, i+1, d);
     else
        return PesquisaBinaria(x, v, e, i-1);
}

//Busca por um contato especifico

void EncNomeSobrenome(){
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin);
    gets(agenda[total].nome);
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin);
    gets(agenda[total].sobrenome);
    if(ExisteContato()==-1){
        system("cls");
        printf("Nenhum contato encontrado!!");
        Visualizacao();
    } else
        VerContato(ExisteContato());
}


*/
