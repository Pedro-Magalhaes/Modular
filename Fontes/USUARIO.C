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
*
***************************************************************************/
#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   <ctype.h>

#define USUARIO_OWN
#include "USUARIO.h"
#undef USUARIO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: USU Perfil Usuario
*
*
***********************************************************************/

   typedef struct tagPerfilUsuario { //TODO: juntei perfil com usuario, alterar modelo fisico!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        int idUsuario;

        char * nomeUsuario ;
                /* String com até 50 caracteres contendo o nome de um usuário */
        char generoUsuario;
                /* Char contendo o genero do usuário ('F','M' ou 'O' ) */

        int idadeUsuario ;
                /* Inteiro com a idade de um usuário */

   } tpPerfilUsuario ;



/***********************************************************************
*  $TC Tipo de dados: Int id Usuario
*       variável que vai gerar os ids de perfil de cada usuário
*
***********************************************************************/
static int IdSequencial = 0;

/***** Protótipos das funções encapuladas no módulo *****/


static void CopiaNome(char* destino, char * origem);

static void GetIdUsuario(int* Id_destino);

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: USU  &Cria Usuario
*  ****/

USU_tpCondRet USU_CriaUsuario(char * nome , int idade , char genero )
{
      tpPerfilUsuario * perfil = NULL;
      perfil =(tpPerfilUsuario*) malloc(sizeof(tpPerfilUsuario));
      if (perfil == NULL)
      {//erro de memoria
        return USU_CondRetFaltouMemoria;
      }/* if */

      perfil ->nomeUsuario = (char*) malloc(sizeof(char)*51);
      
      if (perfil->nomeUsuario == NULL)
      {//erro de memoria
        return USU_CondRetFaltouMemoria;
      }/* if */
      
      CopiaNome(perfil->nomeUsuario, nome); //atribuindo o nome

      if(idade > 0 && idade < 200)
      {
        perfil->idadeUsuario = idade; //atribuindo idade
      }/*if*/
      else
      {
        return USU_CondRetPerfilIncorreto;
      }/* else */
      
      if (genero == 'M' ||genero == 'F' || genero == 'O' || 
          genero == 'm' || genero == 'f'|| genero == 'o')
      {
        perfil->generoUsuario = toupper(genero); //atribuindo genero
      }/* if */
      else
      {
        return USU_CondRetPerfilIncorreto;
      }/* else */

      GetIdUsuario( perfil->idUsuario ); //atribuindo o Id
      return USU_CondRetOK;
}

/* Fim função: USU  &Cria Usuario */

/***************************************************************************
*
*  Função: USU  &Cria Usuario
*  ****/

USU_tpCondRet USU_AdicionaAmigo( int id_usuario ) ;


/* Fim função: USU  &Cria Usuario */

/***************************************************************************
*
*  Função: USU  &Cria Usuario
*  ****/

 USU_tpCondRet USU_EditarPerfil() ;

/* Fim função: USU  &Cria Usuario */




/***************************************************************************
*
*  Função: USU  &Cria Usuario
*  ****/

USU_tpCondRet USU_AdicionaUsuario() ;     


/* Fim função: USU  &Cria Usuario */




/****** Fim funções exportadas pelo modulo USU ******/

/*****  Código das funções encapsuladas no módulo  *****/

/***************************************************************************
*
*  Função: USU  &Copia Nome
*       Copia o nome do usuario com até 50 caracteres, qualquer valor maior é 
        ignorado.
*  ****/
static void CopiaNome(char* destino, char * origem)
{
        int i;
        if (destino == NULL || origem == NULL)
        {
                printf("Função copia nome: erro com os parametros de entrada");
                return; 
        }/*if*/

        for (i=0;i<50;i++)
        {
                destino[i] = origem[i];
                if(destino[i]=='\0')
                {
                        return;
                }
        }/*for*/
        destino[i] = 51;
}

/***************************************************************************
*
*  Função: USU  &Id Usuario
*       Preenche o id do usuário(recebido como parametro) com o próximo
*       valor da variável global IdSequencial. Em caso de erro aborta.
*  ****/
static void GetIdUsuario(int* id_destino)
{
        if( id_destino == NULL )
        {
                printf("Funcao IdUsuario: parametro recebido == NULL abortando\n");
                exit(-1);
        }
        //incremento a variavel global e atribuo a variavel recebida
        id_destino = ++IdSequencial; 
}