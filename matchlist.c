#include "matchlist.h"
#include <stdlib.h>

typedef struct node {
    Match *match;
    struct node *next;
} Node;

struct matchlist {
    Node *first;
    Node *last;  // permite inserir no final em O(1) mantendo a ordem do arquivo
    int count;
};

MatchList *ml_create(void) {
    MatchList *ml = malloc(sizeof(MatchList));
    if (ml == NULL) {
        return NULL;
    }

    ml->first = NULL;
    ml->last = NULL;
    ml->count = 0;
    return ml;
}

void ml_append(MatchList *ml, Match *m) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return;
    }

    node->match = m;
    node->next = NULL;

    if (ml->last != NULL) {
        ml->last->next = node;
    } else {
        ml->first = node;
    }
    ml->last = node;
    ml->count++;
}

int ml_size(MatchList *ml) {
    return ml->count;
}

Match *ml_get(MatchList *ml, int i) {
    Node *curr = ml->first;
    for (int idx = 0; idx < i; idx++) {
        curr = curr->next;
    }
    return curr->match;
}

void ml_free(MatchList *ml) {
    if (ml != NULL) {
        Node *curr = ml->first;
        while (curr != NULL) {
            Node *next = curr->next;  // guardado antes de liberar o nó
            match_free(curr->match);
            free(curr);
            curr = next;
        }
        free(ml);
    }
}