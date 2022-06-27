#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
namespace Tree{
  template<typename T>
  struct data{      ///Tree Type
    T prop, sum;
    data(): sum(0), prop(0){}
    data(T _sum, T _prop): sum(_sum), prop(_prop){}
  };

  template<typename D, typename U> /**'D' = tree Type, 'U'  = value type and query type, **/
  class segmentLazy{

  protected:
    virtual inline U propinf() = 0;  /// propagate default value
    virtual D neutral() = 0;
    virtual D merge(D x, D y) = 0;
    virtual D valueOf(U x) = 0; /// convert the value to tree type
    virtual U returnValue(D x) = 0;    /// convert tree type to query type value
    virtual bool ifProp(D x) = 0;       /// if you need to propagate it's child
    virtual void propagate(int node, int lo, int hi, D* tree, U value) = 0;

  private:
    int n;
    D* tree;
    void build(const vector<U>& given, int node, int lo, int high){

      if (lo == high){
          tree[node] = valueOf(given[lo]);
          return;
      }
      build(given, (node << 1), lo, ((lo + high) >> 1));
      build(given, 1 + (node << 1), 1 + ((lo + high) >> 1), high);
      tree[node] = merge(tree[(node << 1)], tree[1 + (node << 1)]);
    }
    void update(int node, int lo, int hi, int i, int j, U value){

      if(ifProp(tree[node])) propagate(node, lo, hi, tree, propinf());

      if(hi < i || j < lo) return;
      if(lo >= i && hi <= j){  ///replace
          propagate(node, lo, hi, tree, value);
          return;
      }
      update((node << 1), lo, (lo+hi) >> 1, i, j, value);
      update(1 + (node << 1), 1 + ((lo + hi) >> 1), hi, i, j, value);
      tree[node] = merge(tree[(node << 1)], tree[1 + (node << 1)]);
    }
    D query(int node, int lo, int hi, int i, int j){

      if(ifProp(tree[node])) propagate(node, lo, hi, tree, propinf());
      if(hi < i || j < lo) return neutral();
      if(lo >= i && hi <= j)
          return tree[node];
      return merge(query((node << 1), lo, (lo + hi) >> 1, i, j), query(1 + (node << 1), 1 + ((lo + hi) >> 1) , hi, i, j));
    }

  public:
    segmentWithLazy(){}
    void init(int _n){
      n =_n;
      tree = new D[4 * n];
      for(int i = 0; i < 4 * n; i++) tree[i] = valueOf(0);
    }
    void build(const vector<U>& given){ build(given, 1, 1, n);   }
    void update(int l, int r, U value){ update(1, 1, n, l, r, value);    }
    U query(int l, int r){ return returnValue(query(1, 1, n, l, r));    }

  };

  template<typename D, typename U> /**'D' = tree Type, 'U'  = value type and query type, **/
  class AddSegTree: public segmentLazy<D, U>{
    virtual inline U propinf()override {return numeric_limits<U>::min() / 2; } /// propagate default value
    virtual D neutral()override {return D(0, propinf()) ;}
    virtual D merge(D x, D y) override{return D(x.sum + y.sum, propinf());  }
    virtual D valueOf(U x) override{ return D(x, propinf());    }
    virtual U returnValue(D x) override {return x.sum; }
    virtual bool ifProp(D x) override { return (x.prop != propinf()? true:false);}
    virtual void propagate(int node,int lo,int hi, D* tree, U value) override{    ///replace

      assert((value == propinf()) ^ (tree[node].prop == propinf())); /** must be okay **/

      {   /** change the block if you need **/
        value = (value == propinf()? tree[node].prop : value);
        tree[node].sum = (hi - lo + 1) * value;
        if(hi != lo){
          tree[(node << 1)].prop = value;
          tree[1 + (node << 1)].prop = value;
        }
        tree[node].prop = propinf();
      }
    }
  };
}
using namespace Tree;

int main(){

    int n, q; cin>>n>>q;
    vector<ll> v(n);
    for(ll& in: v) cin>>in; v.insert(v.begin(), 0);

    AddSegTree<data, ll> seg; seg.init(n); seg.build(v);
    while(q--){
        int c, ind, ind2; cin>>c>>ind>>ind2;
        if(c==1){
            ll val; cin>>val;
            seg.update(ind, ind2, val);
        }else cout<<seg.query(ind, ind2)<<"\n";
    }

    return 0;
}
