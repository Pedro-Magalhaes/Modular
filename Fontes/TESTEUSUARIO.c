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
static const char EDITAR_PERFIL_CMD		   [ ] = "=editarperfil"   ;
static const char DELETAR_USUARIO_CMD      [ ] = "=deletarusuario"   ;
static const char DESTRUIR_USUARIOS_CMD    [ ] = "=destruirusuarios"   ;
static const char TOTAL_USUARIOS_CMD       [ ] = "=totalusuarios"   ;
static const char PEGAR_CORRENTE_CMD       [ ] = "=pegarcorrente"   ;




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
*     =adicionaramigo               inxusuario   string1     CondRetEsp
*     =editarperfil                 inxusuario   XXXX     CondRetEsp
*     =deletarusuario               int1     CondRetEsp
*     =destruirusuarios             inxusuario     CondRetEsp
*     =totalusuarios				inxusuario	   ValEsp
*     =pegarcorretne				inxusuario	   string1
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
   

      int i ;
	  int intdado1 = 0 ;

      

      StringDado1[ 0 ] = 0 ;
	  StringDado2[ 0 ] = 0 ;
	  StringDado3[ 0 ] = 0 ;
	  StringDado4[ 0 ] = 0 ;

      
      /* Testar iniciar módulo usuário */

         if ( strcmp( ComandoTeste , INICIAR_MODULO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxusuario ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxusuario( inxusuario , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtusuarios[ inxusuario ] =
                 USU_InicializarModulo() ;

            return TST_CompararPonteiroNulo( 1 , vtusuarios[ inxusuario ] ,
               "Erro em ponteiro de novo usuario."  ) ;

         } /* fim ativa: Testar Criar usuario */

      /* Testar Criar usuario */

         else if ( strcmp( ComandoTeste , CRIAR_USUARIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isisi" ,
                       &inxusuario, StringDado1, &intdado1, StringDado2, &ValEsp ) ;

            if ( ( numLidos != 5 )
              || ( ! ValidarInxusuario( inxusuario , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = (TST_tpCondRet) USU_CriaUsuario(vtusuarios[ inxusuario ], StringDado1, intdado1, StringDado2[0] ) ;

            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao criar usuario.") ;

         } /* fim ativa: Testar Criar usuario */

      /* Testar adicionar amigo */

         else if ( strcmp( ComandoTeste , ADICIONAR_AMIGO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                               &inxusuario, StringDado1, &ValEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = (TST_tpCondRet) USU_AdicionaAmigo(vtusuarios[ inxusuario ], StringDado1);

            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao adicionar amigo.") ;


         } /* fim ativa: Testar adicionar amigo */

      /* Testar editar perfil */

         else if ( strcmp( ComandoTeste , EDITAR_PERFIL_CMD ) == 0 )
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

         } /* fim ativa: Testar editar perfil */

      /* Testar deletar usuario */

         else if ( strcmp( ComandoTeste , DELETAR_USUARIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                       &inxusuario, &ValEsp ) ;

            if ( ( numLidos != 2 ) 
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			

			


            CondRet = (TST_tpCondRet) USU_DeletarUsuario( vtusuarios[ inxusuario ]) ;


            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao deletar usuario.") ;

         } /* fim ativa: Testar deletar usuario */

      /* Testar destruir usuarios */

         else if ( strcmp( ComandoTeste , DESTRUIR_USUARIOS_CMD ) == 0 )
         {

             numLidos = LER_LerParametros( "ii" ,
                       &inxusuario , &ValEsp ) ;

            if ( ( numLidos != 2 ) 
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            

            CondRet = (TST_tpCondRet) USU_DestruirUsuarios( vtusuarios[ inxusuario ] ) ;



            return TST_CompararInt( ValEsp , CondRet ,
                     "Condicao de retorno errada ao destruir usuarios."                   ) ;

         } /* fim ativa: Testar destruir usuarios */

      /* Testar obter o total de usuarios */

         else if ( strcmp( ComandoTeste , TOTAL_USUARIOS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxusuario , &ValEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( ValEsp ,
                      USU_TotalUsuarios( vtusuarios[ inxusuario ] ) ,
                     "Numero de usuarios esperado errado."   ) ;

         } /* fim ativa: Testar obter total de usuarios */

      /* Testar obter nome do usuario corrente */

         else if ( strcmp( ComandoTeste , PEGAR_CORRENTE_CMD ) == 0 )
         {
			 char* stringtemp;

            numLidos = LER_LerParametros( "is" ,
                       &inxusuario, StringDado1) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxusuario( inxusuario , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            stringtemp = USU_PegaNomeUsuarioCorrente( vtusuarios[ inxusuario ] ) ;

            if ( StringDado1 == NULL )
            {
               return TST_CompararPonteiroNulo( 0 , stringtemp ,
                         "Nome não deveria existir." ) ;
            } /* if */

            if ( stringtemp == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , stringtemp ,
                         "Nome deveria existir." ) ;
            } /* if */

			return (TST_tpCondRet) (TST_CompararString( StringDado1 , stringtemp ,
                         "Nome corrente errado." )) ;

         } /* fim ativa: Testar obter nome do usuario corrente */

      

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