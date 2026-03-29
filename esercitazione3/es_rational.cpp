#include <iostream>
#include "rational_class.hpp"

int main(void)
{ 
    std::cout << "Inserire il numeratore del primo razionale: \n";
    int num_a;
    std::cin >> num_a;
    std::cout << "Inserire il denominatore del primo razionale: \n";
    int den_a;
    std::cin >> den_a;
    std::cout << "Inserire il numeratore del secondo razionale: \n";
    int num_b;
    std::cin >> num_b;
    std::cout << "Inserire il denominatore del secondo razionale: \n";
    int den_b;
    std::cin >> den_b;

    rational<int> a(num_a,den_a);
    rational<int> b(num_b,den_b);
    // rational<int> a; inizializzo a con i valori forniti nel costruttore di default

    std::cout << "Primo razionale: " << a << "\n";
    std::cout << "Secondo razionale: " << b << "\n";
    
    std::cout << "Somma: " << a.operator+(b) << "\n"; 
    std::cout << "Differenza: " << a.operator-(b) << "\n";
    std::cout << "Moltiplicazione: " << a.operator*(b) << "\n";
    std::cout << "Divisione: " << a.operator/(b) << "\n";

    return 0;
}