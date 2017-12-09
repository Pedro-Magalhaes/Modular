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
*	  4		Hfac & Pfm	   16/out/2017   Finalização do modulo; Testes concluidos; Melhor definição das funçoes no .H
*	  5       Pfm 		   06/dez/2017   adicionados: Instrumentação, função de verificação,de recuperação e deturpação
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

#ifdef _DEBUG
#include "CESPDIN.H"
#include "CONTA.H"
#include "GENERICO.H"
#endif // _DEBUG


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
#ifdef _DEBUG
	int idGrafo;
	/* identificador do grafo a qual pertence o vertice*/
	int numArestas;
	/* Numero de arestas do vértice*/
#endif


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

#ifdef _DEBUG
	LIS_tppLista _pOrigemGrafoRedundante;
	/* Cópia do Ponteiro para a origem do grafo */
	int numVertices;
	/* Redundancia para saber o numero de elementos */
	int idGrafo;
	/* identificador do grafo seus vertices devem ter o mesmo id*/

#endif

} GRA_tpGrafo;

#ifdef _DEBUG
enum GRA_tipoDeDado
{
	GRA_TipoCabeca,
	GRA_TipoVertice
};
#endif // DEBUG


/***** Protótipos das funções encapuladas no módulo *****/

/*static void LiberarElemento(LIS_tppLista   pLista,
	tpElemLista  * pElem);*/

static GRA_tpCondRet EfetuaExclusaoAresta(tpVerticeGrafo* vertice1, tpVerticeGrafo* vertice2);

static tpVerticeGrafo* GRA_ProcurarValor (LIS_tppLista pOrigemGrafo, void* pValor);

static tpVerticeGrafo* CriarElemento(void * pValor);

static void LimparCabeca(GRA_tppGrafo pGrafo);  /* por enquanto nao foi utilizada */

static void naoExclui(void * pDado);

#ifdef _DEBUG
GRA_tpCondRet GRA_DeturpaIDgrafo(GRA_tppGrafo pGrafo);
GRA_tpCondRet GRA_DeturpaCabeca (GRA_tppGrafo pGrafo);
GRA_tpCondRet GRA_VerificaCabeca(GRA_tppGrafo pGrafo);
GRA_tpCondRet GRA_VerificaVertice(GRA_tppGrafo pGrafo);
GRA_tpCondRet GRA_VerificaTamanho(GRA_tppGrafo pGrafo);
GRA_tpCondRet GRA_VerificaId(GRA_tppGrafo pGrafo, tpVerticeGrafo * vertice);
#endif
/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRA  &Criar grafo
*  ****/

GRA_tppGrafo GRA_CriarGrafo(void(*ExcluirValor)(void *pDado))
{
	GRA_tpGrafo * pGrafo = NULL;

#ifdef _DEBUG
	CNT_CONTAR("GRA_CriarGrafo");
#endif

	pGrafo = (GRA_tpGrafo *)malloc(sizeof(GRA_tpGrafo));
	if (pGrafo == NULL)
	{
		return NULL;
	}/*if*/
	pGrafo->ExcluirValor = ExcluirValor;
	pGrafo->pArestas = NULL;
	pGrafo->pOrigemGrafo = LIS_CriarLista(ExcluirValor); //criando uma lista vazia
	pGrafo->pVertice = NULL;
	
	#ifdef _DEBUG
	CED_DefinirTipoEspaco(pGrafo, GRA_TipoCabeca);
	pGrafo->_pOrigemGrafoRedundante = pGrafo->pOrigemGrafo;
	pGrafo->idGrafo = 0; //valor de exemplo, todos serao 0
	pGrafo->numVertices = 0; //vertices iniciais
	#endif

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
	 CNT_CONTAR("GRA_DestruirGrafo");
     assert( pGrafo != NULL ) ;
    #endif
	  if (pGrafo == NULL)
	  {//nada a ser feito
	  return;
	  }/*if*/
  
    GRA_EsvaziarGrafo( pGrafo );
	  	  
	  free(pGrafo);
	  
   }
   /* Fim função: GRA  &Destruir grafo */
  
/*************************************************************************
* 
* função: GRA  &Esvaziar grafo
*****/

 void GRA_EsvaziarGrafo(GRA_tppGrafo pGrafo)
 {


	 LIS_tppLista Elem;
	 tpVerticeGrafo * atual;
	 #ifdef _DEBUG
		CNT_CONTAR("GRA_EsvaziarGrafo");
		assert(pGrafo != NULL) ;
	#endif
	 if (pGrafo == NULL)
	 {
		 return;
	 }/*if*/

	 Elem = pGrafo->pOrigemGrafo;

	 LIS_IrInicioLista(Elem); //indo pro inicio da lista
	 atual = LIS_ObterValor(Elem);//pegando o primeiro valor
	 if (atual != NULL)
	 {//limpando a lista de arestas
		 LIS_DestruirLista(atual->pVerticeArestas); 
	 }/*if*/
	 else
	 {//nao há o que fazer, lista de vertices vazia
		 return;
	 }/*else*/	
	 	 	 
	 while (LIS_AvancarElementoCorrente(Elem, 1) == LIS_CondRetOK)
	 {		 
		 //limpa as outras listas de arestas se existirem		 
		 atual = LIS_ObterValor(Elem);
		 if(atual == NULL)
		 {
			 break;
		 }
		 LIS_IrInicioLista(atual->pVerticeArestas);
		 LIS_DestruirLista(atual->pVerticeArestas);	 
	 }/*while*/

	 //limpando a lista de vertices
	 LIS_EsvaziarLista(pGrafo->pOrigemGrafo);
	 pGrafo->pArestas = NULL;
	 pGrafo->pVertice = NULL;
	 #ifdef _DEBUG
	 	pGrafo->numVertices = 0;
	 #endif
	 

	 return;

 } /* Fim função: GRA  &Esvaziar grafo */

   /***************************************************************************
   *
   *  Função: GRA  &InserirVertice
   *  ****/

 GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo, void* pValor)
 {	
	tpVerticeGrafo* pVerticeAux = NULL;
	#ifdef _DEBUG
		CNT_CONTAR("GRA_InserirVertice");
		assert(pGrafo != NULL) ;
	#endif
	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNulo;  
	}
	
	if (GRA_ProcurarValor(pGrafo->pOrigemGrafo, pValor) != NULL)
	{//valor já existe
		return GRA_CondRetVerticeJaExiste; 
	}/*if*/

	pVerticeAux = CriarElemento( pValor);
	if (pVerticeAux==NULL)
	{
		return GRA_CondRetFaltouMemoria; 
	}/*if*/

	LIS_IrFinalLista(pGrafo->pOrigemGrafo);

	if (LIS_InserirElementoApos(pGrafo->pOrigemGrafo, pVerticeAux) != LIS_CondRetOK)
	{
		return GRA_CondRetFaltouMemoria; 
	}/*if*/

	if (pGrafo->pVertice == NULL) //se for o primeiro elemento inserido ele se torna o corrente
	{
		
		pGrafo->pVertice = pVerticeAux;
		pGrafo->pArestas = pGrafo->pVertice->pVerticeArestas;
	}/*if*/
	#ifdef _DEBUG
		pGrafo->numVertices++;
		pVerticeAux->idGrafo = pGrafo->idGrafo;
	#endif

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
	 tpVerticeGrafo *vizinho;

#ifdef _DEBUG
	 CNT_CONTAR("GRA_ExcluirVertice");
#endif // _DEBUG

	 
	 if (pGrafo == NULL || pGrafo->pVertice == NULL )
	 {
		 return GRA_CondRetGrafoNulo;
	 }/*if*/
	  vizinho = LIS_ObterValor(pGrafo->pArestas);
	 LIS_IrInicioLista(pGrafo->pArestas);//indo p/ o inicio das arestas
	 
	 if (vizinho != NULL)
	 {//percorre as arestas efetuando a exclusao mutua das arestas
		 EfetuaExclusaoAresta(pGrafo->pVertice,vizinho);

		 while (LIS_AvancarElementoCorrente(vizinho->pVerticeArestas,1)==LIS_CondRetOK)
		 {
			 vizinho = LIS_ObterValor(pGrafo->pArestas);
			 EfetuaExclusaoAresta(pGrafo->pVertice, vizinho);
		 }/*while*/
		 
	 }/*if*/
	 
	LIS_DestruirLista(pGrafo->pArestas);
	LIS_IrInicioLista(pGrafo->pOrigemGrafo);
	if (LIS_ProcurarValor(pGrafo->pOrigemGrafo, pGrafo->pVertice) == LIS_CondRetOK)
	{
		LIS_ExcluirElemento(pGrafo->pOrigemGrafo);
	}/*if*/
	vizinho = LIS_ObterValor(pGrafo->pOrigemGrafo);
	if (vizinho != NULL)
	{
		pGrafo->pVertice = vizinho;
		pGrafo->pArestas = vizinho->pVerticeArestas;
	}/*if*/
	else
	{
		pGrafo->pVertice = NULL;
		pGrafo->pArestas = NULL;
	}/*else*/
	#ifdef _DEBUG
		pGrafo->numVertices--;
	#endif
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
	 GRA_tppGrafo gAux = pGrafo;
	 tpVerticeGrafo* vAux;
	 GRA_tpCondRet CondRet;
#ifdef _DEBUG
	 CNT_CONTAR("GRA_ExcluirAresta");
#endif
	 if (pGrafo == NULL)
	 {
		 return GRA_CondRetGrafoNulo;  
	 }/*if*/
	 vAux = GRA_ProcurarValor(gAux->pOrigemGrafo, valor);
	 CondRet = EfetuaExclusaoAresta(pGrafo->pVertice, vAux);
#ifdef _DEBUG
		if (CondRet == GRA_CondRetOK)
		{
			if(vAux != pGrafo->pVertice)
			{
				vAux->numArestas--;
				pGrafo->pVertice->numArestas--;
			}
			else
			{
				pGrafo->pVertice->numArestas--;
			}
			
		}				
#endif
	 
	 
	 return CondRet;
 }

 /* Fim Função: GRA  &ExcluirAresta */



 /***************************************************************************
 *
 *  Função: GRA  &IrVertice
 *  ****/
 GRA_tpCondRet GRA_IrVertice(GRA_tppGrafo pGrafo, void *valor)
 {
	tpVerticeGrafo* vertAux;
	#ifdef _DEBUG
		CNT_CONTAR("GRA_IrVertice");
		assert(pGrafo != NULL);
	#endif
	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNulo;
	}/*if*/
	
	vertAux = GRA_ProcurarValor(pGrafo->pOrigemGrafo,valor);

	if (vertAux==NULL)
	 {
		return GRA_CondRetNaoAchou;
	 }/*if*/
	//pGrafo->pVertice = LIS_ObterValor(pGrafo->pOrigemGrafo);
	pGrafo->pVertice = vertAux;
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

	 CNT_CONTAR("GRA_ObterValorCorrente");
	 assert(pGrafo != NULL);
	#endif
	 if (pGrafo != NULL && pGrafo->pVertice != NULL)
	 {
		 return pGrafo->pVertice->valor;
	 }/*if*/
		
	 return NULL;
 }

 /* Fim Função: GRA  &ObterCorrente */


 /***************************************************************************
 *
 *  Função: GRA  &CriarAresta
 *  ****/

 GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo, void* valor)
 {
	

	tpVerticeGrafo *aux;
#ifdef _DEBUG
	CNT_CONTAR("GRA_CriarAresta");
	assert(pGrafo != NULL);
#endif
	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNulo; 
	}/*if*/
	aux = GRA_ProcurarValor(pGrafo->pOrigemGrafo, valor);
	 if (aux != NULL)
	 {	
		 LIS_tpCondRet retBusca;
		 LIS_IrInicioLista (pGrafo->pArestas);
		 retBusca = LIS_ProcurarValor(pGrafo->pArestas, aux);
		 if ( retBusca == LIS_CondRetNaoAchou || retBusca == LIS_CondRetListaVazia)
		 {
			 LIS_IrFinalLista(pGrafo->pArestas);
			 if (LIS_InserirElementoApos(pGrafo->pArestas, aux) == LIS_CondRetFaltouMemoria)
			 {
				 return GRA_CondRetFaltouMemoria;
			 }/*if*/
		 }/*if*/
		 else
		 {
			 return GRA_CondRetVerticeJaExiste;  
		 }/*else*/
		 
		 LIS_IrInicioLista(aux->pVerticeArestas);
		 retBusca=LIS_ProcurarValor(aux->pVerticeArestas, pGrafo->pVertice);
		 if ( retBusca== LIS_CondRetNaoAchou || retBusca == LIS_CondRetListaVazia)
		 {
			 LIS_IrFinalLista(aux->pVerticeArestas);
			 if (LIS_InserirElementoApos(aux->pVerticeArestas, pGrafo->pVertice) == LIS_CondRetFaltouMemoria)
			 {
				 return GRA_CondRetFaltouMemoria;
			 }/*if*/
			 #ifdef _DEBUG
			 	if(aux == pGrafo->pVertice)
				 {
					 aux->numArestas++;
				 }
				 else
				 {
					aux->numArestas++;
					pGrafo->pVertice->numArestas++;
				 }
				
			#endif			 
		 }/*if*/
		 return GRA_CondRetOK;
	 }
	 return GRA_CondRetNaoAchou; //não achou vertice
 }

 /* Fim Função: GRA  &CriarAresta */

   /***************************************************************************
  *
  *  Função: GRA  &QntVertices
  *  ****/

 int GRA_QntVertices(GRA_tppGrafo pGrafo)
 {
#ifdef _DEBUG
	 CNT_CONTAR("GRA_QntVertices");
#endif
	 if (pGrafo == NULL || pGrafo->pOrigemGrafo == NULL)
	 {
		 return -1;					
	 }/*if*/
	 return LIS_ObtemTamanho(pGrafo->pOrigemGrafo); 
 }
 /* Fim Função: GRA  &QntVertices */


 /***************************************************************************
 *
 *  Função: GRA  &QntArestas
 *  ****/

 int GRA_QntArestas(GRA_tppGrafo pGrafo)
 {
#ifdef _DEBUG
	 CNT_CONTAR("GRA_QntArestas");
#endif
	 if (pGrafo == NULL)
	 {
		 return -1;					
	 }/*if*/
	 return LIS_ObtemTamanho(pGrafo->pArestas);
 }

 /* Fim Função: GRA  &QntArestas */

 /***************************************************************************
 *
 *  Função: GRA  &AvancarElementoCorrente
 *  ****/
 GRA_tpCondRet GRA_AvancarElementoCorrente( GRA_tppGrafo pGrafo ,
                                              int numElem ) 
{
	LIS_tpCondRet retorno;
#ifdef _DEBUG
	CNT_CONTAR("GRA_AvancarElementoCorrente");
#endif
	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNulo;
	}/* if */
	retorno = LIS_AvancarElementoCorrente (pGrafo->pOrigemGrafo,numElem);

	switch (retorno)
	{
	case LIS_CondRetFimLista:
		return GRA_CondRetFimGrafo;
	case LIS_CondRetListaVazia:
		return GRA_CondRetGrafoVazia;
	default:
		pGrafo->pVertice = LIS_ObterValor(pGrafo->pOrigemGrafo);
		pGrafo->pArestas = pGrafo->pVertice->pVerticeArestas;
		return GRA_CondRetOK;
		break;
	}/* switch */
}											  
 /* Fim Função: GRA  &AvancarElementoCorrente */
 /***************************************************************************
 *
 *  Função: GRA  &IrInicioOrigens
 *  ****/
 void GRA_IrInicioOrigens( GRA_tppGrafo pGrafo )
 {
#ifdef _DEBUG
	CNT_CONTAR("GRA_IrInicioOrigens");
	assert(pGrafo != NULL);
#endif

	LIS_IrInicioLista(pGrafo->pOrigemGrafo);
	pGrafo->pVertice = LIS_ObterValor(pGrafo->pOrigemGrafo);
	if (pGrafo->pVertice != NULL)
	{
		pGrafo->pArestas = pGrafo->pVertice->pVerticeArestas;
	}/* if */
 }
 /* Fim Função: GRA  &IrInicioOrigens */
 /***************************************************************************
 *
 *  Função: GRA  &IrFinalOrigens
 *  ****/
void GRA_IrFinalOrigens( GRA_tppGrafo pGrafo )
{
#ifdef _DEBUG
	CNT_CONTAR("GRA_IrFinalOrigens");
	assert(pGrafo != NULL);
#endif

	LIS_IrFinalLista(pGrafo->pOrigemGrafo);
	pGrafo->pVertice = LIS_ObterValor(pGrafo->pOrigemGrafo);
	if (pGrafo->pVertice != NULL)
	{
		pGrafo->pArestas = pGrafo->pVertice->pVerticeArestas;
	}/* if */
}
 /* Fim Função: GRA  &IrFinalOrigens */

 /***************************************************************************
 *
 *  Função: GRA  &GRA_AvancarElementoAresta
 *  ****/
GRA_tpCondRet GRA_AvancarElementoAresta( GRA_tppGrafo pGrafo ,
                                              int numElem ) 
{
		
	LIS_tpCondRet retorno;
	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNulo;
	}/* if */
	retorno = LIS_AvancarElementoCorrente (pGrafo->pArestas ,numElem);

	switch (retorno)
	{
	case LIS_CondRetFimLista:
		return GRA_CondRetFimGrafo;
	case LIS_CondRetListaVazia:
		return GRA_CondRetGrafoVazia;
	default:
		return GRA_CondRetOK;
		break;
	}/* switch */
	
}											  
 /* Fim Função: GRA  &GRA_AvancarElementoAresta */

 /***************************************************************************
 *
 *  Função: GRA  &GRA_ObterValorAresta
 *  ****/
void* GRA_ObterValorAresta(GRA_tppGrafo pGrafo)
{
	tpVerticeGrafo * aux;
	if (pGrafo == NULL)
	{
		return NULL;
	}/* if */
	
	aux = LIS_ObterValor(pGrafo->pArestas);
	if (aux == NULL)
	{
		return NULL;
	}
	return aux->valor;
}
 /* Fim Função: GRA  &GRA_ObterValorAresta */
 /***************************************************************************
 *
 *  Função: GRA  &IrInicioArestas
 *  ****/
 void GRA_IrInicioArestas( GRA_tppGrafo pGrafo )
 {
	 if (pGrafo == NULL)
	{
		return;
	}/* if */

	LIS_IrInicioLista(pGrafo->pArestas);
 }

 /* Fim Função: GRA  &IrInicioArestas */
 /***************************************************************************
 *
 *  Função: GRA  &GRA_IrFinalArestas
 *  ****/
void GRA_IrFinalArestas( GRA_tppGrafo pGrafo )
{
	 if (pGrafo == NULL)
	{
		return;
	}/* if */
	LIS_IrFinalLista(pGrafo->pArestas);
}
 /* Fim Função: GRA  &GRA_IrFinalArestas */
#ifdef _DEBUG
/***************************************************************************
 * 	FUNÇÕES DE DEBUG ENCAPSULADAS PELO MODULO
 *  ****/ 
/***************************************************************************
 *  Função: GRA  &DeturpaGrafo
 * Faz deturpações no grafo
 *  ****/
GRA_tpCondRet GRA_DeturpaGrafo(GRA_tppGrafo pGrafo,int opcao)
{
	switch (opcao)
	{
		case 0:
			return GRA_DeturpaCabeca(pGrafo);
			break;
		case 1:
			return GRA_DeturpaIDgrafo(pGrafo);
			break;		
	default:
			return GRA_CondRetOK;
			break;
	}/* switch */
}

/***************************************************************************
 *  Função: GRA  &Verificadora
 * Torna o ponteiro pra cabeça do grafo null
 *  ****/
GRA_tpCondRet GRA_Verificadora(GRA_tppGrafo pGrafo)
{
	GRA_tpCondRet retorno;
	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNulo;
	}/* if */

	/* Faz duas verificações se o tipo da cabeça está correto e se a origem foi perdida,
		no segundo caso vamos usar a redundancia para recupera-la
	 */
	retorno = GRA_VerificaCabeca(pGrafo);
	if (retorno != GRA_CondRetOK)
	{
		if ( retorno == GRA_CondRetOrigemPerdida )
		{//vou usar a função de recuperação
			GRA_RecuperaCabeca(pGrafo);
		}/* if */
		else
		{
			return retorno;
		}/* else */
		
	}/* if */
	
	/* Percorre todos os vertices do grafo verificando:
 * 		1- Se o tipo alocado está correto 
 * 		2- Se o numero de arestas está correto	
 * 		3- Se o id dos vertices é o mesmo do grafo a que pertence */
	retorno = GRA_VerificaVertice(pGrafo);
	
	if (retorno != GRA_CondRetOK)
	{
		return retorno;
	}/* if */

	return GRA_CondRetOK;
}
/***************************************************************************
 *  Função: GRA  &Recupera Cabeca
 *  		Função corretora
 * Utiliza a estrutura auxiliar para recuperar o ponteiro pra cabeça
 *  ****/
GRA_tpCondRet GRA_RecuperaCabeca (GRA_tppGrafo pGrafo)
{
	if (pGrafo == NULL || pGrafo->_pOrigemGrafoRedundante == NULL )
	{
		return GRA_CondRetGrafoNulo;		
	} /* if */
	pGrafo->pOrigemGrafo = pGrafo->_pOrigemGrafoRedundante;
	return GRA_CondRetOK;

}

/***************************************************************************
 * 	FUNÇÕES DE DEBUG ENCAPSULADAS PELO MODULO
 *  
 /***************************************************************************
 *  Função: GRA  &Deturpa Cabeca
 * Torna o ponteiro pra cabeça do grafo null
 *  ****/

GRA_tpCondRet GRA_DeturpaCabeca (GRA_tppGrafo pGrafo)
{
	if(pGrafo == NULL)
	{
		return GRA_CondRetGrafoNulo;
	}/* if */
	pGrafo->pOrigemGrafo = NULL;
	return GRA_CondRetOK;
}

/* Fim Função: GRA  &Deturpa Cabeca */
 /***************************************************************************
 *  Função: GRA  &DeturpaIDgrafo
 * Torna a variavel de verificação ID do grafo diferente da que era antes
 *  ****/
GRA_tpCondRet GRA_DeturpaIDgrafo(GRA_tppGrafo pGrafo)
{
	if (pGrafo != NULL)
	{
		pGrafo->idGrafo++;
		return GRA_CondRetOK;
	}/* if */
	return GRA_CondRetGrafoNulo;
}

 /***************************************************************************
 *  Função: GRA  &Verifica Cabeca
 * Verifica se o tipo definido na alocação da memoria da cabeça do grafo está correto
 *  ****/

GRA_tpCondRet GRA_VerificaCabeca(GRA_tppGrafo pGrafo)
{
	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNulo;
	}/* if */
	if( TST_CompararInt(GRA_TipoCabeca,
		CED_ObterTipoEspaco(pGrafo),
		"Tipo cabeça errado") != TST_CondOK)
			{
				return GRA_CondRetTipoIncorreto;
			}
	if(pGrafo->pOrigemGrafo == NULL && pGrafo->_pOrigemGrafoRedundante != NULL)
	{
		return GRA_CondRetOrigemPerdida;
	}
	return GRA_CondRetOK;	
}

 /***************************************************************************
 *  Função: GRA  &Verifica Vertice
 * Percorre todos os vertices do grafo verificando:
 * 		1- Se o tipo alocado está correto 
 * 		2- Se o numero de arestas está correto	
 * 		3- Se o id dos vertices é o mesmo do grafo a que pertence
 * Casos de retorno:
 * 		1- GRA_CondRetTipoIncorreto
 * 		2- GRA_CondRetNumeroArestaIncorreto
 * 		3- GRA_CondRetVerticeNaoPertenceGrafo
 * 	GRA_CondRetGrafoNulo - ponteiro do grafo nulo
 *  GRA_CondRetGrafoVazia - não há elementos no grafo
 *   ****/
GRA_tpCondRet GRA_VerificaVertice(GRA_tppGrafo pGrafo)
{
	tpVerticeGrafo * auxiliar;
	tpVerticeGrafo * verticeInicial;
	GRA_tpCondRet retorno;

	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNulo;
	}/* if */

	verticeInicial = LIS_ObterValor(pGrafo->pOrigemGrafo);

	if( verticeInicial == NULL )
	{
		return GRA_CondRetGrafoVazia;
	}/* if */
	LIS_IrInicioLista(pGrafo->pOrigemGrafo);
	do{
		auxiliar = LIS_ObterValor(pGrafo->pOrigemGrafo);

		if(auxiliar == NULL)
		{//não poderia entrar aqui por causa da assertiva do verticeInicial
			return GRA_CondRetGrafoVazia;
		}/* if */

		if(TST_CompararInt(GRA_TipoVertice,
			CED_ObterTipoEspaco(auxiliar),
			"Tipo vertice errado") != TST_CondOK)
			{
				return GRA_CondRetTipoIncorreto;
			}/* if */
		if( TST_CompararInt(auxiliar->numArestas,
		LIS_ObtemTamanho(auxiliar->pVerticeArestas),
		"Numero de arestas incompativel") != TST_CondOK)		
		{
			return GRA_CondRetNumeroArestaIncorreto;
		}
		retorno = GRA_VerificaId(pGrafo,auxiliar);
		if ( retorno != GRA_CondRetOK)
		{//pode retornar grafo null, grafo vazio ou vertice nao pertence ao grafo
			return retorno;
		}
	}while(LIS_AvancarElementoCorrente(pGrafo->pOrigemGrafo,1) == LIS_CondRetOK);

	if( auxiliar != verticeInicial ) //recuperando o vertice corrente
	{
		LIS_ProcurarValor(pGrafo->pOrigemGrafo,verticeInicial);
	}		
	return GRA_CondRetOK;	
}

 /***************************************************************************
 *  Função: GRA  &Verifica Tamanho
 * 		Verifica se a quantidade de elementos na lista é o mesmo que o numero de 
 * 		elementos que foram alocados
 *  ****/

GRA_tpCondRet GRA_VerificaTamanho(GRA_tppGrafo pGrafo)
{
	
	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNulo;
	}/* if */

	if (pGrafo->pOrigemGrafo == NULL)
	{
		return GRA_CondRetGrafoVazia;
	}/* if */
	if( TST_CompararInt(LIS_ObtemTamanho(pGrafo->pOrigemGrafo),
		pGrafo->numVertices,
		"Numero de vertices do grafo incompativel") != TST_CondOK)
	{
		return GRA_CondRetNumeroVerticeIncorreto;
	}/* if */

	return GRA_CondRetOK;
}

/***************************************************************************
 *  Função: GRA  &Verifica Id
 * 		Verifica se o id do vertice é o mesmo id do grafo que o contém
 * 		
 *  ****/
GRA_tpCondRet GRA_VerificaId(GRA_tppGrafo pGrafo , tpVerticeGrafo * vertice)
{
	if (pGrafo == NULL)
	{// não deve ocorerr pois a função que chama já trata isso
		return GRA_CondRetGrafoNulo;
	}/* if */
	if (vertice == NULL)
	{//se recebi nulo significa que a lista de origens estava vazia
		GRA_CondRetGrafoVazia;
	}/* if */
	
	if (pGrafo->idGrafo != vertice->idGrafo)
	{
		return GRA_CondRetVerticeNaoPertenceGrafo;
	}
	return GRA_CondRetOK;
}

#endif




 /***** ******************** Código das funções encapsuladas no módulo  ****************************/

  /***************************************************************************
  *
  $FC Função: GRA  &ProcurarValor
  *
  *  $ED Descrição da função
  *     Busca por um elemento com determinado endereço do valor passado na lista de vertices ou de arestas,
  *		retornando esse valor já transformardo em tipo vertice se ele existir, retorna null do contrario
  *
  *  $EP Parâmetros
  *     pOrigemGrafo  - Origem da lista de vertices onde deseja-se buscar (pode ser a de arestas tambem)
  *
  *  $FV Valor retornado
  *     Se encontrado, retorna o endereço para o elemento
  *
  *     Se não encontrar o elemento ou se o ponteiro para a lista pe NULL, retorna NULL.
  *     Não será dada mais informação quanto ao problema ocorrido.
  *
  *  ****/

 static tpVerticeGrafo* GRA_ProcurarValor(LIS_tppLista pOrigemGrafo, void* pValor)
 {

	 LIS_tppLista Lisaux = pOrigemGrafo;
	 tpVerticeGrafo *vertaux;

	#ifdef _DEBUG
	 assert(pOrigemGrafo != NULL);
	#endif
	 if (pOrigemGrafo == NULL)
	 {
		 return NULL;
	 }/*if*/
		 

	 LIS_IrInicioLista(Lisaux);
	 vertaux = LIS_ObterValor(Lisaux);
	 if (vertaux == NULL)
	 {
		 return NULL;
	 }/*if*/
	 if (vertaux->valor == pValor)
	 {
		 return vertaux;
	 }/*if*/
	 while (LIS_AvancarElementoCorrente(Lisaux,1)==LIS_CondRetOK)
	 {
		 vertaux = LIS_ObterValor(Lisaux);
		 if (vertaux != NULL && vertaux->valor == pValor)
		 {
			 return vertaux;
		 }/*if*/
	 }/*while*/


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
#ifdef _DEBUG
	 CNT_CONTAR("GRA_CriarElemento");
#endif
	 if (pVertice == NULL)
	 {
		 return NULL;
	 }/*if*/
	 pVertice->valor = pValor;

#ifdef _DEBUG
	 CED_DefinirTipoEspaco(pVertice, GRA_TipoVertice);	
	 pVertice->numArestas=0; 
#endif

	 //criando a lista de arestas com a função que nao desaloca os vertices(ao exluir arestas nao queremos desalocar vertices) 
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
	 LIS_tpCondRet retorno;
	 if (vertice1 == NULL || vertice2 == NULL)
	 {
		 return GRA_CondRetGrafoNulo; 
	 }/*if*/
	 
	 LIS_IrInicioLista(vertice1->pVerticeArestas);
	 retorno = LIS_ProcurarValor(vertice1->pVerticeArestas, vertice2);
	 if (retorno == LIS_CondRetListaVazia)
	 {
		 return GRA_CondRetGrafoVazia;
	 }/*if*/
	 if (retorno == LIS_CondRetNaoAchou)
	 {	//nao possui aresta, nao há o que deletar
		 return GRA_CondRetOK;
	 }/*if*/

	 //agora com certeza achou o vertice
	 LIS_ExcluirElemento(vertice1->pVerticeArestas);//excluimos do primeiro

	 LIS_IrInicioLista(vertice2->pVerticeArestas);
	 retorno = LIS_ProcurarValor(vertice2->pVerticeArestas, vertice1);
	 if (retorno == LIS_CondRetNaoAchou)
	 {	//nao possui aresta, nao há o que deletar(aqui seria um erro na inclusao de arestas)
		 return GRA_CondRetOK;
	 }/*if*/
	 LIS_ExcluirElemento(vertice2->pVerticeArestas);//excluimos no segundo	 

	 return GRA_CondRetOK;
 }

 /* Fim Função: GRA  &EfetuaExclusaoAresta */

 /*******************************************************
 *
 *  Função: GRA  &naoExclui
 *	função para criar a lista de arestas dos vertices sem que ao deletar alguma aresta
 *	o vertice seja desalocado
 *  ****/
 static void naoExclui (void * pDado)
 {
	 return;
 }

/* Fim Função: GRA  &naoExclui */

