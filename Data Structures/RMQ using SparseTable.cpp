#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
template<typename T>
class RMQ{  ///'max' for MAX Query and 'min' for MIN Query
private:
    int n, Log;
    vector<int> calLog;
    vector<vector<T> > sparse;
public:
    RMQ():n(2e5),Log(log2(n)+1),calLog(n+5,0),sparse(Log+1,vector<T>(n+5,0)){};
    RMQ(int _n):n(_n),Log(log2(n)+1),calLog(n+5,0),sparse(Log+1,vector<T>(n+5,0)){};
    void init(int _n){n = _n,Log = 1+log2(n),calLog.assign(n+5,0),sparse.assign(Log+1,vector<T>(n+5,0));}
    void preProcess(vector<T>& given){
        for(int i=2;i<=n;i++) calLog[i] = 1 + calLog[i/2];
        for(int i=0;i<n;i++) sparse[0][i] = given[i];
        for(int i=1;i<=Log;i++)
            for(int j=0;j+(1<<(i-1))<n;j++)
                sparse[i][j] = min(sparse[i-1][j],sparse[i-1][j+(1<<(i-1))]);
    }
    T getValue(int l, int r){
        if(l>r) return 0;
        int k = calLog[r-l+1];
        return min(sparse[k][l], sparse[k][r-(1<<k)+1]); ///checking first 2^k element and last 2^k
    }
};

int main(){
    int n, q;
    scanf("%d %d", &n,&q);
    vector<int> v(n);
    for(int& in:v) scanf("%d", &in);
    RMQ <int> rmq(n);
    rmq.preProcess(v);
    printf("Case %d:\n",++cs);
    while(q--){
        int l, r;scanf("%d %d", &l, &r);
        printf("%d\n",rmq.getValue(--l,--r));
    }
    return 0;
}


