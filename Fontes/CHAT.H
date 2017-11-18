#if ! defined( CHAT_ )
#define CHAT_
/***************************************************************************
*
*  $MCD Módulo de definição: CHA  Chat da rede de relacionamentos
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
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações*     
*     1       pfs   17/11/2017 início desenvolvimento
*
*  $ED Descrição do módulo
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

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct CHA_tagLista * CHA_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: CHA Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do CHAT
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
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   CHA_tppLista CHA_CriarChat(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;


#undef CHAT_EXT

/********** Fim do módulo de definição: CHA  Chat **********/

#else
#endif
