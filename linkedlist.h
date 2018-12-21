#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
//This is a linked list that acts as an edge, it is comprised of nodes that
//store int vertice that it points to and weight of the edge.
struct ll_node {
  int vertice; //vertice it points to
  float weight; //weight of edge
  struct ll_node *next;
};

struct linkedlist {
  struct ll_node *head;
  struct ll_node *tail;
  int size;
};

struct linkedlist* init_linkedlist();
int ll_size(struct linkedlist *ll);
void ll_add(struct linkedlist *ll, int vertice, float weight);
void ll_del(struct linkedlist *ll, int index);
void ll_print(struct linkedlist *ll);
int ll_get_neighbor(struct linkedlist *ll, int index);
float ll_get_weight(struct linkedlist *ll, int index);
int ll_in(struct linkedlist *ll, int);
void ll_deallocate(struct linkedlist *ll);
#endif
