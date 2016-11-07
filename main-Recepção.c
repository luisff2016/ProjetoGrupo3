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


/* PROJETO DE PROGRAMAÇÃO IMPERATIVA GRUPO 3 */
/*  -Luis Fernando Feitosa.
    -Wendhio Thalison Neres dos Santos.
    -Rodrigo Oliveira Santos. */


/*definindo variavel para registro */
typedef struct{
char nome[TAM_NOME];            /* nao pode ser vazio*/
char sobrenome[TAM_SOBRENOME];
char telefone[3][TAM_FONE];     /* modelo: '+99 (99) 9 9999 9999' */
char email[3][TAM_EMAIL];       /* 'modelo: a-z . _ 0-9 @ a-z . a-z . a-z' */
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

/* Confere se o contato ja foi registrada*/
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

/* Mostra todos os contatos com o mesmo nome */
void EncNome();

/* Mostra todos os contatos com o mesmo nome */
void EncSobrenome();

/* Encontra um contato especifico atraves de nome e sobrenome */
void EncNomeSobrenome();

/* Verifica se o email é válido */
int ValidarEmail(int i);

/* Verifica se o telefone é valido */
int ValidarTelefone(int i);

 /* Converte a primeiro letra do nome para Maiuscula */
void NomeMaiuscula();

 /* Converte a primeiro letra do sobrenome para Maiuscula */
void SobrenomeMaiuscula();


/* funcao principal*/
int main(){
    setlocale(LC_ALL, "portuguese");
    CarregarDados();
    AddMenu();
    SalvarDados();
    return 0;
}
/*A funcao SalvarDados() além de ser executado no main, também é executado na função AddMenu()
    salvando os dados sempre que o programa volta para o menu, evitando perda de dados
    no caso do usuario fechar o programa de forma inadequada.*/

/* exibe menu de opcoes */
void Menu(){
    printf("\t============================================\n");
    printf("\t\t\t AGENDA TELEFONICA \t\t\n");
    printf("\t============================================\n");
    printf ("\t1. Adicionar contato e ordenar agenda \n");
    printf ("\t2. Apagar contato \n");
    printf ("\t3. Atualizar contato \n");
    printf ("\t4. Ver todos os contatos da agenda \n");
    printf ("\t5. Buscar pelo nome e navegar pela agenda \n");
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

 /* Converte a primeiro letra do nome para Maiuscula */
void NomeMaiuscula(){
    int i;
    if (isalpha(agenda[total].nome[0])) agenda[total].nome[0] = toupper(agenda[total].nome[0]);
    for (i=1; i<strlen(agenda[total].nome)-1; i++){
        if (agenda[total].nome[i]==' '
            && isalpha(agenda[total].nome[i+1])!= 0 )
            agenda[total].nome[i+1] = toupper(agenda[total].nome[i+1]);
    }
}

 /* Converte a primeiro letra do sobrenome para Maiuscula */
void SobrenomeMaiuscula(){
    int i;
    if (isalpha(agenda[total].sobrenome[0])) agenda[total].sobrenome[0] = toupper(agenda[total].sobrenome[0]);
    for (i=1; i<strlen(agenda[total].sobrenome)-1; i++){
        if (agenda[total].sobrenome[i]==' '
            && isalpha(agenda[total].sobrenome[i+1])!= 0 )
            agenda[total].sobrenome[i+1] = toupper(agenda[total].sobrenome[i+1]);
    }
}

/* Lê nome e sobrenome, e, se não forem repetidos, lê e grava os outros dados */
void AdicionaContato(){
    setbuf(stdin, NULL);
    system("cls");
    printf("(Os campos com um '*' são obrigátorios, os demais são opcionais.)\n\n");
    do {
        printf("*Digite o primeiro nome:\n");
        gets(agenda[total].nome);
        NomeMaiuscula();
    } while(agenda[total].nome[0]=='\0' || agenda[total].nome[0]=='\n');
    agenda[total].sobrenome[0]='\0';
    setbuf(stdin, NULL);
    do {
        printf("*Digite o sobrenome:\n");
        gets(agenda[total].sobrenome);
        SobrenomeMaiuscula();
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
    int telefoneOk;
    int emailOk;
    for (i=0; i<3; i++){
        do { printf("\nDigite o telefone %d: \n", i+1 );
             gets(agenda[total].telefone[i]);
             if( ValidarTelefone(i) == 0 )
             {
                printf("\n Telefone invalido.\n");
                printf(" Alguns exemplos válidos: +99(99)9 9999 9999 | 12345678 )\n");
                telefoneOk=0;
             }
             else telefoneOk=1; }
        while (telefoneOk == 0);
    }
    for (i=0; i<3; i++){
        do { printf("\nDigite o email %d: \n", i+1 );
             gets(agenda[total].email[i]);
             if( ValidarEmail(i) == 0 )
             {
                printf("\n Email invalido.\n");
                printf("Alguns exemplos validos: a-z 0-9@ a-z. a-z. a-z | usuario09@web.com.br \n");
                emailOk=0;
             }
             else emailOk=1; }
        while (emailOk == 0);
    }
}

/* Faz a validação do Email */
int ValidarEmail(int i){
    int nc=0;
    int j;
    char emailPP[TAM_EMAIL];
    char emailUP[TAM_EMAIL];
    int teup;
    int k;
    /* o Email é valido ja de cara, se for vazio. */
    if( strlen(agenda[total].email[i]) == 0 )
        return 1;
    /* Invalido se não houver '@'. */
    else if( strchr(agenda[total].email[i], '@') == NULL )
        return 0;
     /* Contando numero de caracteres antes do '@' */
    while(agenda[total].email[i][nc] != '@')
        nc++;
    /* Passando a primeira parte pra outra string */
    strncpy(emailPP,agenda[total].email[i], nc);
    /* Invalido se houver qualquer coisa além de letras minusculas, numeros, ponto e underline nesta parte. */
    for(j=0; j<nc; j++){
        if(isalpha(emailPP[0])==0)
            return 0;
        else
            if((isalpha(emailPP[j])==0
                && isdigit(emailPP[j])==0
                && emailPP[j] != '_'
                && emailPP[j] != '.')
               || isupper(emailPP[j]) )
            return 0;
    }
    /* Passando a ultima parte para outra string */
    strcpy(emailUP,agenda[total].email[i]);
    teup = strlen(emailUP);
    for(k=0; k<=nc; k++){
        for(j=0; j<=teup; j++){
            emailUP[j]=emailUP[j+1];
        }
        teup = strlen(emailUP);
    }
    /*Invalido se: Tem algo alem de letras e pontos, tem letras com acentos,
      tem dois pontos juntos, tem ponto no final, não tem ponto algum.*/
    for(j=0; j<teup; j++){
        if((isalpha(emailUP[j])==0 && emailUP[j] != '.')
            || (emailUP[j] == '.' && emailUP[j+1] == '.')
            || emailUP[teup-1] == '.'
            || strchr(emailUP, '.') == NULL )
            return 0;
    }
    /* Email valido se passar por todos os testes*/
    return 1;
}

/* Faz a validação do Telefone */
int ValidarTelefone(int i){
    /* Criando uma nova string pra receber e tirar os espaços do telefone,
     facilitando a validação */
    int j, k=0;
    char ch1;
    char telefonetemp[TAM_FONE];
    for (j = 0; j < strlen(agenda[total].telefone[i]); j++) {
      if (agenda[total].telefone[i][j] != ' ') {
         ch1 = agenda[total].telefone[i][j];
         telefonetemp[k] = ch1;
         k++;
      }
   }
   telefonetemp[k] = '\0';
    /* Inicialmente já é invalido se for vazio.*/
    if( strlen(telefonetemp) == 0 )
        return 1;
    /* Inicialmente já é invalido se for menor que 8.*/
    if( strlen(telefonetemp) <= 7 )
        return 0;
    /* checando casos validos.*/
    if( strlen(telefonetemp) == 15 || strlen(telefonetemp) == 16) {
        for(j=0; j<strlen(telefonetemp); j++){
            if(j==0){
                if(telefonetemp[j] != '+')
                    return 0; }
            else
            if(j==3){
                if(telefonetemp[j] != '(')
                    return 0; }
            else
            if(j==6){
                if(telefonetemp[j] != ')')
                    return 0; }
            else
                if(isdigit(telefonetemp[j]) == 0)
                    return 0;
        }
        return 1;
    }
    if( strlen(telefonetemp) == 12 || strlen(telefonetemp) == 13) {
        for(j=0; j<strlen(telefonetemp); j++){
            if(j==0){
                if(telefonetemp[j] != '(')
                    return 0;
                else{
                    if(j==3)
                        if(telefonetemp[j] != ')')
                            return 0;
                    }
            }
            else{
                if(isdigit(telefonetemp[j]) == 0)
                    return 0;
                }
        return 1;
        }
    }
    if(strlen(telefonetemp) == 8 || strlen(telefonetemp) == 9) {
        for(j=0; j<strlen(telefonetemp); j++){
            if(isdigit(telefonetemp[j]) == 0)
                return 0;
        }
        return 1;
    }
    return 0;
}

/* Grava a leitura feita, na agenda*/
void GravaContato(int i){
       total++;
}

/* Confere se o contato ja foi registrada*/
int ExisteContato(){
    int i;
    for (i=0; i<total ; i++)
    if (strcmp(agenda[i].nome, agenda[total].nome) == 0 && strcmp(agenda[i].sobrenome, agenda[total].sobrenome) == 0)
        return i;
    return -1;
}

/* Visualizar um contato */
void VerContato(int n){
        register int j;
        if (n>total-1) printf("\nContato nao existe\n");
        printf("\nNome: %s Sobrenome: %s\n", agenda[n].nome,agenda[n].sobrenome);
        for (j=0; j<3; j++)
            printf("Fone%d: %s \n", j+1, agenda[n].telefone[j]);
        for (j=0; j<3; j++)
            printf("Email%d: %s \n", j+1, agenda[n].email[j]);
        getch();
}

/* Navegar pelos contatos da agenda */
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
    fflush(stdin); /* Limpa o buffer de entrada */
    gets(agenda[total].nome);
    NomeMaiuscula();
    printf("\nDigite o sobrenome do contato que deseja apagar:\n");
    fflush(stdin); /* Limpa o buffer de entrada */
    gets(agenda[total].sobrenome);
    SobrenomeMaiuscula();
    if ( ExisteContato() != -1 ){
        agenda[ExisteContato()] = agenda[total-1];
        total--;
        Ordenar();
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
    fflush(stdin); /* Limpa o buffer de entrada */
    gets(agenda[total].nome);
    NomeMaiuscula();
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin); /* Limpa o buffer de entrada */
    gets(agenda[total].sobrenome);
    SobrenomeMaiuscula();
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

/* Visualizar ordenação */
void VerOrdenado(){
    int i;
    Ordenar();
    printf("\nImprimindo os nomes ordenados\n");
    for(i = 0; i < total;++i)
        printf("%s %s\n", agenda[i].nome,agenda[i].sobrenome);
    Visualizacao();
}

/* Função de ordenação */
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

/* Busca Binaria pelo nome */
void BuscaNomeBinaria(){
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin); /* Limpa o buffer de entrada */
    gets(agenda[total].nome);
    NomeMaiuscula();
    system("cls");
    VerContato( BuscaBinaria(0, total-1));
    NavegarAgenda(BuscaBinaria(0, total-1));
}

/* Funcao de Busca Binaria */
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
    int i, k=0;
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin); /* Limpa o buffer de entrada */
    gets(agenda[total].nome);
    NomeMaiuscula();
    for (i=0 ; i<total ; i++){
            if (strcmp(agenda[i].nome, agenda[total].nome) == 0){
                VerContato(i);
                k++;
                }
            }
    system("cls");
    if(k!=0)
        printf("\nTodos os contatos de nome: '%s' foram mostrados.\n\n", agenda[total].nome);
    else
        printf("\nNenhum contato de nome: '%s' foi encontrado.\n\n", agenda[total].nome);
    Visualizacao();
}

/* Mostra todos os contatos com o mesmo sobrenome */
void EncSobrenome(){
    int i, k=0;
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin); /* Limpa o buffer de entrada */
    gets(agenda[total].sobrenome);
    SobrenomeMaiuscula();
    for (i=0 ; i<total ; i++){
        if (strcmp(agenda[i].sobrenome, agenda[total].sobrenome) == 0)
            VerContato(i);
    }
    system("cls");
    if(k!=0)
        printf("\nTodos os contatos de sobrenome: '%s' foram mostrados.\n\n", agenda[total].sobrenome);
    else
        printf("\nNenhum contato de sobrenome: '%s' foi encontrado.\n\n", agenda[total].sobrenome);
    Visualizacao();
}

/*Busca por um contato especifico*/
void EncNomeSobrenome(){
    printf("\nDigite o primeiro nome do contato:\n");
    fflush(stdin); /* Limpa o buffer de entrada */
    gets(agenda[total].nome);
    NomeMaiuscula();
    printf("\nDigite o sobrenome do contato:\n");
    fflush(stdin); /* Limpa o buffer de entrada */
    gets(agenda[total].sobrenome);
    SobrenomeMaiuscula();
    if(ExisteContato()==-1){
        system("cls");
        printf("Nenhum contato encontrado!!");
        Visualizacao();
    } else
        VerContato(ExisteContato());
}

