// Campeonato Computacional de Futebol: lê os times e as partidas, apura as estatísticas,
// monta a classificação e imprime a tabela e o resumo. Não há interação com o usuário.

#include "match.h"
#include "matchlist.h"
#include "team.h"
#include "teamlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Etapa 1a: lê times.csv (ID,Nome) para uma lista, na ordem do arquivo.
// Retorna NULL se o arquivo não puder ser aberto.
static TeamList *ler_times(void) {
    FILE *fp = fopen("times.csv", "r");
    if (fp == NULL) {
        perror("times.csv");
        return NULL;
    }

    TeamList *tl = tl_create();
    char line[256];
    char name[128];
    int id;

    fgets(line, sizeof(line), fp);  // ignora o cabeçalho
    while (tl != NULL && fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';
        // O nome é tudo que vem depois da primeira vírgula.
        if (sscanf(line, "%d,%127[^\n]", &id, name) == 2) {
            Team *t = team_create(id, name);
            if (t != NULL) {
                tl_append(tl, t);
            }
        }
    }

    fclose(fp);
    return tl;
}

// Etapa 1b: lê partidas.csv (ID,Time1,Time2,GolsTime1,GolsTime2) para uma lista, na
// ordem do arquivo. Retorna NULL se o arquivo não puder ser aberto.
static MatchList *ler_partidas(void) {
    FILE *fp = fopen("partidas.csv", "r");
    if (fp == NULL) {
        perror("partidas.csv");
        return NULL;
    }

    MatchList *ml = ml_create();
    char line[256];
    int id, team1, team2, goals1, goals2;

    fgets(line, sizeof(line), fp);  // ignora o cabeçalho
    while (ml != NULL && fgets(line, sizeof(line), fp) != NULL) {
        if (sscanf(line, "%d,%d,%d,%d,%d", &id, &team1, &team2, &goals1, &goals2) == 5) {
            Match *m = match_create(id, team1, team2, goals1, goals2);
            if (m != NULL) {
                ml_append(ml, m);
            }
        }
    }

    fclose(fp);
    return ml;
}

// Etapa 2: percorre as partidas e atualiza as estatísticas dos dois times de cada uma.
// Cada time vê a partida do seu ponto de vista: primeiro os gols que ele marcou.
static void apurar(TeamList *teams, MatchList *matches) {
    for (int i = 0; i < ml_size(matches); i++) {
        Match *m = ml_get(matches, i);
        Team *t1 = tl_find(teams, match_team1(m));
        Team *t2 = tl_find(teams, match_team2(m));

        if (t1 != NULL && t2 != NULL) {  // ignora partida com time desconhecido
            team_record_result(t1, match_goals1(m), match_goals2(m));
            team_record_result(t2, match_goals2(m), match_goals1(m));
        }
    }
}

// Etapa 3: devolve uma NOVA lista com os mesmos times, ordenada pela classificação,
// construída por inserção ordenada. Os times são compartilhados com a lista original.
static TeamList *classificar(TeamList *teams) {
    TeamList *ranking = tl_create();
    if (ranking == NULL) {
        return NULL;
    }

    for (int i = 0; i < tl_size(teams); i++) {
        tl_insert_sorted(ranking, tl_get(teams, i));
    }
    return ranking;
}

// Imprime s alinhado à esquerda numa coluna de `largura` caracteres. O printf com %-15s
// conta BYTES, e "õ" ocupa 2 bytes em UTF-8; aqui contamos caracteres, ignorando os bytes
// de continuação (10xxxxxx), para a coluna não desalinhar.
static void imprimir_nome(const char *s, int largura) {
    int caracteres = 0;
    for (const char *p = s; *p != '\0'; p++) {
        if (((unsigned char)*p & 0xC0) != 0x80) {
            caracteres++;
        }
    }

    printf("%s", s);
    for (int i = caracteres; i < largura; i++) {
        printf(" ");
    }
}

// Etapa 4a: imprime a tabela de classificação.
static void imprimir_tabela(TeamList *ranking) {
    printf("%-4s%-4s", "Pos", "ID");
    imprimir_nome("Time", 15);
    printf("%3s%3s%3s%4s%4s%4s%4s\n", "V", "E", "D", "GM", "GS", "S", "PG");

    for (int i = 0; i < tl_size(ranking); i++) {
        Team *t = tl_get(ranking, i);
        printf("%-4d%-4d", i + 1, team_id(t));
        imprimir_nome(team_name(t), 15);
        printf("%3d%3d%3d%4d%4d%4d%4d\n",
               team_wins(t), team_draws(t), team_losses(t),
               team_goals_scored(t), team_goals_conceded(t),
               team_goal_diff(t), team_points(t));
    }
}

// Etapa 4b: imprime o resumo do campeonato.
static void imprimir_resumo(TeamList *ranking, MatchList *matches) {
    int n = tl_size(ranking);
    int total = n * (n - 1) / 2;  // turno único: todos contra todos, uma vez
    int jogadas = ml_size(matches);

    printf("===== Resumo do campeonato =====\n");
    printf("Partidas disputadas: %d de %d\n", jogadas, total);

    if (jogadas == 0) {
        printf("Nenhuma partida foi disputada: o campeonato ainda não começou.\n");
        return;
    }

    // "Campeão" só quando todas as partidas foram disputadas.
    Team *primeiro = tl_get(ranking, 0);
    printf("%s: %s (%d pontos)\n", jogadas == total ? "Campeão" : "Líder",
           team_name(primeiro), team_points(primeiro));

    // Melhor ataque e melhor defesa: percorre a classificação do 1º ao último e só troca
    // se o valor for ESTRITAMENTE melhor, então o empate fica com o mais bem colocado.
    Team *ataque = primeiro;
    Team *defesa = primeiro;
    for (int i = 1; i < n; i++) {
        Team *t = tl_get(ranking, i);
        if (team_goals_scored(t) > team_goals_scored(ataque)) {
            ataque = t;
        }
        if (team_goals_conceded(t) < team_goals_conceded(defesa)) {
            defesa = t;
        }
    }
    printf("Melhor ataque: %s (%d gols marcados)\n",
           team_name(ataque), team_goals_scored(ataque));
    printf("Melhor defesa: %s (%d gols sofridos)\n",
           team_name(defesa), team_goals_conceded(defesa));

    // Maior goleada: só troca se a diferença for ESTRITAMENTE maior, então o empate
    // fica com a primeira partida do arquivo.
    Match *goleada = ml_get(matches, 0);
    for (int i = 1; i < jogadas; i++) {
        Match *m = ml_get(matches, i);
        if (abs(match_goals1(m) - match_goals2(m)) >
            abs(match_goals1(goleada) - match_goals2(goleada))) {
            goleada = m;
        }
    }
    Team *t1 = tl_find(ranking, match_team1(goleada));
    Team *t2 = tl_find(ranking, match_team2(goleada));
    if (t1 != NULL && t2 != NULL) {
        printf("Maior goleada: %s %d x %d %s\n", team_name(t1), match_goals1(goleada),
               match_goals2(goleada), team_name(t2));
    }
}

// Etapa 4c: grava a tabela em classificacao.csv, na ordem da classificação.
static void gravar_csv(TeamList *ranking) {
    FILE *fp = fopen("classificacao.csv", "w");
    if (fp == NULL) {
        perror("classificacao.csv");
        return;
    }

    fprintf(fp, "Pos,ID,Time,V,E,D,GM,GS,S,PG\n");
    for (int i = 0; i < tl_size(ranking); i++) {
        Team *t = tl_get(ranking, i);
        fprintf(fp, "%d,%d,%s,%d,%d,%d,%d,%d,%d,%d\n",
                i + 1, team_id(t), team_name(t),
                team_wins(t), team_draws(t), team_losses(t),
                team_goals_scored(t), team_goals_conceded(t),
                team_goal_diff(t), team_points(t));
    }
    fclose(fp);
}

int main(void) {
    TeamList *teams = ler_times();
    MatchList *matches = ler_partidas();
    if (teams == NULL || matches == NULL) {
        tl_free(teams);
        ml_free(matches);
        return 1;
    }

    apurar(teams, matches);
    TeamList *ranking = classificar(teams);
    if (ranking != NULL) {
        imprimir_tabela(ranking);
        imprimir_resumo(ranking, matches);
        gravar_csv(ranking);
    }

    // Os times pertencem a `teams`; `ranking` só os emprestou. Por isso ranking é
    // liberada sem liberar os times (senão haveria liberação dupla).
    tl_free_shallow(ranking);
    tl_free(teams);
    ml_free(matches);
    return 0;
}