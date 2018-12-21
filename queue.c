#include "queue.h"

struct queue* init_queue() { //initializing ll
  struct queue* q = (struct queue*)malloc(sizeof(struct queue));
  q->head = NULL;
  q->tail = NULL;
  q->size = 0;
  return q;
}

int q_size(struct queue *q) { //returning queue size
  return q->size;
}

void q_add(struct queue *q, int vertice) { //adding to queue
  struct q_node *temp = (struct q_node*)malloc(sizeof(struct q_node));
  temp->vertice = vertice;

  if (q_size(q) == 0) { //if there are no nodes in queue
    q->head = temp;
    q->tail = temp;
    q->tail->next = NULL;
  }
  else { //if there are nodes in queue
    q->tail->next = temp;
    q->tail = temp;
    q->tail->next = NULL;
  }

  q->size++;
}

int q_del(struct queue *q) {
  if (is_empty(q)) {
    return -1;
  }
  struct q_node *temp = q->head;
  q->head = temp->next;
  int toRet = temp->vertice;
  free(temp);
  q->size--;
  return toRet;
}

int q_del_min(struct queue *q) {
  int min = INT_MAX;
  int index_min = 0;
  struct q_node *temp = q->head;
  for (int i = 0; i < q->size; i++) {
    if (peek(temp) < min) {
      min = peek(temp);
      index_min = i;
    }
    temp = temp->next;
  }


  int toRet;
  temp = q->head;
  if (index_min == 0) {
    q->head = temp->next;
    toRet = temp->vertice;
    free(temp);
  }
  else if (index_min == q_size(q)) {
    for (int i = 1; i < q_size(q)-1; i++) {
      temp = temp->next;
    }
    free(temp->next);
    q->tail = temp;
    q->tail->next = NULL;
  }
  else {
    for (int i = 0; i < index_min-1; i++) { //because index is assumed to be 1 more than actual index
      temp = temp->next;
    }
    struct q_node *toDel = temp->next;
    temp->next = temp->next->next;
    free(toDel);
  }

  q->size--;
  return toRet;
}

void q_print(struct queue *q){
  struct q_node *temp = q->head;
  int count = 0;
  printf("[");
  while (temp != NULL) {
    if (count == q_size(q)-1) {
      printf("%d", temp->vertice);
    }
    else {
      printf("%d, ", temp->vertice);
    }
    count++;
    temp = temp->next;
  }

  printf("]\n");
}

int is_empty(struct queue *q) {
  return(!q_size(q));
}

int peek(struct q_node *temp) {
  return temp->vertice;
}

void q_deallocate(struct queue *q) {
	struct q_node *tmp = q->head;
	for (int i = 0; i < q->size; i++) 
	{
		q->head = q->head->next;
		free(tmp);
		tmp = q->head;
	}
	q = NULL;
}
