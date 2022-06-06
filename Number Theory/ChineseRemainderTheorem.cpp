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

/// x = (a1*m2*q + a2*m1*p) % lcm(m1, m2)
template<typename T>
pair<T, T> ChineseRemainderTheorem(T a1, T m1, T a2, T m2){
    T p, q;
    T g = extendedEuclid(m1, m2, p, q);
    if(a1 % g != a2 % g) return pair<T, T>(0, -1);
    T m = (m1 / g) * m2;
    p = (p % m + m) % m;
    q = (q % m + m) % m;
    return pair<T, T>(((((a1 * q) % m) * (m2 / g)) % m + (((a2 * p) % m) * (m1 / g)) % m) % m, m); /// returns {x, m}, m = lcm(m1, m2)
}
int main(){

    cout << ChineseRemainderTheorem(1, 4, 2, 7).first << "\n";
    return 0;
}

