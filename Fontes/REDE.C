/***************************************************************************
*
*  $MCD Módulo de implementação: USU  Usuário da rede de relacionamentos
*
*  Arquivo gerado:              USUARIO.c
*  Letras identificadoras:      USU
*
*  Nome da base de software:    iMigo - a sua nova rede de relacionamentos
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301/ iMigo - a sua nova rede de relacionamentos
*  Gestor:  LES/DI/PUC-Rio
*  Autores: pfs, hfac , yan
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações*     
*     1       pfs   17/11/2017 início desenvolvimento
*     2       pfs   26/11/2017 Continuação do desenvolvimento
*     3       pfs   29/11/2017 Continuação do desenvolvimento
*
***************************************************************************/
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   <ctype.h>

#include "USUARIO.H"

   typedef enum {

         RED_CondRetOK ,
               /* Concluiu corretamente */
               
         RED_CondRetPerfilIncorreto ,
               /* O perfil do usuário está incorreto */

         RED_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de lista */

   } RED_tpCondRet ;


void criarUsuario (USU_tppUsuario minhaRede);
RED_tpCondRet pegaAtributosUsuario(char * nome, int * idade, char * genero);
void removerUsuario (USU_tppUsuario minhaRede);
void adicionarAmigo (USU_tppUsuario minhaRede);

int verificaIdade (int idade);
int verificaGenero (char genero);


int main (void)
{    
    int opcao;
    USU_tppUsuario minhaRede;
    opcao = 1;
    minhaRede = USU_InicializarModulo();
    printf(" \n Bem vindo ao iMigo a sua nova rede de relacionametos\n\n\n");
    do{
        printf (" Digite o que deseja fazer:\n0- Finalizar execucao\n1- Criar Usuario\n2- Remover Usuario\n3- Adicionar Amigo\n");
        scanf("%d",&opcao);
        switch (opcao)
        {
            case 1:
                criarUsuario(minhaRede);
                break;
            case 2:
                removerUsuario(minhaRede);
                break;
            case 3:
                adicionarAmigo(minhaRede);
                break;
            default:
                break;
        }
    } while(opcao != 0);

    USU_DestruirUsuarios(minhaRede);
    return 0;
}



void criarUsuario (USU_tppUsuario minhaRede)
{
    RED_tpCondRet RED_retorno;
    USU_tpCondRet USU_retorno;
    char nome[50];
    int idade;
    char genero;

    RED_retorno = pegaAtributosUsuario(nome, &idade , &genero);
    if(RED_retorno == RED_CondRetOK)
    {
        printf("Perfil correto, inserindo usuario...\n");
        USU_retorno = USU_CriaUsuario(minhaRede,nome,idade,genero);
        printf ( "\n\n RETORNO CRIA %d\n\n",USU_retorno);
    }
    else
    {
        printf("Perfil incorreto voltando pro menu...\n");
    }

}
void removerUsuario (USU_tppUsuario minhaRede)
{

}
void adicionarAmigo (USU_tppUsuario minhaRede)
{

}

int verificaIdade (int idade)
{
    if(idade < 1 || idade > 199)
    {
        return 0; 
    }
    return 1;
}

int verificaGenero (char genero)
{
    if(genero == 'M' || genero == 'F' || genero == 'O' )
    {
        return 1;
    }
    return 0;
}

RED_tpCondRet pegaAtributosUsuario(char * nome, int * idade, char * genero)
{
    int contador; // se passar de 3 tentativas vou retornar erro

    /*** NOME ***/
    printf ("Digite o nome do usuario(max 49 caracteres): ");
    scanf(" %49[^\n]",nome);
    fflush(stdin);

    /*** IDADE ***/
    printf ("Digite sua idade: ");
    scanf(" %d",idade);
    fflush(stdin);
    contador = 0;
    while(verificaIdade(*idade) == 0)
    {
        if(++contador > 2)
        {
            return RED_CondRetPerfilIncorreto;
        }
        printf("idade invalida, por favor digite valores entre 1 e 199\n");
        scanf(" %d",idade);
        fflush(stdin);        
    }
    contador = 0;
    /*** GENERO ***/
    printf ("Digite seu genero('M','F' ou 'O' para outros ): ");
    scanf(" %c",genero);
    fflush(stdin);
    *genero = toupper(*genero);

    while(verificaGenero(*genero) == 0)
    {
        if(++contador > 2)
        {
            return RED_CondRetPerfilIncorreto;
        }
        printf("Genero invalido, por favor digite seu genero('M','F' ou 'O' para outros ): \n");
        scanf(" %c",genero);
        fflush(stdin);
        *genero = toupper(*genero);        
    }

    printf ("\n Voce digitou: Nome:%s: \n idade: %d\n sexo: %c \n", nome,*idade,*genero);

    return RED_CondRetOK;
}