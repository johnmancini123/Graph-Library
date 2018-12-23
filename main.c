#include <stdio.h>
#include "linkedlist.h"
#include "graph.h"
#include "queue.h"
int main() {

  struct graph *g = init_graph(1, 4);
  graph_add(g, 0, 1, 10);
  graph_add(g, 0, 2, 6);
  graph_add(g, 2, 3, 4);
  graph_add(g, 1,3 ,4);

  graph_print(g);


  for (int i = 0; i < 4; i++) {
    printf("node %d has indegree %d\n", i, get_in_degree(g, i));
  }
  puts("RUNNING KAHNS\n\n");
  kahns(g);

  graph_deallocate(g);
}
