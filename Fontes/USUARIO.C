/***************************************************************************
*
*  $MCD Módulo de implementação: USU  Usuário da rede de relacionamentos
*
*  Arquivo gerado:              USUARIO.c
*  Letras identificadoras:      USU
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
*     2       pfs   26/11/2017 Continuação do desenvolvimento
*     3       pfs   29/11/2017 Continuação do desenvolvimento
*     4       pfs   01/12/2017 Continuação do desenvolvimento
*     5       pfs   02/12/2017 Continuação do desenvolvimento
*
***************************************************************************/
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   <ctype.h>

#define USUARIO_OWN
#include "USUARIO.h"
#undef USUARIO_OWN

#include "CHAT.h"

#define MAX_USERS 10

/***********************************************************************
*
*  $TC Tipo de dados: USU Perfil Usuario
*
*
***********************************************************************/

   typedef struct tagPerfilUsuario { 
        int idUsuario;
        /* inteiro contendo o id de um usuario */
        char * nomeUsuario ;
        /* String com até 50 caracteres contendo o nome de um usuário */
        char generoUsuario;
        /* Char contendo o genero do usuário ('F','M' ou 'O' ) */

        int idadeUsuario ;
        /* Inteiro com a idade de um usuário */
        LIS_tppLista listaChatPrivado;
        /* lista com todos os chats privados do usuario */

   } tpPerfilUsuario ;

/***********************************************************************
*
*  $TC Tipo de dados: USU Chat privado
*
***********************************************************************/

   typedef struct tagChatUsuario { 
        tpPerfilUsuario * usuario;
        /* Ponteiro para outro usuario que está no chat */
       CHA_tppChat chatPrivado;
        /* ponteiro para o chat */

   } tpChatUsuario ;

/***********************************************************************
*
*  $TC Tipo de dados: USU Cabeça Usuarios
*
*
***********************************************************************/
typedef struct USU_tagUsuario {

	GRA_tppGrafo pGrafo;
        /* Ponteiro pro grafo de usuarios */

        int IdSequencial; 
        /* Inteiro sequencial para gerar o id dos usuários */

        CHA_tppChat chatPublico;

        #ifdef _DEBUG
                tpPerfilUsuario * meus_usuarios[MAX_USERS];
                /* vetor para guardar meus usuários criados (redundancia) */
                int NextPos;
                /* proxima posição para guardar o ponteiro de um usuario no vetor */
        #endif

} GRA_tpUsuario;


/***** Protótipos das funções encapuladas no módulo *****/

static void naoExclui(void* pDado);
static tpPerfilUsuario* buscaPorNome (GRA_tppGrafo pGrafo, char*nome);
static tpPerfilUsuario* buscaArestaPorNome (GRA_tppGrafo pGrafo, char*nome);
static tpChatUsuario* buscaUsuarioListaChat (tpPerfilUsuario * usu1, tpPerfilUsuario * usu2);
static USU_tpCondRet formataDadosUsu (tpPerfilUsuario * usuario,int size,char * minhaString);
static USU_tpCondRet excluiChatPrivado (tpPerfilUsuario * usuario);
static USU_tpCondRet USU_AdicionaUsuario(USU_tppUsuario pUsuario, tpPerfilUsuario* perfil);

static void GetNewIdUsuario(USU_tppUsuario pUsuario,int* Id_destino);

static void excluirUsuario (void* usuario);

static USU_tpCondRet verificaPerfil (USU_tppUsuario pUsuario,char * nome, char genero , int idade);
static USU_tpCondRet verificaNome (USU_tppUsuario pUsuario,char * nome);
static USU_tpCondRet verificaIdade (int idade);
static USU_tpCondRet verificaGenero (char genero );

#ifdef _DEBUG

static void GuardaNoVetor (USU_tppUsuario pUsuario, tpPerfilUsuario * perfil);

static void DeletaDoVetor (USU_tppUsuario pUsuario, tpPerfilUsuario * perfil);

#endif

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: USU  &Inicializar Modulo
*  ****/

USU_tppUsuario USU_InicializarModulo( )
{
        GRA_tpUsuario * pUsuario = NULL;
        pUsuario = (GRA_tpUsuario *) malloc( sizeof (GRA_tpUsuario) );
        if (pUsuario == NULL)
        {
                return pUsuario;
        } /* if */

        pUsuario->pGrafo = GRA_CriarGrafo ( excluirUsuario );
        pUsuario->IdSequencial = 0;
        pUsuario->chatPublico = CHA_CriaChat(pUsuario,naoExclui);
        #ifdef _DEBUG
                pUsuario->NextPos = 0;
        #endif /* _DEBUG */

        return pUsuario;
}

/* Fim função: USU  &Inicializar Modulo */

/***************************************************************************
*
*  Função: USU  &Cria Usuario
*  ****/

USU_tpCondRet USU_CriaUsuario(USU_tppUsuario pUsuario, char * nome , int idade , char genero )
{
      tpPerfilUsuario * perfil = NULL;
      USU_tpCondRet retorno;
      
      if (pUsuario == NULL)
      {
              return USU_CondRetNaoInicializado;
      }/* if */
      if (verificaPerfil(pUsuario,nome,genero,idade) != USU_CondRetOK)
      {
              return USU_CondRetPerfilIncorreto;
      }/* if */
      perfil =(tpPerfilUsuario*) malloc(sizeof(tpPerfilUsuario));

      if (perfil == NULL)
      {//erro de memoria
        return USU_CondRetFaltouMemoria;
      } /* if */

      perfil ->nomeUsuario = (char*) malloc(sizeof(char)*51);
      
      if (perfil->nomeUsuario == NULL)
      {//erro de memoria
        return USU_CondRetFaltouMemoria;
      } /* if */
      
      strcpy_s(perfil->nomeUsuario,50,nome); //atribuindo o nome
     
      perfil->idadeUsuario = idade; //atribuindo idade     
     
      perfil->generoUsuario = (char)toupper(genero); //atribuindo genero
     
      GetNewIdUsuario( pUsuario, &perfil->idUsuario ); //atribuindo o Id

      retorno = USU_AdicionaUsuario(pUsuario,perfil);
      if(retorno == USU_CondRetOK)
      {
              perfil->listaChatPrivado = LIS_CriarLista(naoExclui); //exclusão manual
              if(CHA_AdicionaIntegrante(pUsuario->chatPublico,perfil->nomeUsuario) == CHA_CondRetOK)
                {
                        return USU_CondRetOK;
                }/* if */
      }/* if */
      #ifdef _DEBUG
      if(retorno == USU_CondRetOK)
      {
        GuardaNoVetor(pUsuario,perfil);
        return USU_CondRetOK;
      } /* if */
      #endif/* _DEBUG */

      return retorno;
}

/* Fim função: USU  &Cria Usuario */

/***************************************************************************
*
*  Função: USU  &Adiciona Amigo
*  ****/

USU_tpCondRet USU_AdicionaAmigo( USU_tppUsuario pUsuario, char* nome ) 
{
        tpPerfilUsuario * usuario1;
        tpPerfilUsuario * usuario2;
        GRA_tpCondRet retorno;
        tpChatUsuario * meuChatcom1;
        tpChatUsuario * meuChatcom2;
        CHA_tppChat chat;
        if( pUsuario == NULL )
        {
                return USU_CondRetNaoInicializado;
        }/* if */
        meuChatcom1 = (tpChatUsuario *) malloc (sizeof(tpChatUsuario));
        meuChatcom2 = (tpChatUsuario *) malloc (sizeof(tpChatUsuario));
        if(meuChatcom1 == NULL || meuChatcom2 == NULL)
        {
                return USU_CondRetFaltouMemoria;
        }
        usuario1 = GRA_ObterValorCorrente(pUsuario->pGrafo);
        usuario2 = buscaPorNome(pUsuario->pGrafo ,nome); 
        GRA_IrVertice(pUsuario->pGrafo,usuario2);// agora o corrente do grafo eh usuario2
        if( usuario1 == NULL || usuario2 == NULL )
        {
                return USU_CondRetNaoAchou;
        }/* if */     
        retorno = GRA_CriarAresta(pUsuario->pGrafo,usuario1);
        if( retorno == GRA_CondRetOK)
        {
                if(GRA_IrVertice(pUsuario->pGrafo,usuario1)==GRA_CondRetOK) // voltando o corrente pra usuario1
                {
                        chat = CHA_CriaChat(usuario1->nomeUsuario, naoExclui);
                        if (chat == NULL)
                        {
                                return USU_CondRetPerfilIncorreto;
                        }
                        CHA_AdicionaIntegrante(chat,usuario2->nomeUsuario);
                        meuChatcom1->usuario = usuario1;
                        meuChatcom1->chatPrivado = chat;
                        meuChatcom2->usuario = usuario2;
                        meuChatcom2->chatPrivado = meuChatcom1->chatPrivado;
                        LIS_InserirElementoApos(usuario1->listaChatPrivado,meuChatcom2);
                        LIS_InserirElementoApos(usuario2->listaChatPrivado,meuChatcom1);
                        return USU_CondRetOK;
                }/* if */
                else
                {
                        return USU_CondRetPerfilIncorreto;
                }
        }/* if */
        else
        {
                if(retorno == GRA_CondRetVerticeJaExiste)
                {//ja esta na lista de amigos
                        GRA_IrVertice(pUsuario->pGrafo,usuario1);
                        return USU_CondRetPerfilIncorreto;
                }/* if */
                return USU_CondRetNaoAchou;
        }
        
}/* Fim função: USU  &Adiciona Amigo */



/***************************************************************************
*
*  Função: USU  &Deletar Usuario
*  ****/

USU_tpCondRet USU_DeletarUsuario( USU_tppUsuario pUsuario )
{
        GRA_tpCondRet retorno;
        tpPerfilUsuario * aDeletar;
        #ifdef _DEBUG  // deletando o usuario tambem do vertor de redundâncias
                tpPerfilUsuario * aux;
                assert( pUsuario != NULL );                
                aux = GRA_ObterValorCorrente(pUsuario->pGrafo);
                DeletaDoVetor(pUsuario,aux);
                
        #endif /* _DEBUG */
                
        if(pUsuario == NULL)
        {
                return USU_CondRetNaoInicializado;
        }/* if */
        aDeletar = GRA_ObterValorCorrente(pUsuario->pGrafo);
        if(aDeletar == NULL)
        {
                return USU_CondRetNaoInicializado;
        }
        retorno = excluiChatPrivado(aDeletar);
        if ( retorno == USU_CondRetNaoAchou || retorno == USU_CondRetPerfilIncorreto)
        {
                return USU_CondRetNaoAchou;
        }

        retorno = GRA_ExcluirVertice(pUsuario->pGrafo);
        if(retorno == GRA_CondRetGrafoNulo)
        {
                 return USU_CondRetNaoInicializado;
        }/* if */
    
        return USU_CondRetOK;
           
  
}

/* Fim função: USU  &Deletar Usuario */

/***************************************************************************
*
*  Função: USU  &Editar Nome
*  ****/

 USU_tpCondRet USU_EditarNome(USU_tppUsuario pUsuario, char* nome) 
 {
         tpPerfilUsuario * auxiliar;
         USU_tpCondRet retorno;
         if(pUsuario == NULL)
        {
                return USU_CondRetNaoInicializado;
        }/* if */
        auxiliar = (tpPerfilUsuario *) GRA_ObterValorCorrente(pUsuario->pGrafo);
        if (auxiliar == NULL)
        {
                return USU_CondRetNaoInicializado;
        }/* if */
        retorno = verificaNome(pUsuario,nome);
        if (retorno == USU_CondRetOK)
        {
                strcpy_s(auxiliar->nomeUsuario,50,nome);
                return USU_CondRetOK;
                
        }/* if */
        
        return USU_CondRetPerfilIncorreto;
 }

/* Fim função: USU  &Editar Nome */

/***************************************************************************
*
*  Função: USU  &Editar idade
*  ****/

 USU_tpCondRet USU_EditarIdade(USU_tppUsuario pUsuario, int idade) 
 {
         tpPerfilUsuario * auxiliar;
         if(pUsuario == NULL)
        {
                return USU_CondRetNaoInicializado;
        }/* if */
        auxiliar = (tpPerfilUsuario *) GRA_ObterValorCorrente(pUsuario->pGrafo);
        if (auxiliar == NULL)
        {
                return USU_CondRetNaoInicializado;
        }/* if */
        if (verificaIdade(idade) == USU_CondRetOK)
        {
                auxiliar->idadeUsuario = idade;
                return USU_CondRetOK;
        }/* if */
         return USU_CondRetPerfilIncorreto;
 }

/* Fim função: USU  &Editar idade */

/***************************************************************************
*
*  Função: USU  &Editar Genero
*  ****/

 USU_tpCondRet USU_EditarGenero(USU_tppUsuario pUsuario, char genero) 
 {
         tpPerfilUsuario * auxiliar;
         if(pUsuario == NULL)
        {
                return USU_CondRetNaoInicializado;
        }/* if */
        auxiliar = (tpPerfilUsuario *) GRA_ObterValorCorrente(pUsuario->pGrafo);
        if (auxiliar == NULL)
        {
                return USU_CondRetNaoInicializado;
        }/* if */
        if (verificaGenero(genero) == USU_CondRetOK)
        {
                auxiliar->generoUsuario =(char) toupper(genero);
                return USU_CondRetOK;
        }/* if */
         return USU_CondRetPerfilIncorreto;
 }
/* Fim função: USU  &Editar Genero */

/***************************************************************************
*
*  Função: USU  &enviaMsgPublica
*  ****/
USU_tpCondRet USU_enviaMsgPublica (USU_tppUsuario pUsuario,char * mensagem ,char* nome)
{
        tpPerfilUsuario * aux;
        if(pUsuario == NULL)
        {
                return USU_CondRetNaoInicializado;
        }/* if */

        aux=buscaPorNome(pUsuario->pGrafo,nome);
        if(aux == NULL)
        {
                return USU_CondRetSemUsuarios;
        }/* if */
        if(CHA_EnviaMensagem(pUsuario->chatPublico,mensagem,aux->nomeUsuario)==CHA_CondRetOK)
        {
                return USU_CondRetOK;
        }/* if */
        return USU_CondRetPerfilIncorreto;
}
/* Fim função: USU  &enviaMsgPublica */
/***************************************************************************
*
*  Função: USU  &enviaMsgPublica
*  ****/
char* USU_pegaMsgPublico (USU_tppUsuario pUsuario )
{
        if(pUsuario != NULL)
        {
               return CHA_PegaMensagens(pUsuario->chatPublico);
        }/* if */
        return NULL;
}

/* Fim função: USU  &enviaMsgPublica */

 
/* Fim função: USU  &enviaMsgPublica */
/***************************************************************************
*
*  Função: USU  &enviaMsgPublica
*  ****/
 char* USU_pegaMsgPrivado(USU_tppUsuario pUsuario, char * nomeIntegrante) 
{
        tpChatUsuario * chat;
        tpPerfilUsuario * remetente;
        tpPerfilUsuario * destino;
        if(pUsuario == NULL)
        {
               return NULL;
        }/* if */

        remetente = GRA_ObterValorCorrente( pUsuario->pGrafo );
        if(remetente == NULL)
        {
               return NULL;
        }/* if */

        destino = buscaPorNome( pUsuario->pGrafo, nomeIntegrante );
        if(destino == NULL)
        {
               return NULL;
        }/* if */

        chat = buscaUsuarioListaChat( remetente, destino );
        if(chat == NULL)
        {
               return NULL;
        }/* if */

        return CHA_PegaMensagens(chat->chatPrivado);

}

/* Fim função: USU  &enviaMsgPublica */
/***************************************************************************
*
*  Função: USU  &Total Usuarios
*  em caso de erro GRA_QntVertices retorna -1
*  ****/

 int USU_TotalUsuarios(USU_tppUsuario pUsuario)
 {
         if (pUsuario == NULL)
         {
                 return -1;
         }/* if */
         return GRA_QntVertices( pUsuario->pGrafo );
 }

/* Fim função: USU  &Total Usuarios */

/***************************************************************************
*
*  Função: USU  &Pega Nome Usuario Corrente
*  ****/
char* USU_PegaNomeUsuarioCorrente (USU_tppUsuario pUsuario)
{
        tpPerfilUsuario * aux;
        if(pUsuario == NULL)
        {
                return NULL;
        }/* if */
        aux = GRA_ObterValorCorrente(pUsuario->pGrafo);
        if(aux == NULL)
        {
                return NULL;
        }/* if */
        return aux->nomeUsuario;
}


/* Fim função: USU  &PegaNomeUsuarioCorrente */
/***************************************************************************
*
*  Função: USU  &PegaDadosUsuarioCorrente
*  ****/
USU_tpCondRet USU_PegaDadosUsuarioCorrente (USU_tppUsuario pUsuario,char * minhaString)
{
        tpPerfilUsuario * aux;
        if(pUsuario == NULL)
        {
                return USU_CondRetNaoInicializado;
        }/* if */
        aux = GRA_ObterValorCorrente(pUsuario->pGrafo);
        if(aux == NULL)
        {
                return USU_CondRetNaoInicializado;
        }/* if */

        formataDadosUsu(aux,100,minhaString);

        return USU_CondRetOK;
}
/* Fim função: USU  &PegaDadosUsuarioCorrente */
/***************************************************************************
*
*  Função: USU  &PegaDadosAmigosCorrente
*  ****/
USU_tpCondRet USU_PegaDadosAmigosCorrente (USU_tppUsuario pUsuario,
                                                      char * minhaString)
{
        tpPerfilUsuario * aux;
         //max 10 usuarios com 50 caracteres de nome + 1 sexo + ate 3 de idade
        char stringAuxiliar[100];
        if(pUsuario == NULL)
        {
                return USU_CondRetNaoInicializado;
        }/* if */
        GRA_IrInicioArestas(pUsuario->pGrafo);
        aux = GRA_ObterValorAresta(pUsuario->pGrafo);
        if(aux == NULL)
        {
                return USU_CondRetSemUsuarios;
        }/* if */
        if(minhaString != NULL)
        {
                minhaString[0]='\0';
        }

        do{
                aux = GRA_ObterValorAresta(pUsuario->pGrafo);
                if(aux == NULL)
                {
                        break;
                }
                formataDadosUsu(aux,100,stringAuxiliar);
                strcat_s(minhaString,800,stringAuxiliar);
        }while(GRA_AvancarElementoAresta(pUsuario->pGrafo,1)==GRA_CondRetOK);
        GRA_IrInicioArestas(pUsuario->pGrafo);//voltando
        return USU_CondRetOK;
}
/* Fim função: USU  &PegaDadosUsuarioCorrente */
/***************************************************************************
*
*  Função: USU  &PegaDadosTodos
*  ****/
USU_tpCondRet USU_PegaDadosTodos (USU_tppUsuario pUsuario,
                                                      char * minhaString)
{
        tpPerfilUsuario * inicial;
        tpPerfilUsuario * aux;
         //max 10 usuarios com 50 caracteres de nome + 1 sexo + ate 3 de idade
        char stringAuxiliar[100];
        if(pUsuario == NULL)
        {
                return USU_CondRetNaoInicializado;
        }/* if */
        inicial = GRA_ObterValorCorrente(pUsuario->pGrafo);
        if (inicial == NULL)
        {
                return USU_CondRetNaoInicializado;
        }
        GRA_IrInicioOrigens(pUsuario->pGrafo);
        aux = GRA_ObterValorCorrente(pUsuario->pGrafo);
        if(aux == NULL)
        {
                return USU_CondRetSemUsuarios;
        }/* if */
        if(minhaString != NULL)
        {
                minhaString[0]='\0';
        }

        do{
                aux = GRA_ObterValorCorrente(pUsuario->pGrafo);
                if(aux == NULL)
                {
                        break;
                }
                formataDadosUsu(aux,100,stringAuxiliar);
                strcat_s(minhaString,800,stringAuxiliar);
        }while(GRA_AvancarElementoCorrente(pUsuario->pGrafo,1)==GRA_CondRetOK);
        GRA_IrVertice(pUsuario->pGrafo,inicial);//voltando
        return USU_CondRetOK;
}                                                      
/* Fim função: USU  &PegaDadosTodos */
/***************************************************************************
*
*  Função: USU  &USU_DestruirUsuarios
*  ****/

void USU_DestruirUsuarios (USU_tppUsuario pUsuario)
{
        #ifdef _DEBUG //limpar usuarios da redundancia
                int i;
                assert(pUsuario != NULL);                
                for(i=0;i<MAX_USERS;i++)
                {
                        pUsuario->meus_usuarios[i]=NULL;
                }/* for */
                pUsuario->NextPos = 0;
        #endif /* _DEBUG */
        if( pUsuario == NULL )
        {//nada a ser feito
                return;
        }/* if */
        GRA_DestruirGrafo(pUsuario->pGrafo);
        pUsuario->pGrafo = NULL;                
        pUsuario->IdSequencial = 0;
        
}

/* Fim função: USU  &USU_DestruirUsuarios */

/***************************************************************************
*
*  Função: USU  &USU_IrUsuario
*  ****/
int USU_IrUsuario (USU_tppUsuario pUsuario, char* nome)
{
        tpPerfilUsuario * aux;
        if(pUsuario == NULL)
        {
                return -1;
        }/* if */
        aux = buscaPorNome(pUsuario->pGrafo,nome);
        GRA_IrVertice(pUsuario->pGrafo,aux);
        if(aux == NULL)
        {
                return -1;
        }/* if */
        return aux->idUsuario;
}/* Fim função: USU  &USU_IrUsuario */

/***************************************************************************
*
*  Função: USU  &enviaMsgPrivada
*  ****/
USU_tpCondRet USU_enviaMsgPrivada (USU_tppUsuario pUsuario, char * mensagem ,
                                          char * nomeRemetente, char * nomeDestino)
{
       tpPerfilUsuario * usuRemetente;
       tpPerfilUsuario * usuDestino;
       tpChatUsuario * chat;
        if(pUsuario == NULL)
        {
                return USU_CondRetNaoInicializado;
        }/* if */
        if(nomeRemetente == NULL || nomeDestino == NULL || mensagem == NULL)
        {
                return USU_CondRetNaoInicializado;
        }/* if */

        usuRemetente = GRA_ObterValorCorrente(pUsuario->pGrafo);
        if(usuRemetente == NULL)
        {//grafo vazio
                return USU_CondRetSemUsuarios;
        }/* if */
        usuDestino = buscaPorNome(pUsuario->pGrafo,nomeDestino);
        if(usuDestino == NULL)
        {//não esta no grafo
                return USU_CondRetNaoAchou;
        }/* if */
        chat = buscaUsuarioListaChat(usuRemetente,usuDestino);
        if(chat == NULL)
        {//nao são amigos
                return USU_CondRetPerfilIncorreto;
        }/* if */

        if(CHA_EnviaMensagem(chat->chatPrivado,mensagem,usuRemetente->nomeUsuario) == CHA_CondRetOK)
        {
                return USU_CondRetOK;
        }/* if */

        //unica possibilidade de chegar aqui seria nomeUsuario nulo pro chat
        return USU_CondRetPerfilIncorreto; 

}
/* Fim função: USU  &enviaMsgPrivada */

/****** Fim funções exportadas pelo modulo USU ******/

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: USU  &Adicionar Usúario
*
*  $ED Descrição da função
*     Adiciona o usuario no grafo
*
*  $EP Parâmetros
*     USU_tppUsuario pUsuario  - Ponteiro para a instancia do modulo usuario
*     tpPerfilUsuario* perfil  - Ponteiro para um perfil de usuario que vai ser adicionado  
*  $FV Valor retornado
*     Se executou corretamente retorna USU_CondRetOK.
*     Se ocorreu algum erro de falta de memória retorna USU_CondRetFaltouMemoria,
*     Se o grafo da instancia do módulo usuario nao tiver sido inicializado retorna_
*                                                       USU_CondRetNaoInicializado
*
***********************************************************************/   

USU_tpCondRet USU_AdicionaUsuario(USU_tppUsuario pUsuario, tpPerfilUsuario* perfil)
{
        LIS_tpCondRet retorno;
        #ifdef _DEBUG
		 assert( pUsuario != NULL );
                 assert(pUsuario->pGrafo != NULL );
	#endif /* _DEBUG */
        
        retorno = GRA_InserirVertice( pUsuario->pGrafo , perfil );
        switch ( retorno )
        {
                case GRA_CondRetFaltouMemoria:
                        return USU_CondRetFaltouMemoria;
                        break;
                case GRA_CondRetGrafoNulo:
                        return USU_CondRetNaoInicializado;
                        break;
                default:                        
                        return USU_CondRetOK;
        }/* switch */

}  


/* Fim função: USU  &USU_AdicionaUsuario */
/***************************************************************************
*
*  Função: USU  &VerificaNome
*       Verifica o nome recebido e retorna condretPerfilIncorreto
*       ou condRetOK
*  ****/
static USU_tpCondRet verificaNome (USU_tppUsuario pUsuario,char * nome)
{
        tpPerfilUsuario * inicial;
        if(nome == NULL)
        {
                return USU_CondRetPerfilIncorreto;
        }/* if */

        if(strlen(nome) > 50)
        {
                return USU_CondRetPerfilIncorreto;
        }/* if */

        inicial = GRA_ObterValorCorrente( pUsuario->pGrafo);
        
        if(buscaPorNome(pUsuario->pGrafo,nome)!= NULL)
        {
             return USU_CondRetPerfilIncorreto;   
        }
        GRA_IrVertice(pUsuario->pGrafo,inicial);
        return USU_CondRetOK;
}
/* Fim função: USU  &USU_AdicionaUsuario */

/***************************************************************************
*
*  Função: USU  &Verifica idade
*       Verifica a idade recebida e retorna condretPerfilIncorreto
*       ou condRetOK
*  ****/
static USU_tpCondRet verificaIdade (int idade)
{
        if(idade > 0 && idade < 200)        
        {
                return USU_CondRetOK;
        }/* if */

        return USU_CondRetPerfilIncorreto;
}
/* Fim função: USU  &USU_AdicionaUsuario */

/***************************************************************************
*
*  Função: USU  &VerificaGenero
*       Verifica o genero recebido e retorna condretPerfilIncorreto
*       ou condRetOK
*  ****/
static USU_tpCondRet verificaGenero (char genero )
{
        if (genero == 'M' ||genero == 'F' || genero == 'O' || 
          genero == 'm' || genero == 'f'|| genero == 'o')
        {
                return USU_CondRetOK;
        } /* if */

        return USU_CondRetPerfilIncorreto;
}
/* Fim função: USU  &USU_AdicionaUsuario */

/***************************************************************************
*
*  Função: USU  &VerificaPerfil
*       Verifica os dados de perfil recebidos e retorna condretPerfilIncorreto
*       ou condRetOK
*  ****/
static USU_tpCondRet verificaPerfil (USU_tppUsuario pUsuario,char * nome, char genero , int idade)
{
        if (verificaNome(pUsuario,nome) != USU_CondRetOK)
        {
                return USU_CondRetPerfilIncorreto;
        }/* if */
        
        if (verificaIdade(idade) != USU_CondRetOK)
        {
                return USU_CondRetPerfilIncorreto;
        }/* if */

        if (verificaGenero(genero) != USU_CondRetOK)
        {
                return USU_CondRetPerfilIncorreto;
        }/* if */        

      return USU_CondRetOK;
}

/* Fim função: USU  &Verifica Perfil */

/***************************************************************************
*
*  Função: USU  &formataDadosUsu
*       Formata os dados de perfil do usuario recebido em uma string de pelo
*       menos 100 caracteres por segurança
*  ****/
static USU_tpCondRet formataDadosUsu (tpPerfilUsuario * usuario,int size,char * minhaString)
{
        if(usuario == NULL)
        {
                return USU_CondRetSemUsuarios;
        }
        sprintf_s(minhaString,size,"\tUsuario: %s\n\tSexo: '%c'\n\tIdade: %d\n",usuario->nomeUsuario,
                                                                usuario->generoUsuario,usuario->idadeUsuario);
        return USU_CondRetOK;                                                                
}
/* Fim função: USU  &formataDadosUsu */
/***************************************************************************
*
*  Função: USU  &GetNewIdUsuario
*       Preenche o id do usuário(recebido como parametro) com o próximo
*       valor da variável IdSequencial. Em caso de erro aborta.
*  ****/
static void GetNewIdUsuario(USU_tppUsuario pUsuario, int* id_destino)
{
        if( id_destino == NULL || pUsuario == NULL)
        {
                return;
        }/* if */
        //incremento a variavel global e atribuo a variavel recebida
        *id_destino = ++pUsuario->IdSequencial; 
}
/* Fim função: USU  &GetNewIdUsuario */

/***************************************************************************
*
*  Função: USU  &excluir Usuario
*       Faz a exclusão dos dados guardados no perfil
*  ****/
static void excluirUsuario (void* dado)
{       
        tpPerfilUsuario * perfil = (tpPerfilUsuario*) dado;
        if(perfil == NULL)
        {
                return;
        }
        if(perfil != NULL)
        {
                free(perfil->nomeUsuario);
        }
       
}

/* Fim função: USU  &excluirUsuario */
/***************************************************************************
*
*  Função: USU  &excluiChatPrivado
*       Faz a exclusão mutua do chat privado entre usuarios
*  ****/
static USU_tpCondRet excluiChatPrivado (tpPerfilUsuario * usuario)
{
        tpChatUsuario * aux;
        tpPerfilUsuario * usuarioPermanece;
        tpChatUsuario * chatDeletar;
        if(usuario == NULL)
        {
                return USU_CondRetNaoInicializado;
        }
        LIS_IrInicioLista(usuario->listaChatPrivado);
        aux = LIS_ObterValor(usuario->listaChatPrivado);
        if (aux == NULL)
        {//não possi chat privado
                return USU_CondRetSemUsuarios;
        }
        do{
                usuarioPermanece = aux->usuario;
                chatDeletar = buscaUsuarioListaChat(usuarioPermanece,usuario);
                if(chatDeletar == NULL)
                {                        
                        return USU_CondRetNaoAchou;
                }
                LIS_IrInicioLista(usuarioPermanece->listaChatPrivado);
                if(LIS_ProcurarValor(usuarioPermanece->listaChatPrivado,chatDeletar) == LIS_CondRetOK)
                {
                        LIS_ExcluirElemento(usuarioPermanece->listaChatPrivado);
                        LIS_IrInicioLista(usuarioPermanece->listaChatPrivado);
                }
                else
                {
                        return USU_CondRetPerfilIncorreto;  
                }

        }while(LIS_AvancarElementoCorrente(usuario->listaChatPrivado,1)==LIS_CondRetOK);
        LIS_IrInicioLista(usuario->listaChatPrivado);
        LIS_DestruirLista(usuario->listaChatPrivado);
        return USU_CondRetOK;

}
/* Fim função: USU  &excluiChatPrivado */
/***************************************************************************
*
*  Função: USU  &naoExclui
*       Função passada para o chat, como nenhum dado com alocação dinamica é
*       passado a função é vazia
*  ****/
static void naoExclui(void* pDado)
{

}
/* Fim função: USU  &naoExclui */
/***************************************************************************
*
*  Função: USU  &BuscaPorNome
*       Faz a busca de um usuario no grafo recebido por parametro
*        através no nome também recebido por parametro.
*       retorna nullo em caso de erro e se não encontrar
*  ****/
static tpPerfilUsuario* buscaPorNome (GRA_tppGrafo pGrafo, char*nome)
{
        tpPerfilUsuario * inicial;
        tpPerfilUsuario * aux;
        if ( pGrafo == NULL )
        {
                return NULL;
        }/* if */
        inicial = GRA_ObterValorCorrente(pGrafo);
        if (inicial == NULL)
        {
                return NULL;
        }/* if */
        GRA_IrInicioOrigens(pGrafo);        
        do
        {
                aux = GRA_ObterValorCorrente(pGrafo);
                if(aux == NULL)
                {
                        GRA_IrVertice(pGrafo,inicial);
                        return NULL;
                }/* if */
                if(strcmp(aux->nomeUsuario,nome)==0)
                {
                        GRA_IrVertice(pGrafo,inicial);
                        return aux;
                }/* if */
        }while(GRA_AvancarElementoCorrente(pGrafo,1) == GRA_CondRetOK);
        GRA_IrVertice(pGrafo,inicial);
        return NULL;
}/* Fim função: USU  &buscaPorNome */

/***************************************************************************
*
*  Função: USU  &buscaArestaPorNome
*       Faz a busca de um usuario nas arestas do grafo recebido por parametro
*        através no nome também recebido por parametro.
*       retorna null em caso de erro e se não encontrar
*  ****/
static tpPerfilUsuario* buscaArestaPorNome (GRA_tppGrafo pGrafo, char*nome)
{
        tpPerfilUsuario * inicial;
        tpPerfilUsuario * aux;
        if ( pGrafo == NULL )
        {
                return NULL;
        }/* if */
        inicial = GRA_ObterValorAresta(pGrafo);
        GRA_IrInicioArestas(pGrafo);        
        do
        {
                aux = GRA_ObterValorAresta(pGrafo);
                if(aux == NULL)
                {
                        return NULL;
                }
                if(strcmp(aux->nomeUsuario,nome)==0)
                {
                        return aux;
                }/* if */
        }while(GRA_AvancarElementoAresta(pGrafo,1) == GRA_CondRetOK);
        GRA_IrInicioArestas(pGrafo);
        return NULL;
}/* Fim função: USU  &buscaArestaPorNome */
/***************************************************************************
*
*  Função: USU  &buscaUsuarioListaChat
*       Faz a busca de um usuario(usu2) na lista de chats de um usuario(usu1)
*       retorna null em caso de erro e se não encontrar retorna o chat 
*  ****/
static tpChatUsuario* buscaUsuarioListaChat (tpPerfilUsuario * usu1, tpPerfilUsuario * usu2)
{
        tpChatUsuario * aux;
        if ( usu1 == NULL || usu2 == NULL )
        {
                return NULL;
        }/* if */
        LIS_IrInicioLista(usu1->listaChatPrivado);
        do
        {
                aux = LIS_ObterValor(usu1->listaChatPrivado);
                if ( aux == NULL)
                {
                        return NULL;
                }
                if (usu2 == aux->usuario )
                {
                        LIS_IrInicioLista(usu1->listaChatPrivado);
                        return aux;
                }
        }while(LIS_AvancarElementoCorrente(usu1->listaChatPrivado,1)==LIS_CondRetOK);
        LIS_IrInicioLista(usu1->listaChatPrivado);
        return NULL;
}
/* Fim função: USU  &buscaUsuarioListaChat */
/*****  Código das funções usadas apenas em DEBUG  *****/
#ifdef _DEBUG
/***************************************************************************
*
*  Função: USU  &GuardaNoVetor
*       Guarda o perfil no vetor de redundancias e atualiza a proxima posição disponivel
*  ****/
        static void GuardaNoVetor ( USU_tppUsuario pUsuario,  tpPerfilUsuario * perfil)
        {
               
                assert( pUsuario->meus_usuarios[pUsuario->NextPos] == NULL );
                
                pUsuario->meus_usuarios[pUsuario->NextPos] = perfil;
                pUsuario->NextPos++;

        }

        /* Fim função: USU  &GuardaNoVetor */

/***************************************************************************
*
*  Função: USU  &Deleta do Vetor
*       Seta todas as posições do vetor como null, como os dados estão alocados no grafo
*       não libero a memória
*  ****/
        static void DeletaDoVetor (USU_tppUsuario pUsuario, tpPerfilUsuario * perfil)
        {                
                int i = 0;
                assert((pUsuario != NULL) && (pUsuario->meus_usuarios != NULL));
                while(i<MAX_USERS)
                {
                        if(pUsuario->meus_usuarios[i] == perfil)
                        {
                                pUsuario->NextPos--;
                                pUsuario->meus_usuarios[i] = pUsuario->meus_usuarios[pUsuario->NextPos];
                                pUsuario->meus_usuarios[pUsuario->NextPos] = NULL;
                                return;
                        }/* if */
                        i++;
                }/* while */
        }
#endif