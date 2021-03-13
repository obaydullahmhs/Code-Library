template<typename T>
class mergeSortTree{    /** 1 - Base **/
private:

    int n;
    vector< vector<T> > tree;

    virtual inline T segValue(const vector<T>& v, T val){  /// queryType
        return upper_bound(v.begin(), v.end(), val) - v.begin();    ///number of elements less than or equal to val
    }

    void buildTree(int node, int lo, int hi,const vector<T>& v){

        if(lo == hi){

            tree[node].push_back(v[lo]);
            return;
        }

        buildTree(node<<1, lo, (lo + hi)>>1, v);
        buildTree(1|(node<<1), 1 + ((lo + hi)>>1), hi, v);

        tree[node].resize(tree[node<<1].size() + tree[1|(node<<1)].size());
        merge(tree[node<<1].begin(), tree[node<<1].end(), tree[1|(node<<1)].begin(), tree[1|(node<<1)].end(), tree[node].begin());
    }

    T query(int node, int lo, int hi, int i, int j, T val){

        if(i > hi || j < lo) return 0;
        if(lo >= i && hi <= j){
            return segValue(tree[node], val);
        }

        return query(node<<1, lo, (lo + hi)>>1, i, j, val) + query(1|(node<<1), 1 + ((lo + hi)>>1), hi, i, j, val);
    }


public:

    void init(int _n){
       n = _n;   tree.resize(4*_n, vector<T>());
    }
    void buildTree(const vector<T>& v){
        buildTree(1, 1, n, v);
    }
    T query(int l, int r, T val){
        return query(1, 1, n, l, r, val);
    }
};
