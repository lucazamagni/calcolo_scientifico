#include <utility>
#include <eigen3/Eigen/Dense>

// A->R(nxn), b->R(n), x->R(n)
std::pair<
Eigen::VectorXd, 
unsigned int
> gradiente_coniugato(const Eigen::MatrixXd A, const Eigen::VectorXd b, const Eigen::VectorXd x_0, const double tol_ass, const unsigned int it_max) {
    // const double tol = 1.0e-12;
    // int it_max = 10000;

    if (A.rows() != A.cols()) {
        std::cerr << "La matrice deve essere quadrata.\n";
        std::exit(EXIT_FAILURE);
    }
    int n = A.rows();
    if (b.size() != n || x_0.size() != n) {
        std::cerr << "Le lunghezze dei vettori non sono coerenti con quella della matrice.\n";
        std::exit(EXIT_FAILURE);
    }

    Eigen::VectorXd x = x_0;
    Eigen::VectorXd res = b - A * x;
    Eigen::VectorXd p = res;

    double alpha;
    double beta;
    unsigned int it = 0;

    // La convergenza in n passi (normalmente garantita dal metodo) in questo caso non è garantita a causa dell'aritmetica floating point,
    // quindi non posso fare un for su n iterazioni, ma impongo una condizione di arresto sulla norma del residuo e sul numero max di iterazioni
    while (res.norm() > tol_ass && it < it_max) {

        alpha = p.dot(res) / (p.dot(A * p));
        x = x + alpha * p;
        res = b - A * x;
        beta = p.dot(A * res) / (p.dot(A * p));
        p = res - beta * p;
        it = it + 1;
    }
    return {x,it}; // Restituisco la soluzione e il numero di iterazioni
}