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
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       Hfac   10/out/2017 início desenvolvimento
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

	void * pVerticeArestas;
	/* Ponteiro para a listacom as arestas do vertice  */

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

	LIS_tppLista * pOrigemGrafo;
	/* Ponteiro para a origem do grafo */

	tpVerticeGrafo * pVertice;
	/* Ponteiro para o vertice corrente do grafo */

	LIS_tppLista * pArestas;
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
   *  Função: GRA  &Esvaziar grafo
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