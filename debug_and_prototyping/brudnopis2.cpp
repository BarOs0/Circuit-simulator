#include <vector>
#include <iostream>
#include <complex>

int main(){

    int n = 4;
    int m = 5;

    std::vector<std::vector<std::complex<double>>> mtrx;

    mtrx.resize(n, std::vector<std::complex<double>>(n));

    std::vector<int> vec1(2, 1);
    std::vector<int> vec2(3, 2);
    std::vector <int> vec3(2, 3);
    std::vector<int> vec12(vec1);
    vec12.insert(vec12.end(), vec2.begin(), vec2.end());
    vec12.insert(vec12.end(), vec3.begin(), vec3.end());
}


