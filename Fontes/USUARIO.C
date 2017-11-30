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



/***********************************************************************
*  $TC Tipo de dados: Int id Usuario
*       variável que vai gerar os ids de perfil de cada usuário
*
***********************************************************************/
static int IdSequencial = 0; //sequencia para gerar o id dos usuários
static int NextPos = 0; // proxima posição para guardar o ponteiro de um usuario no vetor
static GRA_tppGrafo pGrafo = NULL; // ponteiro para o tipo grafo
static tpPerfilUsuario * meus_usuarios[MAX_USERS]; // vetor para guardar meus usuários criados


/***** Protótipos das funções encapuladas no módulo *****/


static void CopiaNome(char* destino, char * origem);

static void GetNewIdUsuario(int* Id_destino);

static void GuardaNoVetor (tpPerfilUsuario** vetor , tpPerfilUsuario * perfil);

static void DeletaDoVetor (tpPerfilUsuario** vetor , tpPerfilUsuario * perfil);

static void excluirUsuario (void* usuario);

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: USU  &Inicializar Modulo
*  ****/

USU_tpCondRet USU_InicializarModulo( )
{
        if( pGrafo != NULL )
        {
                GRA_DestruirGrafo(pGrafo);
        }/*If*/

        pGrafo = GRA_CriarGrafo ( excluirUsuario );
        IdSequencial = 0;
        NextPos = 0;
}

/* Fim função: USU  &Inicializar Modulo */

/***************************************************************************
*
*  Função: USU  &Cria Usuario
*  ****/

USU_tpCondRet USU_CriaUsuario(char * nome , int idade , char genero )
{
      tpPerfilUsuario * perfil = NULL;
      USU_tpCondRet retorno;
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

      GetNewIdUsuario( perfil->idUsuario ); //atribuindo o Id

      retorno = USU_AdicionaUsuario(perfil);
      switch ( retorno )
        {
                case GRA_CondRetFaltouMemoria:
                        return USU_CondRetFaltouMemoria;
                        break;
                case GRA_CondRetGrafoNulo:
                        return USU_CondRetNaoInicializado;
                        break;
                default:    
                        GuardaNoVetor(meus_usuarios,perfil);
                        return USU_CondRetOK;
        }
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
*  Função: USU  &Total Usuarios
*  em caso de erro GRA_QntVertices retorna -1
*  ****/

 int USU_TotalUsuarios()
 {
         return GRA_QntVertices(pGrafo);
 }

/* Fim função: USU  &Total Usuarios */




/***************************************************************************
*
*  Função: USU  &USU_AdicionaUsuario
*  ****/

USU_tpCondRet USU_AdicionaUsuario(USU_tppUsuario usuario)
{
        #ifdef _DEBUG
		 assert( usuario != NULL );
                 assert(pGrafo != NULL );
	#endif
        LIS_tpCondRet retorno;
        retorno = GRA_InserirVertice( pGrafo,usuario );
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
/* Fim função: USU  &Copia Nome */
/***************************************************************************
*
*  Função: USU  &GetNewIdUsuario
*       Preenche o id do usuário(recebido como parametro) com o próximo
*       valor da variável global IdSequencial. Em caso de erro aborta.
*  ****/
static void GetNewIdUsuario(int* id_destino)
{
        if( id_destino == NULL )
        {
                printf("Funcao IdUsuario: parametro recebido == NULL abortando\n");
                exit(-1);
        }
        //incremento a variavel global e atribuo a variavel recebida
        id_destino = ++IdSequencial; 
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



/***************************************************************************
*
*  Função: USU  &GuardaNoVetor
*       Guarda o perfil no vetor e atualiza a proxima posição disponivel
*  ****/
static void GuardaNoVetor ( tpPerfilUsuario** vetor , tpPerfilUsuario * perfil)
{
        #ifdef _DEBUG
                assert( vetor[NextPos] == NULL );
        #endif
        vetor[NextPos] = perfil;
        NextPos++;

}

/* Fim função: USU  &GuardaNoVetor */

static void DeletaDoVetor (tpPerfilUsuario** vetor , tpPerfilUsuario * perfil)
{
        int i = 0;

        while(i<MAX_USERS)
        {
                if(vetor[i] == perfil)
                {
                        NextPos--;
                        vetor[i] = vetor[NextPos];
                        vetor[NextPos] = NULL;
                        return;
                }
                i++;
        }/* while */
}