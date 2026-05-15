#include "edge_class.hpp"
#include "graph_class.hpp"
#include "contenitori_class.hpp"
#include <map>
#include <queue>
#include <limits>
#include <optional>

/* Funzione di visita di grafi con DFS o BFS */
// avendo "uniformato" i metodi di stack e queue sotto un unico nome, a seconda del tipo di contenitore dato in input
template<typename T>
unidirected_graph<T> graph_visit(const unidirected_graph<T>& G, const T& nodo_start, auto& cont) {

    std::set<T> nodi = G.all_nodes();
    std::map<T,bool> reached; // reached è una mappa che associa ad ogni nodo (chiave di tipo T) il booleano
    for (auto  u = nodi.begin(); u != nodi.end(); u++) {
        reached[*u] = false;      //Inizializzo reached con tutti False
    }

    reached[nodo_start] = true;
    cont.put(nodo_start);

    unidirected_graph<T> albero_visita;

    while (!cont.empty()) {

        T u = cont.get();

        std::set<T> vicini_u = G.neighbours(u);
        for (auto w = vicini_u.begin(); w != vicini_u.end(); w++) {
            if (!reached[*w]) {
                reached[*w] = true;
                cont.put(*w);
                albero_visita.add_edge(u,*w); // se w è visitato, allora aggiungo l'arco (u,w) all'albero di visita     
            }
        } // poichè il nostro grafo non è orientato, la lista di adiacenza di un nodo u (LA[u]) corrisponede all'insieme dei vicini di u (neighbours(u))
    }
return albero_visita;
}


/* DFS ricorsivo */
// si implementa un DFS ricorsivo (questa volta INDIPENDENTEMENTE dal tipo di contenitore dato)
// si richiama ricorsivamente il metodo chiamandolo con il nodo sorgente aggiornato
// nella versione ricorsiva non serve implementare direttamente uno stack poichè il meccanismo delle chiamate ricorsive implicitamente crea uno stack (LIFO)
// interno alla memoria del sistema
// --> il nodo viene aggiunto in cima quando la funzione ricorsiva è chiamata rispetto a tale nodo
// --> il nodo viene rimosso per primo quando la funzione finisce di operare 

template<typename T>
void dfs_fake(const unidirected_graph<T>& G, const T& u, std::map<T,bool>& reached, unidirected_graph<T>& albero_visita) { //--> il nodo u viene aggiunto in cima

    reached[u] = true;

    std::set<T> vicini_u = G.neighbours(u);
        for (auto w = vicini_u.begin(); w != vicini_u.end(); w++) {
            if (!reached[*w]) {
                albero_visita.add_edge(u,*w);
                dfs_fake(G, *w, reached, albero_visita); // --> processo il nodo successivo
            }
        } // --> il nodo viene rimosso (dopo aver processato ricorsivamente, l'ultimo nodo che sarà inserito verrà rimosso: dopodichè si procede a ritroso sui padri)
}

template<typename T>
unidirected_graph<T> recursive_dfs(const unidirected_graph<T>& G, const T& nodo_start) {

    std::set<T> nodi = G.all_nodes();
    std::map<T,bool> reached;
    for (auto  u = nodi.begin(); u != nodi.end(); u++) {
        reached[*u] = false;      
    }

    unidirected_graph<T> albero_visita;

    dfs_fake(G, nodo_start, reached, albero_visita);

return albero_visita;
} 


/* Algoritmo di Dijkstra */

template<typename T>
unidirected_graph<T> dijkstra(const unidirected_graph<T>& G, const T& nodo_start) {

    std::set<T> nodi = G.all_nodes();
    std::map<T,std::optional<T>> pred; // mappa con (nodo,predecessore) dove il predecessore è rappresentato dal puntatore
    std::map<T,double> dist; //mappa con (nodo, distanza dal nodo sorgente)

    for (auto  u = nodi.begin(); u != nodi.end(); u++) { // inizializzo le mappe con valori flag
        pred[*u] = std::nullopt;
        dist[*u] = std::numeric_limits<double>::infinity();
    }

    dist[nodo_start] = 0.0; // il nodo sorgente ha distanza nulla da sè stesso

    // inizializzo la coda con priorità
    std::priority_queue<
    std::pair<double,T>,  //tipo
    std::vector<std::pair<double, T>>, //contenitore
    std::greater<std::pair<double,T>> //comparatore
    > pq;

    pq.push({dist[nodo_start],nodo_start}); //enqueue del nodo sorgente

    while (!pq.empty()) {
        auto [p, u] = pq.top(); // dequeue della coppia con priorità (distanza minima)
        pq.pop();

        if (p > dist[u]) continue; // controllo di validità della priorità (se )

        std::set<T> vicini_u = G.neighbours(u);
        for (auto w = vicini_u.begin(); w != vicini_u.end(); w++) {

            double peso_uw = G.get_weight(u,*w);

            if (dist[*w]>dist[u]+peso_uw) {
                dist[*w]=dist[u]+peso_uw;
                pred[*w]=u;
                pq.push({dist[*w],*w}); // inserisco la nuova coppia
            }
        }
    }

    unidirected_graph<T> cammino_minimo; // inizializzo il grafo di cammino minimo

    std::set<T> nodi_cammino = G.all_nodes(); // passo al cammino i nodi del grafo

    for (const auto& [nodo, predecessore] : pred) { // ciclo sulle coppie per accedere ai predecessori e costruire il cammino in base alla mappa ricavata prima

        if (predecessore != std::nullopt) {
            T u = *predecessore; // recupero un nodo di tipo T da un tipo std::optional<T>
            T v = nodo; // recupero il successivo nodo
            double peso = G.get_weight(u,v); // recupero il peso dell'arco

            cammino_minimo.add_edge(u, v, peso);
        }
    }

    return cammino_minimo; // restituisce l'albero contenente i percorsi meno costosi per arrivare a tutti nodi a partire dal nodo sorgente (nel main ho messo 1)
}

