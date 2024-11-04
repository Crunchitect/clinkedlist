#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define new(x) (x*)malloc(sizeof(x))

typedef struct Node {
    void* data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
} LinkedList;

LinkedList* _l_from(int length, size_t sz, void* data) {
    LinkedList* ll = new (LinkedList);
    ll->head = NULL;
    ll->tail = NULL;

    if (!length) return ll;

    for (int i = 0; i < length; i++) {
        Node* node = new (Node);
        node->data = malloc(sz);
        memcpy(node->data, (char*)data + (i * sz), sizeof(sz));

        // No elems.
        if (!ll->tail) {
            ll->head = node;
            ll->tail = node;
            node->prev = NULL;
            node->next = NULL;
            continue;
        }

        node->prev = ll->tail;
        node->next = NULL;
        ll->tail->next = node;
        ll->tail = node;
    }
    return ll;
}
#define l_from(len, dtype, data) _l_from(len, sizeof(dtype), data)

int l_free(LinkedList* ll) {
    for (Node* node = ll->head->next; node; node = node->next) {
        free(node->prev->data);
        free(node->prev);
    }
    free(ll->tail->data);
    free(ll->tail);
    free(ll);
}

int l_length(LinkedList* ll) {
    int len = 0;
    for (Node* node = ll->head; node; node = node->next, len++);
    return len;
}

void* l_at(LinkedList* ll, int idx) {
    int len = l_length(ll);
    int new_idx = idx;
    new_idx = (idx + len) % len;
    Node* node = ll->head;
    for (; node && new_idx; node = node->next, new_idx--);
    if (new_idx) fprintf(stderr, "Index Error\n");
    return node->data;
}

void _l_push(LinkedList* ll, int sz, void* data) {
    Node* new_node = new (Node);
    new_node->data = malloc(sz);
    memcpy(new_node->data, &data, sz);
    new_node->prev = ll->tail;
    new_node->next = NULL;
    ll->tail->next = new_node;
    ll->tail = new_node;
    if (!ll->head) ll->head = new_node;
}
#define l_push(ll, dtype, data) _l_push(ll, sizeof(dtype), (void*)data)

void* l_pop(LinkedList* ll) {
    if (!ll->tail) fprintf(stderr, "tf you poppin?");
    Node* old_tail = ll->tail;
    void* old_tail_data = old_tail->data;
    ll->tail = ll->tail->prev;
    free(old_tail);
    return old_tail_data;
}

int main() {
    int test[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    LinkedList* l = l_from(10, int, test);
    l_push(l, int, 4);
    printf("%d\n", *(int*)l_at(l, -1));
    printf("%d\n", *(int*)l_pop(l));
    l_free(l);
    return 0;
}
