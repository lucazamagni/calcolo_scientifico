#include "alg_sorting.hpp"
#include "randfiller.h"
#include <vector>
#include <cstdlib>

int main() {

randfiller rf;
std::vector<int> dim_vec;
dim_vec.resize(100);
rf.fill(dim_vec, 10, 10000); //Genero un vettore contenente le 100 dimensioni casuali dei vettori con cui testerò gli algoritmi


std::vector<double> double_vec;
bool flag; //Non c'è bisogno di gestire con optional il caso del vettore nullo poichè genero dimensioni dei vettori tutte >0

for (int i=0; i<=99; i+=1){

    double_vec.resize(dim_vec[i]);
    rf.fill(double_vec, -10000.0, 10000.0);

    selectionsort(double_vec);

    flag=is_sorted(double_vec);
    if (flag==false) {
        std::cout << "Failure \n";
        return EXIT_FAILURE;} // Se in uno dei 100 vettori l'algoritmo fallisce esco e segnalo il fallimento (1)
}

std::vector<std::string> str_vec = {"Z","Ciao","0","Zante","45","41","a","zante","£","A"};
bool flag2;

selectionsort(str_vec);

flag2=is_sorted(str_vec);
if (flag2==false) {
    std::cout << "Failure \n";
    return EXIT_FAILURE;}

std::cout << "Success \n";
return EXIT_SUCCESS;
}
