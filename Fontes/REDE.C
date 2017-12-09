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
RED_tpCondRet verificaGenero (char genero);
RED_tpCondRet verificaIdade (int idade);
RED_tpCondRet editarPerfil(USU_tppUsuario minhaRede,char* nome);

void loopPerfil (USU_tppUsuario minhaRede,char* nome);
void loopMensgens (USU_tppUsuario minhaRede,char* nome);
void criarUsuario (USU_tppUsuario minhaRede);
void removerUsuario (USU_tppUsuario minhaRede);
void adicionarAmigo (USU_tppUsuario minhaRede);
void IrUsuario (USU_tppUsuario minhaRede);
void mostrarAmigos(USU_tppUsuario minhaRede);
void msgPublica(USU_tppUsuario minhaRede,char* nome);
void msgPrivada(USU_tppUsuario minhaRede,char* nome);
void pegaMsgPublica(USU_tppUsuario minhaRede,char* nome);
void pegaMsgPrivada(USU_tppUsuario minhaRede,char* nome);
void preencheMsg(char * msg,char * nome);
void enviaMsgPrivada(USU_tppUsuario minhaRede,char* nome);
void mostraUsuarios(USU_tppUsuario minhaRede);


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
        printf ("Digite o que deseja fazer:\n\t0- Finalizar execucao\n\t1- Criar Usuario\n\t2- Remover Usuario atual\n\t3- Adicionar Amigo\n\t4- Meu perfil\n\t5- Assumir outro usuario\n\t6- Mostrar Amigos\n\t7- Mensagens\n\t8- Ver todos usuarios\n");
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
                loopPerfil(minhaRede,nome);
            break;
            case 5:
                IrUsuario(minhaRede);
                break;
            case 6:
                mostrarAmigos(minhaRede);
                break;
            case 7:
                loopMensgens(minhaRede,nome);                
                break;
            case 8:
                mostraUsuarios(minhaRede);
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
    int totalUsuarios;
    totalUsuarios = USU_TotalUsuarios(minhaRede);
    if(totalUsuarios > 10)
    {
        printf("Numero Maximo de usuarios atingido. (10) delete alguem para tentar novamente\n");
        return;
    }
    RED_retorno = pegaAtributosUsuario(minhaRede,nome, &idade , &genero);
    if(RED_retorno == RED_CondRetOK)
    {        
        USU_retorno = USU_CriaUsuario(minhaRede,nome,idade,genero);
        if(USU_retorno == USU_CondRetOK)
        {
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
        }/* if */
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
    USU_tpCondRet retorno;
    if(minhaRede == NULL)
    {
        printf("Rede não inicializada\n");
        return;
    }/* if */
    nomeUsuarioCorrente = USU_PegaNomeUsuarioCorrente(minhaRede);
    if(nomeUsuarioCorrente == NULL)
    {
        usuarios = USU_TotalUsuarios(minhaRede);
        if(usuarios < 0)
        {
            printf("Rede não inicializada\n");
            return;
        }/* if */
        if (usuarios == 0)
        {
            printf("Ninguem foi adicionado ainda, tente adicionar usuarios primeiro\n");
            return;
        }/* if */
        printf("erro no usuario corrente dentro da funcao RED_adicionarAmigo,numero de usuarios: %d\n",usuarios);
        return;
    }/* if */
    printf("%s digite no nome do amigo a adicionar:\n",nomeUsuarioCorrente);
    scanf(" %49[^\n]",nome);
    retorno = USU_AdicionaAmigo(minhaRede,nome);
    if(  retorno == USU_CondRetOK)
    {
        printf("Usuario adicionado\n");
        return;
    }/* if */
    if( retorno == USU_CondRetPerfilIncorreto )
    {
        printf("Usuario ja esta na sua lista de amigos\n");
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
}/* if */

RED_tpCondRet verificaGenero (char genero)
{
    if(genero == 'M' || genero == 'F' || genero == 'O' )
    {
        return RED_CondRetOK;
    }/* if */
    return RED_CondRetPerfilIncorreto;
}/* if */

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
}/* if */

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
}/* if */

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
        }/* if */
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
    }/* if */

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
    char * nome;
    nome = USU_PegaNomeUsuarioCorrente(minhaRede);
    if(USU_PegaDadosAmigosCorrente(minhaRede,buffer) == USU_CondRetOK && nome != NULL)
    {
        printf("\nSEUS AMIGOS %s:\n%s\n",nome,buffer);
    }/* if */
    
}

void msgPublica(USU_tppUsuario minhaRede,char* nome)
{
    char mensagemFinal[152];
    if ( nome == NULL )
    {
        printf("Precisa estar logado para mandar msg\n");
        return;
    }/* if */
    
    if (minhaRede != NULL)
    {
        preencheMsg(mensagemFinal, nome);
        USU_enviaMsgPublica(minhaRede,mensagemFinal,nome);
    }/* if */

}

void msgPrivada(USU_tppUsuario minhaRede,char* nome)
{
    char mensagemFinal[152];
    char amigos[1000];
    char destinatario[50];

    if ( nome == NULL )
    {
        printf("Precisa estar logado para mandar msg\n");
        return;
    }/* if */
    
    if (minhaRede != NULL)
    {
        if(USU_PegaDadosAmigosCorrente(minhaRede,amigos) == USU_CondRetOK)
        {
            printf("Opcoes de Chat:\n%s\nDigite o nome do usuario desejado:\n",amigos);
        }/* if */
        else
        {
            printf("Nao ha chats privados, retornando:\n");
            return;
        }/* else */
        
        scanf(" %50[^\n]",destinatario);
        preencheMsg(mensagemFinal, nome);        
        if(USU_enviaMsgPrivada(minhaRede,mensagemFinal,nome,destinatario) != USU_CondRetOK)
        {
            printf("mensagem não enviada, o destinatario estava correto?");
        }/* if */
    }

}

void pegaMsgPublica(USU_tppUsuario minhaRede,char* nome)
{
    char * msg;
    if(minhaRede == NULL)
    {
        return;
    }/* if */
    if (nome == NULL)
    {
        printf("Voce deve estar logado para ver msgs\n");
        return;
    }/* if */

    msg = USU_pegaMsgPublico(minhaRede);
    printf("\tMensagens:\n%s",msg);
    free(msg);//msg é alocada dentro de outro modulo e é responsabilidade do usuario remover
}
void pegaMsgPrivada(USU_tppUsuario minhaRede,char* nome)
{
    char * msg;
    char amigos[1000];
    char destinatario[50];
    if(minhaRede == NULL)
    {
        return;
    }/* if */
    if (nome == NULL)
    {
        printf("Voce deve estar logado para ver msgs\n");
        return;
    }/* if */
    if(USU_PegaDadosAmigosCorrente(minhaRede,amigos) == USU_CondRetOK)
    {
        printf("Opcoes de Chat:\n%s\nDigite o nome do usuario desejado:\n",amigos);
    }/* if */
    else
    {
        printf("Nao ha chats privados, retornando:\n");
        return;
    }/*else */

    scanf(" %50[^\n]",destinatario);
    
    msg = USU_pegaMsgPrivado(minhaRede,destinatario);
    printf("\tMensagens:\n%s",msg);
    free(msg);//msg é alocada dentro de outro modulo e é responsabilidade do usuario remover
}
void preencheMsg(char * msg,char * nome)
{
    char mensagem[100];
    printf("digite sua msg ate 100 caracteres: \n");
    scanf(" %100[^\n]",mensagem);
    fflush(stdin);
    msg[0]='\0';
    strcat_s(msg,150,nome);
    strcat_s(msg,150,": ");
    strcat_s(msg,150,mensagem);
}


void loopPerfil (USU_tppUsuario minhaRede,char* nome)
{
    int opcao;
    char perfil[100];
    if(nome == NULL)
    {
        printf("Nao ha perfil, tente adicionar um usuario.\n");
        return;
    }/* if */
    printf("Digite o que deseja fazer:\n\t0- Voltar\n\t1- Editar Perfil\n\t2 -Ver perfil\n");    
    scanf("%d",&opcao);
    do
    {
        fflush(stdin);
        if(opcao == 1)
        {
            editarPerfil(minhaRede,nome);
        }/* if */
        else if (opcao == 2)
        {
            USU_PegaDadosUsuarioCorrente(minhaRede,perfil);
            printf("Seu Perfil:\n%s",perfil);
        }/* elseif */
        else
        {
            return;
        }/* if */
        printf("Digite o que deseja fazer:\n\t0- Voltar\n\t1- Editar Perfil\n\t2 -Ver perfil\n"); 
    }while(scanf("%d",&opcao)==1);
    fflush(stdin);
    
}

void loopMensgens (USU_tppUsuario minhaRede,char* nome)
{
    int opcao;
    if(nome == NULL)
    {
        printf("Nao ha usuario, tente adicionar um.\n");
        return;
    }/* if */
    printf("Digite o que deseja fazer:\n\t0- Voltar\n\t1- Enviar msg publica\n\t2 -Ver msgs Publicas\n\t3- enviar msg privada\n\t4- Ver msg privada\n");
    scanf("%d",&opcao);
    do
    {
        fflush(stdin);
        switch (opcao)
        {
            case 0:
                return;
            case 1:
                msgPublica(minhaRede,nome);
                break;
            case 2:
                pegaMsgPublica(minhaRede,nome);
                break;
            case 3:
                msgPrivada(minhaRede,nome);
                break;  
            case 4:
                pegaMsgPrivada(minhaRede,nome);
                break;      
            default:
                break;
        }/* switch */
        
        printf("Digite o que deseja fazer:\n\t0- Voltar\n\t1- Enviar msg publica\n\t2 -Ver msgs Publicas\n\t3- enviar msg privada\n\t4- Ver msg privada\n");
    }while(scanf("%d",&opcao)==1);
}

void mostraUsuarios(USU_tppUsuario minhaRede)
{
    char minhaString[1000];
    int numeroUsuarios;
    if (minhaRede == NULL)
    {
        return;
    }/* if */
    numeroUsuarios = USU_TotalUsuarios(minhaRede);
    if(numeroUsuarios == -1)
    {
        printf("Funcao REDE_mostraUsuario. Erro ao tentar pegar numero de usuarios, rede foi inicializada?\n");
    }/* if */
    if(USU_PegaDadosTodos(minhaRede,minhaString) == USU_CondRetOK)
    {
        printf("\tUsuarios cadastrados na rede:\n%s\n",minhaString);
    }/* if */
}