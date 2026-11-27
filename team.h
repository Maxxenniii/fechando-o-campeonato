// Um time de futebol: identificação e estatísticas acumuladas. Saldo de gols e pontos
// não são armazenados; são sempre calculados a partir das estatísticas.

#ifndef TEAM_H
#define TEAM_H

typedef struct team Team;

// Cria um time com o id e o nome dados; as 5 estatísticas (vitórias, empates, derrotas,
//   gols marcados, gols sofridos) começam em zero.
// Retorna NULL se faltar memória.
// Propriedade: quem recebe o time (ou a lista que o guarda) o libera com team_free.
Team *team_create(int id, const char *name);

// Retorna o id do time t.
int team_id(Team *t);

// Retorna o nome do time t (somente leitura).
const char *team_name(Team *t);

// Retorna o número de vitórias de t.
int team_wins(Team *t);

// Retorna o número de empates de t.
int team_draws(Team *t);

// Retorna o número de derrotas de t.
int team_losses(Team *t);

// Retorna os gols marcados por t.
int team_goals_scored(Team *t);

// Retorna os gols sofridos por t.
int team_goals_conceded(Team *t);

// Registra o resultado de uma partida de t: soma os gols e conta vitória, empate ou
//   derrota conforme quem marcou mais.
void team_record_result(Team *t, int goals_scored, int goals_conceded);

// Retorna o saldo de gols de t (marcados - sofridos).
int team_goal_diff(Team *t);

// Retorna os pontos ganhos de t (3 por vitória + 1 por empate).
int team_points(Team *t);

// Libera o time t.
void team_free(Team *t);

#endif
