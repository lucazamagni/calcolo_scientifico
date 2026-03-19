#include <iostream>
#include <cmath>
using namespace std;

int main() {

static const int N = 10;
double arr[N] = {3,5,8,3,4,4,2,1,1,5};

double massimo;
double minimo;
massimo=arr[0];
minimo=arr[0];
for ( int i=1; i<N; i=i+1 ) {
    massimo=max(massimo,arr[i]);
    minimo=min(minimo,arr[i]);
}

double sum1;
double media;
sum1=0;
for ( int i=0; i<N; i=i+1 ) {
    sum1=sum1+arr[i];
}
media=sum1/N;


double scarto_q_medio;
double sum2;
double dev_st;
sum2=0;

for ( int i=0; i<N; i=i+1 ) {
    scarto_q_medio=pow(arr[i]-media, 2);
    sum2=sum2+scarto_q_medio;
}
dev_st=sqrt(sum2/N);


cout << "Massimo: " << massimo << "\n";
cout << "Minimo: " << minimo << "\n";
cout << "Deviazione standard: " << dev_st << "\n";

return 0;
}