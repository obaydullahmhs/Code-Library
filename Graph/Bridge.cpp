#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
class Bridge{
private:
    int N, Time;
    vector<int> low,disc;
    vector<pair<int,int> > bridges;
    vector<bool> vis;
    vector<vector<int> > adj;
public:
    Bridge(){
        N = 2e5;
        low.assign(N+10,0);
        disc.assign(N+10,0);
        vis.assign(N+10,false);
        adj.resize(N+10);
        Time = 1;
    }
    Bridge(int _N){
        N = _N;
        low.assign(N+10,0);
        disc.assign(N+10,0);
        vis.assign(N+10,false);
        adj.resize(N+10);
        Time = 1;
    }
    void init(int _N){
        N = _N;
        low.assign(N+10,0);
        disc.assign(N+10,0);
        vis.assign(N+10,false);
        adj.resize(N+10);
        Time = 1;
    }
    inline void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int node, int par = -1){
        disc[node] = low[node] = Time++;
        vis[node] = true;

        for(int v:adj[node]){
            if(v == par) continue; ///Ignore parent
            if(!vis[v]){        ///Tree edge
                dfs(v, node);
                if(disc[node]<low[v]){  ///{node and v} is a bridge
                    bridges.emplace_back(node, v);
                }
                low[node] = min(low[node], low[v]);
            }
            else{                               ///Back edge
                low[node] = min(low[node], disc[v]);
            }

        }
    }
    vector<pair<int,int> > &getBridges(){
        return bridges;
    }
    vector<pair<int, int> > &getBridges(int node){
        dfs(node);
        return bridges;
    }
};
int main() {
    int n, m;
    cin>>n>>m;
    Bridge bridge(n);
    for(int i=0;i<m;i++){
        int u, v;
        cin>>u>>v;
        bridge.addEdge(u,v);
    }
    vector<pair<int, int> > ans = bridge.getBridges(1);
    cout<<"Total Bridge:- "<<ans.size()<<endl;
    for(auto it:ans){
        cout<<it.first<<" "<<it.second<<endl;
    }

	return 0;
}
