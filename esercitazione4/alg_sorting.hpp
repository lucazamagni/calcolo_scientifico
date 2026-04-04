#include <vector>
#include <iostream>
#include <concepts>


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
