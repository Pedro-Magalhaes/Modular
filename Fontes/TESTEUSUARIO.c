/***************************************************************************
*  $MCI Módulo de implementação: TUSU Teste usuario da rede
*
*  Arquivo gerado:              TESTEUSUARIO.c
*  Letras identificadoras:      TUSU
*
*  Nome da base de software:    iMigo - a sua nova rede de relacionamentos
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301/ iMigo - a sua nova rede de relacionamentos
*  Gestor:  LES/DI/PUC-Rio
*  Autores: pfs, hfac , yan
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*
*     1       pfs   29/11/2017 início desenvolvimento
*	  2		  yan	02/12/2017 continuação do desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "USUARIO.h"


static const char INICIAR_MODULO_CMD       [ ] = "=iniciarmodulo"   ;
static const char CRIAR_USUARIO_CMD        [ ] = "=criarusuario"   ;
static const char ADICIONAR_AMIGO_CMD      [ ] = "=adicionaramigo"   ;
static const char EDITARPERFIL_CMD		   [ ] = "=editarperfil"   ;
static const char DELETAR_USUARIO_CMD      [ ] = "=deletarusuario"   ;
static const char DESTRUIR_USUARIOS_CMD    [ ] = "=destruirusuarios"   ;
static const char TOTAL_USUARIOS_CMD       [ ] = "=totalusuarios"   ;




#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_USUARIO   10
#define DIM_VALOR     100

USU_tppUsuario   vtusuarios[ DIM_VT_USUARIO ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxusuario( int inxusuario , int Modo ) ;

/*****  Definição da struct de teste  *****/

   typedef struct no_teste 
   {
	   char nome[31];
	   char data_nasc[11];
	   char email[51];
	   char cidade[31];
   } no_teste;

	no_teste vtstructs [DIM_VT_USUARIO];
/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TUSU &Testar usuario
*
*  $ED Descrição da função
*     Podem ser criados até 10 usuarios, identificados pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =iniciarmodulo                inxusuario     
*     =criarusuario                 inxusuario   string1   int1   string2     CondRetEsp
*     =adicionaramigo               inxusuario   int1     CondRetEsp
*     =editarperfil                 inxusuario   XXXX     CondRetEsp
*     =deletarusuario               int1     CondRetEsp
*     =destruirusuarios             inxusuario     CondRetEsp
*     =totalusuarios				ValEsp
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxusuario  = -1 ,
          numLidos   = -1 ,
          ValEsp = -1 ,
			inxstruct =-1;

      TST_tpCondRet CondRet ;

      char   StringDado1[  DIM_VALOR ] ;
	  char   StringDado2[  DIM_VALOR ] ;
	  char   StringDado3[  DIM_VALOR ] ;
	  char   StringDado4[  DIM_VALOR ] ;
      no_teste * pDado ;   

      int i ;

      

      StringDado1[ 0 ] = 0 ;
	  StringDado2[ 0 ] = 0 ;
	  StringDado3[ 0 ] = 0 ;
	  StringDado4[ 0 ] = 0 ;

      /* Efetuar reset de teste de usuario */

         if ( strcmp( ComandoTeste , RESET_usuario_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_usuario ; i++ )
            {
               vtusuarios[ i ] = NULL ;
			   
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de usuario */

      /* Testar Criarusuario */

         else if ( strcmp( ComandoTeste , CRIAR_usuario_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxusuario ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxusuario( inxusuario , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtusuarios[ inxusuario ] =
                 USU_Criarusuario( DestruirValor ) ;

            return TST_CompararPonteiroNulo( 1 , vtusuarios[ inxusuario ] ,
               "Erro em ponteiro de novo usuario."  ) ;

         } /* fim ativa: Testar Criar usuario */

      /* Testar Esvaziar usuario */

         else if ( strcmp( ComandoTeste , ESVAZIAR_usuario_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxusuario ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            USU_Esvaziarusuario( vtusuarios[ inxusuario ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar usuario */

      /* Testar Destruir usuario */

         else if ( strcmp( ComandoTeste , DESTRUIR_usuario_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxusuario ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            USU_Destruirusuario( vtusuarios[ inxusuario ] ) ;
            vtusuarios[ inxusuario ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir usuario */

      /* Testar inserir vertice */

         else if ( strcmp( ComandoTeste , INS_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iissssi" ,
                       &inxusuario , &inxstruct ,StringDado1, StringDado2, StringDado3, StringDado4 , &ValEsp ) ;

            if ( ( numLidos != 7 ) //6
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			
			strcpy( vtstructs[ inxstruct ].nome , StringDado1 ) ;
			strcpy( vtstructs[ inxstruct ].data_nasc , StringDado2 ) ;
			strcpy( vtstructs[ inxstruct ].email , StringDado3 ) ;
			strcpy( vtstructs[ inxstruct ].cidade , StringDado4 ) ;

            pDado =  &vtstructs[ inxstruct ];  
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

			


            CondRet = (TST_tpCondRet) USU_InserirVertice( vtusuarios[ inxusuario ] , pDado ) ;

            if ( CondRet != USU_CondRetOK )
            {
               //free( pDado ) ; //não foi alocado dinamicamente
            } /* if */

            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao inserir vertice.") ;

         } /* fim ativa: Testar inserir vertice */

      /* Testar criar aresta */

         else if ( strcmp( ComandoTeste , CRIAR_ARESTA_CMD ) == 0 )
         {

             numLidos = LER_LerParametros( "iii" ,
                       &inxusuario , &inxstruct , &ValEsp ) ;

            if ( ( numLidos != 3 ) //6
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado =  &vtstructs[inxstruct]; //( no_teste * ) malloc( sizeof(no_teste) ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            CondRet = (TST_tpCondRet) USU_CriarAresta( vtusuarios[ inxusuario ] , pDado ) ;

            if ( CondRet != USU_CondRetOK )
            {
               //free( pDado ) ;//não foi alocado dinamicamente
            } /* if */

            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao criar aresta."                   ) ;

         } /* fim ativa: Testar criar aresta */

      /* Testar excluir vertice */

         else if ( strcmp( ComandoTeste , EXC_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxusuario , &ValEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( ValEsp ,
                      USU_ExcluirVertice( vtusuarios[ inxusuario ] ) ,
                     "Condição de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir vertice */

      /* Testar obter valor do vertice corrente */

         else if ( strcmp( ComandoTeste , OBTER_CORRENTE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issssi" ,
                       &inxusuario, StringDado1, StringDado2, StringDado3, StringDado4, &ValEsp ) ;

            if ( ( numLidos != 6 )
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( no_teste * ) USU_ObterValorCorrente( vtusuarios[ inxusuario ] ) ;

            if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , pDado ,
                         "Valor não deveria existir." ) ;
            } /* if */

            if ( pDado == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pDado ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

			return (TST_tpCondRet) (TST_CompararString( StringDado1 , pDado->nome ,
                         "Valor do elemento errado." ) && TST_CompararString( StringDado2 , pDado->data_nasc ,
                         "Valor do elemento errado." ) && TST_CompararString( StringDado3 , pDado->email ,
                         "Valor do elemento errado." ) && TST_CompararString( StringDado4 , pDado->cidade ,
                         "Valor do elemento errado." )) ;

         } /* fim ativa: Testar obter valor do vertice corrente */

      /* Testar excluir aresta entre o corrente e o pvalor recebido */

         else if ( strcmp( ComandoTeste , EXC_ARESTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxusuario, &inxstruct, &ValEsp ) ; //str1234

            if ( ( numLidos != 3 ) //6
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			 pDado = &vtstructs[inxstruct];//( no_teste * ) malloc( sizeof(no_teste) ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            CondRet = (TST_tpCondRet) USU_ExcluirAresta( vtusuarios[ inxusuario ] , pDado ) ;

            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao excluir aresta."                   ) ;

         } /* fim ativa: Testar excluir aresta */

      /* USU  &Ir para o vertice com o indice passado */

         else if ( strcmp( ComandoTeste , IR_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxusuario, &inxstruct, &ValEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			 pDado = &vtstructs[ inxstruct ];//( no_teste * ) malloc( sizeof(no_teste) ) ;
			 
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */


            CondRet = (TST_tpCondRet) USU_IrVertice(vtusuarios[inxusuario], pDado);

           return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao ir para vertice."                   ) ;

         } /* fim ativa: USU  &Ir para o vertice */

		 /*USU &Ver quantidade de vertices*/

		 else if ( strcmp( ComandoTeste , QNT_VERTICE_CMD ) == 0 )
		 {
			 numLidos = LER_LerParametros( "ii" , &inxusuario, &ValEsp);

			 if ( ( numLidos != 2 )
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			 return TST_CompararInt( ValEsp , USU_QntVertices(vtusuarios[inxusuario]) ,
                     "Quantidade de vertices errada."                   ) ;

		 }/* fim ativa: USU &Ver quantidade de vertices */

		 /*USU &Ver quantidade de arestas do vertice corrente*/

		  else if ( strcmp( ComandoTeste , QNT_ARESTA_CMD ) == 0 )
		 {
			 numLidos = LER_LerParametros( "ii" , &inxusuario, &ValEsp);

			 if ( ( numLidos != 2 )
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			 return TST_CompararInt( ValEsp , USU_QntArestas(vtusuarios[inxusuario]) ,
                     "Quantidade de arestas errada."                   ) ;

		 }/* fim ativa: USU &Ver quantidade de arestas do vertice corrente */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TUSU &Testar usuario */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TUSU -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      //free( pValor ) ; Não foi alocado dinamicamente, para testes com memoria dinamica descomentar

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TUSU -Validar indice do usuario
*
***********************************************************************/

   int ValidarInxusuario( int inxusuario , int Modo )
   {

      if ( ( inxusuario <  0 )
        || ( inxusuario >= DIM_VT_usuario ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtusuarios[ inxusuario ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtusuarios[ inxusuario ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TUSU -Validar indice do usuario */


/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/