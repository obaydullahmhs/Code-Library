#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
class Matrix{
private:

    int r, c;
    vector< vector<T> > a;
public:

    Matrix(): r(5), c(5), a(r, vector<T>(c, 0)){}
    Matrix(int _n): r(_n), c(_n), a(r, vector<T>(c, 0)){}
    Matrix(int _r, int _c): r(_r), c(_c), a(r, vector<T>(c, 0)){}
    void init(int _r, int _c){r = _r, c = _c; a.assign(r, vector<T>(c, 0));}

    inline Matrix<T> operator * (Matrix<T> b){

        Matrix<T> res(r, b.c);
        for(int i = 0; i < r; i++){
            for(int j = 0; j < b.c; j++){
                T temp = 0;
                for(int k = 0; k < c; k++){
                    temp = (temp + (a[i][k] * b.a[k][j]));
                }
                res.a[i][j] = temp;
            }
        }
        return res;
    }

    Matrix<T> operator ^(long long n){

        Matrix<T> res(r);
        res.identity();
        Matrix<T> p(r, c);
        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++)  p.a[i][j] = a[i][j];

        while(n){

            if( n & 1 ) res = res * p;
            p = p * p;
            n >>= 1;
        }

        return res;
    }

    inline void identity(){
        for(int i = 0; i < min(r, c); i++) a[i][i] = 1;
    }

    inline void assign(int x, int y, T val){     ///matrix assign
        a[x][y] = val;
    }

    inline T valueOf(int x, int y){
        return a[x][y];
    }

};

void solve(){

    {
       /// https://codeforces.com/gym/102644/problem/A
        long long n;
        double p;

        cin >> n >> p;
        Matrix<double> mat(2);
        mat.assign(0, 0, 1.0 - p);
        mat.assign(0, 1, p);
        mat.assign(1, 0, p);
        mat.assign(1, 1, 1.0 - p);
        mat = mat^n;

        cout << fixed << setprecision(10) << mat.valueOf(0, 0) << "\n";
    }


}
int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc = 1; ///cin>>tc;
    while(tc--){
        solve();
    }

    return 0;
}
/**

f(n) = f(n - 1) * (1 - p) + g(n - 1) * p      happy
g(n) = f(n - 1) * p + g(n - 1) * (1 - p)      sad

f(n)|1 - p     p   | f(n - 1) |
g(n)|  p    1 - p  | g(n - 1) |

**/
