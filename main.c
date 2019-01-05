#include <stdio.h>
#include "linkedlist.h"
#include "graph.h"
#include "queue.h"
int main() {

  struct graph *g = init_graph(1, 6);
  graph_add(g, 5, 2, 10);
  graph_add(g, 5, 0, 6);
  graph_add(g, 4, 0, 4); 
  graph_add(g, 4, 1, 4); 
  graph_add(g, 2, 3, 4); 
  graph_add(g, 3, 1, 4); 
  graph_print(g);
  g->cyclic=0;
  kahns(g);

  graph_deallocate(g);
}
