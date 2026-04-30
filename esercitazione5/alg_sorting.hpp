#include <vector>
#include <iostream>
#include <concepts>
#include <limits>


template<typename T>
bool is_sorted(const std::vector<T>& vec) {
    
    if (vec.size()==0) {return true;}

    for (std::size_t i=0; i<vec.size()-1; i+=1) {

        if (vec[i]>vec[i+1]) {return false;}
    }

return true; //True(1) se è ordinato, False(0) se non è ordinato
}


template<typename T>
void print_vector(const std::vector<T>& v)
{
    for (std::size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}


template<typename T>
std::vector<T> bubblesort(std::vector<T>& vec) {

for (std::size_t i=0; i<=vec.size()-2; i+=1) {
    for (std::size_t j=vec.size()-1; j>=i+1; j-=1) {
        if (vec[j]<vec[j-1]) {std::swap(vec[j] , vec[j-1]);}
    }
}
return vec;
}


template<typename T>
std::vector<T> insertionsort(std::vector<T>& vec) {

T key;
std::size_t i;

for (std::size_t j = 1; j < vec.size(); ++j) {
    key = vec[j];
    i = j;
    while (i > 0 && vec[i-1] > key) {
        vec[i] = vec[i-1];
        i=i-1;}
    vec[i] = key;
}
return vec;
}


template<typename T>
std::vector<T> selectionsort(std::vector<T>& vec) {

std::size_t min;

for (std::size_t i=0; i<=vec.size()-2; i+=1) {
    min=i;
    for (std::size_t j=i+1; j<=vec.size()-1; j+=1) {
        if (vec[j]<vec[min]) {
            min=j;
        }
    }
    std::swap(vec[i] , vec[min]);
}
return vec;
}

//NUOVA ESERCITAZIONE

template<typename T>
void merge(std::vector<T>& vec, int p, int q, int r) {
    int n1 = q-p+1; //n1 include la posizione di q
    int n2 = r-q; //n2 conta a destra di q escluso
    std::vector<T> L(n1);
    std::vector<T> R(n2);
    for (int i=0; i<n1; i=i+1) {
        L[i]=vec[p+i];
    }
    for (int j=0; j<n2; j=j+1) {
        R[j]=vec[q+j+1];
    }

    int i = 0;
    int j = 0;
    int k = p;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vec[k] = std::move(L[i]);
            i++;
        } else {
            vec[k] = std::move(R[j]);
            j++;
        }
        k++;
    }

    //Copia degli elementi rimanenti in L (se presenti)
    while (i < n1) {
        vec[k] = std::move(L[i]);
        i++;
        k++;
    }
    //Copia degli elementi rimanenti in R (se presenti)
    while (j < n2) {
        vec[k] = std::move(R[j]);
        j++;
        k++;
    }
}

template<typename T>
void mergesort_ricorsivo(std::vector<T>& vec, int p, int r) {
    if (p<r) {
        int q = (p+r)/2; //lo arrotonda sempre per difetto, quindi non serve usare la funzione parte intera
        //se il numero di elementi è pari, q è l'elemento per difetto
        //se il numero di elementi è dispari, q è l'elemento centrale
        mergesort_ricorsivo(vec, p, q);
        mergesort_ricorsivo(vec, q+1, r);
        merge(vec, p, q, r);
    }
}

template<typename T>
void mergesort(std::vector<T>& vec) {
    int p = 0;
    int r = vec.size()-1;
    mergesort_ricorsivo(vec,p,r);
} // NON BISOGNA RETURNARE NULLA PERCHE' MODIFICA I VETTORI



template<typename T>
int partition(std::vector<T>& vec, int p, int r) {
    T x = vec[r]; //scelgo come pivot sempre vec[r], alternativamente è possibile scegliere rand(p,r)
    int i = p-1; 
    for (int j=p; j<=r-1; j=j+1) {
        if (vec[j]<=x) {
            i=i+1;
            std::swap(vec[i] , vec[j]);
        }
    }
    std::swap(vec[i+1] , vec[r]);
    return i+1;
}


template<typename T>
void quicksort_ricorsivo(std::vector<T>& vec, int p, int r) {
    if (p<r) {
        int q = partition(vec,p,r);
        quicksort_ricorsivo(vec,p,q-1);
        quicksort_ricorsivo(vec,q+1,r);
    }
}

template<typename T>
void quicksort(std::vector<T>& vec) {
    int p = 0;
    int r = vec.size()-1;
    quicksort_ricorsivo(vec,p,r);
}


template<typename T>
void quicksort_modificato(std::vector<T>& vec) {
    size_t N_star = 32;
    if (vec.size()<N_star) {
        insertionsort(vec);
    }
    else {
        quicksort(vec);
    }
}