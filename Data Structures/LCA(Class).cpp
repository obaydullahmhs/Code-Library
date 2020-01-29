#include <bits/stdc++.h>

using namespace std;

class LCA{
private:
    int N,LogV;
    vector<vector<int> > sparse;
    vector<int> depth;

public:
    vector<vector<int> > adj;
    LCA(){
        N=20000;
        LogV=20;
    }
    ///Initializing
    void init(int n){
        N=n;
        sparse=vector<vector<int> >(LogV+5,vector<int>(N+10,-1));
        depth=vector<int>(N,0);
        adj=vector<vector<int> >(N+10);
    }
    ///DFS
    void dfs(int node, int par){
        for(int it:adj[node]){
            if(it!=par){
                sparse[0][it]=node;
                depth[it]=depth[node]+1;
                dfs(it, node);
            }
        }
    }
    ///Sparse Table
    void sparseTable(){
        for(int i=1;i<22;i++){
            for(int j=1;j<=N;j++){
                int x=sparse[i-1][j];
                if(x!=-1) sparse[i][j]=sparse[i-1][x];
            }
        }
    }
    ///Level up
    int levelUp(int u, int v){
    int dif=depth[v]-depth[u];
        while(dif>0){
            int logDif=log2(dif);
            v = sparse[logDif][v];
            dif-=(1<<logDif);
        }
        return v;
    }
    ///Find LCA
    int findLCA(int u, int v){
        if(depth[u]>depth[v]) swap(u,v);
        v=levelUp(u,v);
        if(u==v) return u;
        for(int i=LogV+2;i>=0;i--){
            int x=sparse[i][u];
            int y=sparse[i][v];
            if(x == -1 || y == -1) continue;
            if(x!=y){
                u=x;
                v=y;
            }
        }
        return sparse[0][u];
    }

}lca;
int main() {

    int n;
    cin>>n;
    lca.init(n); ///must need to initialize

    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        lca.adj[u].push_back(v);
        lca.adj[v].push_back(u);
    }

    lca.dfs(1,-1);
    lca.sparseTable();

    int q;
    cin>>q;
    ///Query
    while(q--){
        int a,b;
        cin>>a>>b;

        cout<<lca.findLCA(a,b)<<endl;

    }

	return 0;
}

