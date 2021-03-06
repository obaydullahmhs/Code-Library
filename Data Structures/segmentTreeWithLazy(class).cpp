#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
namespace Tree{

    struct data{
        ll prop,sum;
        data():prop(0),sum(0){}
        data(ll _sum,ll _prop):sum(_sum),prop(_prop){}
    };

    template<typename D, typename U, typename T> ///'D' = tree Type, 'U'  = value type, 'T' = query return type .
    class segmentLazy{
    protected:

        virtual D neutral() = 0;
        virtual D merge(D x, D y) = 0;
        virtual D valueOf(U x) = 0; /// convert the value to tree type
        virtual T returnValue(D x) = 0;    /// convert tree type to query type value
        virtual bool ifProp(D x) = 0;       /// if you need to propagate it's child
        virtual void propagate(int node, int lo, int hi, vector<D>& tree, U value = 0) = 0;

    private:

        int n;
        vector<D> tree;
        void build(const vector<U>& given, int node, int low, int high){

            if (low == high){
                tree[node] = valueOf(given[low]);
                return;
            }

            build(given, (node<<1), low, ((low + high)>>1));
            build(given, 1 + (node<<1), 1 + ((low + high)>>1), high);
            tree[node] = merge(tree[(node<<1)], tree[1 + (node<<1)]);
        }
        void update(int node,int lo,int hi,int i,int j,U value){

            if(ifProp(tree[node])) propagate(node,lo,hi, tree);

            if(hi<i||j<lo) return;
            if(lo>=i&&hi<=j){  ///replace
                propagate(node, lo, hi, tree, value);
                return ;
            }

            update((node<<1), lo, (lo+hi)>>1, i, j, value);
            update(1 + (node<<1), 1+ ((lo + hi)>>1), hi, i, j, value);
            tree[node] = merge(tree[(node<<1)], tree[1 + (node<<1)]);
        }
        D query(int node,int low,int hi,int i,int j){

            if(ifProp(tree[node])) propagate(node,low,hi, tree);
            if(hi<i||j<low) return neutral();
            if(low>=i&&hi<=j)
                return tree[node];

            return merge(query((node<<1), low, (low + hi)>>1, i, j), query(1 + (node<<1), 1 + ((low + hi)>>1) , hi, i, j));
        }
    public:

        segmentWithLazy(){}
        void init(int _n){n =_n,tree.assign(4*n+20 ,D(0,0));}
        void build(const vector<U>& given){ build(given, 1, 1, n);   }
        void update(int l, int r, U value){ update(1, 1, n, l, r, value);    }
        T query(int l, int r){ return returnValue(query(1, 1, n, l, r));    }

    };

    template<typename D, typename U, typename T> /**'D' = tree Type, 'U'  = value type, 'T' = query return type . **/
    class AddSegTree: public segmentLazy<D, U, T>{
        virtual D neutral()override {return D(0, 0) ;}
        virtual D merge(D x, D y) override{return D(x.sum + y.sum, 0);  }
        virtual D valueOf(U x) override{ return D(x, 0);    }
        virtual T returnValue(D x) override {return x.sum; }
        virtual bool ifProp(D x) override { return (x.prop? true:false);}
        virtual void propagate(int node,int low,int hi, vector<D>& tree, U value = 0) override{    ///replace

            assert(value == 0 || tree[node].prop==0); /** must be okay **/

            {   /** change the block if you need **/
                value += tree[node].prop;
                tree[node].sum = (hi-low+1) * value;
                if(hi!=low){
                    tree[(node<<1)].prop = value;
                    tree[1 + (node<<1)].prop = value;
                }
                tree[node].prop = 0;
            }
        }
    };
}
using namespace Tree;

int main(){

    int n, q; cin>>n>>q;
    vector<ll> v(n);
    for(ll& in: v) cin>>in; v.insert(v.begin(), 0);

    AddSegTree<data, ll, ll> seg; seg.init(n); seg.build(v);
    while(q--){
        int c, ind, ind2; cin>>c>>ind>>ind2;
        if(c==1){
            ll val; cin>>val;
            seg.update(ind, ind2, val);
        }else cout<<seg.query(ind, ind2)<<"\n";
    }

    return 0;
}
