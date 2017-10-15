#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: GRA  Grafo
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\(a definir)
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Hfac & Pfm 
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor			Data		 Observa��es
*     1       Hfac & Pfm   13/out/2017	 in�cio desenvolvimento
*	  2		  Hfac & Pfm   14/out/2017   continua��o do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa grafos com cabe�a gen�ricos.
*     Podem existir n grafos em opera��o simultaneamente.
*     As grafos possuem uma cabe�a encapsulando o seu estado.
*
*     Cada grafo � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da grafo referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos do grafo.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada grafo referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma grafo.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da grafo seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.L
*
***************************************************************************/

#if defined( GRAFO_OWN )
#define GRAFO_EXT
#else
#define GRAFO_EXT extern
#endif

#include   "LISTA.H"

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma grafo */

typedef struct GRA_tagGrafo * GRA_tppGrafo;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da grafo
*
***********************************************************************/

typedef enum {

	GRA_CondRetOK,
	/* Concluiu corretamente */

	GRA_CondRetGrafoVazia,
	/* A grafo n�o cont�m elementos */

	GRA_CondRetFimGrafo,
	/* Foi atingido o fim de grafo */

	GRA_CondRetNaoAchou,
	/* N�o encontrou o valor procurado */

	GRA_CondRetFaltouMemoria
	/* Faltou mem�ria ao tentar criar um elemento de grafo */

} GRA_tpCondRet;


/***********************************************************************
*
*  $FC Fun��o: GRA  &Criar grafo
*
*  $ED Descri��o da fun��o
*     Cria uma grafo gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � grafo.
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a grafo.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem esta grafo.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

GRA_tppGrafo GRA_CriarGrafo(
	void(*ExcluirValor) (void * pDado));


/***********************************************************************
*
*  $FC Fun��o: GRA  &Destruir grafo
*
*  $ED Descri��o da fun��o
*     Destr�i a grafo fornecida.
*     O par�metro ponteiro para a grafo n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a grafo resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $FV Valor retornado
*     GRA_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

void GRA_DestruirGrafo(GRA_tppGrafo pGrafo);


/***********************************************************************
*
*  $FC Fun��o: GRA  &Esvaziar grafo
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a grafo
*
*  $EP Par�metros
*     pGrafo - ponteiro para a grafo a ser esvaziada
*
***********************************************************************/

void GRA_EsvaziarGrafo(GRA_tppGrafo pGrafo);


/***********************************************************************
*
*  $FC Fun��o: GRA  &Inserir vertice
*
*  $ED Descri��o da fun��o
*     Insere novo vertice.
*     Caso a grafo esteja vazia, insere o primeiro elemento do grafo.
*
*  $EP Par�metros
*     Par�metros
*        pGrafo - ponteiro para a grafo onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*
*
*  $FV Valor retornado
*     Valor retornado
*        GRA_CondRetOK
*        GRA_CondRetFaltouMemoria
*
***********************************************************************/

GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo,
	void * pValor);


/***********************************************************************
*
*  $FC Fun��o: GRA  &Excluir vertice
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da grafo dada.
*     Se existir o elemento aa esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a grafo tornou-se vazia.
*
*  $EP Par�metros
*     pGrafo    - ponteiro para a grafo na qual deve excluir.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetGrafoVazia
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo);


/***********************************************************************
*
*  $FC Fun��o: GRA  &Excluir Aresta
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da grafo dada.
*     Se existir o elemento aa esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a grafo tornou-se vazia.
*
*  $EP Par�metros
*     pGrafo    - ponteiro para a grafo na qual deve excluir.
*	  vertice	- Ponteiro para o vertice cuja aresta deve ser excluida
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetGrafoVazia
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirAresta(GRA_tppGrafo pGrafo, void* vertice);


/***********************************************************************
*
*  $FC Fun��o: GRA  &Obter refer�ncia para o valor contido no elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da grafo
*
*  $EP Par�metros
*     pGrafo - ponteiro para a grafo de onde se quer o valor
*
*  $FV Valor retornado
*     n�o NULL - se o elemento corrente existe
*     NULL     - se a grafo estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

void * GRA_ObterValorCorrente(GRA_tppGrafo pGrafo);



/***********************************************************************
*
*  $FC Fun��o: GRA  &CriarAresta
*
*  $ED Descri��o da fun��o
*    cria uma aresta entre o vertice corrente e o vertice recebido como parametro
*     
*
*  $EP Par�metros
*     pGrafo  - ponteiro para a grafo a ser manipulada
*     vertice - vertice destino 
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimGrafo   - se encontrou o fim da grafo antes de andar numElem
*                         elementos
*     CondRetGrafoVazia - se a grafo est� vazia
*
***********************************************************************/

GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo,
	void* vertice);


/***********************************************************************
*
*  $FC Fun��o: GRA  &Procurar elemento contendo valor
*
*  $ED Descri��o da fun��o
*     Procura o elemento que referencia o valor dado.
*     A fun��o compara ponteiro e n�o conte�do apontado.
*
*  $EP Par�metros
*     pGrafo  - ponteiro para a grafo onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     GRA_CondRetOK  - se encontrou.
*                      O elemento corrente � o primeiro elemento do
*                      elemento corrente inclusive para o fim da grafo
*                      e que cont�m o ponteiro procurado
*
*     GRA_CondRetNaoEncontrou - se o ponteiro n�o foi encontrado
*                      O elemento corrente continua o mesmo
*     GRA_CondRetGrafoVazia   - se a grafo estiver vazia
*
***********************************************************************/

GRA_tpCondRet GRA_ProcurarValor(GRA_tppGrafo pGrafo,
	void * pValor);

#undef GRAFO_EXT

/********** Fim do m�dulo de defini��o: GRA  Grafo duplamente encadeada **********/

#else
#endif