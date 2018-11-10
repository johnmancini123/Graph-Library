#include "graph.h"
#define FLT_MAX 100
//INITIALIZE
struct graph* init_graph(int directed, int number_of_vertices) {
  struct graph* g = (struct graph*)malloc(sizeof(struct graph) + number_of_vertices*sizeof(struct linkedlist));
  g->directed = directed;
  g->num_vertices = number_of_vertices;
  for (int i = 0; i < number_of_vertices; i++) {
    g->edges[i] = init_linkedlist();
  }
  return g;
}
//ADD AND DELETE
  void graph_add(struct graph *g, int start_vertice, int end_vertice, float weight) {
    ll_add(g->edges[start_vertice], end_vertice, weight);
    if (!g->directed) {
      ll_add(g->edges[end_vertice], start_vertice, weight);
    }
  }

  void graph_delete_edge(struct graph *g, int start, int end) {
    for (int i = 0; i < ll_size(g->edges[start]); i++) {
      if(ll_get_neighbor(g->edges[start], i) == end) {
        ll_del(g->edges[start], i);
      }
    }
  }
//PRINTER
  void graph_print(struct graph *g) {
    for (int i = 0; i < g->num_vertices; i++) {
      if (ll_size(g->edges[i])) {
        printf("Vertice %d points to vertices\n", i);
        ll_print(g->edges[i]);
        puts("");
      }
    }
  }
//GRAPH QUALITIES
  int in_degree(struct graph *g, int vertice) {
    return (ll_size(g->edges[vertice]));
  }

  int num_nodes(struct graph *g) {
    return (g->num_vertices);
  }

  int has_edge(struct graph* g, int a, int b) {
    int toRet = 0;
    for (int i = 0; i < ll_size(g->edges[a]); i++) {
      if (b == ll_get_neighbor(g->edges[a], i)) {
        toRet = 1;
        break;
      }
    }
    return toRet;
  }

  float edge_weight(struct graph *g, int a, int b) {
    float toRet = -1;
    if (has_edge(g, a, b)) {
      for (int i = 0; i < ll_size(g->edges[a]); i++) {
        if (b == ll_get_neighbor(g->edges[a], i)) {
          toRet = ll_get_weight(g->edges[a], i);
        }
      }
    }
    return toRet;
  }
//BREADTH_FIRST_SEARCH
  int* breadth_first_search(struct graph *g, int s) {
    int *dist = (int*)malloc(sizeof(int) * num_nodes(g));

    for (int i = 0; i<num_nodes(g); i++) {
      dist[i] = INT_MAX;
    }

    dist[s] = 0;

    struct queue *q = init_queue();
    q_add(q, s);

    int u;
    int v;

    while(!is_empty(q)) {
      u = q_del(q);
      for (int i = 0; i < ll_size(g->edges[u]); i++) {
        v = ll_get_neighbor(g->edges[u], i);
        if (dist[v] == INT_MAX) {
          q_add(q, v);
          dist[v] = dist[u] + 1;
        }
      }
    }

    return dist;

  }
//DEPTH_FIRST_SEARCH
  void depth_first_search(struct graph *g, int v) {
    int visited[num_nodes(g)];

    for (int i = 0; i < num_nodes(g); i++) {
      visited[i] = 0;
    }

    printf("DFS node order\n");
    explore(g, v, visited);
    for (int i = 0; i < num_nodes(g); i++) {
      if (!visited[i]) {
        printf("Next connected component\n");
        explore(g, i, visited);
      }
    }
  }

  void explore(struct graph *g, int v, int *visited) {
    visited[v] = 1;
    printf("%d\n", v);

    for (int i = 0; i < ll_size(g->edges[v]); i++) {
      if (!visited[ll_get_neighbor(g->edges[v], i)]) {
        explore(g, ll_get_neighbor(g->edges[v], i), visited);
      }
    }
  }
//DIJKSTRAS_SHORTEST_PATH
  void dijkstras_shortest_path(struct graph* g, int s) {
    int V = num_nodes(g);
    float dist[V]; //an array to maintain distances
    int set[V];

    for (int i = 0; i < V; i++) {
      dist[i] = FLT_MAX;
      set[i] = 0;
    }
    dist[s] = 0;


    for (int i = 0; i < V-1; i++) { //iterate through every node getting the smallest not in set at beginning
      int u = min_distance(dist, set, V);
      set[u] = 1;

      for (int i = 0; i < ll_size(g->edges[u]); i++) { //for all adjacent nodes to current lowest distance from source node
        int v = ll_get_neighbor(g->edges[u], i);
        //if adjacent node is not in set, distance to u is not infinity and dist to u + l(u, v) < dist[v]
        if (!set[v] && dist[u] != FLT_MAX && dist[u] + edge_weight(g, u, v) < dist[v]) {
          dist[v] = dist[u] + edge_weight(g, u, v);
        }
      }
    }

    //final results
    printf("SHORTEST PATH FROM SOURCE\n");
    for (int i = 0; i < V; i++) {
      printf("node %d is %.2f distance away from %d\n", i, dist[i], s);
    }
  }

  int min_distance(float dist[], int set[], int V) {
    int index_to_ret = -1;
    float min = FLT_MAX;

    for (int i = 0; i < V; i++) {
      if (!set[i] && (dist[i] < min)) {
        min = dist[i];
        index_to_ret = i;
      }
    }
    return index_to_ret;
  }
