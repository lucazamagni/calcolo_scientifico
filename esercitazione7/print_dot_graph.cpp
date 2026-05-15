#include <iostream>
#include "visit_dfs_dijkstra.hpp"
#include "edge_class.hpp"
#include "graph_class.hpp"
#include "contenitori_class.hpp"

int main() {
    unidirected_graph<int> g;
    
    g.add_edge(1, 2);
    g.add_edge(1, 4);
    g.add_edge(1, 6);
    g.add_edge(1, 3);
    g.add_edge(2, 5);
    g.add_edge(2, 4);
    g.add_edge(2, 7); 
    g.add_edge(3, 6);
    g.add_edge(4, 6);
    g.add_edge(4, 7);
    g.add_edge(5, 7);
    g.add_edge(6, 7);
    g.add_edge(6, 8);
    g.add_edge(7, 9);
    g.add_edge(8, 9);

    g.print_dot("Grafo_Originale");


    // Test visit_graph con FIFO
    fifo<int> q;
    unidirected_graph<int> albero_bfs = graph_visit(g, 1, q);
    albero_bfs.print_dot("Albero_BFS");

    // Test visit_graph con LIFO
    lifo<int> s;
    unidirected_graph<int> albero_dfs = graph_visit(g, 1, s);
    albero_dfs.print_dot("Albero_DFS");

    // Test dfs_recursive 
    unidirected_graph<int> albero_dfs_recursive = recursive_dfs(g, 1);
    albero_dfs_recursive.print_dot("Albero_DFS_recursive");



    unidirected_graph<int> g_weight;
    g_weight.add_edge(1, 2, 2.5);
    g_weight.add_edge(1, 4, 1.0);
    g_weight.add_edge(1, 6, 4.5);
    g_weight.add_edge(1, 3, 3.0);
    g_weight.add_edge(2, 5, 7.0);
    g_weight.add_edge(2, 4, 2.0);
    g_weight.add_edge(2, 7, 5.0); 
    g_weight.add_edge(3, 6, 1.2);
    g_weight.add_edge(4, 6, 2.5);
    g_weight.add_edge(4, 7, 3.5);
    g_weight.add_edge(5, 7, 1.8);
    g_weight.add_edge(6, 7, 1.0);
    g_weight.add_edge(6, 8, 2.2);
    g_weight.add_edge(7, 9, 3.0);
    g_weight.add_edge(8, 9, 1.5);

    g_weight.print_dot("Grafo_Originale_pesato");

    // Test Dijkstra
    unidirected_graph<int> albero_cammino_minimo = dijkstra(g_weight, 1);
    albero_cammino_minimo.print_dot("Albero_cammino_minimo");

    return 0;
}

// ora incollo gli output su Graphviz online