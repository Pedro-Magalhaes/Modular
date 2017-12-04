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
*     1       pfs   01/12/2017 início desenvolvimento
*     3       pfs   02/12/2017 Continuação do desenvolvimento
*     3       pfs   03/12/2017 Continuação do desenvolvimento
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

#define MAXNOME 50

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
void IrUsuario (USU_tppUsuario minhaRede);

int verificaIdade (int idade);
int verificaGenero (char genero);


int main (void)
{    
    int opcao;
    char * nome;
    USU_tppUsuario minhaRede;
    opcao = 1;
    minhaRede = USU_InicializarModulo();
    printf(" \n\t\tBem vindo ao iMigo a sua nova rede de relacionametos\n");
    do{
        nome = USU_PegaNomeUsuarioCorrente(minhaRede);
        if(nome != NULL)
        {
            printf("\nVoce esta logado como: %s\n",nome);
        }/* if */
        else
        {
            printf("\nRede atualmente sem usuarios\n");
        }/* else */
        printf ("Digite o que deseja fazer:\n\t0- Finalizar execucao\n\t1- Criar Usuario\n\t2- Remover Usuario\n\t3- Adicionar Amigo\n\t4- Ir para usuario por nome\n");
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
            case 4:
                IrUsuario(minhaRede);
                break;
            default:
                break;
        }/* switch */
    } while(opcao != 0);

    USU_DestruirUsuarios(minhaRede);
    return 0;
}



void criarUsuario (USU_tppUsuario minhaRede)
{
    RED_tpCondRet RED_retorno;
    USU_tpCondRet USU_retorno;
    char nome[MAXNOME];
    int idade;
    char genero;

    RED_retorno = pegaAtributosUsuario(nome, &idade , &genero);
    if(RED_retorno == RED_CondRetOK)
    {
        printf("Perfil correto, inserindo usuario...\n");
        USU_retorno = USU_CriaUsuario(minhaRede,nome,idade,genero);
        if(USU_retorno == USU_CondRetOK)
        {
            printf("Usuario inserido\n");
            return;
        }/* if */
        if(USU_retorno == USU_CondRetFaltouMemoria)
        {
            printf("ERRO criar usuario, falta de memoria\n");
            return;
        }/* if */
        if(USU_retorno == USU_CondRetPerfilIncorreto)
        {// não poderia ocorrer uma vez que o perfil também é verificado na rede, dados deveriam estar corretos
            printf("ERRO criar usuario, perfil incorreto\n");
            return;
        }/* if */
    }/* if */
    else
    {
        printf("Perfil incorreto voltando pro menu...\n");
    }/* else */

}
void removerUsuario (USU_tppUsuario minhaRede)
{
    char * aux;
    char opcao;
    int num_usuarios; 
    int num_usuarios_final;
    aux = USU_PegaNomeUsuarioCorrente(minhaRede);
    num_usuarios = USU_TotalUsuarios(minhaRede);
    if(aux != NULL && num_usuarios > 0)
    {
        printf("Removendo Usuario: %s (total de usu da rede: %d) \nDeseja continuar?(s / n)\n",aux,num_usuarios);
        scanf(" %c",&opcao);
        fflush(stdin);
        if( toupper(opcao) == 'N' )
        {
            printf("Delecao cancelada...\n");
            return;
        }
        if(USU_DeletarUsuario(minhaRede) == USU_CondRetOK)
        {
            num_usuarios_final = USU_TotalUsuarios(minhaRede);
            printf("Usuario %s removido (total de usu da rede: %d)\n",aux,num_usuarios_final);
            return;
        }/* if */
        else
        {
            printf("Usuario %s nao pode ser removido. ERRO.\n",aux);
        }/* else */

        
    }/* if */
    else
    {
        printf("Nao ha usuarios a serem removidos (num usuarios: %d)\n",num_usuarios);
    }/* else */
    
}
void adicionarAmigo (USU_tppUsuario minhaRede)
{
    char nome[MAXNOME];
    char * nomeUsuarioCorrente;
    int usuarios;
    if(minhaRede == NULL)
    {
        printf("Rede não inicializada\n");
        return;
    }
    nomeUsuarioCorrente = USU_PegaNomeUsuarioCorrente(minhaRede);
    if(nomeUsuarioCorrente == NULL)
    {
        usuarios = USU_TotalUsuarios(minhaRede);
        if(usuarios < 0)
        {
            printf("Rede não inicializada\n");
            return;
        }
        if (usuarios == 0)
        {
            printf("Ninguem foi adicionado ainda, tente adicionar usuarios primeiro\n");
            return;
        }
        printf("erro no usuario corrente dentro da funcao RED_adicionarAmigo,numero de usuarios: %d\n",usuarios);
        return;
    }/* if */
    printf("%s digite no nome do amigo a adicionar:\n",nomeUsuarioCorrente);
    scanf(" %49[^\n]",nome);
    if( USU_AdicionaAmigo(minhaRede,nome) == USU_CondRetOK)
    {
        printf("Usuario adicionado ou ja pertencia a sua rede de contatos\n");
        return;
    }/* if */
    printf("usuario nao encontrado na rede\n");
    
}

void IrUsuario (USU_tppUsuario minhaRede)
{
    int aux = -1;
    char nome[MAXNOME];
    printf("digite o nome buscado: \n");
    scanf(" %49[^\n]",nome);
    
    printf("Buscando usuario com nome: %s: ...",nome);
    aux = USU_IrUsuario(minhaRede,nome);
    if(aux >= 0)
    {
        printf("Usuario encontrado com Id: %d\n",aux);
        return;
    }/* if */
    printf("Usuario nao encontrado \n");
        return;
}

int verificaIdade (int idade)
{
    if(idade < 1 || idade > 199)
    {
        return 0; 
    }/* if */
    return 1;
}

int verificaGenero (char genero)
{
    if(genero == 'M' || genero == 'F' || genero == 'O' )
    {
        return 1;
    }/* if */
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
        }/* if */
        printf("idade invalida, por favor digite valores entre 1 e 199\n");
        scanf(" %d",idade);
        fflush(stdin);        
    }/* while */
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
        }/* if */
        printf("Genero invalido, por favor digite seu genero('M','F' ou 'O' para outros ): \n");
        scanf(" %c",genero);
        fflush(stdin);
        *genero = toupper(*genero);        
    }/* while */

    printf ("\tVoce digitou: Nome:%s \n\tidade: %d\n\tsexo: %c \n", nome,*idade,*genero);

    return RED_CondRetOK;
}