#include<bits/stdc++.h>

using namespace std;

namespace Hashing{

  const int N = 500005; /// accordingly
  const int MOD[] = {1000000007, 2117566807};
  const int BASE[] = {1572872831LL, 1971536491};
  int basepow[2][N];

  void prepare_pow(int t){
    basepow[t][0] = 1;
    for(int i = 1; i < N; ++i) {
      basepow[t][i] = (1LL * basepow[t][i - 1] * BASE[t]) % MOD[t];
    }
  }

  struct Hash{
    int type;
    int length;
    int hash_value;
    Hash(): type(0), length(0), hash_value(0){}
    Hash(int x, int y, int z): type(x), length(y), hash_value(z){}
    Hash operator +(const Hash &rhs) const{
      return Hash(type, length + rhs.length, (1LL * hash_value * basepow[type][rhs.length] + rhs.hash_value) % MOD[type]);
    }
    Hash operator -(const Hash &rhs) const{
      return Hash(type, length - rhs.length, ((1LL * hash_value - 1LL * basepow[type][length - rhs.length] * rhs.hash_value) % MOD[type] + MOD[type]) % MOD[type]);
    }
    bool operator ==(const Hash &rhs) const{
      return (length == rhs.length && hash_value == rhs.hash_value);
    }
  };

  struct HashLinear{ ///0 Based
    int n;
    Hash *tree;
    HashLinear(){}
    HashLinear(int _n){init(_n);}
    void init(int _n){
      n = _n;
      tree = (Hash*)calloc(n + 5, sizeof(Hash));
    }
    void update(int p, int val, int t = 0){
      tree[p] = Hash(t, 1, val);
      if(p > 0) tree[p] = tree[p - 1] + tree[p];
    }
    Hash query(int u, int v, int t = 0){
      Hash ans = tree[v];
      if(u > 0) ans = ans - tree[u - 1];
      return ans;
    }
  };
  struct HashSegmentTree{ ///0 Based
    int n;
    Hash *tree;
    HashSegmentTree(){}
    HashSegmentTree(int _n){init(_n);}
    void init(int _n){
      n = _n;
      tree = (Hash*)calloc((n + 5) << 1, sizeof(Hash));
    }
    void update(int p, int val, int t = 0) {
      p += n;
      tree[p] = Hash(t, 1, val);
      for(; p >>= 1; ) {
        tree[p] = tree[p << 1] + tree[p << 1 | 1];
      }
    }
    Hash query(int l, int r, int t = 0) {
      Hash resl, resr;
      resl = Hash(t, 0, 0);
      resr = Hash(t, 0, 0);
      for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if(l & 1) resl = resl + tree[l++];
        if(r & 1) resr = tree[--r] + resr;
      }
      return resl + resr;
    }
  };
  template<typename T>
  void generateFrontHash(const string& s, T& obj){
    int n = s.size();
    for(int i = 0; i < n; i++) obj.update(i, s[i]);
  }
  template<typename T>
  inline int getFrontHash(int l, int r, T& obj){ ///0 Based
    return obj.query(l, r).hash_value;
  }
  template<typename T>
  void generateBackHash(const string& s, T& obj){
    int n = s.size();
    for(int i = n - 1; i >= 0; i--) obj.update(n - i - 1, s[i]);
  }
  template<typename T>
  inline int getBackHash(int l, int r, T& obj){ ///0 Based
    return obj.query(obj.n - r - 1, obj.n - l - 1).hash_value;
  }
}
using namespace Hashing;

void solve(){

  int n, q;
  string s; cin >> s;
  n = s.size();
  HashLinear a(n), b(n);
  generateFrontHash(s, a);
  generateBackHash(s, b);
  cin >> q;
  while(q--){
    int l, r; cin >> l >> r;
    --l, --r;
    cout << (getFrontHash(l, r, a)) << " " << (getBackHash(l, r, b)) << endl;
  }

}

int main() {

  ios_base::sync_with_stdio(false); cin.tie(NULL);

  prepare_pow(0);

  int tc = 1; cin >> tc;
  while(tc--){
    solve();
  }


  return 0;
}
