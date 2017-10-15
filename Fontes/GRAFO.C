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

static tpVerticeGrafo* GRA_ProcurarValor(GRA_tppGrafo pGrafo,
	void* pValor);

static tpVerticeGrafo* CriarElemento(void * pValor);

static void LimparCabeca(GRA_tppGrafo pGrafo);

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

      GRA_EsvaziarGrafo( pGrafo ) ;

      free( pGrafo ) ;

   } /* Fim função: GRA  &Destruir grafo */

	 /***************************************************************************
	 *
	 *  Função: GRA  &Esvaziar grafo
	 *  ****/

 void GRA_EsvaziarGrafo(GRA_tppGrafo pGrafo)
 {

	 LIS_tppLista * Elem= pGrafo->pOrigemGrafo;
	 
	 tpVerticeGrafo * atual;
	 

#ifdef _DEBUG
	 assert(pGrafo != NULL);
#endif
	 if (pGrafo != NULL)
	 {
		 return GRA_CondRetGrafoVazia;
	 }
	 LIS_IrInicioLista(Elem); //indo pro inicio da lista
	 atual = LIS_ObterValor(Elem);//pegando o primeiro valor
	 LIS_DestruirLista(atual->pVerticeArestas); //DECIDIR SE QUEREMOS DELETAR TODOS OS NÓS OU NÃO E DEIXAR A LISTA VAZIA  (pra manter os vertices é só esvaziar suas listas de arestas ao invés de destruir)
	 	 	 
	 while (LIS_AvancarElementoCorrente(Elem, 1) != LIS_CondRetFimLista)
	 {
		 //limpa as outras listas de arestas se existirem		 
		 atual = LIS_ObterValor(Elem);
		 LIS_IrInicioLista(atual->pVerticeArestas);
		 LIS_DestruirLista(atual->pVerticeArestas);
	 }
	 //limpa a lista de vertices
	 LIS_EsvaziarLista(pGrafo->pOrigemGrafo);
	 

	 LimparCabeca(pGrafo);

	 return GRA_CondRetOK;

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
	GRA_tpCondRet retorno;
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
 *  ****/
 GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo)
 {
	 if (pGrafo == NULL || pGrafo->pVertice == NULL)
	 {
		 return GRA_CondRetGrafoVazia;
	 }

	 //Percorre a lista de aresta do vertice a ser excluido (lista do corrente)
	 while (LIS_AvancarElementoCorrente(pGrafo->pArestas, 1) != LIS_CondRetFimLista)
	 {
		 tpVerticeGrafo *aux =(tpVerticeGrafo*) LIS_ObterValor(pGrafo->pArestas);
		
		 //Percorre a lista de arestas dos elementos que tem o vertice a ser excluido como aresta
		 while (LIS_AvancarElementoCorrente(aux->pVerticeArestas, 1) != LIS_CondRetFimLista)
		 {
			 if (aux->valor == pGrafo->pVertice->valor)
			 {
				 LIS_ExcluirElemento(aux->pVerticeArestas);
			 }
		 }
	 }

	 //Eliminar o vertice corrente
	 if (LIS_ExcluirElemento(pGrafo->pOrigemGrafo) == LIS_CondRetListaVazia)
	 {
		 return GRA_CondRetGrafoVazia;
	 }
	 LIS_DestruirLista(pGrafo->pArestas);
	 pGrafo->ExcluirValor(pGrafo->pVertice->valor);
	 free(pGrafo->pVertice);
	 
	 //atualizando o corrente
	 pGrafo->pVertice = LIS_ObterValor(pGrafo->pOrigemGrafo);
	 if (pGrafo->pVertice != NULL)
	 {
		 pGrafo->pArestas = pGrafo->pVertice->pVerticeArestas;
	 }
	 else
	 {
		 pGrafo->pArestas = NULL;
	 }


	 return GRA_CondRetOK;
 }

 /* Fim Função: GRA  &Excluir Vertice */


 /***************************************************************************
 *
 *  Função: GRA  &ExcluirAresta
 *  ****/
 GRA_tpCondRet GRA_ExcluirAresta(GRA_tppGrafo pGrafo, void * vertice)
 {
	#ifdef _DEBUG
	 assert(pGrafo != NULL);
	#endif

	 tpVerticeGrafo * aux = pGrafo->pVertice; //vertice corrente
	 GRA_tpCondRet retorno = GRA_IrVertice(pGrafo, vertice);//corrente é alterado para vertice procurado se for encontrado
	 if (retorno == GRA_CondRetGrafoVazia)
	 {
		 return retorno;
	 }
	 if (retorno==GRA_CondRetNaoAchou)
	 {	//nao possui aresta, nao há o que deletar
		 return GRA_CondRetOK;
	 }
	 //agora com certeza achou o vertice
	 LIS_ProcurarValor(aux->pVerticeArestas, pGrafo->pVertice);
	 LIS_ExcluirElemento(aux->pVerticeArestas);//excluimos no primeiro
	 
	 LIS_ProcurarValor(pGrafo->pArestas, aux);
	 LIS_ExcluirElemento(pGrafo->pArestas);//excluimos do segundo

	 return GRA_CondRetOK;
 }

 /* Fim Função: GRA  &ExcluirAresta */



 /***************************************************************************
 *
 *  Função: GRA  &IrVertice
 *  ****/
 GRA_tpCondRet GRA_IrVertice(GRA_tppGrafo pGrafo, void * vertice)
 {

	#ifdef _DEBUG
		assert(pGrafo != NULL);
	#endif
	tpVerticeGrafo* aux;
	LIS_tpCondRet retorno = LIS_ProcurarValor(pGrafo->pOrigemGrafo, vertice);

	if (retorno==LIS_CondRetListaVazia)
	 {
		 return GRA_CondRetGrafoVazia;
	 }
	if (retorno == LIS_CondRetOK)
	{
		pGrafo->pVertice = LIS_ObterValor(pGrafo->pOrigemGrafo);
		pGrafo->pArestas = pGrafo->pVertice->pVerticeArestas;
		return GRA_CondRetOK;
	}
	return GRA_CondRetNaoAchou;

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

 GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo,
	 void* vertice)
 {
	#ifdef _DEBUG
		 assert(pGrafo != NULL);
	#endif
	 tpVerticeGrafo* aux= GRA_ObterValorCorrente(pGrafo);
	 GRA_tpCondRet retorno = GRA_IrVertice(pGrafo, vertice);
	 if (retorno == GRA_CondRetOK)
	 {		 
		 LIS_InserirElementoApos(pGrafo->pArestas, aux);
		 LIS_InserirElementoApos(aux->pVerticeArestas, pGrafo->pVertice);
	 }
	 GRA_IrVertice(pGrafo, aux->valor);
	 return GRA_CondRetOK;
 }

 /* Fim Função: GRA  &CriarAresta */

 

  /*****  Código das funções encapsuladas no módulo  *****/


  /***************************************************************************
  *
  *  Função: GRA  &ProcurarValor
  *  ****/

 static tpVerticeGrafo* GRA_ProcurarValor(GRA_tppGrafo pGrafo,
	 void* pValor)
 {
#ifdef _DEBUG
	 assert(pGrafo != NULL);
#endif
	 if (pGrafo == NULL)
		 return GRA_CondRetGrafoVazia;
	 LIS_tppLista Lisaux = pGrafo;
	 tpVerticeGrafo *vertaux;
	 LIS_IrInicioLista(Lisaux);
	 vertaux = LIS_ObterValor(Lisaux);
	 if (vertaux == NULL)
	 {
		 return GRA_CondRetGrafoVazia;
	 }
	 if (vertaux->valor == pValor)
	 {
		 return vertaux;
	 }


	 return GRA_CondRetNaoAchou;
 }

 /* Fim Função: GRA  &ProcurarValor */



  /******************************************************
  *
  *  Função: GRA  &LimparCabeca
  *  ****/

 static void LimparCabeca(GRA_tppGrafo pGrafo)
 {
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
 *  Função: GRA  &naoExclui
 *  ****/
 static void naoExclui (void * pDado)
 {
	 return;
 }

 /* Fim Função: GRA  &naoExclui */