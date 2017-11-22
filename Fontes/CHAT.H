#if ! defined( CHAT_ )
#define CHAT_
/***************************************************************************
*
*  $MCD Módulo de definição: CHA  Chat da rede de relacionamentos
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
*	2       hfac  22/11/2017 continuação do desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa o módulo chat da rede de relacionamentos, contém os
*     usuarios participantes e mensagens armazenadas. 
*
*     Cada chat possui um vetor para seus integrantes e até 10 mensagens armazenadas onde
*	  as mais antigas serão deletadas
*
***************************************************************************/
 
#if defined( CHAT_OWN )
   #define CHAT_EXT
#else
   #define CHAT_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um Chat */

typedef struct CHA_tagChat * CHA_tppChat ;


/***********************************************************************
*
*  $TC Tipo de dados: CHA Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do CHAT
*
***********************************************************************/

   typedef enum {

         CHA_CondRetOK ,
               /* Concluiu corretamente */

         CHA_CondRetChatVazia ,
               /* O chat nao possui participantes */

		CHA_CondRetChatNULL,
			   /* O chat nao existe */

         CHA_CondRetSemMensagens ,
               /* O chat nao possui mensagens */

         CHA_CondRetNaoAchou ,
               /* Nao encontrou o chat procurado */

         CHA_CondRetFaltouMemoria ,
               /* Faltou memoria ao tentar criar um chat */

	   CHA_CondRetNaoEstaNoChat
			   /* Nao está incluido no chat em que deseja interagir */

   } CHA_tpCondRet ;


/***********************************************************************
*
*  $FC Função: CHA  &Criar Chat
*
*  $ED Descrição da função
*     Cria um chat. 
*     Os integrantes são desconhecidos a priori.
*
*  $EP Parâmetros
*     participante - Ponteiro para o tipo de integrante que iniciou o chat
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o chat.
*     Este ponteiro será utilizado pelas funções que manipulem este chat.
*
*     Se ocorreu algum erro, por exemplo falta de memoria ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/  

   CHA_tppChat CHA_CriaChat(void* participante);

/***********************************************************************
*
*  $FC Função: CHA  &Adiciona Integrante
*
*  $ED Descrição da função
*     Adiciona um integrante ao chat
*     Os integrantes são desconhecidos a priori.
*
*  $EP Parâmetros
*     participante - Ponteiro para o tipo de integrante que entrara no chat
*
*  $FV Valor retornado
*     Se executou corretamente retorna CHA_CondRetOK
*     Se o integrante a ser adicionado já existir no chat, retorna CHA_CondRetOK
*     Se faltar memoria, retorna CHA_CondRetFaltouMemoria
*	  Se o chat enviado for NULL, retorna CHA_CondRetChatNULL
*     
*
***********************************************************************/

   CHA_tpCondRet CHA_AdicionaIntegrante(CHA_tppChat pChat, void* participante);

/***********************************************************************
*
*  $FC Função: CHA  &Envia Mensagem
*
*  $ED Descrição da função
*     Adiciona uma mensagem no chat
*
*  $EP Parâmetros
*     pChat - Ponteiro para o chat em questão
*	  mensagem - A mensagem que será enviada (limite de 144 caracteres)
*     remetente - Ponteiro para o remetente da mensagem
*
*  $FV Valor retornado
*     CHA_CondRetChatNULL		- Se o ponteiro para o chat for igual a NULL
*     CHA_CondRetNaoEstaNoChat	- Se o rementente nao pertencer ao chat enviado
*     CHA_CondRetFaltouMemoria	- Se faltou memoria ao tentar adicionar a mensagem ao chat
*     CHA_CondRetSemMensagens	- Se não tiver mensagens após o envio da decima primeira mensagem,
*								  indica erro no modulo lista
*     CHA_CondRetOK				- Se tudo tiver dado certo
*
***********************************************************************/  

   CHA_tpCondRet CHA_EnviaMensagem(CHA_tppChat pChat, char mensagem[145], void* remetente) ;

/***********************************************************************
*
*  $FC Função: CHA  &Sair Chat
*
*  $ED Descrição da função
*     Remove o participante o chat desejado
*
*  $EP Parâmetros
*     pChat - Ponteiro para o chat em questão
*	  participante - Ponteiro para o participante a ser removido
*
*  $FV Valor retornado
*	  CHA_CondRetChatNULL	- Se o ponteiro para o chat for igual a NULL
*	  CHA_CondRetOK			- Se tudo tiver dado certo
*
***********************************************************************/  

   CHA_tpCondRet CHA_SairChat(CHA_tppChat pChat, void * participante);

/***********************************************************************
*
*  $FC Função: CHA  &Deletar Chat
*
*  $ED Descrição da função
*     Deleta o chat desejado. Se nao houver participantes, o chat é deletado automaticamente.
*
*  $EP Parâmetros
*     pChat - Ponteiro para o chat em questão
*
*  $FV Valor retornado
*	  CHA_CondRetChatNULL	- Se o ponteiro para o chat for igual a NULL
*	  CHA_CondRetOK			- Se tudo tiver dado certo
*
***********************************************************************/  

   CHA_tpCondRet CHA_DeletarChat(CHA_tppChat pChat);

/***********************************************************************
*
*  $FC Função: CHA  &Deletar Mensagem
*
*  $ED Descrição da função
*     Deleta a ultima mensagem enviada no chat, caso exista
*
*  $EP Parâmetros
*     pChat - Ponteiro para o chat em questão
*
*  $FV Valor retornado
*	  CHA_CondRetChatNULL	- Se o ponteiro para o chat for igual a NULL
*	  CHA_CondRetOK			- Se tudo tiver dado certo
*
***********************************************************************/  

   CHA_tpCondRet CHA_DeletarMensagem(CHA_tppChat pChat);


#undef CHAT_EXT

/********** Fim do módulo de definição: CHA  Chat **********/

#else
#endif
