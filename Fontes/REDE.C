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

         RED_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um elemento de lista */
        RED_CondRetRedeNula

   } RED_tpCondRet ;

RED_tpCondRet pegaNome(USU_tppUsuario minhaRede,char * nome);
RED_tpCondRet pegaIdade(int * idade);
RED_tpCondRet pegaGenero(char * genero);
RED_tpCondRet pegaAtributosUsuario(USU_tppUsuario minhaRede,char * nome, int * idade, char * genero);
void criarUsuario (USU_tppUsuario minhaRede);
void removerUsuario (USU_tppUsuario minhaRede);
void adicionarAmigo (USU_tppUsuario minhaRede);
void IrUsuario (USU_tppUsuario minhaRede);
RED_tpCondRet editarPerfil(USU_tppUsuario minhaRede,char* nome);
void mostrarAmigos(USU_tppUsuario minhaRede);
RED_tpCondRet verificaIdade (int idade);
RED_tpCondRet verificaGenero (char genero);
void msgPublica(USU_tppUsuario minhaRede,char* nome);
void pegaMsgPublica(USU_tppUsuario minhaRede,char* nome);


int main (void)
{    
    int opcao;
    char * nome;
    int size =0;
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
        printf ("Digite o que deseja fazer:\n\t0- Finalizar execucao\n\t1- Criar Usuario\n\t2- Remover Usuario\n\t3- Adicionar Amigo\n\t4- Editar Perfil\n\t5- Ir para usuario por nome\n\t6- Mostrar Amigos\n\t7- Msg Publica\n\t8- ver msgs Publicas\n");
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
                editarPerfil(minhaRede,nome);
            break;
            case 5:
                IrUsuario(minhaRede);
                break;
            case 6:
                mostrarAmigos(minhaRede);
                break;
            case 7:
                msgPublica(minhaRede,nome);
                break;
            case 8:
                pegaMsgPublica(minhaRede,nome);
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
    RED_retorno = pegaAtributosUsuario(minhaRede,nome, &idade , &genero);
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
    char dados[100];
    printf("digite o nome buscado: \n");
    scanf(" %49[^\n]",nome);
    
    printf("Buscando usuario com nome: %s: ...",nome);
    aux = USU_IrUsuario(minhaRede,nome);
    if(aux >= 0)
    {
        USU_PegaDadosUsuarioCorrente(minhaRede,dados);
        printf("usuario encontrado:\n%s\n",dados);
        return;
    }/* if */
    printf("Usuario nao encontrado \n");
        return;
}

RED_tpCondRet verificaIdade (int idade)
{
    if(idade < 1 || idade > 199)
    {
        return RED_CondRetPerfilIncorreto;; 
    }/* if */
    return RED_CondRetOK;
}

RED_tpCondRet verificaGenero (char genero)
{
    if(genero == 'M' || genero == 'F' || genero == 'O' )
    {
        return RED_CondRetOK;
    }/* if */
    return RED_CondRetPerfilIncorreto;
}

RED_tpCondRet editarPerfil(USU_tppUsuario minhaRede,char * nome)
{
    int escolha;
    int idade;
    char genero;
    char novoNome[MAXNOME];
    printf("%s ,digite:\n\t0- Voltar\n\t1- Para alterar nome\n\t2- genero\n\t3- Idade\n",nome);
    scanf("%d",&escolha);
    switch (escolha)
    {
        case 1:
            if(pegaNome(minhaRede,novoNome)==RED_CondRetOK)
            {
                USU_EditarNome(minhaRede,novoNome);
                return RED_CondRetOK;
            }            
            break;
        case 2:
            if(pegaGenero(&genero)==RED_CondRetOK)
            {
             USU_EditarGenero(minhaRede,genero);
             return RED_CondRetOK;
            }
            break;
        case 3:
            if(pegaIdade(&idade)==RED_CondRetOK)
            {
             USU_EditarIdade(minhaRede,idade);            
            }            
            break;
        default:
            return RED_CondRetOK;
            break;
    }/* switch */

    return RED_CondRetPerfilIncorreto;
}

RED_tpCondRet pegaAtributosUsuario(USU_tppUsuario minhaRede,char * nome, int * idade, char * genero)
{
    if( (pegaNome(minhaRede,nome) == RED_CondRetPerfilIncorreto) ||
        (pegaIdade(idade) == RED_CondRetPerfilIncorreto)||
        (pegaGenero(genero) == RED_CondRetPerfilIncorreto))
    {
        return  RED_CondRetPerfilIncorreto;
    }/* if */

    printf ("\tVoce digitou: Nome:%s \n\tidade: %d\n\tsexo: %c \n", nome,*idade,*genero);

    return RED_CondRetOK;
}

RED_tpCondRet pegaNome(USU_tppUsuario minhaRede,char * nome)
{
    char * nomeCorrente;
    int contador = 0;
    int idCorrente;
    int idRecebido;
    if (minhaRede == NULL)
    {
        return RED_CondRetRedeNula;
    }/* if */
    
    nomeCorrente = USU_PegaNomeUsuarioCorrente(minhaRede); //guardando o usuario inicial 
    idCorrente = USU_IrUsuario(minhaRede,nomeCorrente); //guardando id inicial
    printf ("Digite o nome do usuario(max 50 caracteres): ");
    scanf(" %50[^\n]",nome);
    fflush(stdin);
    /*** NOME ***/
    while ((idRecebido = USU_IrUsuario(minhaRede,nome)) != -1)
    {
        if(idRecebido == idCorrente)
        {
            return RED_CondRetOK;
        }
        printf ("Nome '%s' já utilizado digite outro (max 50 caracteres): ",nome);
        scanf(" %50[^\n]",nome);
        fflush(stdin);
        if(contador > 2)
        {
            USU_IrUsuario(minhaRede,nomeCorrente);
            return RED_CondRetPerfilIncorreto;
        }/* if */
        contador++;
    }/* while */
    if(contador != 0)
    {
        USU_IrUsuario(minhaRede,nomeCorrente);
    }

    return RED_CondRetOK;
}
RED_tpCondRet pegaIdade(int * idade)
{
    int contador = 0;
    /*** IDADE ***/
    printf ("Digite sua idade: ");
    scanf(" %d",idade);
    fflush(stdin);
    while(verificaIdade(*idade) == RED_CondRetPerfilIncorreto)
    {
        if(++contador > 2)
        {
            return RED_CondRetPerfilIncorreto;
        }/* if */
        printf("idade invalida, por favor digite valores entre 1 e 199\n");
        scanf(" %d",idade);
        fflush(stdin);        
    }/* while */
    return RED_CondRetOK;
}
RED_tpCondRet pegaGenero(char * genero)
{
     int contador = 0;
    /*** GENERO ***/
    printf ("Digite seu genero('M','F' ou 'O' para outros ): ");
    scanf(" %c",genero);
    fflush(stdin);
    *genero =(char) toupper(*genero);

    while(verificaGenero(*genero) == RED_CondRetPerfilIncorreto)
    {
        if(++contador > 2)
        {
            return RED_CondRetPerfilIncorreto;
        }/* if */
        printf("Genero invalido, por favor digite seu genero('M','F' ou 'O' para outros ): \n");
        scanf(" %c",genero);
        fflush(stdin);
        *genero =(char) toupper(*genero);        
    }/* while */

    return RED_CondRetOK;
}

void mostrarAmigos(USU_tppUsuario minhaRede)
{
    char buffer[800];
    if(USU_PegaDadosAmigosCorrente(minhaRede,buffer) == USU_CondRetOK)
    {
        printf("\nSEUS AMIGOS:\n%s\n",buffer);
    }
    
}

void msgPublica(USU_tppUsuario minhaRede,char* nome)
{
    char mensagem[145];
    if ( nome == NULL )
    {
        printf("Precisa estar logado para mandar msg\n");
        return;
    }/* if */
    
    if (minhaRede != NULL)
    {
        printf("digite sua msg ate 144 caracteres: \n");
        scanf(" %144[^\n]",mensagem);
        fflush(stdin);
        USU_enviaMsgPublica(minhaRede,mensagem,nome);
    }

}

void pegaMsgPublica(USU_tppUsuario minhaRede,char* nome)
{
    char * msg;
    if(minhaRede == NULL)
    {
        return;
    }
    if (nome == NULL)
    {
        printf("Voce deve estar logado para ver msgs\n");
        return;
    }

    msg = USU_pegaMsgPublico(minhaRede);
    printf("mensagens:\n%s",msg);
    free(msg);
}