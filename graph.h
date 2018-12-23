#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <limits.h>
#include "queue.h"
//#include <float.h>

struct graph {
  int directed;
  int cyclic;
  int num_vertices;
  int num_edges;
  int *in_degree;
  struct linkedlist* edges[]; //each vertice has a linked list that points to
                                                //all of its edges
};
//initialize graph
struct graph* init_graph(int directed, int number_of_vertices);
//to add edge or delete edge
void graph_add(struct graph* g, int start_vertice, int end_vertice, float edge_weight);
void graph_delete_edge(struct graph *g, int start, int end);
//printer
void graph_print(struct graph *g);
//graph qualities
int get_in_degree(struct graph *g, int vertice);
int num_nodes(struct graph *g);
int num_edges(struct graph *g);
int has_edge(struct graph* g, int a, int b);
float edge_weight(struct graph *g, int a, int b);
//algorithms
int* breadth_first_search(struct graph *g, int s); //bfs

void depth_first_search(struct graph *g, int v); //dfs
void explore(struct graph *g, int v, int *visited);

void dijkstras_shortest_path(struct graph* g, int s); //dijkstras
int min_distance(float dist[], int set[], int V);

void prims(struct graph *g);

void kahns(struct graph *g);
//to deallocate
struct graph* graph_clone(struct graph *g);
void graph_deallocate(struct graph *g);

#endif
