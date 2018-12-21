#include "linkedlist.h"

struct linkedlist* init_linkedlist() { //initializing ll
  struct linkedlist* ll = (struct linkedlist*)malloc(sizeof(struct linkedlist));
  ll->head = NULL;
  ll->tail = NULL;
  ll->size = 0;
  return ll;
}

int ll_size(struct linkedlist *ll) { //returning queue size
  return ll->size;
}

void ll_add(struct linkedlist *ll, int vertice, float weight) { //adding to queue
  struct ll_node *temp = (struct ll_node*)malloc(sizeof(struct ll_node));
  if (temp == NULL) {
    return;//failure to allocate
  }
  temp->vertice = vertice;
  temp->weight = weight;

  if (ll_size(ll) == 0) { //if there are no nodes in queue
    ll->head = temp;
    ll->tail = temp;
    ll->tail->next = NULL;
  }
  else { //if there are nodes in queue
    ll->tail->next = temp;
    ll->tail = temp;
    ll->tail->next = NULL;
  }

  ll->size++;
}

void ll_del(struct linkedlist *ll, int index) { //removing head of queue and returning its val
  if (index > ll->size - 1) {
    puts("ERROR REMOVING FROM LL");
  }
  else { //deleting head
    struct ll_node *temp = ll->head;
    if (index == 0) {
      ll->head = temp->next;
      free(temp);
    }
    else if (index == ll->size-1) { //deleting tail
      for (int i = 0; i < index - 1; i++) {
        temp = temp->next;
      }
      ll->tail = temp;
      free(temp->next);
      ll->tail->next = NULL;
    }
    else { //deleting some node b/w head and tail
      for (int i = 0; i < index-1; i++) {
        temp = temp->next;
      }
      struct ll_node *toDel = temp->next;
      temp->next = temp->next->next;
      free(toDel);
    }
  }
  ll->size--;
}

void ll_print(struct linkedlist *ll) { //printing values of queue
  struct ll_node *temp = ll->head;

  while (temp != NULL) {
    printf("%d with weight %.2f\n", temp->vertice, temp->weight);
    temp = temp->next;
  }
}

int ll_get_neighbor(struct linkedlist *ll, int index) {
  struct ll_node *temp = ll->head;
  for (int i = 0; i < index; i++) {
    temp = temp->next;
  }
  return temp->vertice;
}

float ll_get_weight(struct linkedlist *ll, int index) {
  struct ll_node *temp = ll->head;
  for (int i = 0; i < index; i++) {
    temp = temp->next;
  }
  return temp->weight;
}

int ll_in(struct linkedlist *ll, int 
vertice){
  struct ll_node *tmp;
  for (int i = 0; i< ll->size; i++) {
    if (vertice == tmp->vertice) return 
    0;
    tmp=tmp->next;
  }
  return 1;
} 

void ll_deallocate(struct linkedlist *ll) {
  struct ll_node *temp;
  for (int i = 0; i < ll->size; i++) {
    temp = ll->head;
    ll->head = ll->head->next;
    free(temp);
  }
  ll = NULL;
}
