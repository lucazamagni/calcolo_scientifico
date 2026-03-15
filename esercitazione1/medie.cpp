#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, const char *argv[]) //argc=numero input; argv=vettore con gli input
{

if ( argc<2 ){
    cerr << "Nome del file mancante\n";
    return 1;
}

string filename = argv[1];

ifstream file(filename); //legge il testo del file
if ( file.is_open() ) {

    string city; //assegno a city il tipo stringa
    double temp1, temp2, temp3, temp4; //assegno alle temp il tipo double

    while ( file >> city >> temp1 >> temp2 >> temp3 >> temp4 ) { //ciclo direttamente sul testo e non uso eof poichè dà problemi nel caso di infinite righe vuote
    double media = (temp1 + temp2 + temp3 + temp4)/4;
    cout << city << " " << media << "\n";
    }
}
else {
    cerr << "Errore nell'apertura del file\n";
return 1;
}
return 0;
}