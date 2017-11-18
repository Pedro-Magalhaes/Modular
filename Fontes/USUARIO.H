#if ! defined( USUARIO_ )
#define USUARIO_
/***************************************************************************
*
*  $MCD Módulo de definição: USU  Usuário da rede de relacionamentos
*
*  Arquivo gerado:              USUARIO.h
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
 
#if defined( USUARIO_OWN )
   #define USUARIO_EXT
#else
   #define USUARIO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct USU_tagLista * USU_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         USU_CondRetOK ,
               /* Concluiu corretamente */

         USU_CondRetListaVazia ,
               /* A lista n�o cont�m elementos */

         USU_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         USU_CondRetNaoAchou ,
               /* N�o encontrou o valor procurado */

         USU_CondRetFaltouMemoria
               /* Faltou mem�ria ao tentar criar um elemento de lista */

   } USU_tpCondRet ;


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

   USU_tppLista USU_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;


#undef USUARIO_EXT

/********** Fim do módulo de definição: USU  Usuário **********/

#else
#endif
