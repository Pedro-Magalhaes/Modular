/***************************************************************************
*  $MCI Módulo de implementação: GRA  Grafo
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\(a definir)
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Hfac
*			Pfm
*
*  $HA Histórico de evolução:
*     Versão  Autor			Data		 Observações
*     1       Hfac & Pfm   13/out/2017	 início desenvolvimento
*	  2		  Hfac & Pfm   14/out/2017   continuação do desenvolvimento
*	  3		  Pfm		   15/out/2017   continuação do desenvolvimento e Modulo pronto para etapa de testes
*
***************************************************************************/
#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>


#define GRAFO_OWN
#include "GRAFO.h"
#undef GRAFO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento do grafo
*
*
***********************************************************************/

typedef struct tagVerticeGrafo {

	LIS_tppLista pVerticeArestas;
	/* Ponteiro para a lista com as arestas do vertice  */

	void * valor;
	/* Ponteiro para o conteudo do vertice */


} tpVerticeGrafo;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça de grafo
*
*
***********************************************************************/

typedef struct GRA_tagGrafo {

	LIS_tppLista pOrigemGrafo;
	/* Ponteiro para a origem do grafo */

	tpVerticeGrafo * pVertice;
	/* Ponteiro para o vertice corrente do grafo */

	LIS_tppLista pArestas;
	/* Ponteiro para arestas do vertice corrente */

	void(*ExcluirValor) (void * pValor);
	/* Ponteiro para a função de destruição do valor contido em um elemento */

} GRA_tpGrafo;

/***** Protótipos das funções encapuladas no módulo *****/

/*static void LiberarElemento(LIS_tppLista   pLista,
	tpElemLista  * pElem);*/

static GRA_tpCondRet EfetuaExclusaoAresta(tpVerticeGrafo* vertice1, tpVerticeGrafo* vertice2);

static tpVerticeGrafo* GRA_ProcurarValor (LIS_tppLista pOrigemGrafo, void* pValor);

static tpVerticeGrafo* CriarElemento(void * pValor);

static void LimparCabeca(GRA_tppGrafo pGrafo);  /* por enquanto nao foi utilizada */

static void naoExclui(void * pDado);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRA  &Criar grafo
*  ****/

GRA_tppGrafo GRA_CriarGrafo(void(*ExcluirValor)(void *pDado))
{
	GRA_tpGrafo * pGrafo = NULL;

	pGrafo = (GRA_tpGrafo *)malloc(sizeof(GRA_tpGrafo));
	if (pGrafo == NULL)
	{
		return NULL;
	}
	pGrafo->ExcluirValor = ExcluirValor;
	pGrafo->pArestas = NULL;
	pGrafo->pOrigemGrafo = LIS_CriarLista(ExcluirValor); //criando uma lista vazia
	pGrafo->pVertice = NULL;
	


	return pGrafo;
}

/* Fim função: GRA  &Criar grafo */

/***************************************************************************
*
*  Função: GRA  &Destruir grafo
*  ****/

 void GRA_DestruirGrafo( GRA_tppGrafo pGrafo )
   {

    #ifdef _DEBUG
      assert( pGrafo != NULL ) ;
    #endif
	  if (pGrafo == NULL)
	  {//nada a ser feito
		  return;
	  }

      GRA_EsvaziarGrafo( pGrafo );
	  	  
	  free(pGrafo);
	  

   } /* Fim função: GRA  &Destruir grafo */

	 /***************************************************************************
	 *
	 *  Função: GRA  &Esvaziar grafo
	 *  ****/

 void GRA_EsvaziarGrafo(GRA_tppGrafo pGrafo)
 {

#ifdef _DEBUG
	 assert(pGrafo != NULL);
#endif

	 if (pGrafo == NULL)
	 {
		 return;
	 }
	 LIS_tppLista Elem= pGrafo->pOrigemGrafo;	 
	 tpVerticeGrafo * atual; 


	 LIS_IrInicioLista(Elem); //indo pro inicio da lista
	 atual = LIS_ObterValor(Elem);//pegando o primeiro valor
	 if (atual != NULL)
	 {
		 LIS_DestruirLista(atual->pVerticeArestas); //DECIDIR SE QUEREMOS DELETAR TODOS OS NÓS OU NÃO E DEIXAR A LISTA VAZIA  (pra manter os vertices é só esvaziar suas listas de arestas ao invés de destruir)
		 pGrafo->ExcluirValor(atual->valor);
		 free(atual);
	 }
		
	 	 	 
	 while (LIS_AvancarElementoCorrente(Elem, 1) == LIS_CondRetOK)
	 {
		 
		 //limpa as outras listas de arestas se existirem		 
		 atual = LIS_ObterValor(Elem);
		 LIS_IrInicioLista(atual->pVerticeArestas);
		 LIS_DestruirLista(atual->pVerticeArestas);
		 pGrafo->ExcluirValor(atual->valor);
		 free(atual);
	 }
	 //limpa a lista de vertices
	 LIS_EsvaziarLista(pGrafo->pOrigemGrafo);
	 pGrafo->pArestas = NULL;
	 pGrafo->pVertice = NULL;
	 

	 return;

 } /* Fim função: GRA  &Esvaziar grafo */

   /***************************************************************************
   *
   *  Função: GRA  &InserirVertice
   *  ****/

 GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo, void* pValor)
 {
	#ifdef _DEBUG
		 assert(pGrafo != NULL);
	#endif

	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoVazia;  //***   Verificar se essa é a condição de retorno adequado pra um ponteiro de grafo NULL  ***//
	}
	
	tpVerticeGrafo* pVerticeAux=NULL;
	pVerticeAux = CriarElemento( pValor);
	if (pVerticeAux==NULL)
	{
		return GRA_CondRetFaltouMemoria; //a função só retorna OK ou Faltou memoria
	}
		
	if (LIS_InserirElementoApos(pGrafo->pOrigemGrafo, pVerticeAux) != LIS_CondRetOK)
	{
		return GRA_CondRetFaltouMemoria; //a função só retorna OK ou Faltou memoria
	}
	if (pGrafo->pVertice == NULL) //se for o primeiro elemento inserido ele se torna o corrente
	{
		
		pGrafo->pVertice = pVerticeAux;
		pGrafo->pArestas = pGrafo->pVertice->pVerticeArestas;
	}

	return GRA_CondRetOK;
 }
 /* Fim função: GRA  &InserirVertice */

 

 /***************************************************************************
 *
 *  Função: GRA  &Excluir Vertice
	
	exclui o corrente
 *  ****/
 GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo)
 {
	 if (pGrafo == NULL || pGrafo->pVertice == NULL)
	 {
		 return GRA_CondRetGrafoVazia;
	 }
	 LIS_IrInicioLista(pGrafo->pArestas);//indo p/ o inicio das arestas
	 tpVerticeGrafo *vizinho = LIS_ObterValor(pGrafo->pArestas);
	 if (vizinho != NULL)
	 {
		 EfetuaExclusaoAresta(pGrafo->pVertice,vizinho);

		 while (LIS_AvancarElementoCorrente(vizinho->pVerticeArestas,1)==LIS_CondRetOK)
		 {
			 vizinho= LIS_ObterValor(pGrafo->pArestas);
			 EfetuaExclusaoAresta(pGrafo->pVertice, vizinho);
		 }
		 
	 }
	 
	LIS_DestruirLista(pGrafo->pArestas);
	LIS_IrInicioLista(pGrafo->pOrigemGrafo);
	LIS_ProcurarValor(pGrafo->pOrigemGrafo, pGrafo->pVertice);
	LIS_ExcluirElemento(pGrafo->pOrigemGrafo);
	vizinho = LIS_ObterValor(pGrafo->pOrigemGrafo);
	if (vizinho != NULL)
	{
		pGrafo->pVertice = vizinho;
		pGrafo->pArestas = vizinho->pVerticeArestas;
	}
	else
	{
		pGrafo->pVertice = NULL;
		pGrafo->pArestas = NULL;
	}
	return GRA_CondRetOK;

 }

 /* Fim Função: GRA  &Excluir Vertice */


 /***************************************************************************
 *
 *  Função: GRA  &ExcluirAresta
	exclui do vertice corrente para o vertice recebido e do recebido para o corrente
 *  ****/
 GRA_tpCondRet GRA_ExcluirAresta(GRA_tppGrafo pGrafo, void * valor)
 {
	#ifdef _DEBUG
	 assert(pGrafo != NULL);
	#endif
	 if (pGrafo == NULL)
	 {
		 return GRA_CondRetGrafoVazia;  //***   Verificar se essa é a condição de retorno adequado pra um ponteiro de grafo NULL  ***//
	 }
	 GRA_tppGrafo gAux = pGrafo;
	 tpVerticeGrafo* vAux = GRA_ProcurarValor(gAux->pOrigemGrafo, valor);
	 GRA_tpCondRet ret = EfetuaExclusaoAresta(pGrafo->pVertice, vAux);
	 
	 return ret;
 }

 /* Fim Função: GRA  &ExcluirAresta */



 /***************************************************************************
 *
 *  Função: GRA  &IrVertice
 *  ****/
 GRA_tpCondRet GRA_IrVertice(GRA_tppGrafo pGrafo, void *valor)
 {

	#ifdef _DEBUG
		assert(pGrafo != NULL);
	#endif
	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoVazia;  //***   Verificar se essa é a condição de retorno adequado pra um ponteiro de grafo NULL  ***//
	}
	tpVerticeGrafo* aux;
	aux = GRA_ProcurarValor(pGrafo->pOrigemGrafo,valor);

	if (aux==NULL)
	 {
		return GRA_CondRetNaoAchou;
	 }	
	//pGrafo->pVertice = LIS_ObterValor(pGrafo->pOrigemGrafo);
	pGrafo->pVertice = aux;
	pGrafo->pArestas = pGrafo->pVertice->pVerticeArestas;

	return GRA_CondRetOK;
	

}

 /* Fim Função: GRA  &IrVertice */



 /***************************************************************************
 *
 *  Função: GRA  &ObterCorrente
 *  ****/

 void* GRA_ObterValorCorrente(GRA_tppGrafo pGrafo)
 {
	#ifdef _DEBUG
	 assert(pGrafo != NULL);
	#endif
	 if(pGrafo!=NULL && pGrafo->pVertice != NULL)
		return pGrafo->pVertice->valor;
	 return NULL;
 }

 /* Fim Função: GRA  &ObterCorrente */


 /***************************************************************************
 *
 *  Função: GRA  &CriarAresta
 *  ****/

 GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo, void* valor)
 {
	#ifdef _DEBUG
		 assert(pGrafo != NULL);
	#endif
	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoVazia;  //***   Verificar se essa é a condição de retorno adequado pra um ponteiro de grafo NULL  ***//
	}


	tpVerticeGrafo *aux = GRA_ProcurarValor(pGrafo->pOrigemGrafo, valor);

	 if (aux != NULL)
	 {	
		 LIS_tpCondRet retBusca;
		 LIS_IrInicioLista (pGrafo->pArestas);
		 retBusca = LIS_ProcurarValor(pGrafo->pArestas, aux);
		 if ( retBusca == LIS_CondRetNaoAchou || retBusca == LIS_CondRetListaVazia)
		 {
			 LIS_IrFinalLista(pGrafo->pArestas);
			 LIS_InserirElementoApos(pGrafo->pArestas, aux);
		 }
		 else
		 {
			 return GRA_CondRetOK;   /******************************* NOVA CONDIÇãO? aresta já existe ***********************************/
		 }
		 
		 LIS_IrInicioLista(aux->pVerticeArestas);
		 retBusca=LIS_ProcurarValor(aux->pVerticeArestas, pGrafo->pVertice);
		 if ( retBusca== LIS_CondRetNaoAchou || retBusca == LIS_CondRetListaVazia)
		 {
			 LIS_IrFinalLista(aux->pVerticeArestas);
			 LIS_InserirElementoApos(aux->pVerticeArestas, pGrafo->pVertice);
		 }
		 return GRA_CondRetOK;
	 }
	 return GRA_CondRetNaoAchou; //não achou vertice
 }

 /* Fim Função: GRA  &CriarAresta */

 

 int GRA_QntVertices(GRA_tppGrafo pGrafo)
 {
	 if (pGrafo == NULL || pGrafo->pOrigemGrafo == NULL)
	 {
		 return -1;					//* RETORNAR -1 QUANDO O PONTEIRO É NULL?????? ********************************//
	 }
	 return LIS_ObtemTamanho(pGrafo->pOrigemGrafo);
 }

 int GRA_QntArestas(GRA_tppGrafo pGrafo)
 {
	 if (pGrafo == NULL)
	 {
		 return -1;
	 }
	 return LIS_ObtemTamanho(pGrafo->pArestas);
 }


  /*****  Código das funções encapsuladas no módulo  *****/


  /***************************************************************************
  *
  *  Função: GRA  &ProcurarValor
  *  ****/

 static tpVerticeGrafo* GRA_ProcurarValor(LIS_tppLista pOrigemGrafo, void* pValor)
 {
#ifdef _DEBUG
	 assert(pOrigemGrafo != NULL);
#endif
	 if (pOrigemGrafo == NULL)
		 return NULL;
	 LIS_tppLista Lisaux = pOrigemGrafo;
	 tpVerticeGrafo *vertaux;
	 LIS_IrInicioLista(Lisaux);
	 vertaux = LIS_ObterValor(Lisaux);
	 if (vertaux == NULL)
	 {
		 return NULL;
	 }
	 if (vertaux->valor == pValor)
	 {
		 return vertaux;
	 }
	 while (LIS_AvancarElementoCorrente(Lisaux,1)==LIS_CondRetOK)
	 {
		 vertaux = LIS_ObterValor(Lisaux);
		 if (vertaux != NULL && vertaux->valor == pValor)
		 {
			 return vertaux;
		 }
	 }


	 return NULL;
 }

 /* Fim Função: GRA  &ProcurarValor */



  /******************************************************
  *
  *  Função: GRA  &LimparCabeca
  *  ****/

 static void LimparCabeca(GRA_tppGrafo pGrafo)
 {
	 if (pGrafo == NULL)
		 return;
	 pGrafo->pArestas = NULL;
	 pGrafo->pOrigemGrafo = NULL;
	 pGrafo->pVertice = NULL;
 }
 /* Fim função: GRA  &LimparCabeca */


 /*******************************************************
 *
 *  Função: GRA  &CriarElemento
 *  ****/
 static tpVerticeGrafo* CriarElemento( void* pValor)
 {
	 tpVerticeGrafo* pVertice = (tpVerticeGrafo *)malloc(sizeof(tpVerticeGrafo));
	 if (pVertice == NULL)
	 {
		 return NULL;
	 }
	 pVertice->valor = pValor;

	 //criando a lista de arestas com a função que nao desaloca os vertices
	 pVertice->pVerticeArestas = LIS_CriarLista(naoExclui);

	 return pVertice;

 }

 /* Fim Função: GRA  &CriarElemento */

 /*******************************************************
 *
 *  Função: GRA  &EfetuaExclusaoAresta
 *  ****/

 static GRA_tpCondRet EfetuaExclusaoAresta(tpVerticeGrafo* vertice1, tpVerticeGrafo* vertice2)
 {
	 if (vertice1 == NULL || vertice2 == NULL)
	 {
		 return GRA_CondRetGrafoVazia; //*************      MELHORAR ESSA CONDIÇÃO DE RETORNO, CRIAR UMA NOVA? COMO É INTERNA RETORNAR -1?? *******//
	 }
	 LIS_tpCondRet retorno;
	 LIS_IrInicioLista(vertice1->pVerticeArestas);
	 retorno = LIS_ProcurarValor(vertice1->pVerticeArestas, vertice2);
	 if (retorno == LIS_CondRetListaVazia)
	 {
		 return GRA_CondRetGrafoVazia;
	 }
	 if (retorno == LIS_CondRetNaoAchou)
	 {	//nao possui aresta, nao há o que deletar
		 return GRA_CondRetOK;
	 }
	 //agora com certeza achou o vertice
	 LIS_ExcluirElemento(vertice1->pVerticeArestas);//excluimos do primeiro

	 LIS_IrInicioLista(vertice2->pVerticeArestas);
	 retorno = LIS_ProcurarValor(vertice2->pVerticeArestas, vertice1);
	 if (retorno == LIS_CondRetNaoAchou)
	 {	//nao possui aresta, nao há o que deletar(aqui seria um erro na inclusao de arestas)
		 return GRA_CondRetOK;
	 }
	 LIS_ExcluirElemento(vertice2->pVerticeArestas);//excluimos no segundo	 

	 return GRA_CondRetOK;
 }

 /* Fim Função: GRA  &EfetuaExclusaoAresta */

 /*******************************************************
 *
 *  Função: GRA  &naoExclui
 *	função para criar a lista de arestas dos vertices sem que ao deletar alguma aresta
 *	o vertice não seja desalocado
 *  ****/
 static void naoExclui (void * pDado)
 {
	 return;
 }

 /* Fim Função: GRA  &naoExclui */