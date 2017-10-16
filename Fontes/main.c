#include "GRAFO.H"
#include "LISTA.H"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void excluir(void* dado);

int main(void)
{
	//LIS_tppLista lis = LIS_CriarLista(excluir);
	//int a = 0, b = 1, c = 2, d = 3, e = 4;
	//LIS_tpCondRet retorno;
	//LIS_InserirElementoAntes(lis, &a);
	//LIS_InserirElementoAntes(lis, &b);
	//LIS_InserirElementoAntes(lis, &c);
	//LIS_InserirElementoAntes(lis, &d);
	//retorno = LIS_InserirElementoAntes(lis, &e);
	//if (retorno == LIS_CondRetOK)
	//	printf("inseriu elemento ok\n");
	//int* obtem1 = LIS_ObterValor(lis);
	//if (obtem1 == NULL)
	//{
	//	printf("deu ruim obtem 1");
	//}
	//retorno=LIS_AvancarElementoCorrente(lis, 1);
	//int* obtem2 = LIS_ObterValor(lis);
	//if (obtem2 == NULL)
	//{
	//	printf("deu ruim obtem 2");
	//}
	//printf("obtem 1 = %d , obtem2 = %d \n", *obtem1, *obtem2);

	//if (retorno == LIS_CondRetFimLista)
	//{
	//	int *aux = LIS_ObterValor(lis);
	//	int tam = LIS_ObtemTamanho(lis);
	//	printf("fim da lista, ultimo valor= %d tam=%d \n",*aux,tam);
	//}
	//	
	//LIS_IrInicioLista(lis); //sem isso ele nao acha o elemento
	//retorno = LIS_ProcurarValor(lis, &c);
	//if (retorno == LIS_CondRetOK)
	//{
	//	int *aux = LIS_ObterValor(lis);
	//	printf("valor retornado == %d \n", *aux);
	//}
	//else
	//	printf("nao encontrou c\n");


	//printf("\n******************************** \n *****************************\n ***************\n ***********\n *******\n");

	//LIS_IrInicioLista(lis);
	//obtem1 = LIS_ObterValor(lis);
	//while (LIS_AvancarElementoCorrente(lis, 1) != LIS_CondRetFimLista)
	//{
	//	printf("Obtem1 = %d\n", *obtem1);
	//	obtem1 = LIS_ObterValor(lis);
	//}
	//printf("Obtem1 = %d\n", *obtem1);



	//LIS_DestruirLista(lis);
	typedef struct meuTipo {
		int valor;
		char letra;		
	}MeuTipo;
	int tam;
	GRA_tppGrafo g = GRA_CriarGrafo(excluir);
	puts("criei");
	if (g == NULL)
	{
		puts("erro ao criar \n");
		return -1;
	}
	tam = GRA_QntVertices(g);
	printf("Tam apos criar grafo vazio = %d\n", tam);

	MeuTipo	a = { 0,'a'}, b = { 1,'b' }, c = { 2,'c' }, d = { 3,'d' }, e = { 4,'e' };
	GRA_tpCondRet retGra;	

	puts("inserindo a=0");
	retGra = GRA_InserirVertice(g, &a);
	if (retGra == GRA_CondRetFaltouMemoria)
	{
		puts("erro de memoria\n");
		exit(-1);
	}
	else
		puts("ok");
	puts("inserindo b=1");
	retGra = GRA_InserirVertice(g, &b);
	if (retGra == GRA_CondRetFaltouMemoria)
	{
		puts("erro de memoria");
		exit(-1);
	}
	puts("inserindo c=2");
	retGra = GRA_InserirVertice(g, &c);
	if (retGra == GRA_CondRetFaltouMemoria)
	{
		puts("erro de memoria");
		exit(-1);
	}
	puts("inserindo d=3");
	retGra = GRA_InserirVertice(g, &d);
	if (retGra == GRA_CondRetFaltouMemoria)
	{
		puts("erro de memoria");
		exit(-1);
	}	
	puts("obentendo corrente");
	MeuTipo* aux = GRA_ObterValorCorrente(g);
	if (aux != NULL)
		printf("retorno = letra %c valor= %d \n", aux->letra,aux->valor);
	retGra = GRA_IrVertice(g, &c);
	if (retGra != GRA_CondRetNaoAchou)
	{
		aux= GRA_ObterValorCorrente(g);
	}
	if (aux != NULL)
		printf("retorno apos busca por c(2) -> letra %c valor %d\n", aux->letra, aux->valor);

	retGra = GRA_IrVertice(g, &b);
	if (retGra != GRA_CondRetNaoAchou)
	{
		aux = GRA_ObterValorCorrente(g);
	}
	if (aux != NULL)
		printf("retorno apos busca por b(1) -> letra %c valor %d\n", aux->letra, aux->valor);

	retGra = GRA_IrVertice(g, &e);
	
	aux = GRA_ObterValorCorrente(g);
	
	if (aux != NULL)
		printf("retorno apos busca por e(nao esta no grafo) -> letra %c valor %d\n", aux->letra, aux->valor);

	GRA_ExcluirVertice(g);
	
	aux = GRA_ObterValorCorrente(g);

	if (aux != NULL)
		printf("corrente apos deleção -> letra %c valor %d\n", aux->letra, aux->valor);

	retGra = GRA_IrVertice(g, &b);

	aux = GRA_ObterValorCorrente(g);

	if (aux != NULL)
		printf("retorno apos busca por b(deletado) -> letra %c valor %d\n", aux->letra, aux->valor);


	GRA_IrVertice(g, &c);
	aux = GRA_ObterValorCorrente(g);

	if (aux != NULL)
		printf("retorno apos ir c(2) -> letra %c valor %d\n", aux->letra, aux->valor);

	tam = GRA_QntArestas(g);
	printf("\n\n\narestas de c %d\n", tam);

	GRA_CriarAresta(g, &a);

	tam = GRA_QntArestas(g);
	printf("arestas de c apos criar %d\n\n", tam);

	aux = GRA_ObterValorCorrente(g);

	if (aux != NULL)
		printf("corrente apos criar c->a = letra %c valor %d\n", aux->letra, aux->valor);

	GRA_IrVertice(g, &c);

	GRA_ExcluirVertice(g);

	GRA_IrVertice(g, &a);
	tam = GRA_QntArestas(g);
	printf("arestas de a apos deletar c %d\n\n", tam);
	aux = GRA_ObterValorCorrente(g);

	if (aux != NULL)
		printf("apos ir a -> letra %c valor %d\n", aux->letra, aux->valor);
	GRA_ExcluirAresta(g, &c);
	aux = GRA_ObterValorCorrente(g);
	tam = GRA_QntArestas(g);
	printf("arestas de a apos destruir com c %d\n\n", tam);

	tam = GRA_QntVertices(g);
	printf("Tam antes destruir grafo = %d\n", tam);

	GRA_DestruirGrafo(g);

	//g = GRA_CriarGrafo(excluir);
	


	
	return 0;
}

void excluir(void* dado)
{
	
	//free(dado);
	return;
}