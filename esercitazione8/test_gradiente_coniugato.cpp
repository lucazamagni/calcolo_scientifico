#include <iostream>
#include <cstdlib>
#include <vector>
#include "gradiente_coniugato.hpp"
#include <eigen3/Eigen/Dense>

// il metodo mi genera una matrice nxn che sia simmetrica definita positiva a coeff reali per poter applicarci il metodo del gradiente coniugato
Eigen::MatrixXd genero_simmdefpos(const unsigned int& n) {
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(n, n);
    Eigen::MatrixXd B = A.transpose() * A;
    B += n * Eigen::MatrixXd::Identity(n, n); // sommo l'identità per far si che la matrice B diventi ben condizionata 
    return B;
}

int main() {

    int n = 100;
    const double tol = 1.0e-12;
    const int it_max = 10000;
    Eigen::VectorXd exactSolution = Eigen::VectorXd::Ones(n); // imposto la soluzionen esatta a quella unitaria e ricavo b a partire da questa
    const Eigen::VectorXd x_0 = Eigen::VectorXd::Zero(n); // imposto il vettore iniziale a quello nullo

    for (int i=0; i<20; i=i+1) { // testo il metodo su 20 matrici 100x100

        Eigen::MatrixXd A = genero_simmdefpos(n);
        Eigen::VectorXd b = A * exactSolution;
 
        auto [sol , num_it] = gradiente_coniugato(A, b, x_0, tol, it_max);
        
        if ((sol - exactSolution).norm() > tol) {
            std::cout << "Test fallito. \n";
            return EXIT_FAILURE;
        }
    }
    std::cout << "Test riuscito. \n";
    return EXIT_SUCCESS;
}