#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
T extendedEuclid(T a, T b, T& x, T& y){
    if(b == 0){
        x = 1, y = 0;
        return a;
    }
    T x1, y1;
    T g = extendedEuclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);

    return g;
}

template<typename T>
T modularInverse(T a, T b){
    T x, y;
    T g = extendedEuclid(a, b, x, y);
    if(g != 1) return -1;
    return (x % b + b) % b;
}

int main(){

    int a = 5;
    int b = modularInverse(a, 19);
    cout << (a * b) % 19 << endl;
}

