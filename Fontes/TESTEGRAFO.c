/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste grafo de símbolos
*
*  Arquivo gerado:              TESTEGRAFO.c.c
*  Letras identificadoras:      TGRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
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

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  Definição da struct de teste  *****/

   typedef struct no_teste 
   {
	   char nome[31];
	   char data_nasc[11];
	   char email[51];
	   char cidade[31];
   } no_teste;


/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
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
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

      char   StringDado1[  DIM_VALOR ] ;
	  char   StringDado2[  DIM_VALOR ] ;
	  char   StringDado3[  DIM_VALOR ] ;
	  char   StringDado4[  DIM_VALOR ] ;
      no_teste * pDado ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

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

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

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

      /* Testar Esvaziar lista lista */

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

      /* Testar Destruir lista */

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

      /* Testar inserir elemento antes */

         else if ( strcmp( ComandoTeste , INS_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issssi" ,
                       &inxgrafo , StringDado1, StringDado2, StringDado3, StringDado4 , &CondRetEsp ) ;

            if ( ( numLidos != 6 )
              || ( ! ValidarInxLista( inxgrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( no_teste * ) malloc( sizeof(no_teste) ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

			strcpy( pDado->nome , StringDado1 ) ;
			strcpy( pDado->data_nasc , StringDado2 ) ;
			strcpy( pDado->email , StringDado3 ) ;
			strcpy( pDado->cidade , StringDado4 ) ;


            CondRet = (TST_tpCondRet) GRA_InserirVertice( vtgrafos[ inxgrafo ] , pDado ) ;

            if ( CondRet != GRA_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir vertice.") ;

         } /* fim ativa: Testar inserir vertice */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , CRIAR_ARESTA_CMD ) == 0 )
         {

             numLidos = LER_LerParametros( "issssi" ,
                       &inxgrafo , StringDado1, StringDado2, StringDado3, StringDado4 , &CondRetEsp ) ;

            if ( ( numLidos != 6 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( no_teste * ) malloc( sizeof(no_teste) ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

			strcpy( pDado->nome , StringDado1 ) ;
			strcpy( pDado->data_nasc , StringDado2 ) ;
			strcpy( pDado->email , StringDado3 ) ;
			strcpy( pDado->cidade , StringDado4 ) ;



            CondRet = (TST_tpCondRet) GRA_CriarAresta( vtgrafos[ inxgrafo ] , pDado ) ;

            if ( CondRet != GRA_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao criar aresta."                   ) ;

         } /* fim ativa: Testar criar aresta */

      /* Testar excluir simbolo */

         else if ( strcmp( ComandoTeste , EXC_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxgrafo , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      GRA_ExcluirVertice( vtgrafos[ inxgrafo ] ) ,
                     "Condição de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir simbolo */

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

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar ir para o elemento inicial */

         else if ( strcmp( ComandoTeste , EXC_ARESTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issssi" , &inxgrafo, StringDado1, StringDado2, StringDado3, StringDado4, &ValEsp ) ;

            if ( ( numLidos != 6 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			 pDado = ( no_teste * ) malloc( sizeof(no_teste) ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

			strcpy( pDado->nome , StringDado1 ) ;
			strcpy( pDado->data_nasc , StringDado2 ) ;
			strcpy( pDado->email , StringDado3 ) ;
			strcpy( pDado->cidade , StringDado4 ) ;


            CondRet = (TST_tpCondRet) GRA_ExcluirAresta( vtgrafos[ inxgrafo ] , pDado ) ;

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao excluir aresta."                   ) ;

         } /* fim ativa: Testar ir para o elemento inicial */

      /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issssi" , &inxgrafo, StringDado1, StringDado2, StringDado3, StringDado4, &ValEsp ) ;

            if ( ( numLidos != 6 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			 pDado = ( no_teste * ) malloc( sizeof(no_teste) ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

			strcpy( pDado->nome , StringDado1 ) ;
			strcpy( pDado->data_nasc , StringDado2 ) ;
			strcpy( pDado->email , StringDado3 ) ;
			strcpy( pDado->cidade , StringDado4 ) ;

            CondRet = (TST_tpCondRet) GRA_IrVertice(vtgrafos[inxgrafo], pDado);

           return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao ir para vertice."                   ) ;

         } /* fim ativa: LIS  &Ir para o elemento final */

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

   } /* Fim função: TGRA &Testar grafo */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
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

   } /* Fim função: TLIS -Validar indice de lista */

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

