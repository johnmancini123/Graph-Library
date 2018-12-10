#include <stdio.h>
#include "linkedlist.h"
#include "graph.h"
#include "queue.h"
int main() {
  struct queue *q = init_queue();
  q_add(q, 1);
  q_add(q, 2);
  q_add(q,3);
  q_print(q);
  q_deallocate(q);
  q_print(q);

  // struct linkedlist *ll = init_linkedlist();
  // ll_add(ll, 1, 2);
  // ll_add(ll, 3, 4);
  // ll_print(ll);
  // ll_deallocate(ll);
  // ll_print(ll);
  //TODO make graph_delete_edge accomodate directed and undirected graphs!


}
