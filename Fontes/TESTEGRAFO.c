/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste grafo de símbolos
*
*  Arquivo gerado:              TESTEGRAFO.c
*  Letras identificadoras:      TGRA
*
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
static const char IR_FINAL_CMD            [ ] = "=irfinal"        ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"        ;
static const char AVANCAR_ELEMENTO_CMD    [ ] = "=avancar"        ;
#ifdef _DEBUG
static const char DETURPA_CABECA_CMD      [ ] = "=deturpacabeca"        ;
static const char RECUPERA_CABECA_CMD     [ ] = "=recuperacabeca"        ;
#endif


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_GRAFO   10
#define DIM_VALOR     100

GRA_tppGrafo   vtgrafos[ DIM_VT_GRAFO ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxGrafo( int inxgrafo , int Modo ) ;

/*****  Definição da struct de teste  *****/

   typedef struct no_teste 
   {
	   char nome[31];
	   char data_nasc[11];
	   char email[51];
	   char cidade[31];
   } no_teste;

	no_teste vtstructs [DIM_VT_GRAFO];
/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TGRA &Testar grafo
*
*  $ED Descrição da função
*     Podem ser criados até 10 grafos, identificados pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de grafos. Provoca vazamento de memória
*     =criargrafo                   inxgrafo     CondRetEsp
*     =destruirgrafo                inxgrafo     CondRetEsp
*     =esvaziargrafo                inxgrafo     CondRetEsp
*     =insvertice                   inxgrafo  string1 string2 string3 string4  CondRetEsp
*     =excvertice                   inxgrafo   CondRetEsp
*     =excaresta               	    inxgrafo  indstruct  CondretPonteiro
*     =obtervalorcorrente           inxgrafo  string1 string2 string3 string4   CondRetEsp
*     =criararesta                  inxgrafo   inxstruct   CondRetEsp
*     =irvertice                    inxgrafo   inxstruct   ValEsp
*     =qntvertice                   inxgrafo  ValEsp
*     =qntaresta                    inxgrafo  ValEsp
*     =irfinal                      inxgrafo  ValEsp
*     =irinicio                     inxgrafo  ValEsp
*     =avancar                      inxgrafo  numElem  ValEsp               
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxgrafo  = -1 ,
          numLidos   = -1 ,
          ValEsp = -1 ,
			    inxstruct =-1,
          numElem = -1;

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

      /* Testar inserir vertice */

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
               //free( pDado ) ; //não foi alocado dinamicamente
            } /* if */

            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao inserir vertice.") ;

         } /* fim ativa: Testar inserir vertice */

      /* Testar criar aresta */

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
               //free( pDado ) ;//não foi alocado dinamicamente
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
                     "Condição de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir vertice */

      /* Testar obter valor do vertice corrente */

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

         } /* fim ativa: Testar obter valor do vertice corrente */

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

      /* GRA  &Ir para o vertice com o indice passado */

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

         } /* fim ativa: GRA  &Ir para o vertice */

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
     
     /* Testar IrInicio grafo */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxgrafo ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            GRA_IrInicioOrigens( vtgrafos[ inxgrafo ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Irinicio grafo */

          /* Testar IrFinal grafo */

         else if ( strcmp( ComandoTeste , IR_FINAL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxgrafo ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            GRA_IrFinalOrigens( vtgrafos[ inxgrafo ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar IrFinal grafo */

          /* Testar avancar elemento grafo */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEMENTO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                               &inxgrafo, &numElem ,&ValEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            
            return TST_CompararInt( ValEsp , GRA_AvancarElementoCorrente( vtgrafos[ inxgrafo ] , numElem ) ,
                     "Erro ao avancar elemento corrente do Grafo."                   ) ;

         } /* fim ativa: Testar avancar elemento grafo */

     #ifdef _DEBUG
      /********** FUNÇOES DEBUG  *********/
      /*GRA &Deturpa Cabeça do grafo ( torna ponteiro para origem do grafo null */
            else if ( strcmp( ComandoTeste , DETURPA_CABECA_CMD ) == 0 )
		 {
			 numLidos = LER_LerParametros( "ii" , &inxgrafo, &ValEsp);

			 if ( ( numLidos != 2 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			 return TST_CompararInt( ValEsp , GRA_DeturpaCabeca(vtgrafos[inxgrafo]) ,
                     "Erro ao deturpar Cabeça do Grafo."                   ) ;

		 }/* fim ativa: GRA &Ver quantidade de arestas do vertice corrente */

     /*GRA &Ver quantidade de arestas do vertice corrente*/
     else if ( strcmp( ComandoTeste , RECUPERA_CABECA_CMD ) == 0 )
		 {
			 numLidos = LER_LerParametros( "ii" , &inxgrafo, &ValEsp);

			 if ( ( numLidos != 2 )
              || ( ! ValidarInxGrafo( inxgrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			 return TST_CompararInt( ValEsp , GRA_RecuperaCabeca(vtgrafos[inxgrafo]) ,
                     "Erro ao recuperar cabeça, Grafo era realmente null?."                   ) ;

		 }/* fim ativa: GRA &Ver quantidade de arestas do vertice corrente */


     /********** FIM FUNÇÕES DEBUG  *********/
     #endif

      return TST_CondRetNaoConhec ;

   } /* Fim função: TGRA &Testar grafo */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TGRA -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      //free( pValor ) ; Não foi alocado dinamicamente, para testes com memoria dinamica descomentar

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TGRA -Validar indice do Grafo
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

   } /* Fim função: TGRA -Validar indice do Grafo */


/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/
