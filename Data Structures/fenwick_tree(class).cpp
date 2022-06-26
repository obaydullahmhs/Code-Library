#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

template<typename T>
class fenwick{  ///1 Based

private:
  int n, logn;
  vector<T> tree;
  void update(int pos, T val, int _n){
    for(int i = pos; i <= _n; i += (i & (-i)))
      tree[i] += val;
  }

  T query(int pos){
    T sum = 0;
    for(int i = pos; i > 0; i -= (i & (-i)))
      sum += tree[i];

    return sum;
  }

  int kthElement(int v){ ///kTh element or lower_bound or binary lifting on BIT //Complexity per query log(n)
    T sum = 0;
    int pos = 0;
    for(int i = logn; i >= 0; i--){
      if(pos + (1 << i) < n && sum + tree[pos + (1 << i)] < v){
        sum += tree[pos + (1 << i)];
        pos += (1 << i);
      }
    }
    return pos + 1;
  }

public:

  fenwick(int _n): n(_n), logn(log2(n) + 1), tree(n + 5, 0){}
  void init(int _n){n = _n, logn = log2(n) + 1, tree.assign(n + 5, 0);}

  void update(int pos, T val){
    update(pos, val, this->n);
  }
  T query(int u, int v){
    if(v < u) return -1; /// returning unusual value
    return query(v) - query(max(u - 1, 0));
  }
  int kth(int n){
    return kthElement(n);
  }

};

int main(){

  vector<int> v({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  fenwick<int> fen(v.size() - 1);
  for(int i = 1; i < v.size(); i++)
    fen.update(i, v[i]);

  cout << fen.query(2, 9) << endl;

  return 0;
}


