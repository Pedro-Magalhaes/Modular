#include "GRAFO.H"
#include "LISTA.H"
#include <stdio.h>
#include <stdlib.h>

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

	GRA_tppGrafo g = GRA_CriarGrafo(excluir);
	puts("criei");
	if (g == NULL)
	{
		puts("erro ao criar \n");
		return -1;
	}
	int a = 0, b = 1, c = 2, d = 3, e = 4;
	GRA_tpCondRet retGra;
	puts("inseri 1");
	retGra = GRA_InserirVertice(g, &a);
	if (retGra == GRA_CondRetFaltouMemoria)
	{
		puts("erro de memoria\n");
		exit(-1);
	}
	else
		puts("ok\n");
	puts("inseri 1");
	retGra = GRA_InserirVertice(g, &b);
	if (retGra == GRA_CondRetFaltouMemoria)
	{
		puts("erro de memoria\n");
		exit(-1);
	}
	puts("inseri 1");
	retGra = GRA_InserirVertice(g, &c);
	if (retGra == GRA_CondRetFaltouMemoria)
	{
		puts("erro de memoria\n");
		exit(-1);
	}
	puts("inseri 1");
	retGra = GRA_InserirVertice(g, &d);
	if (retGra == GRA_CondRetFaltouMemoria)
	{
		puts("erro de memoria\n");
		exit(-1);
	}
	puts("obentendo corrente");
	int* aux = GRA_ObterValorCorrente(g);
	if (aux != NULL)
		printf("retorno = %d\n", *aux);
	return 0;
}

void excluir(void* dado)
{
	return;
}