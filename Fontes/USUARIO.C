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
*
***************************************************************************/
#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define USUARIO_OWN
#include "USUARIO.h"
#undef USUARIO_OWN

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
