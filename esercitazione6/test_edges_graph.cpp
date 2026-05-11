#include <iostream>
#include <cstdlib>
#include "edge_class.hpp"
#include "graph_class.hpp"

int main() {

    // TEST SU EDGE
    std::cout << "TEST OPERAZIONI SU ARCHI: \n";

    unidirected_edge<int> arco1(10,20);
    unidirected_edge<int> arco2(20,30);
    unidirected_edge<int> arco3(10,20);

    if (arco2.operator<(arco1) || arco1.operator==(arco2) || !arco1.operator==(arco3)) {
        std::cerr << "Test fallito." << std::endl;
        return EXIT_FAILURE;}

    std::cout << "--------------------------- \n";

    // TEST SU GRAPH
    std::cout << "TEST OPERAZIONI SU GRAFI: \n";
    std::cout << "GRAFO g1: \n";
    unidirected_graph<int> g1;
    g1.add_edge(10,20);
    g1.add_edge(20,30);
    g1.add_edge(20,40);
    g1.add_edge(0,20);
    g1.add_edge(10,20);
    g1.print_graph();

    if (g1.all_nodes().size() != 5 || g1.all_edges().size() != 4 || g1.neighbours(20).size() != 4) {
        std::cerr << "Test fallito." << std::endl;
        return EXIT_FAILURE;}

    std::cout << "I vicini del nodo 20 in g1 sono: \n";
    g1.print_nodes(g1.neighbours(20));

    std::cout << "L'arco " << unidirected_edge(10,20) << " è il numero " << g1.edge_number(unidirected_edge(10,20)) << "\n";
    std::cout << "L'arco numero 2 è " << g1.edge_at(2) << "\n";
    
    std::cout << "GRAFO g2: \n";
    unidirected_graph<int> g2;
    g2.add_edge(10,20);
    g2.add_edge(20,30);
    g2.print_graph();

    std::cout << "GRAFO g3=g1-g2: \n";
    unidirected_graph<int> g3 = g1.operator-(g2);
    g3.print_graph();

    if (g3.all_edges().size() != 2) {
        std::cerr << "Test fallito." << std::endl;
        return EXIT_FAILURE;}
    
    std::cout << "Test effettuato con successo." << std::endl;
    return EXIT_SUCCESS;
}