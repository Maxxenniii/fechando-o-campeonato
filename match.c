#include "match.h"
#include <stdlib.h>

struct match {
    int id;
    int team1;
    int team2;
    int goals1;
    int goals2;
};

Match *match_create(int id, int team1, int team2, int goals1, int goals2) {
    Match *m = malloc(sizeof(Match));
    if (m == NULL) {
        return NULL;
    }

    m->id = id;
    m->team1 = team1;
    m->team2 = team2;
    m->goals1 = goals1;
    m->goals2 = goals2;
    return m;
}

int match_id(Match *m) {
    return m->id;
}

int match_team1(Match *m) {
    return m->team1;
}

int match_team2(Match *m) {
    return m->team2;
}

int match_goals1(Match *m) {
    return m->goals1;
}

int match_goals2(Match *m) {
    return m->goals2;
}

void match_free(Match *m) {
    free(m);
}