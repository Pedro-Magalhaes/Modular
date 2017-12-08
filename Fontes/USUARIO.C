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

   typedef struct tagPerfilUsuario { //TODO: juntei perfil com usuario, alterar modelo fisico!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        int idUsuario;

        char * nomeUsuario ;
                /* String com até 50 caracteres contendo o nome de um usuário */
        char generoUsuario;
                /* Char contendo o genero do usuário ('F','M' ou 'O' ) */

        int idadeUsuario ;
                /* Inteiro com a idade de um usuário */

   } tpPerfilUsuario ;


typedef struct USU_tagUsuario {

	GRA_tppGrafo pGrafo;
        /* Ponteiro pro grafo de usuarios */

        int IdSequencial; 
        /* Inteiro sequencial para gerar o id dos usuários */

        #ifdef _DEBUG
                tpPerfilUsuario * meus_usuarios[MAX_USERS];
                /* vetor para guardar meus usuários criados (redundancia) */
                int NextPos;
                /* proxima posição para guardar o ponteiro de um usuario no vetor */
        #endif

} GRA_tpUsuario;


/***** Protótipos das funções encapuladas no módulo *****/
static tpPerfilUsuario* buscaPorNome (GRA_tppGrafo pGrafo, char*nome);

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
        if( pUsuario == NULL )
        {
                return USU_CondRetNaoInicializado;
        }/* if */
        usuario1 = GRA_ObterValorCorrente(pUsuario->pGrafo);
        usuario2 = buscaPorNome(pUsuario->pGrafo ,nome); // agora o corrente do grafo eh usuario2
        if( usuario1 == NULL || usuario2 == NULL )
        {
                return USU_CondRetNaoAchou;
        }/* if */     
        if(GRA_CriarAresta(pUsuario->pGrafo,usuario1) == GRA_CondRetOK)
        {
                if(GRA_IrVertice(pUsuario->pGrafo,usuario1)==GRA_CondRetOK) // voltando o corrente pra usuario1
                {
                        return USU_CondRetOK;
                }/* if */
        }/* if */
        return USU_CondRetNaoAchou;
}/* Fim função: USU  &Adiciona Amigo */



/***************************************************************************
*
*  Função: USU  &Deletar Usuario
*  ****/

USU_tpCondRet USU_DeletarUsuario( USU_tppUsuario pUsuario )
{
        GRA_tpCondRet retorno;
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

/* Fim função: USU  &Total Usuarios */
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
        free(pUsuario);
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
        }
        aux = buscaPorNome(pUsuario->pGrafo,nome);

        if(aux == NULL)
        {
                return -1;
        }/* if */
        return aux->idUsuario;
}/* Fim função: USU  &USU_IrUsuario */


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

/* Fim função: USU  &USU_Verifica Perfil */

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
                printf("Funcao IdUsuario: parametro recebido == NULL abortando\n");
                exit(-1);
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
        free(perfil->nomeUsuario);
}

/* Fim função: USU  &excluirUsuario */

/***************************************************************************
*
*  Função: USU  &excluir Usuario
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
        GRA_IrInicioOrigens(pGrafo);        
        do
        {
                aux = GRA_ObterValorCorrente(pGrafo);
                if(aux == NULL)
                {
                        return NULL;
                }
                if(strcmp(aux->nomeUsuario,nome)==0)
                {
                        return aux;
                }/* if */
        }while(GRA_AvancarElementoCorrente(pGrafo,1) == GRA_CondRetOK);
        GRA_IrVertice(pGrafo,inicial);
        return NULL;
}/* Fim função: USU  &buscaPorNome */

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