#pragma once
#include <iostream>

template<typename T>
class unidirected_edge {

    T nodo_start;
    T nodo_end;


public:

/* Costruttore */ // Accetto i due nodi che ho come input e mi assicuro già ora che quello iniziale ha valore minore di quello finale
unidirected_edge(const T& u, const T& v) {  
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


/* Implementazione operatori di confronto (tramite i nodi)*/
// Dati due archi e_1 = (u_1, v_1) e e_2 = (u_2, v_2)
// Si confronta u_1 con u_2 :se sono diversi, quello col nodo minore viene prima, se sono uguali, si confronta v_1 con v_2

// aggiungo const perchè questi operatori non modificano l'oggetto

bool operator<(const unidirected_edge& other) const { //returna True se e_1<e_2 e False se > o ==
   if (nodo_start < other.nodo_start) {return true;}
   else if (nodo_start > other.nodo_start) {return false;}
   else {
    if (nodo_end < other.nodo_end) {return true;}
    else {return false;}
}
}

bool operator==(const unidirected_edge& other) const { //returna True se e_1==e_2 e False se !=
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
