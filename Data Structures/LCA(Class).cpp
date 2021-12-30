template<typename T> /// lca, max and min road cost
class LCA{

private:
    int n, logv;
    const T inf = numeric_limits<T>::max()/3;
    vector<vector<T> > sparse, maxsparse, minsparse;
    vector<vector<pair<T, T> > > adj;
    vector<int> depth;

public:

    LCA(int _n):n(_n),logv(log2(n) + 1), sparse(logv + 2, vector<T>(n + 5, -1)), maxsparse(logv + 5, vector<T>(n + 5, -1)),
    minsparse(logv + 5, vector<T>(n + 5, inf)), depth(n + 5, 0), adj(n + 5, vector<pair<T, T> >()){}

    void init(int _n){
        n = _n, logv = log2(n) + 1;
        sparse.assign(logv + 2, vector<T>(n + 5, -1));
        maxsparse.assign(logv + 5, vector<T>(n + 5, -1));
        minsparse.assign(logv + 5, vector<T>(n + 5, inf));
        depth.assign(n + 5, 0);
        adj.assign(n + 5, vector<pair<T, T> >());
    }

    inline void addEdge(int u, int v, T w){
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    void dfs(int node, int par, long long val = -1){
        if(par != -1){
            sparse[0][node] = par;
            minsparse[0][node] = val;
            maxsparse[0][node] = val;
            depth[node] = depth[par] + 1;
        }
        for(int i = 1; i < logv + 2; i++) {
            if(sparse[i - 1][node] != -1) {
                sparse[i][node] = sparse[i-1][sparse[i - 1][node]];
                maxsparse[i][node] = max(maxsparse[i - 1][node], maxsparse[i-1][sparse[i - 1][node]]);
                minsparse[i][node] = min(minsparse[i - 1][node], minsparse[i-1][sparse[i - 1][node]]);
            }
            else break;
        }
        for(auto it:adj[node]){
            if(it.first!=par){
                dfs(it.first, node,it.second);
            }
        }
    }
    inline tuple<T, T, T> findLCA(int u, int v){
        if(depth[u] > depth[v]) swap(u, v);
        tuple<T, T, T> ans(u, -1, inf);
        for(int i = logv + 1; i >= 0; i--) {
            if(sparse[i][v] != -1 && depth[sparse[i][v]] >= depth[u]) {
                get<2>(ans) = min(get<2>(ans), minsparse[i][v]);
                get<1>(ans) = max(get<1>(ans), maxsparse[i][v]);
                v = sparse[i][v];
            }
        }
        if(u == v){
            get<0>(ans) = u;
            return ans;
        }
        for(int i = logv + 1; i >= 0; i--) {
            if(sparse[i][v] != sparse[i][u]) {
                get<2>(ans) = min({get<2>(ans), minsparse[i][v], minsparse[i][u]});
                get<1>(ans) = max({get<1>(ans), maxsparse[i][v], maxsparse[i][u]});
                v = sparse[i][v];
                u = sparse[i][u];
            }
        }
        get<2>(ans) = min({get<2>(ans), minsparse[0][v], minsparse[0][u]});
        get<1>(ans) = max({get<1>(ans), maxsparse[0][v], maxsparse[0][u]});
        get<0>(ans) = sparse[0][u];
        return ans;
    }

};
