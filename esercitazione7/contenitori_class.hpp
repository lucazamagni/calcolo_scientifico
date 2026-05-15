// std::list è una sequenza di elementi in cui ogni elemento è collegato al successivo e al precedente (per arrivare al decimo devo scorrere i primi nove)
// std::set contiene una collezione di oggetti unici, ordinati automaticamente secondo un criterio, mantiene gli elementi sempre ordinati dopo ogni modifica
// std::map associa una chiave (Key) a un valore (T), e le chiavi sono uniche e ordinate
// std::unordered_map simile a std::map, associa chiavi a valori, ma non garantisce alcun ordine (non ci si può quindi iterare)


#pragma once
#include <queue>
#include <stack>

template<typename T>
class fifo { // First In First Out

    std::queue<T> q;

public:

/* Costruttuore di default */
fifo() {};

/* Metodi */
void put(T val) {q.push(val);}
T get() {
    T val = q.front();
    q.pop();
return val;
}
bool empty() {return q.empty();}
};


template<typename T>
class lifo { // First In First Out

    std::stack<T> s;

public:

/* Costruttuore di default */
lifo() {};

/* Metodi */
void put(T val) {s.push(val);}

T get() {
    T val = s.top();
    s.pop();
return val;
}

bool empty() {return s.empty();}

};
