#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace Tree{
  template<typename T, typename Y> /** T = Tree Type, Y = value Type **/
  class SegmentTree{
  protected:
    virtual T merge(T x, T y) = 0;
    virtual T valueOf(Y a) = 0;
    virtual T neutral() = 0;
  private:
    int n; vector<T> tree;
    void build(const vector<Y> &given, int node, int low, int high){
      if (low == high){
        tree[node] = valueOf(given[low]);
        return;
      }
      build(given, (node<<1), low, (low+high)>>1 );
      build(given, 1 + (node<<1), ((low + high)>>1) + 1, high);
      tree[node] = merge(tree[(node<<1)], tree[1 + (node<<1)]);
    }
    void update(int node, int low, int hi, int i, Y value){
      if (low == hi){
        tree[node] = valueOf(value);
        return;
      }
      if (i <= ((low + hi)>>1)) update((node<<1), low, (low + hi)>>1, i, value);
      else update(1 + (node<<1), ((low + hi)>>1) + 1, hi, i, value);
      tree[node] = merge(tree[(node<<1)], tree[1 + (node<<1)]);
    }
    T query(int node, int low, int hi, int i, int j){
      if (i>hi || j<low) return neutral();
      if (low >= i&&hi <= j) return tree[node];
      return merge(query((node<<1), low, (low + hi)>>1, i, j), query(1 + (node<<1), ((low + hi)>>1) + 1, hi, i, j)) ;
    }
  public:
    SegmentTree(){}
    void init(int _n){n = _n, tree.assign(4*n + 20, neutral());} /// Must need to initialize
    void build(const vector<Y>& given){
      build(given, 1, 1, n);
    }
    void update(int ind, Y value){
      update(1, 1, n, ind, value);
    }
    T query(int l, int r){
      return query(1, 1, n, l, r);
    }
  };

  template<typename T, typename Y>
  class AddSegTree: public SegmentTree<T, Y>{
    virtual T merge(T x, T y)override { return x + y;}
    virtual T valueOf(Y x)override { return T(x); }
    virtual T neutral()override{ return 0;}
  };

  template<typename T, typename Y>
  class MinSegTree: public SegmentTree<T, Y>{
    virtual T merge(T x, T y)override { return min(x, y); }
    virtual T valueOf(Y x)override { return T(x); }
    virtual T neutral()override { return numeric_limits<Y> ::max()/2; }
  };

  template<typename T, typename Y>
  class MaxSegTree: public SegmentTree<T, Y>{
    virtual T merge(T x, T y)override { return max(x, y);}
    virtual T valueOf(Y x)override { return T(x); }
    virtual T neutral()override { return numeric_limits<Y> ::min()/2; }
  };
}
using namespace Tree;

int main (){
  int n, q; cin>>n>>q;
  vector<ll> v(n);
  for(ll& in: v) cin>>in; v.insert(v.begin(), 0);

  AddSegTree<ll, ll> seg; seg.init(n); seg.build(v);
  while(q--){
    int c, ind; ll val; cin>>c>>ind>>val;
    if(c==1){
      seg.update(ind, val);
    }else cout<<seg.query(ind, val)<<"\n";

  }
    return 0;
}

