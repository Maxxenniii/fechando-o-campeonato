// Uma coleção de partidas, na ordem do arquivo, implementada com lista encadeada.

#ifndef MATCHLIST_H
#define MATCHLIST_H

#include "match.h"

typedef struct matchlist MatchList;

// Cria uma coleção vazia. Retorna NULL se faltar memória.
MatchList *ml_create(void);

// Adiciona a partida m ao final de ml.
// Propriedade: ml passa a ser dona de m (ver ml_free).
// Custo: O(1).
void ml_append(MatchList *ml, Match *m);

// Retorna o número de partidas em ml.
int ml_size(MatchList *ml);

// Retorna a partida na posição i de ml, na ordem do arquivo.
// Requer: 0 <= i < ml_size(ml).
// Propriedade: a partida continua pertencendo a ml.
// Custo: O(n).
Match *ml_get(MatchList *ml, int i);

// Libera ml e todas as partidas guardadas nela.
// Custo: O(n).
void ml_free(MatchList *ml);

#endif