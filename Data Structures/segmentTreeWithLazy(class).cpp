#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

template<typename T>
class segmentWithLazy{
private:
    struct data{
        T prop,sum;
        data():prop(0),sum(0){}
        data(T _sum,T _prop):sum(_sum),prop(_prop){}
    };
    int n;
    vector<data> tree;
public:
    segmentWithLazy():n(2e5),tree(3*n+15,data(0,0)){}
    segmentWithLazy(int _n):n(_n),tree(3*n+15,data(0,0)){}
    void init(int _n){n =_n,tree.assign(3*n+15,data(0,0));}
    void SegmentTree(vector<T> &given, int node, int low, int high){
        if (low == high){
            tree[node].sum = given[low];
            return;
        }
        int left = 2 * node;
        int right = 2 * node + 1;
        int mid = (low + high) / 2;
        SegmentTree(given, left, low, mid);
        SegmentTree(given, right, mid + 1, high);
        tree[node].sum = tree[left].sum + tree[right].sum;
    }
    void propagate(int node,int low,int hi){
        int left=2*node;
        int right=left+1;
        int mid =(low+hi)/2;
        tree[node].sum+=(hi-low+1)*tree[node].prop;
        if(hi!=low){
            tree[left].prop+=tree[node].prop;
            tree[right].prop+=tree[node].prop;
        }
        tree[node].prop=0;
    }
    void update(int node,int low,int hi,int i,int j,T value){
        int left=2*node;
        int right=left+1;
        if(tree[node].prop) propagate(node,low,hi);
        if(hi<i||j<low) return;
        if(low>=i&&hi<=j){
            tree[node].sum+=(hi-low+1)*value;
            if(hi!=low){
                tree[left].prop+=value;
                tree[right].prop+=value;
            }
            tree[node].prop=0;
            return ;
        }
        int mid=(low+hi)/2;
        update(left,low,mid,i,j,value);
        update(right,mid+1,hi,i,j,value);
        tree[node].sum=tree[left].sum+tree[right].sum;
    }
    T query(int node,int low,int hi,int i,int j){
        int left=2*node;
        int right=left+1;
        if(tree[node].prop) propagate(node,low,hi);
        if(hi<i||j<low) return 0;
        if(low>=i&&hi<=j)
            return tree[node].sum;
        int mid=(low+hi)/2;
        T x= query(left,low,mid,i,j);
        T y= query(right,mid+1,hi,i,j);
        return x+y;
    }
};
int main() {

    int n,q;
    cin>>n>>q;

    segmentWithLazy<int> seg(n);


    while(q--){
        int a,b,c;
        cin>>a>>b>>c;
        if(a==0){
            ll d;
            cin>>d;
            seg.update(1,1,n,b,c,d);
        }
        else cout<<seg.query(1,1,n,b,c)<<endl;

    }

	return 0;
}
