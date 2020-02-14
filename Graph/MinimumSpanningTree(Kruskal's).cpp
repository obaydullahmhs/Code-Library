#include <bits/stdc++.h>

using namespace std;

class MST{

private:

    struct data{
        int u,v;
        long long w;
        data(){
            u=v=w=0;
        }
        data(int _u,int _v, long long _w){
            u=_u,v=_v,w=_w;
        }
        bool operator<(const data& ob)const{
            return w<ob.w;
        }
    };
    vector<int> path;
    vector<data> graph;

public:
    MST(){
        path=vector<int>(2e5+25);
        root(2e5+20);
    }

    MST(int n){
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

    long long getMST(int n){
        sort(graph.begin(),graph.end());
        long long ans=0;
        int cnt=0;
        for(int i=0;i<graph.size();i++){
            if(!sameset(graph[i].u,graph[i].v)){
                ans+=graph[i].w;cnt++;
                mergeUnion(graph[i].u,graph[i].v);
            }
            if(cnt==n-1) break;
        }
        return ans;
    }

    void Add(int u, int v, long long w){
        graph.push_back(data(u,v,w));
    }
};
int main(){

    int n,m;
    cin>>n>>m;
    MST mst(n);
    for(int i=0;i<m;i++){
        int u,v;
        long long w;
        cin>>u>>v>>w;
        mst.Add(u,v,w);
    }
    cout<<mst.getMST(n)<<endl;
}

