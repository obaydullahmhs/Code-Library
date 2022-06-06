#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef long long ll;

template<typename T>
using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

template<typename T>
using ordered_multiset=tree<T, null_type, less_equal<T>, rb_tree_tag,tree_order_statistics_node_update>;

template<typename T>
class mergeSortTreeUpdate{    /** 1 - Base **/
private:

    int n;
    vector<ordered_multiset<T> > Tree;
    virtual inline T segValue(const ordered_multiset<T>& v, T val){  /// queryType
        return v.order_of_key(val);    ///number of elements less than
    }

    void buildTree(int node, int lo, int hi,const vector<T>& v){

        if(lo == hi){
            Tree[node].insert(v[lo]);
            return;
        }

        for(int i = lo; i <= hi; i++)
            Tree[node].insert(v[i]);

        buildTree(node<<1, lo, (lo + hi)>>1, v);
        buildTree(1|(node<<1), 1 + ((lo + hi)>>1), hi, v);

    }

    T query(int node, int lo, int hi, int i, int j, T val){

        if(i > hi || j < lo) return 0;
        if(lo >= i && hi <= j){
            return segValue(Tree[node], val);
        }

        return query(node<<1, lo, (lo + hi)>>1, i, j, val) + query(1|(node<<1), 1 + ((lo + hi)>>1), hi, i, j, val);
    }

    void update(int node, int lo, int hi, int pos, T old, T nwv){
        if(pos < lo || hi < pos)  return;

        if(lo == pos && hi == pos){
          Tree[node].erase(Tree[node].find_by_order(Tree[node].order_of_key(old)));
          Tree[node].insert(nwv);
          return;
        }

        update(node<<1, lo,  (lo + hi) >> 1, pos, old, nwv);
        update(1|(node << 1), 1 +  ((lo + hi) >> 1), hi, pos, old, nwv);

        Tree[node].erase(Tree[node].find_by_order(Tree[node].order_of_key(old)));
        Tree[node].insert(nwv);
    }



public:

    void init(int _n){
       n = _n;   Tree.resize(4*_n, ordered_multiset<T>());
    }
    void buildTree(const vector<T>& v){
        buildTree(1, 1, n, v);
    }
    T query(int l, int r, T val){
        return query(1, 1, n, l, r, val);
    }
    void update(int pos, T old, T nwv){
      update(1, 1, n, pos, old, nwv);
    }
};

const int N = 300000;
vector<int> v(N);

int main(){

    int n, q; scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; i++){
        scanf("%d", &v[i]);
    }

    mergeSortTreeUpdate<int> mrg;
    mrg.init(n);
    mrg.buildTree(v);

    while(q--){
        int c, a, b; scanf("%d %d %d", &c, &a, &b);

        if(c == 1){
            int val; scanf("%d", &val);
            printf("%d\n", mrg.query(a, b, val));
        }else{
            swap(v[a], v[b]);
            mrg.update(a, v[b], v[a]);
            mrg.update(b, v[a], v[b]);
        }
    }

    return 0;
}
/**

**/
