#include <bits/stdc++.h>

using namespace std;

class DSU{

private:
    vector<int> path;
public:
    DSU(){
        path=vector<int>(2e5+25);
        root(2e5+20);
    }
    DSU(int n){
        path=vector<int>(n+25);
        root(n+20);
    }
    void root(int n) {
        for(int i=0; i<=n; i++)
            path[i]=i;
    }
    int findUnion(int x) {
        if(path[x]==x) return x;
        return path[x]=findUnion(path[x]);

    }
    void mergeUnion(int x,int y) {
        path[findUnion(x)]=findUnion(y);
    }
    bool sameSet(int x,int y) {
        return findUnion(x)==findUnion(y);
    }
};
int main(){

    int n,m;
    cin>>n>>m;
    DSU dsu(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        cout<<dsu.sameSet(u,v)<<endl;
        if(!dsu.sameSet(u,v)) dsu.mergeUnion(u,v);
    }
}


