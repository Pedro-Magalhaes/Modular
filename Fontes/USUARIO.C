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

#define USUARIO_OWN
#include "USUARIO.h"
#undef USUARIO_OWN

#define MAX_USERS 10

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


typedef struct USU_tagUsuario {

	GRA_tppGrafo pGrafo;
        /* Ponteiro pro grafo de usuarios */

        int IdSequencial; 
        /* Inteiro sequencial para gerar o id dos usuários */

        #ifdef _DEBUG
                tpPerfilUsuario * meus_usuarios[MAX_USERS];
                /* vetor para guardar meus usuários criados (redundancia) */
                int NextPos;
                /* proxima posição para guardar o ponteiro de um usuario no vetor */
        #endif

} GRA_tpUsuario;


/***** Protótipos das funções encapuladas no módulo *****/

USU_tpCondRet USU_AdicionaUsuario(USU_tppUsuario pUsuario, tpPerfilUsuario* perfil);

static void CopiaNome(char* destino, char * origem);

static void GetNewIdUsuario(USU_tppUsuario pUsuario,int* Id_destino);

static void excluirUsuario (void* usuario);

#ifdef _DEBUG

static void GuardaNoVetor (USU_tppUsuario pUsuario, tpPerfilUsuario * perfil);

static void DeletaDoVetor (USU_tppUsuario pUsuario,tpPerfilUsuario** vetor , tpPerfilUsuario * perfil);

#endif

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: USU  &Inicializar Modulo
*  ****/

USU_tppUsuario USU_InicializarModulo( )
{
        GRA_tpUsuario * pUsuario = NULL;
        pUsuario = (GRA_tpUsuario *) malloc( sizeof (GRA_tpUsuario) );
        if (pUsuario == NULL)
        {
                return pUsuario;
        } /* if */
        pUsuario->pGrafo = GRA_CriarGrafo ( excluirUsuario );
        pUsuario->IdSequencial = 0;
        #ifdef _DEBUG
                pUsuario->NextPos = 0;
        #endif
        return pUsuario;
}

/* Fim função: USU  &Inicializar Modulo */

/***************************************************************************
*
*  Função: USU  &Cria Usuario
*  ****/

USU_tpCondRet USU_CriaUsuario(USU_tppUsuario pUsuario, char * nome , int idade , char genero )
{
      tpPerfilUsuario * perfil = NULL;
      USU_tpCondRet retorno;
      perfil =(tpPerfilUsuario*) malloc(sizeof(tpPerfilUsuario));

      if (perfil == NULL)
      {//erro de memoria
        return USU_CondRetFaltouMemoria;
      } /* if */

      perfil ->nomeUsuario = (char*) malloc(sizeof(char)*51);
      
      if (perfil->nomeUsuario == NULL)
      {//erro de memoria
        return USU_CondRetFaltouMemoria;
      } /* if */
      
      CopiaNome(perfil->nomeUsuario, nome); //atribuindo o nome

      if(idade > 0 && idade < 200)
      {
        perfil->idadeUsuario = idade; //atribuindo idade
      } /* if */
      else
      {
        return USU_CondRetPerfilIncorreto;
      } /* else */
      
      if (genero == 'M' ||genero == 'F' || genero == 'O' || 
          genero == 'm' || genero == 'f'|| genero == 'o')
      {
        perfil->generoUsuario = (char)toupper(genero); //atribuindo genero
      } /* if */
      else
      {
        return USU_CondRetPerfilIncorreto;
      } /* else */

      GetNewIdUsuario( pUsuario, &perfil->idUsuario ); //atribuindo o Id

      retorno = USU_AdicionaUsuario(pUsuario,perfil);
      #ifdef _DEBUG
      if(retorno == USU_CondRetOK)
      {
        GuardaNoVetor(pUsuario,perfil);
        return USU_CondRetOK;
      } /* if */
      #endif
      return retorno;
}

/* Fim função: USU  &Cria Usuario */

/***************************************************************************
*
*  Função: USU  &Cria Usuario
*  ****/

USU_tpCondRet USU_AdicionaAmigo( USU_tppUsuario pUsuario, int id_usuario ) ;


/* Fim função: USU  &Cria Usuario */

/***************************************************************************
*
*  Função: USU  &Cria Usuario
*  ****/

 USU_tpCondRet USU_EditarPerfil() ;

/* Fim função: USU  &Cria Usuario */


/***************************************************************************
*
*  Função: USU  &Total Usuarios
*  em caso de erro GRA_QntVertices retorna -1
*  ****/

 int USU_TotalUsuarios(USU_tppUsuario pUsuario)
 {
         return GRA_QntVertices( pUsuario->pGrafo );
 }

/* Fim função: USU  &Total Usuarios */


/***************************************************************************
*
*  Função: USU  &USU_DestruirUsuarios
*  ****/

void USU_DestruirUsuarios (USU_tppUsuario pUsuario)
{
        #ifdef _DEBUG //limpar usuarios da redundancia
                int i;
                for(i=0;i<MAX_USERS;i++)
                {
                        pUsuario->meus_usuarios[i]=NULL;
                }
                pUsuario->NextPos = 0;
        #endif
        
        GRA_DestruirGrafo(pUsuario->pGrafo);
        pUsuario->pGrafo = NULL;                
        pUsuario->IdSequencial = 0;     
}

/* Fim função: USU  &USU_DestruirUsuarios */

/****** Fim funções exportadas pelo modulo USU ******/

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: USU  &Adicionar Usúario
*
*  $ED Descrição da função
*     Adiciona o usuario no grafo
*
*  $EP Parâmetros
*     USU_tppUsuario pUsuario  - Ponteiro para a instancia do modulo usuario
*     tpPerfilUsuario* perfil  - Ponteiro para um perfil de usuario que vai ser adicionado  
*  $FV Valor retornado
*     Se executou corretamente retorna USU_CondRetOK.
*     Se ocorreu algum erro de falta de memória retorna USU_CondRetFaltouMemoria,
*     Se o grafo da instancia do módulo usuario nao tiver sido inicializado retorna_
*                                                       USU_CondRetNaoInicializado
*
***********************************************************************/   

USU_tpCondRet USU_AdicionaUsuario(USU_tppUsuario pUsuario, tpPerfilUsuario* perfil)
{
        #ifdef _DEBUG
		 assert( pUsuario != NULL );
                 assert(pUsuario->pGrafo != NULL );
	#endif
        LIS_tpCondRet retorno;
        retorno = GRA_InserirVertice( pUsuario->pGrafo , perfil );
        switch ( retorno )
        {
                case GRA_CondRetFaltouMemoria:
                        return USU_CondRetFaltouMemoria;
                        break;
                case GRA_CondRetGrafoNulo:
                        return USU_CondRetNaoInicializado;
                        break;
                default:                        
                        return USU_CondRetOK;
        }

}  


/* Fim função: USU  &USU_AdicionaUsuario */

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
/* Fim função: USU  &Copia Nome */
/***************************************************************************
*
*  Função: USU  &GetNewIdUsuario
*       Preenche o id do usuário(recebido como parametro) com o próximo
*       valor da variável global IdSequencial. Em caso de erro aborta.
*  ****/
static void GetNewIdUsuario(USU_tppUsuario pUsuario, int* id_destino)
{
        if( id_destino == NULL )
        {
                printf("Funcao IdUsuario: parametro recebido == NULL abortando\n");
                exit(-1);
        }
        //incremento a variavel global e atribuo a variavel recebida
        *id_destino = ++pUsuario->IdSequencial; 
}
/* Fim função: USU  &GetNewIdUsuario */

/***************************************************************************
*
*  Função: USU  &excluir Usuario
*       Faz a exclusão dos dados guardados no perfil
*  ****/
static void excluirUsuario (void* dado)
{
        tpPerfilUsuario * perfil = (tpPerfilUsuario*) dado;
        free(perfil->nomeUsuario);
}

/* Fim função: USU  &excluirUsuario */


/*****  Código das funções usadas apenas em DEBUG  *****/
#ifdef _DEBUG
        /***************************************************************************
        *
        *  Função: USU  &GuardaNoVetor
        *       Guarda o perfil no vetor e atualiza a proxima posição disponivel
        *  ****/
        static void GuardaNoVetor ( USU_tppUsuario pUsuario,  tpPerfilUsuario * perfil)
        {
               
                assert( pUsuario->meus_usuarios[pUsuario->NextPos] == NULL );
                
                pUsuario->meus_usuarios[pUsuario->NextPos] = perfil;
                pUsuario->NextPos++;

        }

        /* Fim função: USU  &GuardaNoVetor */

        static void DeletaDoVetor (USU_tppUsuario pUsuario, tpPerfilUsuario** vetor , tpPerfilUsuario * perfil)
        {
                int i = 0;

                while(i<MAX_USERS)
                {
                        if(vetor[i] == perfil)
                        {
                                pUsuario->NextPos--;
                                vetor[i] = vetor[pUsuario->NextPos];
                                vetor[pUsuario->NextPos] = NULL;
                                return;
                        }
                        i++;
                }/* while */
        }
#endif