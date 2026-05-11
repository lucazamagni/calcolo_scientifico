// std::list è una sequenza di elementi in cui ogni elemento è collegato al successivo e al precedente (per arrivare al decimo devo scorrere i primi nove)
// std::set contiene una collezione di oggetti unici, ordinati automaticamente secondo un criterio, mantiene gli elementi sempre ordinati dopo ogni modifica
// std::map associa una chiave (Key) a un valore (T), e le chiavi sono uniche e ordinate
// std::unordered_map simile a std::map, associa chiavi a valori, ma non garantisce alcun ordine (non ci si può quindi iterare)

#pragma once
#include <iostream>
#include <set>
#include "edge_class.hpp"

template<typename T>
class unidirected_graph {
    // set è molto comodo per confrontare archi e nodi perchè mantengono lo stesso ordine
    std::set<T> nodi; 
    std::set<unidirected_edge<T>> archi;
    
public:

/* Costruttore di default */ 
// Chiamando la classe si inizializzano le strutture di default
// Inizializzo i set vuoti
unidirected_graph() {};


/* Costruttore di copia */
// Se utilizzo un tipo di sequenza non ordinata, se l'user definisce il grafo in modo disordinato esso resta disordinato
// Utilizzando set, che utilizza una logica del tipo operator<, la sequenza viene ordinata

// ha sintassi del tipo unidirected_graph(grafo)
unidirected_graph(const unidirected_graph& other) {}; //other-->grafo


/* Metodo che restituisce i vicini di un nodo */
//Dato un nodo target, restituisce il set dei nodi vicini
std::set<T> neighbours(const T& nodo_target) const { // non modifica l'oggetto
    std::set<T> vicini;
    for (auto& e : archi) { //auto rappresenta la deduzione AUTOMATICA del tipo
        if (e.from() == nodo_target) {vicini.insert(e.to());}
        else if (e.to() == nodo_target) {vicini.insert(e.from());}
    }
    return vicini;
}


/* Metodo che aggiunge un arco al grafo */
// Dati due nodi target, verifico se esiste già un arco che li collega, altrimenti lo creo
// Non distinguo nodo di partenza e nodo di arrivo perchè il grafo non è orientato
void add_edge(const T& nodo1, const T& nodo2) { // non metto const perchè il set archi viene modificato!
    // Seguendo la logica data nella classe degli archi, non è necessario verificare che (nodo1,nodo2)=(nodo2,nodo1)
    // Il set controlla da solo se esiste già l'arco
    nodi.insert(nodo1);
    nodi.insert(nodo2); // Li inserisco nel set dei nodi: se già esistono non succede nulla, se solo uno esiste creo un nuovo arco connesso, se nessuno dei due esiste creo un arco sconnesso
    unidirected_edge<T> arco_nuovo(nodo1,nodo2);
    archi.insert(arco_nuovo);
}


/* Metodo che restituisce tutti gli archi */
const std::set<unidirected_edge<T>>& all_edges() const { //lo memorizzo come una costante in modo tale che non siano autorizzate modifiche (se non con metodi autorizzati che ho definito nella classe)
    return archi;
}


/* Metodo che restituisce tutti i nodi */
const std::set<T>& all_nodes() const {
    return nodi;
}


/* Metodo che restituisce la numerazione di un arco all'interno del grafo */
// std::set è implementato con un albero red-black
// Tramite il comando "set".find() che implementa il BST trovo la posizione di un dato arco e lo salvo in un iteratore (simile ad un puntatore e permette di iterare su strutture come se fossero arrays)
// dopodichè conto la distanza di tale arco dall'inizio dell'albero con std::distance
// (sfrutta un algoritmo di visita dei grafi simile al DFS, che tiene conto della relazione d'ordine che esiste tra nodi e archi in memoria)
// considero tale posizione +1 perchè la distanza fornisce il numero di passi che distanziano i due archi nell'ordine (l'arco 3 dista 2 dal primo,...)
int edge_number(const unidirected_edge<T>& arco_target) const {
    /* auto itor = archi.find(arco_target);
    if (itor != archi.end()) { //se l'arco non è nel grafo l'iteratore arriva fino alla fine
        return std::distance(archi.begin(),itor)+1; 
    }
    else {
        std::cerr << "Arco non esistente" << std::endl;
        return -1;
    } */
    int num = 1;
    for (auto  itor = archi.begin(); itor != archi.end(); itor++) { //Ciclo sull'iteratore
        if (*itor == arco_target) { //Quando trovo l'arco puntato dall'iteratore restituisco il numero di passi fatti per trovarlo (al passo 0 num=1, infatti l'arco iniziale è l'arco 1)
            return num;
        }
        num=num+1;
    }
    std::cerr << "Arco non esistente" << std::endl; //Se il ciclo finisce senza averlo trovato
    return -1;
}
    

/* Metodo che restituisce l'arco dato il suo numero all'interno del grafo */
const unidirected_edge<T>& edge_at(int num) const {
    int max = archi.size();
    if (num < 1 || num > max) {
        std::cerr << "Numero dell'arco fuori dai limiti" << std::endl;
        throw std::invalid_argument("L'arco cercato non esiste nel set."); // mi permette di non forzare l'uscita e di continuare a far funzionare il programma
    }
    auto itor = archi.begin(); //Inizializzo l'iteratore all'inizio
    for (int i=1; i<num; i=i+1) { //Lo faccio scorrere fino alla posizione cercata
        itor++;
    }
    return *itor; //Dereference dell'oggetto puntato dall'iteratore
}


/* Operatore di differenza fra grafi (la differenza G-G' è data dai grafi presenti in G e non in G') */
// Returno il grafo dato dalla differenza
unidirected_graph operator-(const unidirected_graph& other) const {
    // Versione ottimizzata tramite la funzione find
    /* for (auto itor1 = archi.begin(); itor1 != archi.end(); itor1++) {
        if (other.archi.find(*itor1) == other.archi.end()) {  //se arriva alla fine allora non l'ho trovato
            differenza.archi.insert(*itor1);
        }
    }
    */
    unidirected_graph differenza;
    differenza.nodi = nodi;
    for (auto itor1 = archi.begin(); itor1 != archi.end(); itor1++) { //Faccio un doppio ciclo annidato per vedere quali archi si trovano in G e non in G'
        bool found_in_other = false;
        for (auto itor2 = other.archi.begin(); itor2 != other.archi.end(); itor2++) {
            if (*itor1 == *itor2) {
                found_in_other = true;
                break; //se l'ho trovato, significa che non lo devo aggiungere alla differenza
            }
        }
        if (found_in_other == false) {
            differenza.archi.insert(*itor1);
        }
    }
    return differenza;
}


/* Funzioni di print per visualizzare i test su archi e grafi */


void print_nodes(std::set<T> nodi) const {
    if (nodi.empty()) {
        std::cout << "Non ci sono nodi. \n";
    }
    else {
        for (auto& nodo : nodi) {
            std::cout << nodo << "\n";
        }
    }
}


void print_graph() const {
    std::cout << "Nel grafo ci sono " << nodi.size() << " nodi e " << archi.size() << " archi: \n";
    if (archi.empty()) {
        std::cout << "Il grafo è vuoto. \n";
    }
    else {
        for (auto& e : archi) {
            std::cout << e << std::endl;
        }
    }
}

};
