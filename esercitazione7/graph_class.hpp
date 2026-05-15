#pragma once
#include <iostream>
#include <set>
#include <string>
#include <optional>
#include <limits>
#include "edge_class.hpp"

template<typename T>
class unidirected_graph {
    std::set<T> nodi;
    std::set<unidirected_edge<T>> archi;
        
public:

/* Costruttore di default */ 
unidirected_graph() {};


/* Costruttore di copia */
unidirected_graph(const unidirected_graph& other) {
    nodi = other.nodi;
    archi = other.archi;
};


/* Metodo che restituisce i vicini di un nodo */
std::set<T> neighbours(const T& nodo_target) const { 
    std::set<T> vicini;
    for (auto& e : archi) {
        if (e.from() == nodo_target) {vicini.insert(e.to());}
        else if (e.to() == nodo_target) {vicini.insert(e.from());}
    }
    return vicini;
}


/* Metodo che aggiunge un arco al grafo */
void add_edge(const T& nodo1, const T& nodo2, double peso = 1.0) {
    nodi.insert(nodo1);
    nodi.insert(nodo2); 
    unidirected_edge<T> arco_nuovo(nodo1,nodo2,peso);
    archi.insert(arco_nuovo);
}


/* Metodo che restituisce tutti gli archi */
const std::set<unidirected_edge<T>>& all_edges() const { 
    return archi;
}


/* Metodo che restituisce tutti i nodi */
const std::set<T>& all_nodes() const {
    return nodi;
}


/* Metodo che restituisce il peso di un arco */
double get_weight(const T& u, const T& v) const {

    unidirected_edge<T> arco_target(u,v);

    auto itor = archi.find(arco_target);

    if (itor != archi.end()) {
        return (*itor).get_weight(); 
    }

    std::cerr << "Arco non esistente tra " << u << " e " << v << std::endl;
    return std::numeric_limits<double>::infinity();
}



/* Metodo che restituisce la numerazione di un arco all'interno del grafo */
int edge_number(const unidirected_edge<T>& arco_target) const {
    int num = 1;
    for (auto  itor = archi.begin(); itor != archi.end(); itor++) { 
        if (*itor == arco_target) {
            return num;
        }
        num=num+1;
    }
    std::cerr << "Arco non esistente" << std::endl;
    return -1;
}
    

/* Metodo che restituisce l'arco dato il suo numero all'interno del grafo */
const unidirected_edge<T>& edge_at(int num) const {
    int max = archi.size();
    if (num < 1 || num > max) {
        std::cerr << "Numero dell'arco fuori dai limiti" << std::endl;
        throw std::invalid_argument("L'arco cercato non esiste nel set."); 
    }
    auto itor = archi.begin(); 
    for (int i=1; i<num; i=i+1) { 
        itor++;
    }
    return *itor; 
}


/* Operatore di differenza fra grafi (la differenza G-G' è data dai grafi presenti in G e non in G') */
unidirected_graph operator-(const unidirected_graph& other) const {

    unidirected_graph differenza;
    differenza.nodi = nodi;
    for (auto itor1 = archi.begin(); itor1 != archi.end(); itor1++) {
        bool found_in_other = false;
        for (auto itor2 = other.archi.begin(); itor2 != other.archi.end(); itor2++) {
            if (*itor1 == *itor2) {
                found_in_other = true;
                break; 
            }
        }
        if (found_in_other == false) {
            differenza.archi.insert(*itor1);
        }
    }
    return differenza;
}


/* Funzione di print per visualizzare grafi su Graphviz*/

void print_dot(const std::string& label) const {
    std::cout << "graph \"" << label << "\" {\n";

    for (const auto& e : archi) {
        std::cout << "  \"" << e.from() << "\" -- \"" << e.to() 
                  << "\" [label=\"" << e.get_weight() << "\"];\n";
    }

    std::cout << "}\n";
}

};

