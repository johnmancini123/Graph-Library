#include "graph.h"
#define FLT_MAX 100
//INITIALIZE
struct graph* init_graph(int directed, int number_of_vertices) {
  struct graph* g = (struct graph*)malloc(sizeof(struct graph) + number_of_vertices*sizeof(struct linkedlist));
  g->directed = directed;
  if (directed) {
    g->in_degree = (int*)malloc(sizeof(int) * number_of_vertices);
    for (int i = 0; i <  number_of_vertices; i++ ) {
      g->in_degree[i]= 0;
    }
  }
  g->num_vertices = number_of_vertices;
  for (int i = 0; i < number_of_vertices; i++) {
    g->edges[i] = init_linkedlist();
  }
  g->cyclic = 0;
  return g;
}
//ADD AND DELETE
  void graph_add(struct graph *g, int start_vertice, int end_vertice, float weight) {
    if ((is_in_node(g, end_vertice) &&  is_in_node(g, start_vertice)) ||  is_out_node(g, end_vertice)) {
         g->cyclic=1;
    }
   
    ll_add(g->edges[start_vertice], end_vertice, weight);
    if (!g->directed) {
      ll_add(g->edges[end_vertice], start_vertice, weight);
    }
    else {
      g->in_degree[end_vertice]++;
    }
    g->num_edges++;
  }

  void graph_delete_edge(struct graph *g, int start, int end) {
    for (int i = 0; i < ll_size(g->edges[start]); i++) {
      if (ll_get_neighbor(g->edges[start], i) == end) {
        ll_del(g->edges[start], i);
        if (!g->directed) {
          ll_del(g->edges[end], start);
        }
        else {
          g->in_degree[end]--;
        }
      }
    }
    g->num_edges--;
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
  int is_out_node(struct graph *g, int v){
    if (ll_size(g->edges[v])) return 1;
    return 0;
  }

  int is_in_node(struct graph *g, int vertice) {
    for (int v = 0; v < num_nodes(g); v++) {
      for (int u = 0; u < ll_size(g->edges[v]); u++) {
        if (ll_get_neighbor(g->edges[v], u)  == vertice) return 1;
      }
    }
    return 0;
  }

  int get_in_degree(struct graph *g, int vertice) {
    return g->in_degree[vertice];
  }

  int num_nodes(struct graph *g) {
    return (g->num_vertices);
  }

  int num_edges(struct graph *g) {
    return (g->num_edges);
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

  float edge_weight(struct graph *g,
    int a, int b) {
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

//PRIMS
  void prims(struct graph *g) {
    struct linkedlist *mst = init_linkedlist(); // holds all the nodes in the mst and the weights that connect them

    float min; //to track minimum edge weight
    int minVertice; //vertice pointed to by that edge
    int currentVertice; //current vertice in the mst we are looking at
    int verticeToPrint; //simply to mainting the vertice that is in the set connected to an outside vertice with the lowest edge
    ll_add(mst, 0, 0.0);

    puts("Resulting Minimum Spanning Tree");

    if (g->directed) {
    }
    else { //for undirected graph
      while (ll_size(mst) < num_nodes(g)){ //mst size < number of nodes in the graph
        min = FLT_MAX;
        for (int i = 0; i < ll_size(mst); i++) {
          currentVertice = ll_get_neighbor(mst, i); //get a node from mst
          for (int j = 0; j < ll_size(g->edges[currentVertice]); j++) {
            int tempV = ll_get_neighbor(g->edges[currentVertice],j); //look at vertices it points to
            if (!ll_in(mst, tempV)) { //if node connected to by current node in set does is not also in set
              float tempWeight = ll_get_weight(g->edges[currentVertice],j); //get that edges weight
              if (tempWeight < min) { //if its less than min, set it as min
                min = tempWeight;
                minVertice = tempV;
                verticeToPrint = currentVertice;
              }
            }

          }
        }
        printf("(%d)-----%.2f-----(%d)\n", verticeToPrint, min, minVertice);
        ll_add(mst, minVertice, min);
      }
    }
    puts("");
    float sum = 0;
    for (int v = 0; v < ll_size(mst);v++) {
      sum += ll_get_weight(mst, v);
    }
    printf("Sum of minimum spanning tree = %.2f\n", sum);

    ll_deallocate(mst);
  }

  //kahns
  void kahns(struct graph *g) {
    if (!(g->directed && !g->cyclic)) {
      puts("Graph is not a DAG");
      return;
    }
    struct graph *toSort = graph_clone(g); //getting clone graph
    int topSort[num_nodes(g)]; //will contain the resulting order of topological sort
    int deletedNodes[num_nodes(g)];
    for (int i = 0; i < num_nodes(g);i++) {
      deletedNodes[i] = 0;
    }
    int i = 0;
    int j = 0;
//while graph has remaininf edges    
    while (j++ < num_nodes(toSort)) { 
      for (int v = 0; v < num_nodes(toSort); v++) {
       //if indegree to vertice is 0 and  it hasnt been deleted
        if (get_in_degree(toSort, v) == 0  && !deletedNodes[v] ) {   
          for (int u =  ll_size(toSort->edges[v])-1; u >=0; u--) {
      //delete all edges from that node     
            if (has_edge(toSort,  v,ll_get_neighbor(toSort->edges[v], u)))    
               graph_delete_edge(toSort, v,   ll_get_neighbor(toSort->edges[v], u));
          }
     //mark it as deleted and add it to top sort array
          deletedNodes[v] = 1;
          topSort[i++] = v;
        }
      }
    }

    graph_deallocate(toSort);

//printing topological sort
    puts("Topological Sort:");
    for (int i = 0; i < num_nodes(g); i++) {
      if (i==num_nodes(g)-1)
        printf("%d", topSort[i]);
      else {
        printf("%d->",topSort[i]);
      }
    }
    puts("");
  }

//END OF ALGORITHMS
  struct graph* graph_clone(struct graph *g) {
    struct graph *toRet = init_graph(g->directed, num_nodes(g));
    //cloning graph
    for (int i = 0; i < num_nodes(g); i++) {
      for (int j = 0; j < ll_size(g->edges[i]); j++) {
        graph_add(toRet, i, ll_get_neighbor(g->edges[i], j), ll_get_weight(g->edges[i], j));
      }
    }
    return toRet;
  }
  void graph_deallocate(struct graph *g) {
    for (int i = 0; i < g->num_vertices; i++) {
      ll_deallocate(g->edges[i]);
    }
    if (g->directed) {
      free(g->in_degree);
    }
    g = NULL;
  }
