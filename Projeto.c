#include <stdio.h>
#include <stdlib.h>  // malloc para listas encadeadas
#include <string.h>  // strcpy, strcmp, strstr, entre outras funções
#include <windows.h> // Sleeep

#define NADA " " // Para melhor entendimento da funções que limpa a tela

// Projeto: Medicos e Pacientes (Consultas e Acompanhamentos)

// As funções do código se baseiam principalmente em manipulação de dados em arquivos
// Ele possui:
// 1 - Sistema de Login e Cadastro (sendo possível fazer alteração nos dados posteriormente)
// 2 - Consultas (Marcar, desmarcar e concluir)
// 3 - Acompanhamentos (Criar, alterar e deletar)

// Estruturas para o cadastramento
typedef struct PACIENTE
{
    char NOME[60];
    char DATADEN[15];
    char CPF[15];
    char EMAIL[40];
    char SENHA[25];
    struct PACIENTE *proximo;
} CADP;

typedef struct CONSULTA
{
    int POSICAO;
    char CPF[15];
    char NOMEPAC[55];
    char IDENTIFICACAO[55];
    char CRMMED[10];
    char DESCRICAO[100];
    struct CONSULTA *proximo;
} CON;

typedef struct ACOMPANHAMENTO
{
    char CPF[15];
    char MEDICO[20];
    char CRM[15];
    char STATUS[60];
    char MEDICACAO[60];
    char DOSAGEM[60];
    char RECOMENDACAO[60];
    char PERIODO[60];
    struct ACOMPANHAMENTO *proximo;
} ACOMP;

typedef struct MEDICO
{
    char CRM[15];
    char NOME[60];
    char AREA[40];
    char PRECO[20];
    char EMAIL[40];
    char SENHA[25];
    struct MEDICO *proximo;
} CADM;

// FUNÇÕES
// CMD (print)
void TABELA_LOGIN();

void SYSTEM_PRINT(char *);

// Features do programa (para melhor divisão)
void LOGIN_PACIENTE();

void LOGIN_MEDICO();

void CADASTRO_PACIENTE();

void CADASTRO_MEDICO();

// Entradas
void NOME(char *);

void DATADENASCIMENTO(char *);

void CPF(char *);

void CRM(char *);

void PRECO(char *);

void AREA(char *);

void EMAIL(char *);

void SENHA(char *);

void DESCRICAO(char *, char *);

// Criação dos arquivos (caso ainda não existam na máquina)
void CRIA_ARQUIVO(char *);

// Verificação do login
int VERIFICA_PACIENTE(char *, char *, CADP *);

int VERIFICA_MEDICO(char *, char *, CADM *);

// adicionar Usuários no cadastro
void ADD_PACIENTE(CADP *);

void ADD_MEDICO(CADM *);

// Alterar dados dos aquivos do cadastro
void ALTERAR_DADO_PACIENTE(CADP *);

void ALTERAR_DADO_MEDICO(CADM *);

// tratamento da funções fgets
void TRATAMENTO(char *);

void TRATA_NOME(char *);

// Verificação das entradas do cadastro
int VERIFICA_CPF(char *);

int VERIFICA_DATA(char *);

int VERIFICA_FORMATO_NOME(char *, char);

int VERIFICA_SENHA(char *);

int VERIFICA_FORMATO_CRM(char *);

int VERIFICA_CRM_CONSULTA(char *, CADM *);

int VERIFICA_CRM(char *);

int VERIFICA_NUMERO(char *);

int VERIFICA_MAIUSCULO(char *);

int VERIFICA_ASCII(char *);

// verficar o tamanho da entrada
int VERIFICA_TAMANHO_ENTRADA(char *, size_t, size_t);

int VERIFICA_TAMANHO_EXATO(char *, size_t);

// CONSULTAS
void MOSTRA_MEDICOS();

void MARCA_CONSULTA(char *, char *, char *, char *, char *);

void MOSTRAR_CONSULTAS(char *, char *);

void EXCLUI_CONSULTA(char *, char *);

int VERIFICA_CONSULTA(char *, char *);

// ACOMPANHAMENTOS
void ACOMPANHAMENTOS(char *, char *, char *, int, ACOMP *);

void ADD_ACOMP(ACOMP *);

int VERIFICA_ACOMPANHAMENTO(char *, char *, ACOMP *);

void MOSTRAR_ACOMPANHAMENTOS(char *, char *);

void ALTERA_ACOMP(ACOMP *);

void EXCLUI_ACOMP(char *, char *);

// Programa Principal
int main()
{
    CRIA_ARQUIVO("Pacientes.txt");
    CRIA_ARQUIVO("Medicos.txt");
    CRIA_ARQUIVO("Consultas.txt");
    CRIA_ARQUIVO("Acompanhamentos.txt");

    int INICIO;
    do
    {
        SYSTEM_PRINT(NADA);
        TABELA_LOGIN();
        scanf("%d", &INICIO);
        fflush(stdin);
        switch (INICIO)
        {
        case 1:
            LOGIN_PACIENTE();
            break;
        case 2:
            LOGIN_MEDICO();
            break;
        case 3:
        {
            int CAD;
            do
            {
                SYSTEM_PRINT(" ");

                printf("CADASTRO\n");
                printf("1 - Pacientes\n");
                printf("2 - Medicos\n");
                printf("0 - Sair\n");
                scanf("%d", &CAD);
                fflush(stdin);
                switch (CAD)
                {
                case 1:
                {
                    CADASTRO_PACIENTE();
                    break;
                }
                case 2:
                {
                    CADASTRO_MEDICO();
                    break;
                }
                case 0:
                    break;
                default:
                    printf("Opcao Invalida\n");
                    break;
                }
            } while (CAD != 0);
            break;
        }
        case 0:
            break;
        default:
            printf("Opcao Invalida\n");
            break;
        }
    } while (INICIO != 0);
    return 0;
}

// Funções do CMD (Para printar informação)
void TABELA_LOGIN()
{
    // Imprime a tabela inicial do programa
    printf("Tipo de Login\n");
    printf("1 - Paciente\n");
    printf("2 - Medico\n");
    printf("3 - Cadastramento\n");
    printf("0 - Fechar Programa\n");
}

void SYSTEM_PRINT(char *frase)
{
    /*
    Executa o comando system e imprime uma frase (ou não)
    Devido a incompatibilidade de sistemas operacionais entre membros da equipe
    */
    system("cls");
    if (*frase != ' ')
        printf("%s\n\n", frase);
}

// Aqueles que se pode tomar durante a execução do programa
void LOGIN_PACIENTE()
{
    SYSTEM_PRINT(" ");
    char CADASTROLOGIN[15];
    char SENHALOGIN[25];
    int CONTINUAR;
    do
    {
        CADP PLOG;
        printf("CPF: ");
        fgets(CADASTROLOGIN, 15, stdin);
        TRATAMENTO(CADASTROLOGIN);
        fflush(stdin);

        printf("Senha: ");
        fgets(SENHALOGIN, 20, stdin);
        TRATAMENTO(SENHALOGIN);
        fflush(stdin);

        if (VERIFICA_PACIENTE(CADASTROLOGIN, SENHALOGIN, &PLOG) == 0)
        {
            SYSTEM_PRINT("Usuario ou senha invalidos");
            printf("Tentar de Novo?\n");
            printf("1 - Sim\n");
            printf("0 - Nao\n");
            scanf("%d", &CONTINUAR);
            fflush(stdin);
            if (CONTINUAR == 0)
                break;
        }
        else
        {
            SYSTEM_PRINT("Login realizado com sucesso");
            Sleep(3000);
            int OPCAO;
            SYSTEM_PRINT(NADA);
            printf("Bem vindo %s, o que deseja fazer hoje?\n\n", PLOG.NOME);
            do
            {
                printf("1 - Consultas\n");
                printf("2 - Acompanhamento\n");
                printf("3 - Alterar cadastro\n");
                printf("0 - Sair\n");
                scanf("%d", &OPCAO);
                fflush(stdin);
                SYSTEM_PRINT(NADA);
                if (OPCAO == 1)
                {
                    int CONSULTAS;
                    printf("CONSULTAS\n\n");
                    printf("1 - Marcar Consulta\n");
                    printf("2 - Desmarcar Consulta\n");
                    printf("3 - Visualizar Consultas\n");
                    printf("0 - Voltar\n");
                    scanf("%d", &CONSULTAS);
                    fflush(stdin);
                    SYSTEM_PRINT(NADA);
                    if (CONSULTAS == 1)
                    {
                        int CHECAGEM;
                        char SENHAALT[25];
                        do
                        {
                            printf("Digite sua senha (Enter para voltar ao inicio):");
                            fgets(SENHAALT, 20, stdin);
                            fflush(stdin);
                            TRATAMENTO(SENHAALT);
                            if (SENHAALT[0] == '\0')
                            {
                                CHECAGEM = 0;
                                break;
                            }
                            else if (strcmp(SENHAALT, PLOG.SENHA) == 0)
                            {
                                CHECAGEM = 1;
                                break;
                            }
                        } while (1);

                        if (CHECAGEM == 1)
                        {
                            char CRM[15];
                            char DESCRICAO_CONSULTA[100];
                            CADM MED;
                            MOSTRA_MEDICOS();
                            do
                            {
                                printf("Digite o CRM correspondente ao medico para marcar a consulta\n");
                                printf("CRM (Pressione Enter para sair): ");
                                fgets(CRM, 12, stdin);
                                fflush(stdin);
                                TRATAMENTO(CRM);
                                if (CRM[0] == '\0')
                                {
                                    SYSTEM_PRINT(NADA);
                                    break;
                                }
                                if (VERIFICA_CRM_CONSULTA(CRM, &MED) == 1)
                                {
                                    printf("CRM nao encontrado\n\n");
                                }
                                else
                                {
                                    DESCRICAO(DESCRICAO_CONSULTA, "Descricao dos Sintomas");
                                    MARCA_CONSULTA(PLOG.NOME, PLOG.CPF, DESCRICAO_CONSULTA, MED.NOME, MED.CRM);
                                    SYSTEM_PRINT("Consulta Marcada com Sucesso");
                                    Sleep(3000);
                                    break;
                                }
                            } while (1);
                        }
                    }
                    else if (CONSULTAS == 2)
                    {
                        do
                        {
                            MOSTRAR_CONSULTAS(" ", PLOG.CPF);
                            char CRM[15];
                            printf("Qual consulta deseja Desmarcar (Digite o CRM do medico)?\n");
                            fgets(CRM, 13, stdin);
                            fflush(stdin);
                            TRATAMENTO(CRM);
                            if (CRM[0] == '\0')
                            {
                                SYSTEM_PRINT(NADA);
                                break;
                            }
                            if (VERIFICA_CONSULTA(CRM, PLOG.CPF) == 0)
                            {
                                SYSTEM_PRINT("Consulta nao encontrada");
                            }
                            else
                            {
                                EXCLUI_CONSULTA(PLOG.CPF, CRM);
                                SYSTEM_PRINT("Consulta desmarcada com sucesso!");
                                Sleep(2000);
                            }
                        } while (1);
                    }
                    else if (CONSULTAS == 3)
                    {
                        MOSTRAR_CONSULTAS(" ", PLOG.CPF);
                        printf("Pressione a tecla Enter a qualquer momento para voltar\n");
                        getchar();
                        fflush(stdin);
                        SYSTEM_PRINT(NADA);
                    }
                }
                else if (OPCAO == 2)
                {
                    MOSTRAR_ACOMPANHAMENTOS(PLOG.CPF, " ");
                    printf("Pressione a tecla Enter a qualquer momento para voltar\n");
                    getchar();
                    fflush(stdin);
                    SYSTEM_PRINT(NADA);
                }
                else if (OPCAO == 3)
                {
                    int ALTERACAO;
                    char SENHAALT[25];
                    do
                    {
                        printf("Digite sua senha (Enter para voltar ao inicio):");
                        fgets(SENHAALT, 20, stdin);
                        fflush(stdin);
                        TRATAMENTO(SENHAALT);
                        if (SENHAALT[0] == '\0')
                        {
                            ALTERACAO = 0;
                            break;
                        }
                        else if (strcmp(SENHAALT, PLOG.SENHA) == 0)
                        {
                            ALTERACAO = 1;
                            break;
                        }
                    } while (1);

                    SYSTEM_PRINT(NADA);
                    while (ALTERACAO != 0)
                    {
                        printf("CONFIGURACOES\n\n");
                        printf("Qual informacao deseja alterar?\n");
                        printf("Atencao: Uma vez comecada a alteracao voce nao podera mais voltar ate concluila\n");
                        printf("1 - E-mail\n");
                        printf("2 - Senha\n");
                        printf("0 - Voltar\n");
                        scanf("%d", &ALTERACAO);
                        fflush(stdin);
                        if (ALTERACAO == 0)
                        {
                            SYSTEM_PRINT(NADA);
                            break;
                        }
                        else if (ALTERACAO == 1)
                        {
                            EMAIL(PLOG.EMAIL);
                            break;
                        }
                        else if (ALTERACAO == 2)
                        {
                            SENHA(PLOG.SENHA);
                            break;
                        }
                        else
                        {
                            SYSTEM_PRINT("Opcao Invalida!");
                        }
                    }
                    if (ALTERACAO == 1 || ALTERACAO == 2)
                    {
                        ALTERAR_DADO_PACIENTE(&PLOG);

                        SYSTEM_PRINT(NADA);
                        printf("Alteracao realizada com sucesso!\n");
                        Sleep(3000);
                    }
                }
                else if (OPCAO == 0)
                    break;
            } while (1);
            break;
        }
    } while (1);
}

void LOGIN_MEDICO()
{
    SYSTEM_PRINT(" ");
    char CADASTROLOG[15];
    char SENHALOG[25];
    int CONTINUAR;
    do
    {
        CADM MLOG;
        printf("CRM: ");
        fgets(CADASTROLOG, 15, stdin);
        TRATAMENTO(CADASTROLOG);
        fflush(stdin);

        printf("Senha: ");
        fgets(SENHALOG, 20, stdin);
        TRATAMENTO(SENHALOG);
        fflush(stdin);

        if (VERIFICA_MEDICO(CADASTROLOG, SENHALOG, &MLOG) == 0)
        {
            SYSTEM_PRINT("Usuario ou senha invalidos");
            printf("Tentar de Novo?\n");
            printf("1 - Sim\n");
            printf("0 - Nao\n");
            scanf("%d", &CONTINUAR);
            fflush(stdin);
            if (CONTINUAR == 0)
                break;
        }
        else
        {
            SYSTEM_PRINT("Login realizado com sucesso");
            Sleep(3000);
            int OPCAO;
            SYSTEM_PRINT(NADA);
            printf("Bem vindo %s, o que deseja fazer hoje?\n\n", MLOG.NOME);
            do
            {
                printf("1 - Visualizar/Concluir Consultas\n");
                printf("2 - Gerir acompanhamentos\n");
                printf("3 - Configuracoes\n");
                printf("0 - Sair\n");
                scanf("%d", &OPCAO);
                fflush(stdin);
                if (OPCAO == 1)
                {
                    SYSTEM_PRINT(NADA);
                    char CPF[12];
                    do
                    {
                        MOSTRAR_CONSULTAS(MLOG.CRM, NADA);
                        printf("Para remover um paciente da lista digite o CPF correspondente a ele\n");
                        printf("CPF (Pressione Enter para voltar): ");
                        fgets(CPF, 13, stdin);
                        TRATAMENTO(CPF);
                        fflush(stdin);
                        if (CPF[0] == '\0')
                        {
                            SYSTEM_PRINT(NADA);
                            break;
                        }
                        else if (VERIFICA_CONSULTA(MLOG.CRM, CPF) == 0)
                        {
                            SYSTEM_PRINT("CPF nao encontrado");
                        }
                        else
                        {
                            EXCLUI_CONSULTA(CPF, MLOG.CRM);
                            SYSTEM_PRINT(NADA);
                        }
                    } while (1);
                }
                else if (OPCAO == 2)
                {
                    SYSTEM_PRINT(NADA);
                    int AC;
                    do
                    {
                        char CPF[15];
                        printf("ACOMPANHAMENTOS\n\n");
                        printf("1 - Adicionar novo paciente\n");
                        printf("2 - Alterar acompanhamento\n");
                        printf("3 - Visualizar/Encerrar acompanhamento\n");
                        printf("0 - Voltar a pagina anterior\n");
                        scanf("%d", &AC);
                        fflush(stdin);
                        if (AC == 1)
                        {
                            SYSTEM_PRINT(NADA);
                            do
                            {
                                printf("CPF do Paciente (Enter para voltar): ");
                                fgets(CPF, 14, stdin);
                                TRATAMENTO(CPF);
                                fflush(stdin);
                                if (CPF[0] == '\0')
                                    break;
                                if (VERIFICA_CPF(CPF) == 1)
                                {
                                    SYSTEM_PRINT("CPF nao encontrado");
                                }
                                else
                                {
                                    ACOMP APAC;
                                    ACOMPANHAMENTOS(CPF, MLOG.CRM, MLOG.NOME, 0, &APAC);
                                    SYSTEM_PRINT(NADA);
                                    break;
                                }
                            } while (1);
                        }
                        else if (AC == 2)
                        {
                            SYSTEM_PRINT(NADA);
                            do
                            {
                                ACOMP APAC;
                                MOSTRAR_ACOMPANHAMENTOS(NADA, MLOG.CRM);
                                printf("CPF do Paciente (Pressione Enter para cancelar): ");
                                fgets(CPF, 14, stdin);
                                TRATAMENTO(CPF);
                                fflush(stdin);
                                if (CPF[0] == '\0')
                                {
                                    SYSTEM_PRINT(NADA);
                                    break;
                                }
                                else if (VERIFICA_ACOMPANHAMENTO(CPF, MLOG.CRM, &APAC) == 0)
                                {
                                    SYSTEM_PRINT("Voce nao possui acompanhamentos com este CPF");
                                }
                                else
                                {
                                    int ALT;
                                    do
                                    {
                                        SYSTEM_PRINT(NADA);
                                        printf("CPF do Paciente: %s\n", CPF);
                                        printf("1 - Status: %s\n", APAC.STATUS);
                                        printf("2 - Medicacao: %s\n", APAC.MEDICACAO);
                                        printf("3 - Dosagem: %s\n", APAC.DOSAGEM);
                                        printf("4 - Recomendacao: %s\n", APAC.RECOMENDACAO);
                                        printf("5 - Periodo: %s\n", APAC.PERIODO);
                                        printf("0 - Voltar\n\n");

                                        printf("Qual informacao deseja alterar?");
                                        scanf("%d", &ALT);
                                        fflush(stdin);
                                        if (ALT >= 1 && ALT <= 5)
                                        {
                                            ACOMPANHAMENTOS(CPF, MLOG.CRM, MLOG.NOME, ALT, &APAC);
                                            SYSTEM_PRINT(NADA);
                                            break;
                                        }
                                        else if (ALT == 0)
                                            break;
                                        else
                                            SYSTEM_PRINT("Opcao invalida!");
                                    } while (1);
                                }
                            } while (1);
                        }
                        else if (AC == 3)
                        {
                            SYSTEM_PRINT(NADA);
                            do
                            {
                                MOSTRAR_ACOMPANHAMENTOS(NADA, MLOG.CRM);
                                ACOMP APAC;
                                printf("CPF do Paciente (Pressione Enter para cancelar): ");
                                fgets(CPF, 14, stdin);
                                TRATAMENTO(CPF);
                                fflush(stdin);
                                if (CPF[0] == '\0')
                                {
                                    break;
                                }
                                else if (VERIFICA_ACOMPANHAMENTO(CPF, MLOG.CRM, &APAC) == 0)
                                {
                                    SYSTEM_PRINT("Voce nao possui acompanhamentos com este CPF");
                                }
                                else
                                {
                                    EXCLUI_ACOMP(MLOG.CRM, CPF);
                                    printf("Acompanhamento Encerrado com sucesso");
                                    Sleep(3000);
                                    SYSTEM_PRINT(NADA);
                                    break;
                                }
                            } while (1);
                        }
                        else
                        {
                            SYSTEM_PRINT("Opcao invalida!");
                        }
                    } while (AC != 0);
                }
                else if (OPCAO == 3)
                {
                    int ALTERACAO;
                    char SENHAALT[25];
                    do
                    {
                        printf("Digite sua senha (Enter para voltar ao inicio):");
                        fgets(SENHAALT, 20, stdin);
                        fflush(stdin);
                        TRATAMENTO(SENHAALT);
                        if (SENHAALT[0] == '\0')
                        {
                            ALTERACAO = 0;
                            break;
                        }
                        else if (strcmp(SENHAALT, MLOG.SENHA) == 0)
                        {
                            ALTERACAO = 1;
                            break;
                        }
                    } while (1);

                    while (ALTERACAO != 0)
                    {
                        printf("CONFIGURACOES\n\n");
                        printf("Qual informacao deseja alterar?\n");
                        printf("Atencao: Uma vez comecada a alteracao voce nao podera mais voltar ate concluila\n");
                        printf("1 - Valor da consulta:\n");
                        printf("2 - Area de Atuacao\n");
                        printf("3 - E-mail\n");
                        printf("4 - Senha\n");
                        printf("0 - Sair\n");
                        scanf("%d", &ALTERACAO);
                        fflush(stdin);
                        if (ALTERACAO == 0)
                        {
                            SYSTEM_PRINT(NADA);
                            break;
                        }
                        else if (ALTERACAO == 1)
                        {
                            PRECO(MLOG.PRECO);
                            break;
                        }
                        else if (ALTERACAO == 2)
                        {
                            AREA(MLOG.AREA);
                            break;
                        }
                        else if (ALTERACAO == 3)
                        {
                            EMAIL(MLOG.EMAIL);
                            break;
                        }
                        else if (ALTERACAO == 4)
                        {
                            SENHA(MLOG.SENHA);
                            break;
                        }
                        else
                            SYSTEM_PRINT("Opcao Invalida!");
                    }

                    if (ALTERACAO > 0 && ALTERACAO < 5)
                    {
                        ALTERAR_DADO_MEDICO(&MLOG);

                        SYSTEM_PRINT("Alteracao realizada com sucesso");
                        Sleep(3000);
                    }
                }
            } while (OPCAO != 0);
            break;
        }
    } while (1);
}

void CADASTRO_PACIENTE()
{
    CADP PCAD;
    int SN, ALTERACAO = 0;
    do
    {
        if (ALTERACAO == 0 || ALTERACAO == 1)
        {
            NOME(PCAD.NOME);
        }

        if (ALTERACAO == 0 || ALTERACAO == 2)
        {
            DATADENASCIMENTO(PCAD.DATADEN);
        }

        if (ALTERACAO == 0 || ALTERACAO == 3)
        {
            CPF(PCAD.CPF);
        }

        if (ALTERACAO == 0 || ALTERACAO == 4)
        {
            EMAIL(PCAD.EMAIL);
        }

        if (ALTERACAO == 0 || ALTERACAO == 5)
        {
            SENHA(PCAD.SENHA);
        }

        SYSTEM_PRINT(NADA);
        printf("1 - Nome Completo: %s\n", PCAD.NOME);
        printf("2 - Data de Nascimento: %s\n", PCAD.DATADEN);
        printf("3 - CPF: %s\n", PCAD.CPF);
        printf("4 - E-mail: %s\n", PCAD.EMAIL);
        printf("5 - Senha: %s\n\n", PCAD.SENHA);

        Sleep(2000);

        printf("Deseja alterar alguma informacao?\n");
        printf("1 - Sim\n");
        printf("0 - Nao\n");
        scanf("%d", &SN);
        if (SN == 1)
        {
            printf("Qual informacao deseja alterar? (Digite o numero correspondente)\n");
            printf("Digitar qualquer numero diferente dos mostrados acima confirmara as informacoes\n\n");
            scanf("%d", &ALTERACAO);
            fflush(stdin);
            if (ALTERACAO < 1 || ALTERACAO > 5)
                break;
        }
        else
            break;
    } while (1);

    ADD_PACIENTE(&PCAD);

    SYSTEM_PRINT(NADA);
    printf("Conta criada com sucesso!\n");
    Sleep(3000);
}

void CADASTRO_MEDICO()
{
    CADM MEDCAD;
    int SN, ALTERACAO = 0;
    do
    {
        if (ALTERACAO == 0 || ALTERACAO == 1)
        {
            NOME(MEDCAD.NOME);
        }

        if (ALTERACAO == 0 || ALTERACAO == 2)
        {
            CRM(MEDCAD.CRM);
        }

        if (ALTERACAO == 0 || ALTERACAO == 3)
        {
            PRECO(MEDCAD.PRECO);
        }

        if (ALTERACAO == 0 || ALTERACAO == 4)
        {
            AREA(MEDCAD.AREA);
        }

        if (ALTERACAO == 0 || ALTERACAO == 5)
        {
            EMAIL(MEDCAD.EMAIL);
        }

        if (ALTERACAO == 0 || ALTERACAO == 6)
        {
            SENHA(MEDCAD.SENHA);
        }

        SYSTEM_PRINT(NADA);

        printf("1 - Nome Completo: %s\n", MEDCAD.NOME);
        printf("2 - CRM: %s\n", MEDCAD.CRM);
        printf("3 - Valor da consulta: %s\n", MEDCAD.PRECO);
        printf("4 - Area de Atuacao: %s\n", MEDCAD.AREA);
        printf("5 - E-mail: %s\n", MEDCAD.EMAIL);
        printf("6 - Senha: %s\n", MEDCAD.SENHA);

        Sleep(3000);

        printf("Deseja alterar alguma informacao?\n");
        printf("1 - Sim\n");
        printf("0 - Nao\n");
        scanf("%d", &SN);
        if (SN == 1)
        {
            printf("Qual informacao deseja alterar? (Digite o numero correspondente)\n");
            printf("Digitar qualquer numero diferente dos mostrados acima confirmara os dados\n\n");
            scanf("%d", &ALTERACAO);
            fflush(stdin);
            if (ALTERACAO < 1 || ALTERACAO > 6)
                break;
        }
        else
            break;
    } while (1);

    ADD_MEDICO(&MEDCAD);
    SYSTEM_PRINT(NADA);
    printf("Conta criada com sucesso!\n");
    Sleep(5000);
}

void NOME(char *strPtr)
{
    SYSTEM_PRINT(NADA);
    do
    {
        printf("Formatacao: (Apenas letras e pontos para abreviacao)\n");
        printf("Maximo de 50 caracteres\n");
        printf("Nome: ");
        fgets(strPtr, 55, stdin);
        if (VERIFICA_TAMANHO_ENTRADA(strPtr, 51, 2) == 0)
        {
            fflush(stdin);
            SYSTEM_PRINT("Quantidade de caracteres invalida (Tente abreviar seu nome)!");
        }
        else if (VERIFICA_FORMATO_NOME(strPtr, '.') == 0)
            SYSTEM_PRINT("Seu nome nao deve conter acentos ou outros caracteres especiais!");
        else
        {
            TRATA_NOME(strPtr);
            break;
        }
    } while (1);
}

void DATADENASCIMENTO(char *dataPtr)
{
    SYSTEM_PRINT(NADA);
    do
    {
        printf("Formatacao: 31/12/2023\n");
        printf("Data de Nascimento: ");
        fgets(dataPtr, 13, stdin);
        if (VERIFICA_TAMANHO_EXATO(dataPtr, 11) == 0)
        {
            fflush(stdin);
            SYSTEM_PRINT("Formato invalido!");
        }
        else if (VERIFICA_DATA(dataPtr) == 0)
            SYSTEM_PRINT("Data de Nascimento invalida, por favor digite uma diferente!");
        else
            break;
    } while (1);
}

void CPF(char *CPFPtr)
{
    SYSTEM_PRINT(NADA);
    do
    {
        printf("Formatacao: 12345678910\n");
        printf("CPF: ");
        fgets(CPFPtr, 14, stdin);
        if (VERIFICA_TAMANHO_EXATO(CPFPtr, 12) == 0)
        {
            fflush(stdin);
            SYSTEM_PRINT("Quantidade de caracteres invalida!");
        }
        else if (VERIFICA_NUMERO(CPFPtr) == 0)
            SYSTEM_PRINT("Utilize apenas numeros");
        else if (VERIFICA_CPF(CPFPtr) == 0)
            SYSTEM_PRINT("CPF ja cadastrado");
        else
            break;
    } while (1);
}

void CRM(char *CRMPtr)
{
    SYSTEM_PRINT(NADA);
    do
    {
        printf("Formatacao: 123456/PB\n");
        printf("CRM: ");
        fgets(CRMPtr, 12, stdin);
        if (VERIFICA_TAMANHO_EXATO(CRMPtr, 10) == 0)
        {
            fflush(stdin);
            SYSTEM_PRINT("Formato Incorreto!");
        }
        else if (VERIFICA_FORMATO_CRM(CRMPtr) == 0)
            SYSTEM_PRINT("Utilize apenas numeros");
        else if (VERIFICA_CRM(CRMPtr) == 0)
            SYSTEM_PRINT("CRM ja cadastrado");
        else
            break;
    } while (1);
}

void PRECO(char *valorPtr)
{
    SYSTEM_PRINT(NADA);
    do
    {
        printf("Formatacao: 100,00\n");
        printf("Valor da Consulta: ");
        fgets(valorPtr, 13, stdin);
        if (VERIFICA_TAMANHO_ENTRADA(valorPtr, 11, 4) == 0)
        {
            fflush(stdin);
            SYSTEM_PRINT("Quantidade de caracteres invalida!");
        }
        else if (strstr(valorPtr, ",") == NULL)
            SYSTEM_PRINT("Formato invalido!");
        else
            break;
    } while (1);
}

void AREA(char *areaPtr)
{
    SYSTEM_PRINT(NADA);
    do
    {
        printf("Formatacao: (Apenas letras e pontos para abreviacao)\n");
        printf("Maximo de 30 caracteres\n");
        printf("Area de Atuacao: ");
        fgets(areaPtr, 35, stdin);
        if (VERIFICA_TAMANHO_ENTRADA(areaPtr, 31, 2) == 0)
        {
            fflush(stdin);
            SYSTEM_PRINT("Quantidade de caracteres invalida!");
        }
        else if (VERIFICA_FORMATO_NOME(areaPtr, '.') == 0)
            SYSTEM_PRINT("Formato Invalido!");
        else
        {
            TRATA_NOME(areaPtr);
            break;
        }
    } while (1);
}

void EMAIL(char *emailPtr)
{
    SYSTEM_PRINT(NADA);
    do
    {
        printf("Formatacao: endereco@dominio.com\n");
        printf("Maximo de 30 caracteres\n");
        printf("Email: ");
        fgets(emailPtr, 35, stdin);
        if (VERIFICA_TAMANHO_ENTRADA(emailPtr, 31, 9) == 0)
        {
            fflush(stdin);
            SYSTEM_PRINT("Quantidade de caracteres invalida!");
        }
        else if (strstr(emailPtr, "@") == NULL || strstr(emailPtr, ".com") == NULL)
            SYSTEM_PRINT("Formato invalido de email");
        else
            break;
        ;
    } while (1);
}

void SENHA(char *senhaPtr)
{
    char CONFIRMACAO[25];
    SYSTEM_PRINT(NADA);
    do
    {
        printf("Formatacao: Apenas letras, numeros e os seguintes caracteres: @, ., ! e _\n");
        printf("Maximo de 30 caracteres\n");
        printf("Senha: ");
        fgets(senhaPtr, 20, stdin);
        if (VERIFICA_TAMANHO_ENTRADA(senhaPtr, 16, 7) == 0)
        {
            fflush(stdin);
            SYSTEM_PRINT("Quantidade de caracteres invalida!");
        }
        else if (VERIFICA_SENHA(senhaPtr) == 0)
            SYSTEM_PRINT("Senha invalida, Use apenas Letras maiusculas, minusculas e numeros!");
        else
            break;
    } while (1);

    do
    {
        printf("Confirme sua Senha: ");
        fgets(CONFIRMACAO, 20, stdin);
        fflush(stdin);
        TRATAMENTO(CONFIRMACAO);
    } while (strcmp(senhaPtr, CONFIRMACAO) != 0);
}

void DESCRICAO(char *descricaoPtr, char *tipo)
{
    SYSTEM_PRINT(NADA);
    do
    {
        printf("Formatacao: Caracteres especiais nao sao permitidos\n");
        printf("Maximo de 30 caracteres\n");
        printf("%s: ", tipo);
        fgets(descricaoPtr, 55, stdin);
        if (VERIFICA_TAMANHO_ENTRADA(descricaoPtr, 51, 2) == 0)
        {
            fflush(stdin);
            SYSTEM_PRINT("Quantidade de caracteres invalida!");
        }
        else if (VERIFICA_ASCII(descricaoPtr) == 0)
            SYSTEM_PRINT("Evite caracteres com acento ou outros caracteres especiais!");
        else
        {
            TRATA_NOME(descricaoPtr);
            break;
        }
    } while (1);
}
/*
- Ambas as funções funcionam da mesma maneira.
- Recebem um ponteiro para uma struct e adiciona seus elementos ao seu respectivo arquivo.
*/
void ADD_PACIENTE(CADP *P)
{
    FILE *filePtr;
    if ((filePtr = fopen("Pacientes.txt", "a")) == NULL)
        printf("nao foi possivel abrir o arquivo");
    else
    {
        fprintf(filePtr, "\n%s %s %s %s %s", P->CPF,
                P->NOME, P->DATADEN, P->EMAIL, P->SENHA);
        fclose(filePtr);
    }
}

void ALTERAR_DADO_PACIENTE(CADP *PAC)
{
    // Funções já explicada em código posteriores
    CADP *cabeca = NULL;
    CADP **P = &cabeca;
    CADP *atual, *novo, *noatual, *limpeza;
    FILE *leituraPtr;
    if ((leituraPtr = fopen("Pacientes.txt", "r")) == NULL)
        printf("Erro ao abrir o arquivo para leitura\n");
    else
    {
        while (!feof(leituraPtr))
        {
            if (*P == NULL)
            {
                *P = (CADP *)malloc(sizeof(CADP));
                fscanf(leituraPtr, "%s %s %s %s %s", (*P)->CPF, (*P)->NOME,
                       (*P)->DATADEN, (*P)->EMAIL, (*P)->SENHA);
                (*P)->proximo = NULL;
                atual = *P;
            }
            else
            {
                novo = (CADP *)malloc(sizeof(CADP));
                fscanf(leituraPtr, "%s %s %s %s %s", novo->CPF, novo->NOME,
                       novo->DATADEN, novo->EMAIL, novo->SENHA);
                novo->proximo = NULL;
                atual->proximo = novo;
                atual = atual->proximo;
            }
        }
        fclose(leituraPtr);
    }
    FILE *escritaPtr;
    noatual = *P;
    if ((escritaPtr = fopen("Pacientes.txt", "w")) == NULL)
        printf("Falha ao criar o arquivo");
    else
    {
        while (noatual != NULL)
        {
            if (strcmp(noatual->CPF, PAC->CPF) == 0)
            {
                fprintf(escritaPtr, "\n%s %s %s %s %s", PAC->CPF, PAC->NOME,
                        PAC->DATADEN, PAC->EMAIL, PAC->SENHA);
            }
            else
            {
                fprintf(escritaPtr, "\n%s %s %s %s %s", noatual->CPF, noatual->NOME,
                        noatual->DATADEN, noatual->EMAIL, noatual->SENHA);
            }
            noatual = noatual->proximo;
        }
        fclose(escritaPtr);
    }
    limpeza = cabeca;
    while (limpeza != NULL)
    {
        cabeca = limpeza->proximo;
        free(limpeza);
        limpeza = cabeca;
    }
}

void ADD_MEDICO(CADM *M)
{
    FILE *filePtr;
    if ((filePtr = fopen("Medicos.txt", "a")) == NULL)
        printf("nao foi possivel abrir o arquivo");
    else
    {
        fprintf(filePtr, "\n%s %s %s %s %s %s",
                M->CRM, M->NOME, M->AREA,
                M->PRECO, M->EMAIL, M->SENHA);
        fclose(filePtr);
    }
}

void ALTERAR_DADO_MEDICO(CADM *MED)
{
    // Função já explicada em códigos posteriores
    CADM *cabeca = NULL;
    CADM **M = &cabeca;
    CADM *atual, *novo, *noatual, *limpeza;
    FILE *leituraPtr;
    if ((leituraPtr = fopen("Medicos.txt", "r")) == NULL)
        printf("Erro ao abrir o arquivo para leitura\n");
    else
    {
        while (!feof(leituraPtr))
        {
            if (*M == NULL)
            {
                *M = (CADM *)malloc(sizeof(CADM));
                fscanf(leituraPtr, "%s %s %s %s %s %s", (*M)->CRM, (*M)->NOME,
                       (*M)->AREA, (*M)->PRECO, (*M)->EMAIL, (*M)->SENHA);
                (*M)->proximo = NULL;
                atual = *M;
            }
            else
            {
                novo = (CADM *)malloc(sizeof(CADM));
                fscanf(leituraPtr, "%s %s %s %s %s %s", novo->CRM, novo->NOME,
                       novo->AREA, novo->PRECO, novo->EMAIL, novo->SENHA);
                novo->proximo = NULL;
                atual->proximo = novo;
                atual = atual->proximo;
            }
        }
        fclose(leituraPtr);
    }
    FILE *escritaPtr;
    noatual = *M;
    if ((escritaPtr = fopen("Medicos.txt", "w")) == NULL)
        printf("Falha ao criar o arquivo");
    else
    {
        while (noatual != NULL)
        {
            if (strcmp(noatual->CRM, MED->CRM) == 0)
            {
                fprintf(escritaPtr, "\n%s %s %s %s %s %s", MED->CRM, MED->NOME,
                        MED->AREA, MED->PRECO, MED->EMAIL, MED->SENHA);
            }
            else
            {
                fprintf(escritaPtr, "\n%s %s %s %s %s %s", noatual->CRM, noatual->NOME,
                        noatual->AREA, noatual->PRECO, noatual->EMAIL, noatual->SENHA);
            }
            noatual = noatual->proximo;
        }
        fclose(escritaPtr);
    }
    limpeza = cabeca;
    while (limpeza != NULL)
    {
        cabeca = limpeza->proximo;
        free(limpeza);
        limpeza = cabeca;
    }
}

// Cria os arquivos necessários para o programa caso ainda não existam
// (ação necessária para a primeira execução do programa, pois a Área de cadastro
// verifica existencia de algo em arquivos através do modo "r", e se tentarmos abrir
// um arquivo que não existe no modo read ele certamente retorna NULL ao inválida de criar
// o respectivo arquivo)

void CRIA_ARQUIVO(char *arquivoPtr)
{
    FILE *filePtr;
    if ((filePtr = fopen(arquivoPtr, "a")) == NULL)
        printf("Falha ao criar o arquivo");
    else
        fclose(filePtr);
}

// - Ambas recebem um ponteiro para duas strings diferentes, usuário (U) e Senha (S).
// - Comparam primeiro se o usuário existe no arquivo, se não existir retorna falso.
// - Se o usuário existir, compara a senha fornecida com a senha do usuário cadastrado.

int VERIFICA_PACIENTE(char *U, char *S, CADP *P)
{
    // Verificar o Login do Paciente
    FILE *filePtr;
    if ((filePtr = fopen("Pacientes.txt", "r")) == NULL)
        printf("Nao foi possivel abrir o arquivo");
    else
    {
        while (!feof(filePtr))
        {
            fscanf(filePtr, "%s %s %s %s %s", P->CPF,
                   P->NOME, P->DATADEN, P->EMAIL, P->SENHA);
            if (strcmp(P->CPF, U) == 0)
            {
                if (strcmp(P->SENHA, S) == 0)
                    return 1;
            }
        }
        fclose(filePtr);
    }
    return 0;
}

int VERIFICA_MEDICO(char *C, char *S, CADM *M)
{
    // Verificar o Login do Medico
    FILE *filePtr;
    if ((filePtr = fopen("Medicos.txt", "r")) == NULL)
        printf("Nao foi possivel abrir o arquivo");
    else
    {
        while (!feof(filePtr))
        {
            fscanf(filePtr, "%s %s %s %s %s %s",
                   M->CRM, M->NOME, M->AREA,
                   M->PRECO, M->EMAIL, M->SENHA);
            if (strcmp(M->CRM, C) == 0)
                if (strcmp(M->SENHA, S) == 0)
                    return 1;
        }
        fclose(filePtr);
    }
    return 0;
}

// Funções para tratamento de strings adquiridas através de fgets (devido ao '\n' que é adicionado ao final)
void TRATAMENTO(char *charPtr)
{

    // ARGUMENTOS:
    // - *charPtr = Ponteiro para String.

    // EXECUÇÃO:
    // - Troca o '\n', que sempre é adicionado ao final de uma string obtida com
    // a função fgets, por '\0' que representa o final de uma string.

    for (; *charPtr != '\0'; charPtr++)
    {
        if (*charPtr == '\n')
            *charPtr = '\0';
    }
}

void TRATA_NOME(char *nomePtr)
{

    // ARGUMENTOS:
    // - *nomePtr = Ponteiro para String.

    // EXECUÇÃO:
    // - Trata o nome fornecido pelo usuário Substituindo espaços vazios por ponto.
    // - A necessidade dessa implementação se deve a forma da linguagem ler os arquivos
    //   geralmente separados por tokens (espaços vazios os quebras de linha).

    for (; *nomePtr != '\0'; nomePtr++)
    {
        if (*nomePtr == ' ')
            *nomePtr = '_';
        if (*nomePtr == '\n')
            *nomePtr = '\0';
    }
}

// Verificação das entradas do cadastro
int VERIFICA_FORMATO_NOME(char *nomePtr, char caractere)
{

    // ARGUMENTOS:
    // - *nomePtr = Ponteiro para String.

    // EXECUÇÃO:
    // - Verfica cada letra do nome fornecido pelo usuário para garantir que ele não
    //   forneça numeros, letras com acentos ou símbolos estranhos.

    for (; *nomePtr != '\0'; nomePtr++)
    {
        if ((*nomePtr != caractere && *nomePtr != ' ') && *nomePtr < 'A')
            return 0;
        else if ((*nomePtr > 'Z' && *nomePtr < 'a'))
            return 0;
        else if (*nomePtr > 'z')
            return 0;
    }
    return 1;
}

int VERIFICA_DATA(char *dataPtr)
{
    /*
    ARGUMENTOS:
    - *dataPtr = Ponteiro para String.

    EXECUÇÃO:
    - Verifica a data fornecida pelo usuário, baseado nas posição retorna 0 se:
      - O espaço reservado para dias for maior que 39.
      - O espaço reservado para meses for maior que 19.
      - o número de barras (/) for diferente de 2.
    */
    int BARRA = 0;
    int ELEMENTOS = 0;
    for (int i = 0; *dataPtr != '\0'; dataPtr++, i++)
    {
        if (*dataPtr == '/')
            BARRA++;
        if (i == 0)
        {
            if (*dataPtr < '0' || *dataPtr > '3')
                return 0;
        }
        else if (i == 1 || i == 4)
        {
            if (*dataPtr < '0' || *dataPtr > '9')
                return 0;
        }
        else if (i == 3)
        {
            if (*dataPtr < '0' || *dataPtr > '1')
                return 0;
        }
        if (*dataPtr >= '/' && *dataPtr <= '9')
            ELEMENTOS++;
    }
    if (BARRA != 2 || ELEMENTOS != 10)
        return 0;
    return 1;
}

// - Ambas as funções abaixo verificam se o Cadastro (CPF OU CRM) fornecido já estava registrado,
//   através de um ponteiro para uma string retorna 0 caso esteja.

int VERIFICA_CPF(char *userPtr)
{
    CADP P;
    FILE *filePtr;
    if ((filePtr = fopen("Pacientes.txt", "r")) == NULL)
        printf("Nao foi possivel abrir o arquivo");
    else
    {
        while (!feof(filePtr))
        {
            fscanf(filePtr, "%s %s %s %s %s", P.CPF,
                   P.NOME, P.DATADEN, P.EMAIL, P.SENHA);
            if (strcmp(P.CPF, userPtr) == 0)
            {
                return 0;
            }
        }
        fclose(filePtr);
    }
    return 1;
}

int VERIFICA_CRM_CONSULTA(char *userPtr, CADM *M)
{
    // Verifica se o CPF já foi registrado no sistema
    // Para não acontecer casos onde dois CPFs são iguais
    // O que certamente quebraria o Login
    FILE *filePtr;
    if ((filePtr = fopen("Medicos.txt", "r")) == NULL)
        printf("Nao foi possivel abrir o arquivo");
    else
    {
        while (!feof(filePtr))
        {
            fscanf(filePtr, "%s %s %s %s %s %s", M->CRM, M->NOME,
                   M->AREA, M->PRECO,
                   M->EMAIL, M->SENHA);
            if (strcmp(M->CRM, userPtr) == 0)
                return 0;
        }
        fclose(filePtr);
    }
    return 1;
}

int VERIFICA_CRM(char *userPtr)
{
    // Verifica se o CRM já foi registrado no sistema
    // Para não acontecer casos onde dois CRMs são iguais
    // O que certamente quebraria o Login
    CADM M;
    FILE *filePtr;
    if ((filePtr = fopen("Medicos.txt", "r")) == NULL)
        printf("Nao foi possivel abrir o arquivo");
    else
    {
        while (!feof(filePtr))
        {
            fscanf(filePtr, "%s %s %s %s %s %s", M.CRM, M.NOME,
                   M.AREA, M.PRECO,
                   M.EMAIL, M.SENHA);
            if (strcmp(M.CRM, userPtr) == 0)
                return 0;
        }
        fclose(filePtr);
    }
    return 1;
}

int VERIFICA_FORMATO_CRM(char *CRMPtr)
{
    for (int i = 0; *CRMPtr != '\0'; CRMPtr++, i++)
    {
        if (i <= 5 && (*CRMPtr < '0' || *CRMPtr > '9'))
            return 0;
        else if (i == 6 && *CRMPtr != '/')
            return 0;
        else if (i >= 7 && (*CRMPtr < 'A' || *CRMPtr > 'Z'))
            return 0;
    }
    return 1;
}

// - Grande parte das funções de verficação a seguir usa os proprios caracteres para comparacao.
// - Esta comparacao funciona devido ao fato de cada caractere na linguagem estar atribuido a um
//   valor na tabela ASCII (coloque a seta do mouse em cima do caracter isolado para verificar seu valor).

int VERIFICA_SENHA(char *senhaPtr)
{
    // ARGUMENTOS:
    // - *senhaPtr = Ponteiro para String.

    // EXECUÇÃO:
    // - Verifica o formato da senha para que contenha apenas letras e numeros.
    for (; *senhaPtr != '\0'; senhaPtr++)
    {
        if (*senhaPtr < '0' && *senhaPtr != '!' && *senhaPtr != '.')
            return 0;
        else if (*senhaPtr > '9' && *senhaPtr < '@')
            return 0;
        else if (*senhaPtr > 'Z' && *senhaPtr < 'a' && *senhaPtr != '_')
            return 0;
        else if (*senhaPtr > 'z')
            return 0;
    }
    return 1;
}

int VERIFICA_NUMERO(char *numPtr)
{
    // ARGUMENTOS:
    // - *numPtr = Ponteiro para String.

    // EXECUÇÃO:
    // - Verifica a String para que ela contenha apenas números.

    for (; *numPtr != '\0'; numPtr++)
    {
        if (*numPtr < '0' || *numPtr > '9')
            return 0;
    }
    return 1;
}

int VERIFICA_MAIUSCULO(char *MAIPtr)
{
    // ARGUMENTOS:
    // - *MAIPtr = Ponteiro para String.

    // EXECUÇÃO:
    // - Verifica a String para que ela contenha apenas letras maiusculas.

    for (; *MAIPtr != '\0'; MAIPtr++)
    {
        if (*MAIPtr < 'A' || *MAIPtr > 'Z')
            return 0;
    }
    return 1;
}

int VERIFICA_ASCII(char *stringPtr)
{
    for (; *stringPtr != '\0'; stringPtr++)
    {
        if (*stringPtr < 1 || *stringPtr > 126)
            return 0;
    }
    return 1;
}

// Verificação do tamanho das entradas
int VERIFICA_TAMANHO_ENTRADA(char *entradaPtr, size_t maximo, size_t minimo)
{
    // ARGUMENTOS:
    // - *entradaPtr = Ponteiro para String fornecida pela função fgets().
    // - size_t = typedef unsigned long long (usado devido ao compilador que reclama se usarmos int).
    // - tamanho = Tamanho da string para comparação.
    // - *estruturaPtr = Ponteiro para string dentro da respectiva estrutura.

    // EXECUÇÃO:
    // - Verifica o tamanho da string para que esta seja menor ou igual
    //   o tamanho exigido dentro de sua respeciva estrutura.
    // - Também formata o '\n' ao final da string fornecida através da
    //   função fgets().

    size_t tamanho = strlen(entradaPtr);
    if (tamanho > maximo || tamanho < minimo)
        return 0;
    else
    {
        for (; *entradaPtr != '\0'; entradaPtr++)
        {
            if(*entradaPtr == '\n')
                *entradaPtr = '\0';
        }
    }
    return 1;
}

int VERIFICA_TAMANHO_EXATO(char *entradaPtr, size_t tamanhoPtr)
{

    // ARGUMENTOS:
    // - *entradaPtr = Ponteiro para String fornecida pela função fgets().
    // - size_t = typedef unsigned long long (usado devido ao compilador que reclama se usarmos int).
    // - tamanho = Tamanho da string para comparação.
    // - *estruturaPtr = Ponteiro para string dentro da respectiva estrutura.

    // EXECUÇÃO:
    // - Verifica o tamanho da string para que esta seja exatamente igual
    //   ao tamanho exigido dentro de sua respeciva estrutura.
    // - Também formata o '\n' ao final da string fornecida através da
    //   função fgets().

    if ((strlen(entradaPtr)) != tamanhoPtr)
        return 0;
    else
    {
        for (; *entradaPtr != '\0'; entradaPtr++)
        {
            if(*entradaPtr == '\n')
                *entradaPtr = '\0';
        }
    }
    return 1;
}

// CONSULTAS
void MOSTRA_MEDICOS()
{
    // Imprime para o paciente a lista de medicos que trabalham na clinica
    // Lê o arquivo dos medicos e printa suas informações
    CADM M;
    FILE *leituraPtr;
    if ((leituraPtr = fopen("Medicos.txt", "r")) == NULL)
        printf("Erro ao abrir o arquivo para leitura\n");
    else
    {
        while (!feof(leituraPtr))
        {
            fscanf(leituraPtr, "%s %s %s %s %s %s", M.CRM, M.NOME,
                   M.AREA, M.PRECO, M.EMAIL, M.SENHA);
            printf("ID: %s | Nome: Dr(a) %s | Area: %s | Valor da Consulta: %s\n\n",
                   M.CRM, M.NOME, M.AREA, M.PRECO);
        }
        fclose(leituraPtr);
    }
}

void MARCA_CONSULTA(char *pacientePtr, char *CPFPtr, char *descricaoPtr, char *medPtr, char *CRMPtr)
{
    // - Cria uma lista encadeada e copia os dados do arquivo
    // - Passa os dados dessa lista novamente para o arquivo recontando
    // as posições dos pacientes, dessa forma reorganizando as posições
    // para que o último da lista tenha sua posição correta.
    int posicao = 1;                       // Posição para referencia
    CON *cabeca = NULL;                    // Definindo o primeiro nó como Nulo
    CON **C = &cabeca;                     // Atribuindo um ponteiro para um ponteiro, apontando para o primeiro nó
    CON *atual, *novo, *noatual, *limpeza; // criando as demais estruturas
    FILE *leituraPtr;
    if ((leituraPtr = fopen("Consultas.txt", "r")) == NULL) // Lendo o arquivo em questão
        printf("Erro ao abrir o arquivo para leitura\n");
    else
    {
        while (!feof(leituraPtr))
        {
            if (*C == NULL) // colocando as variaveis no primeiro nó
            {
                *C = (CON *)malloc(sizeof(CON));
                fscanf(leituraPtr, "%d %s %s %s %s %s", &(*C)->POSICAO, (*C)->CPF, (*C)->NOMEPAC,
                       (*C)->IDENTIFICACAO, (*C)->CRMMED, (*C)->DESCRICAO);
                (*C)->proximo = NULL;
                atual = *C;
            }
            else // atribuindo as demais informações para os nós subsequentes
            {
                novo = (CON *)malloc(sizeof(CON));
                fscanf(leituraPtr, "%d %s %s %s %s %s", &novo->POSICAO, novo->CPF, novo->NOMEPAC,
                       novo->IDENTIFICACAO, novo->CRMMED, novo->DESCRICAO);
                novo->proximo = NULL;
                atual->proximo = novo;
                atual = atual->proximo;
            }
        }
        fclose(leituraPtr); // Fechando o arquivo para poder abri-lo de novo como escrita
    }
    atual = atual->proximo;
    FILE *escritaPtr;
    noatual = *C;
    if ((escritaPtr = fopen("Consultas.txt", "w")) == NULL) // Abrindo o arquivo como escrita
        printf("Falha ao criar o arquivo");
    else
    {
        while (noatual != NULL)
        {
            if (strcmp(noatual->CRMMED, CRMPtr) == 0) // se o CRM for igual ao argumento da função as posições serão refeitas
            {
                fprintf(escritaPtr, "\n%d %s %s %s %s %s", posicao, noatual->CPF,
                        noatual->NOMEPAC, noatual->IDENTIFICACAO, noatual->CRMMED, noatual->DESCRICAO);
                posicao++;
            }
            else // se o CRM for diferente as informações serão copiadas exatamente como estavam
            {
                fprintf(escritaPtr, "\n%d %s %s %s %s %s", noatual->POSICAO, noatual->CPF,
                        noatual->NOMEPAC, noatual->IDENTIFICACAO, noatual->CRMMED, noatual->DESCRICAO);
            }
            noatual = noatual->proximo;
        }
        fprintf(escritaPtr, "\n%d %s %s %s %s %s", posicao, CPFPtr,
                pacientePtr, medPtr, CRMPtr, descricaoPtr); // adicionando a nova consulta ao arquivo
        fclose(escritaPtr);                                 // Fechando o arquivo
    }
    limpeza = cabeca;
    while (limpeza != NULL) // Limpando as estruturas alocadas dinamicamente
    {
        cabeca = limpeza->proximo;
        free(limpeza);
        limpeza = cabeca;
    }
}

void EXCLUI_CONSULTA(char *CPF, char *CRM)
{
    // - Cria uma lista encadeada e copia os dados do arquivo
    // - Passa os dados dessa lista novamente para o arquivo recontando
    // as posicoes dos pacientes, dessa forma reorganizando as posicoes.
    // Funcionamento parecido com a funçõeo anterior, diferença mostrada no final da função
    int posicao = 1;
    CON *cabeca;
    CON **C = &cabeca;
    CON *atual, *novo, *noatual, *limpeza;
    FILE *leituraPtr;
    if ((leituraPtr = fopen("Consultas.txt", "r")) == NULL)
        printf("Erro ao abrir o arquivo para leitura\n");
    else
    {
        while (!feof(leituraPtr))
        {
            if (*C == NULL)
            {
                *C = (CON *)malloc(sizeof(CON));
                fscanf(leituraPtr, "%s %s %s %s %s", (*C)->CPF, (*C)->NOMEPAC,
                       (*C)->IDENTIFICACAO, (*C)->CRMMED, (*C)->DESCRICAO);
                (*C)->proximo = NULL;
                atual = *C;
            }
            else
            {
                novo = (CON *)malloc(sizeof(CON));
                fscanf(leituraPtr, "%s %s %s %s %s", novo->CPF, novo->NOMEPAC,
                       novo->IDENTIFICACAO, novo->CRMMED, novo->DESCRICAO);
                novo->proximo = NULL;
                atual->proximo = novo;
                atual = atual->proximo;
            }
        }
        printf("Terminei a lista\n");
        fclose(leituraPtr);
    }
    FILE *escritaPtr;
    noatual = *C;
    printf("Declarei as novas funcoes\n");
    if ((escritaPtr = fopen("Consultas.txt", "w")) == NULL)
        printf("Falha ao criar o arquivo");
    else
    {
        printf("Comecando o loop\n");
        while (noatual != NULL)
        {
            printf("Entrei no Loop");
            if (strcmp(noatual->CRMMED, CRM) == 0 && strcmp(noatual->CPF, CPF) != 0)
            { // Verifica o CRM e CPF, se o CRM for igual e o CPF diferente, reposiciona os pacientes
                fprintf(escritaPtr, "\n%d %s %s %s %s %s", posicao, noatual->CPF,
                        noatual->NOMEPAC, noatual->IDENTIFICACAO, noatual->CRMMED, noatual->DESCRICAO);
                posicao++;
            }
            else if (strcmp(noatual->CRMMED, CRM) != 0 || strcmp(noatual->CPF, CPF) != 0)
            { // se ambos, CRM e CPF forem diferentes, apenas grava os dados salvos anteriormente
                fprintf(escritaPtr, "\n%d %s %s %s %s %s", noatual->POSICAO, noatual->CPF,
                        noatual->NOMEPAC, noatual->IDENTIFICACAO, noatual->CRMMED, noatual->DESCRICAO);
            }
            printf("Passei as verificacoes\n");
            noatual = noatual->proximo;
            printf("Proximo no\n");
        }
        printf("Terminei o Loop\n");
        fclose(escritaPtr);
    }
    limpeza = cabeca;
    printf("Comecei a limpeza\n");
    while (limpeza != NULL)
    {
        cabeca = limpeza->proximo;
        free(limpeza);
        limpeza = cabeca;
    }
}

void MOSTRAR_CONSULTAS(char *CRMPtr, char *CPFPtr)
{
    // Mostra as consultas, tanto para pacientes quanto para medicos
    // Para mostrar as consultas dos pacientes o ponteiro para CRM tem que ser igual a ' ' ou NADA
    // e vice versa
    CON C;
    FILE *consultaPtr;
    if ((consultaPtr = fopen("Consultas.txt", "r")) == NULL)
        printf("Erro ao abrir o arquivo para leitura\n");
    else
    {
        printf("Voce possui as seguintes consultas marcadas\n\n");
        while (!feof(consultaPtr))
        {
            if (*CRMPtr != ' ')
            {
                fscanf(consultaPtr, "%d %s %s %s %s %s", &C.POSICAO, C.CPF, C.NOMEPAC,
                       C.IDENTIFICACAO, C.CRMMED, C.DESCRICAO);
                if (strcmp(C.CRMMED, CRMPtr) == 0)
                {
                    printf("Posicao na Lista: %d\n", C.POSICAO);
                    printf("CPF: %s\n", C.CPF);
                    printf("Paciente: %s\n", C.NOMEPAC);
                    printf("Descricao: %s\n\n", C.DESCRICAO);
                }
            }
            if (*CPFPtr != ' ')
            {
                fscanf(consultaPtr, "%d %s %s %s %s %s", &C.POSICAO, C.CPF, C.NOMEPAC,
                       C.IDENTIFICACAO, C.CRMMED, C.DESCRICAO);
                if (strcmp(C.CPF, CPFPtr) == 0)
                {
                    printf("Posicao na Lista: %d\n", C.POSICAO);
                    printf("Medico: %s\n", C.IDENTIFICACAO);
                    printf("CRM: %s\n", C.CRMMED);
                    printf("Descricao: %s\n\n", C.DESCRICAO);
                }
            }
        }
        fclose(consultaPtr);
    }
}

int VERIFICA_CONSULTA(char *CRMPtr, char *CPFPtr)
{
    // Verifica se a consulta existe no arquivo
    // Baseado no CRM e CPF, se os dois forem compatíveis com alguma
    // consulta registrada no arquivo, retorna 1, do contrario, retorna 0
    CON C;
    FILE *leituraPtr;
    if ((leituraPtr = fopen("Consultas.txt", "r")) == NULL)
        printf("Erro ao abrir o arquivo para leitura\n");
    else
    {
        while (!feof(leituraPtr))
        {
            fscanf(leituraPtr, "%d %s %s %s %s %s", &C.POSICAO, C.CPF, C.NOMEPAC,
                   C.IDENTIFICACAO, C.CRMMED, C.DESCRICAO);
            if (strcmp(C.CPF, CPFPtr) == 0 && strcmp(C.CRMMED, CRMPtr) == 0)
                return 1;
        }
        fclose(leituraPtr);
    }
    return 0;
}

// ACOMPANHAMENTOS
void ADD_ACOMP(ACOMP *A)
{
    // Adiciona um novo acompanhamento ao arquivo
    FILE *leituraPtr;
    if ((leituraPtr = fopen("Acompanhamentos.txt", "a")) == NULL)
        printf("Erro ao abrir o arquivo para leitura\n");
    else
    {
        fprintf(leituraPtr, "\n%s %s %s %s %s %s %s %s", A->CPF, A->CRM, A->MEDICO, A->STATUS,
                A->MEDICACAO, A->DOSAGEM, A->RECOMENDACAO, A->PERIODO);
        fclose(leituraPtr);
    }
}

void MOSTRAR_ACOMPANHAMENTOS(char *CPFPtr, char *CRMPtr)
{
    // Imprime os acompanhamentos para ambos, pacientes e medicos
    // funcionamento já mostrado anteriormente
    ACOMP A;
    FILE *leituraPtr;
    if ((leituraPtr = fopen("Acompanhamentos.txt", "r")) == NULL)
        printf("Erro ao abrir o arquivo para leitura\n");
    else
    {
        while (!feof(leituraPtr))
        {
            fscanf(leituraPtr, "%s %s %s %s %s %s %s %s", A.CPF, A.CRM, A.MEDICO, A.STATUS,
                   A.MEDICACAO, A.DOSAGEM, A.RECOMENDACAO, A.PERIODO);
            if (*CPFPtr != ' ')
            {
                if (strcmp(A.CPF, CPFPtr) == 0)
                {
                    printf("Nome do Medico: %s\n", A.MEDICO);
                    printf("Status do Paciente: %s\n", A.STATUS);
                    printf("Medicacao recomendada: %s\n", A.MEDICACAO);
                    printf("Dosagem da medicacao: %s\n", A.DOSAGEM);
                    printf("Recomendacoes: %s\n", A.RECOMENDACAO);
                    printf("Periodo: %s\n\n", A.PERIODO);
                }
            }
            else
            {
                if (strcmp(A.CRM, CRMPtr) == 0)
                {
                    printf("CPF do Paciente: %s\n", A.CPF);
                    printf("Status do Paciente: %s\n", A.STATUS);
                    printf("Medicacao recomendada: %s\n", A.MEDICACAO);
                    printf("Dosagem da medicacao: %s\n", A.DOSAGEM);
                    printf("Recomendacoes: %s\n", A.RECOMENDACAO);
                    printf("Periodo: %s\n\n", A.PERIODO);
                }
            }
        }
        fclose(leituraPtr);
    }
}

void ACOMPANHAMENTOS(char *CPFPtr, char *CRMPtr, char *medPtr, int ALTERACAO, ACOMP *A)
{
    // Funcionamento semelhante as funções de cadastro
    // Neste caso um novo elemento é adicionado chamado CADALT
    // CADALT pode variar entre 0 e algum valor diferente de 0 (positivo entre 1 e 5)
    // esses valores definem se a execução será para cadastro de um novo acompanhamento
    // ou se será apenas a alteração de algum elemento de um dado acompanhamento
    int SN, CADALT = ALTERACAO;
    do
    {
        if (ALTERACAO == 0 || ALTERACAO == 1)
        {
            DESCRICAO(A->STATUS, "Status");
        }

        if (ALTERACAO == 0 || ALTERACAO == 2)
        {
            DESCRICAO(A->MEDICACAO, "Medicacao");
        }

        if (ALTERACAO == 0 || ALTERACAO == 3)
        {
            DESCRICAO(A->DOSAGEM, "Dosagem");
        }

        if (ALTERACAO == 0 || ALTERACAO == 4)
        {
            DESCRICAO(A->RECOMENDACAO, "Recomendacoes");
        }

        if (ALTERACAO == 0 || ALTERACAO == 5)
        {
            DESCRICAO(A->PERIODO, "Periodo");
        }

        SYSTEM_PRINT(NADA);
        printf("CPF do Paciente: %s\n", CPFPtr);
        printf("1 - Status: %s\n", A->STATUS);
        printf("2 - Medicacao: %s\n", A->MEDICACAO);
        printf("3 - Dosagem: %s\n", A->DOSAGEM);
        printf("4 - Recomendacao: %s\n", A->RECOMENDACAO);
        printf("5 - Periodo: %s\n", A->PERIODO);

        Sleep(3000);

        printf("Deseja alterar alguma informacao?\n");
        printf("1 - Sim\n");
        printf("0 - Nao\n");
        scanf("%d", &SN);
        if (SN == 1)
        {
            printf("Qual informacao deseja alterar? (Digite o numero correspondente)\n");
            printf("Digitar qualquer numero diferente dos mostrados acima confirmara os dados anteriores\n\n");
            scanf("%d", &ALTERACAO);
            fflush(stdin);
            if (ALTERACAO < 1 || ALTERACAO > 7)
                break;
        }
        else
            break;
    } while (1);

    if (CADALT == 0) // CADALT = 0, Adicionar um novo acompanhamento
    {
        strcpy(A->CPF, CPFPtr); // Colocando as strings que faltam dentro da estrutura
        strcpy(A->CRM, CRMPtr);
        strcpy(A->MEDICO, medPtr);

        ADD_ACOMP(A);
        SYSTEM_PRINT(NADA);
        printf("Acompanhamento Adicionado com Sucesso!\n");
        Sleep(3000);
        SYSTEM_PRINT(NADA);
    }
    else // CADALT diferente de 0, alterar um acompanhamento
    {
        ALTERA_ACOMP(A);
        SYSTEM_PRINT(NADA);
        printf("Alteracao Realizada com Sucesso!\n");
        Sleep(3000);
        SYSTEM_PRINT(NADA);
    }
}

void EXCLUI_ACOMP(char *CRMPtr, char *CPFPtr)
{
    // Funcionamento igual as outras funções de exclusão
    // Apenas excluindo o elemento da posição que não
    // se faz necessário
    ACOMP *cabeca = NULL;
    ACOMP **A = &cabeca;
    ACOMP *atual, *novo, *noatual, *limpeza;
    FILE *leituraPtr;
    if ((leituraPtr = fopen("Acompanhamentos.txt", "r")) == NULL)
        printf("Erro ao abrir o arquivo para leitura\n");
    else
    {
        while (!feof(leituraPtr))
        {
            if (*A == NULL)
            {
                *A = (ACOMP *)malloc(sizeof(ACOMP));
                fscanf(leituraPtr, "%s %s %s %s %s %s %s %s", (*A)->CPF, (*A)->CRM, (*A)->MEDICO,
                       (*A)->STATUS, (*A)->MEDICACAO, (*A)->DOSAGEM, (*A)->RECOMENDACAO, (*A)->PERIODO);
                (*A)->proximo = NULL;
                atual = *A;
            }
            else
            {
                novo = (ACOMP *)malloc(sizeof(ACOMP));
                fscanf(leituraPtr, "%s %s %s %s %s %s %s %s", novo->CPF, novo->CRM, novo->MEDICO,
                       novo->STATUS, novo->MEDICACAO, novo->DOSAGEM, novo->RECOMENDACAO, novo->PERIODO);
                novo->proximo = NULL;
                atual->proximo = novo;
                atual = atual->proximo;
            }
        }
        fclose(leituraPtr);
    }
    FILE *escritaPtr;
    noatual = *A;
    if ((escritaPtr = fopen("Acompanhamentos.txt", "w")) == NULL)
        printf("Falha ao criar o arquivo");
    else
    {
        while (noatual != NULL)
        {
            if (strcmp(noatual->CRM, CRMPtr) != 0 || strcmp(noatual->CPF, CPFPtr) != 0)
            {
                fprintf(leituraPtr, "\n%s %s %s %s %s %s %s %s", noatual->CPF, noatual->CRM, noatual->MEDICO,
                        noatual->STATUS, noatual->MEDICACAO, noatual->DOSAGEM, noatual->RECOMENDACAO, noatual->PERIODO);
            }
            noatual = noatual->proximo;
        }
        fclose(escritaPtr);
    }
    limpeza = cabeca;
    while (limpeza != NULL)
    {
        cabeca = limpeza->proximo;
        free(limpeza);
        limpeza = cabeca;
    }
}

void ALTERA_ACOMP(ACOMP *AC)
{
    // Usa o mesmo pricipio de copiar os dados de um arquivo e passa-los para uma lista encadeada
    // O diferencial nesse caso é que, ao invés de alterar, apenas printamos os dados do acompanhamento
    // na linha em que o CPF e o CRM são iguais aos do paciente e medico respectivamente
    ACOMP *cabeca = NULL;
    ACOMP **A = &cabeca;
    ACOMP *atual, *novo, *noatual, *limpeza;
    FILE *leituraPtr;
    if ((leituraPtr = fopen("Acompanhamentos.txt", "r")) == NULL)
        printf("Erro ao abrir o arquivo para leitura\n");
    else
    {
        while (!feof(leituraPtr))
        {
            if (*A == NULL)
            {
                *A = (ACOMP *)malloc(sizeof(ACOMP));
                fscanf(leituraPtr, "%s %s %s %s %s %s %s %s", (*A)->CPF, (*A)->CRM, (*A)->MEDICO,
                       (*A)->STATUS, (*A)->MEDICACAO, (*A)->DOSAGEM, (*A)->RECOMENDACAO, (*A)->PERIODO);
                (*A)->proximo = NULL;
                atual = *A;
            }
            else
            {
                novo = (ACOMP *)malloc(sizeof(ACOMP));
                fscanf(leituraPtr, "%s %s %s %s %s %s %s %s", novo->CPF, novo->CRM, novo->MEDICO,
                       novo->STATUS, novo->MEDICACAO, novo->DOSAGEM, novo->RECOMENDACAO, novo->PERIODO);
                novo->proximo = NULL;
                atual->proximo = novo;
                atual = atual->proximo;
            }
        }
        fclose(leituraPtr);
    }
    FILE *escritaPtr;
    noatual = *A;
    if ((escritaPtr = fopen("Acompanhamentos.txt", "w")) == NULL)
        printf("Falha ao criar o arquivo");
    else
    {
        while (noatual != NULL)
        {
            if (strcmp(noatual->CRM, AC->CRM) == 0 && strcmp(noatual->CPF, AC->CPF) == 0)
            { // Se ambas as informações forem iguais, imprime os dados da estrutura passada como argumento
                fprintf(leituraPtr, "\n%s %s %s %s %s %s %s %s", AC->CPF, AC->CRM, AC->MEDICO,
                        AC->STATUS, AC->MEDICACAO, AC->DOSAGEM, AC->RECOMENDACAO, AC->PERIODO);
            }
            else
            { // caso contrário, imprime o resto da lista no arquivo
                fprintf(leituraPtr, "\n%s %s %s %s %s %s %s %s", noatual->CPF, noatual->CRM, noatual->MEDICO,
                        noatual->STATUS, noatual->MEDICACAO, noatual->DOSAGEM, noatual->RECOMENDACAO, noatual->PERIODO);
            }
            noatual = noatual->proximo;
        }
        fclose(escritaPtr);
    }
    limpeza = cabeca;
    while (limpeza != NULL)
    {
        cabeca = limpeza->proximo;
        free(limpeza);
        limpeza = cabeca;
    }
}

int VERIFICA_ACOMPANHAMENTO(char *CPFPtr, char *CRMPtr, ACOMP *A)
{
    // Verifica se existem acompanhamentos referentes ao paciente e ao médico
    // Apenas retorna 1, caso ache uma linha onde o med e o pac forem iguais aos passados nos argumentos
    FILE *leituraPtr;
    if ((leituraPtr = fopen("Acompanhamentos.txt", "r")) == NULL)
        printf("Erro ao abrir o arquivo para leitura\n");
    else
    {
        while (!feof(leituraPtr))
        {
            fscanf(leituraPtr, "%s %s %s %s %s %s %s %s", A->CPF, A->CRM, A->MEDICO,
                   A->STATUS, A->MEDICACAO, A->DOSAGEM, A->RECOMENDACAO, A->PERIODO);
            if (strcmp(A->CPF, CPFPtr) == 0 && strcmp(A->CRM, CRMPtr) == 0)
                return 1;
        }
        fclose(leituraPtr);
    }
    return 0;
}