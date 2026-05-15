#pragma once
#include <iostream>

template<typename T>
class unidirected_edge {

    T nodo_start;
    T nodo_end;
    double peso; // aggiungo il peso


public:

/* Costruttore */ // Accetto i due nodi che ho come input e mi assicuro già ora che quello iniziale ha valore minore di quello finale
unidirected_edge(const T& u, const T& v, double weight = 1.0) {  
peso = weight;
if (u < v) {
            nodo_start = u;
            nodo_end = v;
        } else {
            nodo_start = v;
            nodo_end = u;
        }
}


/* Metodi from , to */
T from() const {return nodo_start;}
T to() const {return nodo_end;}
double get_weight() const {return peso;}

/* Implementazione operatori di confronto (tramite i nodi)*/

bool operator<(const unidirected_edge& other) const { 
   if (nodo_start < other.nodo_start) {return true;}
   else if (nodo_start > other.nodo_start) {return false;}
   else {
    if (nodo_end < other.nodo_end) {return true;}
    else {return false;}
}
}

bool operator==(const unidirected_edge& other) const {
   if (nodo_start == other.nodo_start && nodo_end == other.nodo_end) {return true;}
   else {return false;}
}

};


template<typename T>
std::ostream&
operator<<(std::ostream& os, const unidirected_edge<T>& edge){
    os << "( " << edge.from() << " , " << edge.to() << " )";
    return os;
}
