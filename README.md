# Graph-Library
I made a graph library in c to get better with pointers, data structures, and algorithms
Every data structure was made from scratch

DESIGN: 
  link-list based graph (each vertice contains a linked list with its adjacent neighbors and their respective weights)
ALGORITHMS:
  Depth First Search 
  
  Breadth First Search using queue
  
  Dijkstra's Shortest Path

  Prim's Minimum Spanning Tree
  
  Kahn's Topological Sort (for DAG)
  
  USER GUIDE:
    To create a graph type in:
    
      struct graph *g = graph_init(1 if directed 0 if not, number of vertices)
    
    To add an edge to the graph:
      graph_add(g, start vertice, end vertie, edge weight)
      
    To print the graph:
      graph_print(g)
