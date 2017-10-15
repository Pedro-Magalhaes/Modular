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

static GRA_tpCondRet CriarElemento(tpVerticeGrafo * pVertice, void * pValor);

static void LimparCabeca(GRA_tppGrafo pGrafo);

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
		return GRA_CondRetFaltouMemoria;
	}
	pGrafo->pArestas = NULL;
	pGrafo->pOrigemGrafo = NULL;
	pGrafo->pVertice = NULL;
	pGrafo->ExcluirValor = ExcluirValor;


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
	 
	 GRA_tpGrafo * atual;

#ifdef _DEBUG
	 assert(pGrafo != NULL);
#endif
	 if (pGrafo != NULL)
	 {
		 return GRA_CondRetGrafoVazia;
	 }
	 atual = LIS_ObterValor(Elem);//limpa primeira lista de arestas
	 LIS_EsvaziarLista(atual->pArestas);
	 	  /////////////////////////////////////////////				COLOCAR A LISTA NO INICIO ANTES DE DELETAR!!! (VERIFICAR OUTRAS FUNÇÕES TBM) ////////////////////////////////////////////
	 while (LIS_AvancarElementoCorrente(Elem, 1) != LIS_CondRetFimLista)
	 {
		 //limpa as outras listas de arestas se existirem
		 atual = LIS_ObterValor(Elem);
		 LIS_EsvaziarLista(atual->pArestas);
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

 GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo, void * pValor)
 {
	#ifdef _DEBUG
		 assert(pGrafo != NULL);
	#endif
	
	tpVerticeGrafo * pVerticeAux = NULL;
	if (CriarElemento(pVerticeAux, pValor) != GRA_CondRetOK)
	{
		return GRA_CondRetFaltouMemoria; //a função só retorna OK ou Faltou memoria
	}
	if (LIS_InserirElementoApos(pGrafo->pOrigemGrafo, pVerticeAux) != LIS_CondRetOK)
	{
		return GRA_CondRetFaltouMemoria; //a função só retorna OK ou Faltou memoria
	}
	if (pGrafo->pVertice == NULL) 
	{
		pGrafo->pVertice = pVerticeAux;
		pGrafo->pArestas = pGrafo->pVertice->pVerticeArestas;
	}

	return GRA_CondRetOK;
 }
 /* Fim função: GRA  &InserirVertice */


   /***************************************************************************
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

 /***************************************************************************
 *
 *  Função: GRA  &CriarElemento
 *  ****/
 static GRA_tpCondRet CriarElemento(tpVerticeGrafo * pVertice, void * pValor)
 {
	 pVertice = (tpVerticeGrafo *)malloc(sizeof(tpVerticeGrafo));
	 if (pVertice == NULL)
	 {
		 return GRA_CondRetFaltouMemoria;
	 }
	 pVertice->valor = pValor;
	 
	 pVertice->pVerticeArestas = NULL;

	 return GRA_CondRetOK;

 }

 /* Fim Função: GRA  &CriarElemento */

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

	 //Percorre a lista de aresta do vertice a ser excluido
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

 void * GRA_ObterValorCorrente(GRA_tppGrafo pGrafo)
 {
	 return pGrafo->pVertice->valor;
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


 void naoExclui (void * pDado)
 {
	 return;
 }