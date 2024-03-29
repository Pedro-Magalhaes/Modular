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
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\GRATA.BSW
*
*  Projeto: INF 1301/ iMigo - a sua nova rede de relacionamentos
*  Gestor:  LES/DI/PUC-Rio
*  Autores: pfs, hfac , yan
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações*   
*     3       pfs   01/12/2017 Mudança da assinatura das funções e criação de novas  
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

#include "GRAFO.H"
#include "CHAT.H"
#include "LISTA.H"	

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um Usuario*/

typedef struct USU_tagUsuario * USU_tppUsuario ;


/***********************************************************************
*
*  $TC Tipo de dados: USU Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do módulo usuário
*
***********************************************************************/

   typedef enum {

         USU_CondRetOK ,
               /* Concluiu corretamente */

         USU_CondRetSemUsuarios ,
               /* A lista de usuarios não contém elementos */

         USU_CondRetPerfilIncorreto ,
               /* O perfil do usuário está incorreto */

         USU_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         USU_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um elemento de usuário */
         USU_CondRetNaoInicializado
              /* Modulo usuário não foi inicializado antes de chamar funções de manipulação */

   } USU_tpCondRet ;

/***********************************************************************
*
*  $FC Função: USU  &InicializarModulo
*
*  $ED Descrição da função
*     Faz a inicialização das variavéis internas ao módulo e retorna o
*     ponteiro para o tipo usuario.Este ponteiro será utilizado pelas funções 
*     que manipulem os usuarios.
*
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro pro tipo usuario.
*     em caso de erro retorna nulo
*
***********************************************************************/

   USU_tppUsuario USU_InicializarModulo( ) ;


/***********************************************************************
*
*  $FC Função: USU  &Criar Usuário
*
*  $ED Descrição da função
*     Cria um usuário com seu perfil, (TODO:adiciona-o no chat público )
*
*  $EP Parâmetros
*     Nome  - Nome do usuário com até 50 caracteres
*     idade - inteiro positivo diferente de 0 com a idade do usuário
*     genero - Caracter com o sexo do usuario, 'M' - masculino,
*              'F'- Feminino , 'O' - outros
*
*  $FV Valor retornado
*     Se executou corretamente retorna USU_CondRetOK.
*     USU_CondRetPerfilIncorreto - dados de genero ou idade incorretos
*     USU_CondRetFaltouMemoria - caso não tenha conseguido alocar memoria
*
***********************************************************************/

   USU_tpCondRet USU_CriaUsuario(
             USU_tppUsuario pUsuario, char * nome , int idade , char genero ) ;

/***********************************************************************
*
*  $FC Função: USU  &Adicionar Amigo
*
*  $ED Descrição da função
*     Adiciona ao usuario corrente o amigo com o nome recebido por parametro
*     o usuario deve existir e o nome deve ser igual ao nome inserido ao cria-lo
*
*  $EP Parâmetros
*     nome  - string com o nome do usuario que vai ser adicionado aos amigos do corrente
*     pUsuario - Ponteiro para o tipo usuario
*
*  $FV Valor retornado
*     Se executou corretamente retorna USU_CondRetOK .
*     Se já forem amigos retorna USU_CondRetPerfilIncorreto
*     Nas demais situções, vai retornar USU_CondRetNaoAchou .
*
***********************************************************************/    
      USU_tpCondRet USU_AdicionaAmigo( USU_tppUsuario pUsuario, char* nome ) ;


/***********************************************************************
*
*  $FC Função: USU  &Editar Nome
*     
*  $ED Descrição da função
*     Substitui o genero antigo pelo nome passado para a função 
*  $EP Parâmetros
*     pUsuario - ponteiro para a cabeça do modulo usuário
*     genero - char com 'M' - masculino 'F' - feminino 'O' - outros  
*
*  $FV Valor retornado
*   se ponteiro pUsuario for null - USU_CondRetNaoInicializado
*   se conseguiu fazer a alteração desejada - USU_CondRetOK
*   Se não consegur -- USU_CondRetPerfilIncorreto
*
***********************************************************************/ 
      USU_tpCondRet USU_EditarGenero(USU_tppUsuario pUsuario, char genero);
/***********************************************************************
*
*  $FC Função: USU  &Editar Idade
*     
*  $ED Descrição da função
*     Substitui a idade antiga pela passada para a função 
*  $EP Parâmetros
*     pUsuario - ponteiro para a cabeça do modulo usuário
*     Idade - Inteiro entre 1 e 199  
*
*  $FV Valor retornado
*   se ponteiro pUsuario for null - USU_CondRetNaoInicializado
*   se conseguiu fazer a alteração desejada - USU_CondRetOK
*   Se não consegur -- USU_CondRetPerfilIncorreto
*
***********************************************************************/ 
      USU_tpCondRet USU_EditarIdade(USU_tppUsuario pUsuario, int idade);
/***********************************************************************
*
*  $FC Função: USU  &Editar Nome
*     
*  $ED Descrição da função
*     Substitui o nome antigo pelo nome passado para a função 
*  $EP Parâmetros
*     pUsuario - ponteiro para a cabeça do modulo usuário
*     Nome - vetor de char com até 50 caracteres  
*
*  $FV Valor retornado
*   se ponteiro pUsuario for null - USU_CondRetNaoInicializado
*   se conseguiu fazer a alteração desejada - USU_CondRetOK
*   Se não consegur -- USU_CondRetPerfilIncorreto
*
***********************************************************************/ 
      USU_tpCondRet USU_EditarNome(USU_tppUsuario pUsuario, char* nome);
  

/***********************************************************************
*
*  $FC Função: USU  &Deletar Usuario
*     
*  $ED Descrição da função
*     Deleta o usuario corrente do módulo usuario 
*
*  $EP Parâmetros
*     pUsuario - ponteiro para a cabeça do modulo usuário 
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
      USU_tpCondRet USU_DeletarUsuario( USU_tppUsuario pUsuario ) ;   


/***********************************************************************
*
*  $FC Função: USU  &Destruir Usuarios
*
*  $ED Descrição da função
*     Destroi todos os dados alocados 
*  $EP Parâmetros
*     pUsuario - ponteiro para a cabeça do modulo usuário 
*
*  $FV Valor retornado
*     Não retorna valor
*
***********************************************************************/  
      void USU_DestruirUsuarios (USU_tppUsuario pUsuario);

/***********************************************************************
*
*  $FC Função: USU  &Total Usuarios
*
*  $ED Descrição da função
*     Retorna o numero de usuarios cadastrados atualmente
*  $EP Parâmetros
*     pUsuario - ponteiro para a cabeça do modulo usuário 
*
*  $FV Valor retornado
*     Retorna um inteiro > 0 representando o numero de usuarios
*     Em caso de erro retorna -1
*
***********************************************************************/  
      int USU_TotalUsuarios(USU_tppUsuario pUsuario);

/***********************************************************************
*
*  $FC Função: USU  &pegaNomeUsuarioCorrente
*
*  $ED Descrição da função
*     Retorna o nome do usuario corrente na rede de relacionamentos
*  $EP Parâmetros
*     pUsuario - ponteiro para a cabeça do modulo usuário 
*
*  $FV Valor retornado
*     Retorna um ponteiro pra char com o nome do usuario
*     Em caso de erro retorna NULL
*
***********************************************************************/ 
      char* USU_PegaNomeUsuarioCorrente (USU_tppUsuario pUsuario);
/***********************************************************************
*
*  $FC Função: USU  &USU_PegaDadosUsuarioCorrente
*
*  $ED Descrição da função
*     Retorna um string formatada com os dados de um usuario
*  $EP Parâmetros
*     pUsuario - ponteiro para a cabeça do modulo usuário 
*     minhaString - string onde vai ser guardado os dados deve ter
*                   tamanho suficiente (100 é suficiente)
*
*   $FV Valor retornado
*     USU_CondRetOK - se tudo correu bem
*     USU_CondRetNaoInicializado - caso não tenha corrente
*
***********************************************************************/ 
      USU_tpCondRet USU_PegaDadosUsuarioCorrente (USU_tppUsuario pUsuario,
                                                      char * minhaString);

/***********************************************************************
*
*  $FC Função: USU  &PegaDadosAmigosCorrente
*  $ED Descrição da função
*     Retorna um string formatada com os dados de todos os amigos do
*     usuario corrente
*  $EP Parâmetros
*     pUsuario - ponteiro para a cabeça do modulo usuário 
*     minhaString - string onde vai ser guardado os dados deve ter
*                   tamanho suficiente (perto de 1000 para 10 usuarios)
*
*  $FV Valor retornado
*     USU_CondRetOK - se tudo correu bem
*     USU_CondRetSemUsuarios - se não há amigos
*     USU_CondRetNaoInicializado - caso de ponteiro null
*
***********************************************************************/ 
      USU_tpCondRet USU_PegaDadosAmigosCorrente (USU_tppUsuario pUsuario,
                                                      char * minhaString);
/***********************************************************************
*
*  $FC Função: USU  &PegaDadosTodos
*  $ED Descrição da função
*     Retorna um string formatada com os dados de todos usuarios atualmente
*     cadastrados na rede
*  $EP Parâmetros
*     pUsuario - ponteiro para a cabeça do modulo usuário 
*     minhaString - string onde vai ser guardado os dados deve ter
*                   tamanho suficiente (perto de 1000 para 10 usuarios)
*
*  $FV Valor retornado
*     USU_CondRetOK - se tudo correu bem
*     USU_CondRetSemUsuarios - se não há amigos
*     USU_CondRetNaoInicializado - caso de ponteiro null
*
***********************************************************************/ 
      USU_tpCondRet USU_PegaDadosTodos (USU_tppUsuario pUsuario,
                                                      char * minhaString);                                                                                                              


/***********************************************************************
*
*  $FC Função: USU  &IrUsuario
*
*  $ED Descrição da função
*     Busca pelo nome o usuario desejado e o torna corrente
*
*  $FV Valor retornado
*     inteiro -  (maior ou igual a 0) Id do usuario caso tenha encontrado, 
*                -1 indica que o usuario não foi encontrado no grafo
*
***********************************************************************/ 

      int USU_IrUsuario (USU_tppUsuario pUsuario, char* nome);

/***********************************************************************
*
*  $FC Função: USU  &enviaMsgPublica
*
*  $ED Descrição da função
*     Envia mensagem no chat publico
*
*  $FV Valor retornado
*     condretOK - se tudo correu bem
*     USU_CondRetNaoInicializado - chat null           -
*
***********************************************************************/ 

      USU_tpCondRet USU_enviaMsgPublica (USU_tppUsuario pUsuario, char * mensagem ,
                                           char * nome);

/***********************************************************************
*
*  $FC Função: USU  &enviaMsgPrivada
*
*  $ED Descrição da função
*     Envia mensagem no chat privado, para a pessoa com o nome desejado
*
*  $FV Valor retornado
*     condretOK - se tudo correu bem
*     USU_CondRetNaoInicializado - chat null
*     USU_CondRetNaoAchou - Nao achou o chat desejado
***********************************************************************/ 

      USU_tpCondRet USU_enviaMsgPrivada (USU_tppUsuario pUsuario, char * mensagem ,
                                          char * nomeRemetente, char * nomeDestino);

/***********************************************************************
*
*  $FC Função: USU  &PegaMsgPublico
*
*  $ED Descrição da função
*     Retorna uma string contendo todas as mensagem do chat publico o usuario
*     fica responsável por desalocar a memoria do ponteiro retornado
*
*  $FV Valor retornado
*     ponteiro para a msg - se tudo correu bem
*     NULL - caso contrario           
*
***********************************************************************/ 

      char* USU_pegaMsgPublico (USU_tppUsuario pUsuario );
/***********************************************************************
*
*  $FC Função: USU  &PegaMsgPrivado
*
*  $ED Descrição da função
*     Retorna uma string contendo todas as mensagem do chat desejado o usuario
*     fica responsável por desalocar a memoria do ponteiro retornado
*
*  $FV Valor retornado
*     ponteiro para a msg - se tudo correu bem
*     NULL - caso contrario           
*
***********************************************************************/ 

      char* USU_pegaMsgPrivado (USU_tppUsuario pUsuario, char * nomeIntegrante);      

#undef USUARIO_EXT

/********** Fim do módulo de definição: USU  Usuário **********/

#else
#endif
