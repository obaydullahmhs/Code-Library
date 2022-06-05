#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

namespace Sparse{

  template<typename T>
  class RMQ{      ///0 Base

  protected:
    virtual T merge(T x, T y) = 0;
    virtual T neutral() = 0;
  private:
    int n, Log;
    vector<int> calLog;
    vector<vector<T> > sparse;
  public:
    RMQ(int _n): n(_n), Log(log2(n) + 1), calLog(n + 5, 0), sparse(Log + 1, vector<T>(n + 5, 0)){};
    void init(int _n){n = _n, Log = 1 + log2(n), calLog.assign(n + 5, 0), sparse.assign(Log + 1, vector<T>(n + 5, 0));}
      void preProcess(vector<T>& given){
        for(int i = 2; i <= n; i++) calLog[i] = 1 + calLog[i / 2];
        for(int i = 0;i < n; i++) sparse[0][i] = given[i];
        for(int i = 1; i <= Log; i++)
          for(int j = 0; j + (1 << (i - 1)) < n; j++)
            sparse[i][j] = merge(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);
      }
      T getValue(int l, int r){
        if(l > r) return neutral();
        int k = calLog[r - l + 1];
        return merge(sparse[k][l], sparse[k][r - (1 << k) + 1]); ///checking first 2^k element and last 2^k
      }
  };

  template<typename T>
  class minRMQ: public RMQ<T>{
  public:
    minRMQ(int _n): RMQ<T>(_n){}
    virtual T merge(T x, T y)override { return min(x, y);} /// Query type
    virtual T neutral()override {return 0; } ///change the neutral value if needed
  };
  template<typename T>
  class maxRMQ: public RMQ<T>{
  public:
    maxRMQ(int _n): RMQ<T>(_n){}
    virtual T merge(T x, T y)override { return max(x, y);} /// Query type
    virtual T neutral()override {return 0; } ///change the neutral value if needed
  };
  template<typename T>
  class gcdRMQ: public RMQ<T>{
  public:
    gcdRMQ(int _n): RMQ<T>(_n){}
    virtual T merge(T x, T y)override { return __gcd(x, y);} /// Query type
    virtual T neutral()override {return 0; } ///change the neutral value if needed
  };

}
using namespace Sparse;

int cs;
int main(){

  int n, q;
  scanf("%d %d", &n, &q);
  vector<int> v(n);
  for(int& in: v) scanf("%d", &in);

  minRMQ <int> rmq(n);
  rmq.preProcess(v);
  printf("Case %d:\n", ++cs);

  while(q--){
    int l, r; scanf("%d %d", &l, &r);
    printf("%d\n", rmq.getValue(--l, --r));
  }

  return 0;
}


