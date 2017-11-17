#if ! defined( CHAT_ )
#define CHAT_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: CHA  Usuário da rede de relacionamentos
*
*  Arquivo gerado:              CHAT.h
*  Letras identificadoras:      CHA
*
*  Nome da base de software:    iMigo - a sua nova rede de relacionamentos
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301/ iMigo - a sua nova rede de relacionamentos
*  Gestor:  LES/DI/PUC-Rio
*  Autores: pfs, hfac , yan
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es*     
*     1       pfs   17/11/2017 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa o módulo usuário da rede de relacionamentos, contém os
*     dados dos usuarios, como seu perfil. Possui os métodos de interação
*     do usuário com a rede. Faz uso do módulo Grafo e do Módulo Chat 
*
*     Cada usuário possui um perfil com Nome com no MAX 50 caracteres,
*     idade (inteiro positivo), gênero (char 'M'-Masculino , 'F'-Feminino,
      'O'-Outros)
*
*     FALTA ESCREVER MAIS?????? OLHAR MODULO LISTA.H
*
***************************************************************************/
 
#if defined( CHAT_OWN )
   #define CHAT_EXT
#else
   #define CHAT_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct CHA_tagLista * CHA_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         CHA_CondRetOK ,
               /* Concluiu corretamente */

         CHA_CondRetListaVazia ,
               /* A lista n�o cont�m elementos */

         CHA_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         CHA_CondRetNaoAchou ,
               /* N�o encontrou o valor procurado */

         CHA_CondRetFaltouMemoria
               /* Faltou mem�ria ao tentar criar um elemento de lista */

   } CHA_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

   CHA_tppLista CHA_CriarChat(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;


#undef CHAT_EXT

/********** Fim do m�dulo de defini��o: CHA  Usuário **********/

#else
#endif
