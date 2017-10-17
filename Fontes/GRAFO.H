#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD Módulo de definição: GRA  Grafo
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\(a definir)
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Hfac & Pfm 
*
*  $HA Histórico de evolução:
*     Versão  Autor			Data		 Observações
*     1       Hfac & Pfm   13/out/2017	 início desenvolvimento
*	  2		  Hfac & Pfm   14/out/2017   continuação do desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa grafos com cabeça genéricos.
*     Podem existir n grafos em operação simultaneamente.
*     As grafos possuem uma cabeça encapsulando o seu estado.
*
*     Cada grafo é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da grafo referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos do grafo.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada grafo referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma grafo.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da grafo seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.L
*
***************************************************************************/

#if defined( GRAFO_OWN )
#define GRAFO_EXT
#else
#define GRAFO_EXT extern
#endif

#include   "LISTA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma grafo */

typedef struct GRA_tagGrafo * GRA_tppGrafo;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do grafo
*
***********************************************************************/

typedef enum {

	GRA_CondRetOK,
	/* Concluiu corretamente */

	GRA_CondRetGrafoVazia,
	/* A grafo não contém elementos */

	GRA_CondRetFimGrafo,
	/* Foi atingido o fim de grafo */

	GRA_CondRetNaoAchou,
	/* Não encontrou o valor procurado */

	GRA_CondRetFaltouMemoria,
	/* Faltou memória ao tentar criar um elemento de grafo */

	GRA_CondRetGrafoNulo
	/* Grafo é NULL */

} GRA_tpCondRet;


/***********************************************************************
*
*  $FC Função: GRA  &Criar grafo
*
*  $ED Descrição da função
*     Cria uma grafo genérica com cabeça.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à grafo.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a grafo.
*     Este ponteiro será utilizado pelas funções que manipulem esta grafo.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

GRA_tppGrafo GRA_CriarGrafo(
	void(*ExcluirValor) (void * pDado));


/***********************************************************************
*
*  $FC Função: GRA  &Destruir grafo
*
*  $ED Descrição da função
*     Destrói o grafo fornecido.
*     O parâmetro ponteiro para o grafo não é modificado.
*     Se ocorrer algum erro durante a destruição, o grafo resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para a grafo a ser destruido
*
*  $FV Valor retornado
*     Não possui condição de retorno, assume-se que nada tenha dado errado
*
***********************************************************************/

void GRA_DestruirGrafo(GRA_tppGrafo pGrafo);


/***********************************************************************
*
*  $FC Função: GRA  &Esvaziar grafo
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar o grafo
*
*  $EP Parâmetros
*     pGrafo - ponteiro para a grafo a ser esvaziada
*
*  $FV Valor retornado
*     Não possui condição de retorno, assume-se que nada tenha dado errado
*
***********************************************************************/

void GRA_EsvaziarGrafo(GRA_tppGrafo pGrafo);


/***********************************************************************
*
*  $FC Função: GRA  &Inserir vertice
*
*  $ED Descrição da função
*     Insere novo vertice.
*     Caso a grafo esteja vazia, insere o primeiro elemento do grafo.
*
*  $EP Parâmetros
*     Parâmetros
*        pGrafo - ponteiro para a grafo onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*
*
*  $FV Valor retornado
*     Valor retornado
*	 GRA_CondRetGrafoNulo
*        GRA_CondRetOK
*        GRA_CondRetFaltouMemoria
*
***********************************************************************/

GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo,
	void * pValor);


/***********************************************************************
*
*  $FC Função: GRA  &Excluir vertice
*
*  $ED Descrição da função
*     Exclui o elemento corrente do grafo dado.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir o grafo tornou-se vazia.
*
*  $EP Parâmetros
*     pGrafo    - ponteiro para a grafo na qual deve excluir o vertice corrente.
*
*  $FV Valor retornado
*     GRA_CondRetGrafoNulo
*     GRA_CondRetOK
*     GRA_CondRetGrafoVazia
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo);


/***********************************************************************
*
*  $FC Função: GRA  &Excluir Aresta
*
*  $ED Descrição da função
*     Exclui a aresta entre o vertice corrente e do vertice cujo valor foi dado.
*     A exclusão irá ocorrer em ambos os vertices.
*     Se não existir a aresta a ser excluida o programa ira retornar que tudo deu certo.
*
*  $EP Parâmetros
*     pGrafo    - ponteiro para a grafo na qual deve excluir a aresta do vertice corrente.
*     valor	- Ponteiro para o valor cujo vertice (nao corrente) possui.
*
*  $FV Valor retornado
*     GRA_CondRetGrafoNulo
*     GRA_CondRetOK
*     GRA_CondRetGrafoVazia
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirAresta(GRA_tppGrafo pGrafo, void* valor);


/***********************************************************************
*
*  $FC Função: GRA  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da grafo
*
*  $EP Parâmetros
*     pGrafo - ponteiro para a grafo de onde se quer o valor do vertice corrente
*
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe
*     NULL     - se a grafo estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

void* GRA_ObterValorCorrente(GRA_tppGrafo pGrafo);



/***********************************************************************
*
*  $FC Função: GRA  &CriarAresta
*
*  $ED Descrição da função
*    Cria uma aresta entre o vertice corrente e o vertice recebido como parametro
*     
*
*  $EP Parâmetros
*     pGrafo	- ponteiro para a grafo a ser manipulada
*     valor	- valor contido no vertice destino 
*
*  $FV Valor retornado
*     GRA_CondRetGrafoNulo  - se grafo enviado for nulo
*     GRA_CondRetOK         - se numElem elementos tiverem sido andados
*     GRA_CondRetFimGrafo   - se encontrou o fim da grafo antes de andar numElem
*                         elementos
*     GRA_CondRetGrafoVazia - se a grafo está vazia
*
***********************************************************************/

GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo,
	void* valor);


/***********************************************************************
*
*  $FC Função: GRA  &IrVertice elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*     pGrafo  - ponteiro para a grafo onde procura
*     Valor  - ponteiro para o valor contido no vertice que se
*				deseja chegar
*
*  $FV Valor retornado
*     GRA_CondRetGrafoNulo - se grafo mandado for nulo
*
*     GRA_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da grafo
*                      e que contém o ponteiro procurado
*
*     GRA_CondRetNaoEncontrou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     GRA_CondRetGrafoVazia   - se a grafo estiver vazia
*
***********************************************************************/

GRA_tpCondRet GRA_IrVertice(GRA_tppGrafo pGrafo, void * valor);

/***********************************************************************
*
*  $FC Função: GRA  &QntVertices
*
*  $ED Descrição da função
*     Indica quantidade de vertice em determinado grafo.
*
*  $EP Parâmetros
*     pGrafo  - ponteiro para a grafo onde procura
*     
*
*  $FV Valor retornado
*     int >= 0		  - se o grafo existe
*
*     int < 0		  - se o grafo é nulo
*
***********************************************************************/

int GRA_QntVertices(GRA_tppGrafo pGrafo);

/***********************************************************************
*
*  $FC Função: GRA  &QntArestas
*
*  $ED Descrição da função
*     Indica quantidade de arestas do vertice corrente em determinado grafo.
*
*  $EP Parâmetros
*     pGrafo  - ponteiro para a grafo onde procura
*     
*
*  $FV Valor retornado
*     int >= 0		  - se o grafo existe
*
*     int < 0		  - se o grafo é nulo
*
***********************************************************************/

int GRA_QntArestas(GRA_tppGrafo pGrafo);

#undef GRAFO_EXT

/********** Fim do módulo de definição: GRA  Grafo com cabeça **********/

#else
#endif
