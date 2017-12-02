/***************************************************************************
*  $MCI Módulo de implementação: TCHA Teste chat entre usuários
*
*  Arquivo gerado:              TESTECHAT.C
*  Letras identificadoras:      TCHA
*
*  Nome da base de software:   iMigo - a sua nova rede de relacionamentos
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301/ iMigo - a sua nova rede de relacionamentos
*  Gestor:  LES/DI/PUC-Rio
*  Autores: pfs, hfac , yan
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       yan   01/12/2017 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "CHAT.H"


static const char CRIAR_CHAT_CMD           [ ] = "=criarchat"     ;
static const char ADICIONAR_INTEGRANTE_CMD [ ] = "=adicionarintgrante"     ;
static const char ENVIAR_MENSAGEM_CMD      [ ] = "=enviarmensagem"  ;
static const char SAIR_CHAT_CMD            [ ] = "=sairchat"  ;
static const char DELETAR_CHAT_CMD         [ ] = "=deletarchat"   ;
static const char DELETAR_MENSAGEM_CMD     [ ] = "=deletarmensagem"    ;
static const char PEGAR_MENSAGENS_CMD      [ ] = "=pegarmensagens" ;



#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_CHAT   10
#define DIM_VALOR     100

CHA_tppChat   vtchats[ DIM_VT_CHAT ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxChat( int inxchat , int Modo ) ;

/*****  Definição da struct de teste  *****/

   typedef struct no_teste 
   {
	   char nome[51];
	   int id;
	   char genero;
	   int idade;
   } no_teste;

	no_teste vtstructs [DIM_VALOR];
/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TCHA &Testar chat
*
*  $ED Descrição da função
*     Podem ser criados até 10 chats, identificados pelos índices 0 a 9
*
*     Comandos disponíveis:
*
*    
*     =criarchat					inxchat  inxstruct  string1   int1   string2   int2 
*     =adicionarintgrante			inxchat  inxstruct  string1   int1   string2   int2    CondRetEsp
*     =enviarmensagem				inxchat  inxstruct  string1   CondRetEsp
*     =sairchat						inxchat  inxstruct  CondRetEsp
*     =deletarchat                  inxchat  CondRetEsp
*     =deletarmensagem              inxchat  CondRetEsp
*     =pegarmensagens				inxchat  StringEsp
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxchat  = -1 ,
          numLidos   = -1 ,
          ValEsp = -1 ,
		  inxstruct =-1;

      TST_tpCondRet CondRet ;

      char   StringDado1[  DIM_VALOR ] ;
	  char   StringDado2[  DIM_VALOR ] ;
	  char   StringDado3[  DIM_VALOR ] ;
	  char   StringDado4[  DIM_VALOR ] ;
	  int intdado1;
	  int intdado2;
      no_teste * pDado ;   

      int i ;

      

      StringDado1[ 0 ] = 0 ;
	  StringDado2[ 0 ] = 0 ;
	  StringDado3[ 0 ] = 0 ;
	  StringDado4[ 0 ] = 0 ;

      

      /* Testar Criarchat */

         if ( strcmp( ComandoTeste , CRIAR_CHAT_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iisisi" ,
                       &inxchat, &inxstruct, StringDado1,  &intdado1, StringDado2, &intdado2) ;

            if ( ( numLidos != 6 )
              || ( ! ValidarInxChat( inxchat , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			vtstructs[inxstruct].id = intdado1;
			strcpy(vtstructs[inxstruct].nome, StringDado1);
			vtstructs[inxstruct].genero = StringDado2[0];
			vtstructs[inxstruct].idade = intdado2;

			pDado = (no_teste*) &vtstructs[ inxstruct ];

            vtchats[ inxchat ] =
                 CHA_CriaChat(pDado, DestruirValor ) ;

            return TST_CompararPonteiroNulo( 1 , vtchats[ inxchat ] ,
               "Erro em ponteiro de novo chat."  ) ;

         } /* fim ativa: Testar Criar chat */

      /* Testar adicionar integrante */

         else if ( strcmp( ComandoTeste , ADICIONAR_INTEGRANTE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iisisii" ,
                       &inxchat, &inxstruct, StringDado1,  &intdado1, StringDado2, &intdado2, &ValEsp) ;

            if ( ( numLidos != 7 )
              || ( ! ValidarInxChat( inxchat , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			vtstructs[inxstruct].id = intdado1;
			strcpy(vtstructs[inxstruct].nome, StringDado1);
			vtstructs[inxstruct].genero = StringDado2[0];
			vtstructs[inxstruct].idade = intdado2;

			pDado = (no_teste*) &vtstructs[ inxstruct ];

            CondRet = (TST_tpCondRet) CHA_AdicionaIntegrante( vtchats[ inxchat ], pDado  ) ;

             if ( CondRet != CHA_CondRetOK )
            {
               //free( pDado ) ; //não foi alocado dinamicamente
            } /* if */

            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao adicionar integrante.") ;

         } /* fim ativa: Testar adicionar integrante */

      /* Testar enviar mensagem */

         else if ( strcmp( ComandoTeste , ENVIAR_MENSAGEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iisi" ,
                               &inxchat, &inxstruct, StringDado1, &ValEsp ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxChat( inxchat , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			pDado = (no_teste*) &vtstructs[ inxstruct ];

            CondRet = (TST_tpCondRet) CHA_EnviaMensagem(vtchats[ inxchat ], StringDado1, pDado->nome);

            if ( CondRet != CHA_CondRetOK )
            {
               //free( pDado ) ; //não foi alocado dinamicamente
            } /* if */

            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao enviar mensagem.") ;

         } /* fim ativa: Testar enviar mensagem */

      /* Testar sair do chat */

         else if ( strcmp( ComandoTeste , SAIR_CHAT_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxchat , &inxstruct , &ValEsp ) ;

            if ( ( numLidos != 3 ) 
              || ( ! ValidarInxChat( inxchat , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			


            pDado = (no_teste*) &vtstructs[ inxstruct ];  
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

			


            CondRet = (TST_tpCondRet) CHA_SairChat( vtchats[ inxchat ] , pDado ) ;

            if ( CondRet != CHA_CondRetOK )
            {
               //free( pDado ) ; //não foi alocado dinamicamente
            } /* if */

            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao sair do chat.") ;

         } /* fim ativa: Testar sair do chat */

      /* Testar deletar chat */

         else if ( strcmp( ComandoTeste , DELETAR_CHAT_CMD ) == 0 )
         {

             numLidos = LER_LerParametros( "ii" ,
                       &inxchat , &ValEsp ) ;

            if ( ( numLidos != 2 ) 
              || ( ! ValidarInxChat( inxchat , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            

            CondRet = (TST_tpCondRet) CHA_DeletarChat( vtchats[ inxchat ]) ;

            if ( CondRet != CHA_CondRetOK )
            {
               //free( pDado ) ;//não foi alocado dinamicamente
            } /* if */

            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao deletar chat."                   ) ;

         } /* fim ativa: Testar deletar chat */

      /* Testar deletar mensagem */

         else if ( strcmp( ComandoTeste , DELETAR_MENSAGEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxchat , &ValEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxChat( inxchat , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = (TST_tpCondRet) CHA_DeletarMensagem( vtchats[ inxchat ]) ;

            if ( CondRet != CHA_CondRetOK )
            {
               //free( pDado ) ;//não foi alocado dinamicamente
            } /* if */

            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao deletar mensagem."                   ) ;


         } /* fim ativa: Testar deletar mensagem */

      /* Testar pegar mensagens */

         else if ( strcmp( ComandoTeste , PEGAR_MENSAGENS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "is" ,
                       &inxchat, StringDado1 ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxChat( inxchat , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

           strcpy(StringDado2, CHA_PegaMensagens(vtchats[ inxchat ]));

           return TST_CompararString( StringDado1 , StringDado2 ,
                     "Mensagens devolvidas diferentes das esperadas."                   ) ;

         } /* fim ativa: Testar pegar mensagens */

      

      return TST_CondRetNaoConhec ;

   } /* Fim função: TCHA &Testar chat */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TCHA -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      //free( pValor ) ; Não foi alocado dinamicamente, para testes com memoria dinamica descomentar

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TCHA -Validar indice do chat
*
***********************************************************************/

   int ValidarInxChat( int inxchat , int Modo )
   {

      if ( ( inxchat <  0 )
        || ( inxchat >= DIM_VT_CHAT ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtchats[ inxchat ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtchats[ inxchat ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TCHA -Validar indice do chat */


/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/