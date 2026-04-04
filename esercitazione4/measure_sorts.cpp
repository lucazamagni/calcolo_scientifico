#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>

#include "alg_sorting.hpp"
#include "randfiller.h"
#include "timecounter.h"


// E' NECESSARIO COMPILARE QUESTO FILE INSIEME A timecounter.cpp PERCHE' ESSO CONTIENE LE ISTRUZIONI SU tic e toc CHE INVECE 
// L'HEADER timecounter.h NON CONTIENE

int main() {

std::vector<int> dim_vec;
dim_vec.resize(13);
for (int i=0; i<13; i+=1) {
    dim_vec[i]=std::pow(2,i+1); //Creo il vettore con le dimensioni dei vettori da testare
}


randfiller rf; //Inizializzo le classi
timecounter tc;

std::vector<double> double_vec;

std::vector<double> bubble_times(dim_vec.size()); //Inizializzo i vettori che conterranno gli elapse_time di ogni algoritmo
std::vector<double> insertion_times(dim_vec.size());
std::vector<double> selection_times(dim_vec.size());
std::vector<double> stdsort_times(dim_vec.size());

for (int i=0; i<13; i+=1) {

    double_vec.resize(dim_vec[i]); //Do la dimensione giusta al vettore da riempire con numeri casuali

    rf.fill(double_vec, -10000.0, 10000.0); //Riempo il vettore (e lo rifaccio sempre perchè altrimenti gli alg. successivi agiscono su un vettore già ordinato)
    tc.tic(); //Inizio a misurare il tempo
    bubblesort(double_vec);
    double bubble_secs = tc.toc(); //Finisco di misurare il tempo
    bubble_times[i]=bubble_secs; //Salvo il tempo nel vettore dei tempi 

    rf.fill(double_vec, -10000.0, 10000.0);
    tc.tic();
    insertionsort(double_vec);
    double insertion_secs = tc.toc();
    insertion_times[i]=insertion_secs;

    rf.fill(double_vec, -10000.0, 10000.0);
    tc.tic();
    selectionsort(double_vec);
    double selection_secs = tc.toc();
    selection_times[i]=selection_secs;

    rf.fill(double_vec, -10000.0, 10000.0);
    tc.tic();
    std::sort( double_vec.begin() , double_vec.end() );
    double stdsort_secs = tc.toc();
    stdsort_times[i]=stdsort_secs;
    
}

std::cout << "Vettore delle dimensioni: ";
print_vector(dim_vec);
std::cout << "Vettore dei tempi del bubblesort: ";
print_vector(bubble_times);
std::cout << "Vettore dei tempi del insertionsort: ";
print_vector(insertion_times);
std::cout << "Vettore dei tempi del selectionsort: ";
print_vector(selection_times);
std::cout << "Vettore dei tempi del std::sort: ";
print_vector(stdsort_times);

// std::sort risulta essere il più veloce (utilizza metodi efficienti) --> O(nlogn)
// i tre restanti risultano più lenti --> O(n^2)

}

// Vettore delle dimensioni: 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192
// Vettore dei tempi del bubblesort: 1.4001e-05 7.12e-07 1.172e-06 3.598e-06 1.2747e-05 4.6601e-05 0.000184561 0.000890827 0.00351343 0.0131466 0.0518655 0.246116 1.0794
// Vettore dei tempi del insertionsort: 4.91e-07 3.71e-07 6.51e-07 1.493e-06 4.279e-06 1.373e-05 6.8158e-05 0.000198582 0.000761465 0.00313223 0.0118362 0.0617262 0.204089
// Vettore dei tempi del selectionsort: 4.71e-07 5.51e-07 1.072e-06 2.566e-06 8.067e-06 2.7499e-05 9.8644e-05 0.000369914 0.00149593 0.00593843 0.0247208 0.0940776 0.582836
// Vettore dei tempi del std::sort: 7.92e-07 8.72e-07 1.043e-06 2.305e-06 7.406e-06 1.4651e-05 3.3533e-05 7.5755e-05 0.000167905 0.000356976 0.000776007 0.00197382 0.00513495