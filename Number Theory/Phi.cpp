#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
T phi(T n) {
    T ans = n, m = n;
    for (T i = 2; i * i <= m; i++) {
        if (m % i == 0) {
            while (m % i == 0) m /= i;
            ans = ans / i * (i - 1);
        }
    }
    if (m > 1) ans = ans / m * (m - 1);
    return ans;
}

int main(){

    cout << phi(phi(20)) << endl;

    return 0;
}
/**

**/

