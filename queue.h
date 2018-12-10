#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct q_node {
  struct q_node *next;
  int vertice;
};

struct queue {
  struct q_node *head;
  struct q_node *tail;
  int size;
};

struct queue* init_queue();
int q_size(struct queue *q);
void q_add(struct queue *q, int vertice);
int q_del(struct queue *q);
void q_print(struct queue *q);
int is_empty(struct queue *q);
int peek(struct q_node *temp);
int q_del_min(struct queue *q);
void q_deallocate(struct queue *q);
#endif
