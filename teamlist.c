#include "teamlist.h"
#include <stdlib.h>

typedef struct node {
    Team *team;
    struct node *prev;
    struct node *next;
} Node;

struct teamlist {
    Node *first;
    Node *last;
    int count;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));
    if (tl == NULL) {
        return NULL;
    }

    tl->first = NULL;
    tl->last = NULL;
    tl->count = 0;
    return tl;
}

// Cria um nó para t e o liga logo antes de `next`; next == NULL significa "no final".
// Trata num só lugar os casos lista vazia, novo primeiro, novo último e meio, para que
// tl_append e tl_insert_sorted usem a mesma lógica de ligação.
static void link_before(TeamList *tl, Node *next, Team *t) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return;
    }

    node->team = t;
    node->next = next;
    node->prev = (next == NULL) ? tl->last : next->prev;

    if (node->prev != NULL) {
        node->prev->next = node;
    } else {
        tl->first = node;
    }

    if (node->next != NULL) {
        node->next->prev = node;
    } else {
        tl->last = node;
    }

    tl->count++;
}

void tl_append(TeamList *tl, Team *t) {
    link_before(tl, NULL, t);
}

// Retorna 1 se a vem antes de b na classificação, 0 caso contrário. Cada critério só é
// olhado quando todos os anteriores empatam; o id (único) garante que nunca há empate total.
static int ranks_before(Team *a, Team *b) {
    if (team_points(a) != team_points(b)) {
        return team_points(a) > team_points(b);
    }
    if (team_wins(a) != team_wins(b)) {
        return team_wins(a) > team_wins(b);
    }
    if (team_goal_diff(a) != team_goal_diff(b)) {
        return team_goal_diff(a) > team_goal_diff(b);
    }
    if (team_goals_scored(a) != team_goals_scored(b)) {
        return team_goals_scored(a) > team_goals_scored(b);
    }
    return team_id(a) < team_id(b);
}

void tl_insert_sorted(TeamList *tl, Team *t) {
    // Anda até o primeiro nó que deve vir DEPOIS de t e insere t logo antes dele.
    Node *curr = tl->first;
    while (curr != NULL && !ranks_before(t, curr->team)) {
        curr = curr->next;
    }
    link_before(tl, curr, t);
}

int tl_size(TeamList *tl) {
    return tl->count;
}

Team *tl_get(TeamList *tl, int i) {
    Node *curr;

    // Começa pela ponta mais próxima da posição i.
    if (i < tl->count / 2) {
        curr = tl->first;
        for (int idx = 0; idx < i; idx++) {
            curr = curr->next;
        }
    } else {
        curr = tl->last;
        for (int idx = tl->count - 1; idx > i; idx--) {
            curr = curr->prev;
        }
    }

    return curr->team;
}

Team *tl_find(TeamList *tl, int id) {
    for (Node *curr = tl->first; curr != NULL; curr = curr->next) {
        if (team_id(curr->team) == id) {
            return curr->team;
        }
    }
    return NULL;
}

// Libera os nós; libera também os times apenas se free_teams for diferente de zero.
static void free_nodes(TeamList *tl, int free_teams) {
    if (tl != NULL) {
        Node *curr = tl->first;
        while (curr != NULL) {
            Node *next = curr->next;
            if (free_teams) {
                team_free(curr->team);
            }
            free(curr);
            curr = next;
        }
        free(tl);
    }
}

void tl_free(TeamList *tl) {
    free_nodes(tl, 1);
}

void tl_free_shallow(TeamList *tl) {
    free_nodes(tl, 0);
}