#if ! defined( USUARIO_ )
#define USUARIO_
/***************************************************************************
*
*  $MCD Módulo de definição: USU  Usuário da rede de relacionamentos
*
*  Arquivo gerado:              USUARIO.h
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
*     2       pfs   29/11/2017 Adição de funções e mudança de assinaturas de funções
*     1       pfs   17/11/2017 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa o módulo usuário da rede de relacionamentos, contém os
*     dados dos usuarios, como seu perfil. Possui os métodos de interação
*     do usuário com a rede. Faz uso do módulo Grafo e do Módulo Chat 
*
*     Cada usuário possui um perfil com Nome com no MAX 50 caracteres,
*     idade (inteiro positivo), gênero (char 'M'-Masculino , 'F'-Feminino,
*     'O'-Outros)
*     Apenas uma "instancia" do módulo pode estar ativa, ao tentar inicializar o
*     modulo depois de já ter sido feita uma inicialização todos os dados anteriores
*     serão perdidos pois o modulo vai resetar seu estado para o inicial (a memoria é desalocada)
*
*     FALTA ESCREVER MAIS?????? OLHAR MODULO LISTA.H
*
***************************************************************************/
 
#if defined( USUARIO_OWN )
   #define USUARIO_EXT
#else
   #define USUARIO_EXT extern
#endif

#include   "GRAFO.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um Usuario*/

typedef struct USU_tagUsuario * USU_tppUsuario ;


/***********************************************************************
*
*  $TC Tipo de dados: USU Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         USU_CondRetOK ,
               /* Concluiu corretamente */

         USU_CondRetListaVazia ,
               /* A lista não contém elementos */

         USU_CondRetPerfilIncorreto ,
               /* O perfil do usuário está incorreto */

         USU_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         USU_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um elemento de lista */
         USU_CondRetNaoInicializado
              /* Modulo usuário não foi inicializado antes de chamar funções de manipulação */

   } USU_tpCondRet ;

/***********************************************************************
*
*  $FC Função: USU  &InicializarModulo
*
*  $ED Descrição da função
*     Faz a inicialização das variavéis internas ao módulo 
*
*  $FV Valor retornado
*     Se executou corretamente retorna ok.
*     ******TODO colocar erros
*
***********************************************************************/

   USU_tpCondRet USU_InicializarModulo( ) ;


/***********************************************************************
*
*  $FC Função: USU  &Criar Usuário
*
*  $ED Descrição da função
*     Cria um usuário com seu perfil, adiciona-o no chat público
*
*  $EP Parâmetros
*     Nome  - Nome do usuário com até 50 caracteres
*     idade - inteiro positivo diferente de 0 com a idade do usuário
*     genero - Caracter com o sexo do usuario, 'M' - masculino,
*              'F'- Feminino , 'O' - outros
*
*  $FV Valor retornado
*     Se executou corretamente retorna ok.
*     ******TODO colocar erros
*
***********************************************************************/

   USU_tpCondRet USU_CriaUsuario(
             char * nome , int idade , char genero ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Adicionar Amigo
*
*  $ED Descrição da função
*     
*
*  $EP Parâmetros
*     XXXXXXXXXXXX  - 
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/    
      USU_tpCondRet USU_AdicionaAmigo( int id_usuario ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Editar Perfil
*
*  $ED Descrição da função
*     
*
*  $EP Parâmetros
*     XXXXXXXXXXXX  - 
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/   
      USU_tpCondRet USU_EditarPerfil() ; 

/***********************************************************************
*
*  $FC Função: LIS  &Adicionar Usúario
*
*  $ED Descrição da função
*     
*
*  $EP Parâmetros
*     XXXXXXXXXXXX  - 
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/   
      USU_tpCondRet USU_AdicionaUsuario( USU_tppUsuario usuario ) ;     

/***********************************************************************
*
*  $FC Função: LIS  &Deletar Usuario
*
*  $ED Descrição da função
*     
*
*  $EP Parâmetros
*     XXXXXXXXXXXX  - 
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/   
      USU_tpCondRet USU_DeletarUsuario( int id_usuario ) ;   


/***********************************************************************
*
*  $FC Função: USU  &Destruir Usuarios
*
*  $ED Descrição da função
*     Destroi todos os dados alocados 
*
*  $FV Valor retornado
*     Não retorna valor
*
***********************************************************************/  
      void USU_DestruirUsuarios ();

/***********************************************************************
*
*  $FC Função: USU  &Total Usuarios
*
*  $ED Descrição da função
*     Retorna o numero de usuarios cadastrados atualmente
*
*  $FV Valor retornado
*     Retorna um inteiro > 0 representando o numero de usuarios
*     Em caso de erro retorna -1
*
***********************************************************************/  
      int USU_TotalUsuarios();

#undef USUARIO_EXT

/********** Fim do módulo de definição: USU  Usuário **********/

#else
#endif
