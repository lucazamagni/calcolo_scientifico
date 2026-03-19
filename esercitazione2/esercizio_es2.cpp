 # include <iostream>

int main()
{
double ad[4] = {0.0, 1.1, 2.2, 3.3};
float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
int ai[3] = {0, 1, 2};

int x = 1;
float y = 1.1;

(&y)[1] = 0;
// &y e' l'indirizzo di memoria della var y ed e' salvato come float (4 Byte)
// Quindi starei assegnando alla seconda cella di memoria delle quattro riservate al float lo 0 (e' illecito, poichè sto trattando
// la var y come un array ma in realtà è un float)
// Questa assegnazione impropria può portare a sovrascrivere la cella vicina ad y nello stack, in cui è salvata in questo caso la variabile x
// Infatti, utilizzando il compilatore clang, ad x è assegnato il valore 0 impropriamente, nonostante sia assegnato inizialmente
// al valore 1

std::cout << "x value: " << x << "\n";

std::cout << "\n";

std::cout << "Lunghezza Arr Double: " << 4*sizeof(double) << "\n";
std::cout << "Arr Double 1 address: " << &ad[0] << "\n";
std::cout << "Arr Double 2 address: " << &ad[1] << "\n";
std::cout << "Arr Double 3 address: " << &ad[2] << "\n";
std::cout << "Arr Double 4 address: " << &ad[3] << "\n";

std::cout << "\n";

std::cout << "Lunghezza Float: " << 8*sizeof(float) << "\n";
std::cout << "Arr Float 1 address: " << &af[0] << "\n";
std::cout << "Arr Float 2 address: " << &af[1] << "\n";
std::cout << "Arr Float 3 address: " << &af[2] << "\n";
std::cout << "Arr Float 4 address: " << &af[3] << "\n";
std::cout << "Arr Float 5 address: " << &af[4] << "\n";
std::cout << "Arr Float 6 address: " << &af[5] << "\n";
std::cout << "Arr Float 7 address: " << &af[6] << "\n";
std::cout << "Arr Float 8 address: " << &af[7] << "\n";

std::cout << "\n";

std::cout << "Lunghezza Int: " << 3*sizeof(int) << "\n";
std::cout << "Arr Int 1 address: " << &ai[0] << "\n";
std::cout << "Arr Int 2 address: " << &ai[1] << "\n";
std::cout << "Arr Int 3 address: " << &ai[2] << "\n";

std::cout << "\n";

std::cout << "Lunghezza Int: " << sizeof(int) << "\n";
std::cout << "Int address " << &x << "\n";

std::cout << "\n";

std::cout << "Lunghezza Float: " << sizeof(float) << "\n";
std::cout << "Float address: " << &y << "\n";


return 0;
}