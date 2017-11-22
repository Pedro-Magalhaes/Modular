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
*	    2		    hfac  22/11/2017 continuação do desenvolvimento
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

	void * remetente;
	/* Ponteiro para remetende da mensagem */


} Mensagem;

typedef struct CHA_tagChat {

	LIS_tppLista mensagens;
	/* Ponteiro para a lista de mensagens */

	LIS_tppLista integrantes;
	/* Ponteiro para a lista de integrantes */

	int ID;
	/*Identificador do chat*/

} CHA_tpChat;

/***** Protótipos das funções encapuladas no módulo *****/


static void ExcluirValor();

static void ExcluirMensagens();

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: CHA  &Criar chat
*  ****/

CHA_tppChat CHA_CriaChat(void* participante)
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
	if (LIS_ProcurarValor(pChat->integrantes,participante) == LIS_CondRetNaoAchou)
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

CHA_tpCondRet CHA_EnviaMensagem(CHA_tppChat pChat,char mensagem[145], void* remetente)
{
	if (pChat == NULL)
	{
		return CHA_CondRetChatNULL;
	}/*if*/
	Mensagem *msg;
	msg->conteudo = mensagem;
	msg->remetente = remetente;
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

CHA_tpCondRet CHA_SairChat(CHA_tppChat pChat, void * participante)
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
