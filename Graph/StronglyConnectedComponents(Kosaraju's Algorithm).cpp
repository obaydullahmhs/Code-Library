#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<int> > adj, radj, scc;
stack<int> finishTime;

void dfs(int node, vector<bool>& vis){
    vis[node] = true;
    for(auto v: adj[node]){
        if(vis[v]) continue;
        dfs(v, vis);
    }
    finishTime.push(node); /// top sort
}

void SCC(int node, vector<bool>& vis){
    vis[node] = true;
    scc.back().push_back(node);
    for(auto it: radj[node]){
        if(vis[it]) continue;
        SCC(it, vis);
    }
}

int main(){

    int n, m;
    cin>>n>>m;
    adj.resize(n+1); radj.resize(n+1);

    for(int i = 0;i<m;i++){
        int u, v; cin>>u>>v;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    vector<bool> vis(n+1, false);
    for(int i = 1;i<=n;i++)
        if(vis[i]==0) dfs(i, vis);

    vis.assign(n+1, false);

    while(!finishTime.empty()){

        if(vis[finishTime.top()]==0){
            scc.push_back({});
            SCC(finishTime.top(), vis);
        }
        finishTime.pop();
    }

    cout<<"Number of SCC is : "<<scc.size()<<endl;
    for(auto it: scc){
        for(auto jt:it){
            cout<<jt<<" ";
        }
        cout<<endl;
    }


    return 0;
}

