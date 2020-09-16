#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace Tree{
    ///Start
    template<typename T, typename Y>
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
            int left = node<<1;
            int right = left + 1;
            int mid = (low + high)>>1;
            build(given, left, low, mid);
            build(given, right, mid + 1, high);
            tree[node] = merge(tree[left], tree[right]);
        }
        void update(int node, int low, int hi, int i, Y value){

            if (low == hi){
                tree[node] = valueOf(value);
                return;
            }
            int mid = (low + hi)>>1;
            int left = node<<1;
            int right = left + 1;
            if (i <= mid)
                update(left, low, mid, i, value);
            else
                update(right, mid + 1, hi, i, value);
            tree[node] = merge(tree[left], tree[right]);
        }
        T query(int node, int low, int hi, int i, int j){

            if (i>hi || j<low)
                return neutral();
            if (low >= i&&hi <= j)
                return tree[node];
            int mid = (low + hi)>>1;
            int left = node<<1;
            int right = left + 1;

            return merge(query(left, low, mid, i, j), query(right, mid + 1, hi, i, j)) ;
        }
    public:
        SegmentTree(){}
        void init(int _n){n = _n, tree.assign(4*n + 20, 0);} /// Must need to initialize
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
    ///End

    template<typename T, typename Y>
    class AddSegTree: public SegmentTree<T, Y>{
        virtual T merge(T x, T y)override {
            return x + y;
        }
        virtual T valueOf(Y x)override {
            return T(x);
        }
        virtual T neutral()override{
            return 0;
        }
    };

    template<typename T, typename Y>
    class MinSegTree: public SegmentTree<T, Y>{
        virtual T merge(T x, T y)override {
            return min(x, y);
        }
        virtual T valueOf(Y x)override {
            return T(x);
        }
        virtual T neutral()override {
            return numeric_limits<Y> ::max()/2;
        }
    };

    template<typename T, typename Y>
    class MaxSegTree: public SegmentTree<T, Y>{
        virtual T merge(T x, T y)override {
            return max(x, y);
        }
        virtual T valueOf(Y x)override {
            return T(x);
        }
        virtual T neutral()override {
            return numeric_limits<Y> ::min()/2;
        }
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
            seg.update(++ind, val);
        }else cout<<seg.query(++ind, val)<<"\n";

    }
    return 0;
}

