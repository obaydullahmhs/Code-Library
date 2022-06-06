#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

using ull = uint64_t;
using u128 = ull; /*__uint128_t; */

ull binpower(ull base, ull e, ull mod) {
    ull result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(ull n, ull a, ull d, int s) {
    ull x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;

    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(ull n, int iter=5) { // returns true if n is probably prime, else returns false.
    if (n < 4)
        return n == 2 || n == 3;

    int s = 0;
    ull d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (check_composite(n, a, d, s))
            return false;
    }
    return true;
}

ull PollardRho(ull n){ /// returns its divisor

    if (n == 1) return n;

    if (n % 2 == 0) return 2;

    ull x = (rand() % (n - 2)) + 2;
    ull y = x;

    ull c = (rand() %(n - 1)) + 1;

    ull g = 1;
    if(MillerRabin(n)) return n;

    while (g == 1){

        x = ((x * x) % n + c + n)%n;
        y = ((y * y) % n + c + n)%n;
        y = ((y * y) % n + c + n)%n;

        g = __gcd((ull)abs(x - y), n);

        if (g == n) return PollardRho(n);
    }

    return g;
}

void solve(){
    cout << MillerRabin(19) << endl;

}
int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    srand(time(0));
    int tc = 1; ///cin>>tc;
    while(tc--){
        solve();
    }

    return 0;
}
/**

**/
