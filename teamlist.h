// Uma coleção ordenada de times, implementada com lista duplamente encadeada.

#ifndef TEAMLIST_H
#define TEAMLIST_H

#include "team.h"

typedef struct teamlist TeamList;

// Cria uma coleção vazia. Retorna NULL se faltar memória.
TeamList *tl_create(void);

// Adiciona o time t ao final de tl.
// Propriedade: tl passa a ser dona de t (ver tl_free).
void tl_append(TeamList *tl, Team *t);

// Insere t em tl mantendo a lista ordenada pela classificação do campeonato (melhor
//   primeiro): mais pontos, mais vitórias, maior saldo, mais gols marcados, menor id.
// Requer: tl já ordenada por esse critério (ex.: construída só com tl_insert_sorted).
// Propriedade: tl passa a ser dona de t (ver tl_free).
// Custo: O(n).
void tl_insert_sorted(TeamList *tl, Team *t);

// Retorna o número de times em tl.
int tl_size(TeamList *tl);

// Retorna o time na posição i de tl, na ordem da lista.
// Requer: 0 <= i < tl_size(tl).
// Propriedade: o time continua pertencendo a tl.
Team *tl_get(TeamList *tl, int i);

// Retorna o time de tl com o id dado, ou NULL se não existir.
// Propriedade: o time continua pertencendo a tl.
// Custo: O(n).
Team *tl_find(TeamList *tl, int id);

// Libera tl e todos os times guardados nela.
// Custo: O(n).
void tl_free(TeamList *tl);

// Libera apenas tl e seus nós, SEM liberar os times. Serve para uma lista cujos times
//   também estão em outra lista (evita liberar o mesmo time duas vezes).
// Custo: O(n).
void tl_free_shallow(TeamList *tl);

#endif
