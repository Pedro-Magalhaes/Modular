/***************************************************************************
*
*  $MCD Módulo de implementação: CHA  Chat da rede de relacionamentos
*
*  Arquivo gerado:              CHAT.h
*  Letras identificadoras:      CHA
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
*     2	      hfac  22/11/2017 continuação do desenvolvimento
*     3       hfac  01/12/2017 correção e finalização do módulo
***************************************************************************/
#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>


#define CHAT_OWN
#include "CHAT.h"
#include "LISTA.h"
#undef CHAT_OWN

/***********************************************************************
*
*  $TC Tipo de dados: CHA Mensagem
*
*
***********************************************************************/

typedef struct mensagem {

	char * conteudo;
	/* Ponteiro para a lista com as arestas do vertice  */

	char * remetente;
	/* Ponteiro para remetende da mensagem */


} Mensagem;

typedef struct CHA_tagChat {

	LIS_tppLista mensagens;
	/* Ponteiro para a lista de mensagens */

	LIS_tppLista integrantes;
	/* Ponteiro para a lista de integrantes */

	int ID;
	/*Identificador do chat*/

	void(*ExcluirValor) (void * pValor);
	/* Ponteiro para a função de destruição do valor contido em um elemento */

} CHA_tpChat;

/***** Protótipos das funções encapuladas no módulo *****/


static void ExcluirMensagens(void *msg)
{	
	Mensagem * dado = msg;
	free(dado->conteudo);
	free(msg);
}

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: CHA  &Criar chat
*  ****/

CHA_tppChat CHA_CriaChat(void* participante, void(*ExcluirValor) (void * pDado))
{
	CHA_tpChat * pChat = NULL;

	pChat = (CHA_tpChat *)malloc(sizeof(CHA_tpChat));
	if (pChat == NULL)
	{
		return NULL;
	}/*if*/
	pChat->integrantes = LIS_CriarLista(ExcluirValor); //criando uma lista vazia
	pChat->mensagens = LIS_CriarLista(ExcluirMensagens); //criando uma lista vazia
	if (LIS_InserirElementoApos(pChat->integrantes, participante) != LIS_CondRetOK)
	{
		return NULL;
	}/*if*/
	if (pChat->mensagens == NULL)
	{
		return NULL;
	}
	LIS_IrInicioLista(pChat->integrantes);

	return pChat;
}

/* Fim função: CHA  &Criar chat */


/***************************************************************************
*
*  Função: CHA  &Adiciona Integrante
*  ****/

CHA_tpCondRet CHA_AdicionaIntegrante(CHA_tppChat pChat, void* participante)
{
	if (pChat == NULL)
	{
		return CHA_CondRetChatNULL;
	}/*if*/
	LIS_IrInicioLista(pChat->integrantes);

	if (LIS_ProcurarValor(pChat->integrantes, participante) == LIS_CondRetNaoAchou)
	{
		LIS_IrFinalLista(pChat->integrantes);
		if (LIS_InserirElementoApos(pChat->integrantes, participante) != LIS_CondRetOK)
		{
			return CHA_CondRetFaltouMemoria;
		}
	}

	return CHA_CondRetOK;
}

/* Fim função: CHA  &Adiciona Integrante */



/***************************************************************************
*
*  Função: CHA  &Envia Mensagem
*  ****/

CHA_tpCondRet CHA_EnviaMensagem(CHA_tppChat pChat,char* mensagem, char* remetente)
{
	Mensagem *msg;
	msg = (Mensagem*)malloc(sizeof(Mensagem));
	msg->conteudo = (char*)malloc(sizeof(char)*145);
	if (msg == NULL)
	{
		return CHA_CondRetFaltouMemoria;
	}
	if (pChat == NULL)
	{
		return CHA_CondRetChatNULL;
	}/*if*/

	strcpy(msg->conteudo,mensagem);
	msg->remetente=remetente;
	LIS_IrInicioLista(pChat->integrantes);
	if (LIS_ProcurarValor(pChat->integrantes, msg->remetente) != LIS_CondRetOK)
	{
		return CHA_CondRetNaoEstaNoChat;
	}
	LIS_IrFinalLista(pChat->mensagens);
	if (LIS_InserirElementoApos(pChat->mensagens, (void*)msg) != LIS_CondRetOK)
	{
		return CHA_CondRetFaltouMemoria;
	}
	if (LIS_ObtemTamanho(pChat->mensagens) > 10)
	{
		LIS_IrInicioLista(pChat->mensagens);
		if (LIS_ExcluirElemento(pChat->mensagens) != LIS_CondRetOK)
		{
			return CHA_CondRetSemMensagens; //Não deve atingir esse estado nunca, se atingir, erro no módulo lista
		}
	}

	
	return CHA_CondRetOK;
}

/* Fim função: CHA  &Envia Mensagem */


/***************************************************************************
*
*  Função: CHA  &Sair chat
*  ****/

CHA_tpCondRet CHA_SairChat(CHA_tppChat pChat, void* participante)
{
	if (pChat == NULL)
	{
		return CHA_CondRetChatNULL;
	}/*if*/
	LIS_IrInicioLista(pChat->integrantes);
	if (LIS_ProcurarValor(pChat->integrantes, participante) == LIS_CondRetOK)
	{
		LIS_ExcluirElemento(pChat->integrantes);
	}
	if (LIS_ObtemTamanho(pChat) == 0)
	{
		CHA_DeletarChat(pChat);
	}
	return CHA_CondRetOK;
}

/* Fim função: CHA  &Sair chat */



/***************************************************************************
*
*  Função: CHA  &Deleta chat
*  ****/

CHA_tpCondRet CHA_DeletarChat(CHA_tppChat pChat)
{
	if (pChat == NULL)
	{
		return CHA_CondRetChatNULL;
	}/*if*/
	LIS_DestruirLista(pChat->integrantes);
	LIS_DestruirLista(pChat->mensagens);
	free(pChat);

	return CHA_CondRetOK;
}

/* Fim função: CHA  &Deleta chat */

/***************************************************************************
*
*  Função: CHA  &Deleta mensagem
*  ****/

CHA_tpCondRet CHA_DeletarMensagem(CHA_tppChat pChat)
{
	if (pChat == NULL)
	{
		return CHA_CondRetChatNULL;
	}/*if*/
	if (LIS_ObtemTamanho(pChat->mensagens) > 0)
	{
		LIS_IrFinalLista(pChat->mensagens);
		LIS_ExcluirElemento(pChat->mensagens);
	}
	return CHA_CondRetOK;
}

/* Fim função: CHA  &Deleta chat */

/***************************************************************************
*
*  Função: CHA  &Pega mensagens
*  ****/

char* CHA_PegaMensagens(CHA_tppChat pChat)
{
	char *mensagens;
	char *aux;
	int j = 0;
	int i = 0;
	
	

	Mensagem *m;
	if (pChat == NULL)
	{
		
		return NULL;
	}/*if*/

	mensagens = (char*)malloc(sizeof(char) * 2000);

	LIS_IrInicioLista(pChat->mensagens);
	if (LIS_ObtemTamanho(pChat->mensagens) > 0)
	{
		do
		{
			m = (Mensagem*)LIS_ObterValor(pChat->mensagens);
			aux = m->remetente;
			for (i = 0; aux[i] != '\0'; i++, j++)
			{
				mensagens[j] = aux[i];
			}
			mensagens[j] = ':';
			j++;
			mensagens[j] = ' ';
			j++;
			m = (Mensagem*)LIS_ObterValor(pChat->mensagens);
			aux = m->conteudo;
			for (i = 0; aux[i] != '\0'; i++, j++)
			{
				mensagens[j] = aux[i];
			}
			mensagens[j] = '\n';
			j++;
		} while (LIS_AvancarElementoCorrente(pChat->mensagens, 1) == LIS_CondRetOK);
		mensagens[j] = '\0';
		return mensagens;
	}
	else
		free(mensagens);
		return NULL;
}

/* Fim função: CHA  &Pega mensagens */
