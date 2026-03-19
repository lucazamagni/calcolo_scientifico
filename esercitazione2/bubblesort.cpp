#include <iostream>
using namespace std;

int main() {

static const int N = 10;
double arr[N] = {3,5,8,3,4,4,2,1,1,5};

cout << "Starting array: ";
for (int i=0; i<N; i=i+1){
    cout << arr[i] << " ";
}
cout << "\n" << "Sorted array: ";

double arr_i;
double arr_iu;
int flag;
flag=0; //se è zero indica che non vengono effettuati scambi

do {
    for (int i=0; i<N; i=i+1){
        if (arr[i]>arr[i+1]){
        arr_i=arr[i];
        arr_iu=arr[i+1];
        arr[i+1]=arr_i;
        arr[i]=arr_iu;
        flag=1;
    } else {flag=0;};
}
} while (flag==1);


for (int i=0; i<N; i=i+1){
    cout << arr[i] << " ";
}



}

