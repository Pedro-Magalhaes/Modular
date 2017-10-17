/***************************************************************************
*  $MCI M�dulo de implementa��o: TLIS Teste grafo de s�mbolos
*
*  Arquivo gerado:              TESTEGRAFO.c.c
*  Letras identificadoras:      TGRA
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "GRAFO.h"


static const char RESET_GRAFO_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_GRAFO_CMD         [ ] = "=criargrafo"     ;
static const char DESTRUIR_GRAFO_CMD      [ ] = "=destruirgrafo"  ;
static const char ESVAZIAR_GRAFO_CMD      [ ] = "=esvaziargrafo"  ;
static const char INS_VERTICE_CMD         [ ] = "=insvertice"   ;
static const char EXC_VERTICE_CMD         [ ] = "=excvertice"    ;
static const char EXC_ARESTA_CMD          [ ] = "=excaresta" ;
static const char OBTER_CORRENTE_CMD      [ ] = "=obtervalorcorrente"    ;
static const char CRIAR_ARESTA_CMD        [ ] = "=criararesta"       ;
static const char IR_VERTICE_CMD          [ ] = "=irvertice"        ;
static const char QNT_VERTICE_CMD         [ ] = "=qntvertice"        ;
static const char QNT_ARESTA_CMD          [ ] = "=qntaresta"        ;



#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_GRAFO   10
#define DIM_VALOR     100

GRA_tppGrafo   vtgrafos[ DIM_VT_GRAFO ] ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxGrafo( int inxgrafo , int Modo ) ;

/*****  Defini��o da struct de teste  *****/

   typedef struct no_teste 
   {
	   char nome[31];
	   char data_nasc[11];
	   char email[51];
	   char cidade[31];
   } no_teste;

	no_teste vtstructs [DIM_VT_GRAFO];
/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS &Testar lista
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 listas, identificadas pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de mem�ria
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemantes                 inxLista  string  CondRetEsp
*     =inselemapos                  inxLista  string  CondRetEsp
*     =obtervalorelem               inxLista  string  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxgrafo  = -1 ,
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

      /* Efetuar reset de teste de grafo */

         if ( strcmp( ComandoTeste , RESET_GRAFO_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_GRAFO ; i++ )
            {
               vtgrafos[ i ] = NULL ;
			   
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de grafo */

      /* Testar CriarGrafo */

         else if ( strcmp( ComandoTeste , CRIAR_GRAFO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxgrafo ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxGrafo( inxgrafo , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtgrafos[ inxgrafo ] =
                 GRA_CriarGrafo( DestruirValor ) ;

            return TST_CompararPonteiroNulo( 1 , vtgrafos[ inxgrafo ] ,
               "Erro em ponteiro de novo grafo."  ) ;

         } /* fim ativa: Testar Criar grafo */

      /* Testar Esvaziar grafo */

         else if ( strcmp( ComandoTeste , ESVAZIAR_GRAFO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxgrafo ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            GRA_EsvaziarGrafo( vtgrafos[ inxgrafo ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar grafo */

      /* Testar Destruir grafo */

         else if ( strcmp( ComandoTeste , DESTRUIR_GRAFO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxgrafo ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            GRA_DestruirGrafo( vtgrafos[ inxgrafo ] ) ;
            vtgrafos[ inxgrafo ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir grafo */

      /* Testar inserir elemento */

         else if ( strcmp( ComandoTeste , INS_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iissssi" ,
                       &inxgrafo , &inxstruct ,StringDado1, StringDado2, StringDado3, StringDado4 , &ValEsp ) ;

            if ( ( numLidos != 7 ) //6
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )) )
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

			


            CondRet = (TST_tpCondRet) GRA_InserirVertice( vtgrafos[ inxgrafo ] , pDado ) ;

            if ( CondRet != GRA_CondRetOK )
            {
               //free( pDado ) ; //n�o foi alocado dinamicamente
            } /* if */

            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao inserir vertice.") ;

         } /* fim ativa: Testar inserir vertice */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , CRIAR_ARESTA_CMD ) == 0 )
         {

             numLidos = LER_LerParametros( "iii" ,
                       &inxgrafo , &inxstruct , &ValEsp ) ;

            if ( ( numLidos != 3 ) //6
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado =  &vtstructs[inxstruct]; //( no_teste * ) malloc( sizeof(no_teste) ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            CondRet = (TST_tpCondRet) GRA_CriarAresta( vtgrafos[ inxgrafo ] , pDado ) ;

            if ( CondRet != GRA_CondRetOK )
            {
               //free( pDado ) ;//n�o foi alocado dinamicamente
            } /* if */

            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao criar aresta."                   ) ;

         } /* fim ativa: Testar criar aresta */

      /* Testar excluir vertice */

         else if ( strcmp( ComandoTeste , EXC_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxgrafo , &ValEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( ValEsp ,
                      GRA_ExcluirVertice( vtgrafos[ inxgrafo ] ) ,
                     "Condi��o de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir vertice */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_CORRENTE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issssi" ,
                       &inxgrafo, StringDado1, StringDado2, StringDado3, StringDado4, &ValEsp ) ;

            if ( ( numLidos != 6 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( no_teste * ) GRA_ObterValorCorrente( vtgrafos[ inxgrafo ] ) ;

            if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , pDado ,
                         "Valor n�o deveria existir." ) ;
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

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar excluir aresta entre o corrente e o pvalor recebido */

         else if ( strcmp( ComandoTeste , EXC_ARESTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxgrafo, &inxstruct, &ValEsp ) ; //str1234

            if ( ( numLidos != 3 ) //6
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			 pDado = &vtstructs[inxstruct];//( no_teste * ) malloc( sizeof(no_teste) ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            CondRet = (TST_tpCondRet) GRA_ExcluirAresta( vtgrafos[ inxgrafo ] , pDado ) ;

            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao excluir aresta."                   ) ;

         } /* fim ativa: Testar excluir aresta */

      /* GRA  &Ir para o elemento com endere�o do valor passado */

         else if ( strcmp( ComandoTeste , IR_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxgrafo, &inxstruct, &ValEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			 pDado = &vtstructs[ inxstruct ];//( no_teste * ) malloc( sizeof(no_teste) ) ;
			 
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */


            CondRet = (TST_tpCondRet) GRA_IrVertice(vtgrafos[inxgrafo], pDado);

           return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao ir para vertice."                   ) ;

         } /* fim ativa: GRA  &Ir para o elemento */

		 /*GRA &Ver quantidade de vertices*/

		 else if ( strcmp( ComandoTeste , QNT_VERTICE_CMD ) == 0 )
		 {
			 numLidos = LER_LerParametros( "ii" , &inxgrafo, &ValEsp);

			 if ( ( numLidos != 2 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			 return TST_CompararInt( ValEsp , GRA_QntVertices(vtgrafos[inxgrafo]) ,
                     "Quantidade de vertices errada."                   ) ;

		 }/* fim ativa: GRA &Ver quantidade de vertices */

		 /*GRA &Ver quantidade de arestas do vertice corrente*/

		  else if ( strcmp( ComandoTeste , QNT_ARESTA_CMD ) == 0 )
		 {
			 numLidos = LER_LerParametros( "ii" , &inxgrafo, &ValEsp);

			 if ( ( numLidos != 2 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			 return TST_CompararInt( ValEsp , GRA_QntArestas(vtgrafos[inxgrafo]) ,
                     "Quantidade de arestas errada."                   ) ;

		 }/* fim ativa: GRA &Ver quantidade de arestas do vertice corrente */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TGRA &Testar grafo */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TGRA -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      //free( pValor ) ; N�o foi alocado dinamicamente, para testes com memoria dinamica descomentar

   } /* Fim fun��o: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Fun��o: TGRA -Validar indice do Grafo
*
***********************************************************************/

   int ValidarInxGrafo( int inxgrafo , int Modo )
   {

      if ( ( inxgrafo <  0 )
        || ( inxgrafo >= DIM_VT_GRAFO ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtgrafos[ inxgrafo ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtgrafos[ inxgrafo ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim fun��o: TGRA -Validar indice do Grafo */


/********** Fim do m�dulo de implementa��o: TLIS Teste lista de s�mbolos **********/