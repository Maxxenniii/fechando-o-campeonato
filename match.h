// Uma partida já disputada: os dois times (por id) e os gols de cada um.

#ifndef MATCH_H
#define MATCH_H

typedef struct match Match;

// Cria uma partida com os campos dados. Retorna NULL se faltar memória.
// Propriedade: quem recebe a partida (ou a lista que a guarda) a libera com match_free.
Match *match_create(int id, int team1, int team2, int goals1, int goals2);

// Retorna o id da partida m.
int match_id(Match *m);

// Retorna o id do primeiro time de m.
int match_team1(Match *m);

// Retorna o id do segundo time de m.
int match_team2(Match *m);

// Retorna os gols do primeiro time de m.
int match_goals1(Match *m);

// Retorna os gols do segundo time de m.
int match_goals2(Match *m);

// Libera a partida m.
void match_free(Match *m);

#endif
