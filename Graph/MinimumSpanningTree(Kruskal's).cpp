#include <bits/stdc++.h>

using namespace std;

class MST{

private:
    struct data{
        int u,v;
        long long w;
        data():u(0), v(0), w(0){}
        data(int _u,int _v, long long _w):u(_u), v(_v), w(_w){}
        bool operator<(const data& ob)const{
            return w < ob.w;
        }
    };
    int n;
    vector<int> path;
    vector<data> graph;
    vector<tuple<int, int, long long> > ansG;

public:

    MST(int _n):n(_n), path(n + 5){
        iota(path.begin(), path.end(), 0);
    }
    void init(int _n){
        this->n = _n;
        this->path.resize(n + 5);
        iota(path.begin(), path.end(), 0);
    }

    int findUnion(int x) {
        if(path[x] == x) return x;
        return path[x] = findUnion(path[x]);
    }

    void mergeUnion(int x,int y) {
        path[findUnion(x)] = findUnion(y);
    }

    bool sameSet(int x,int y) {
        return findUnion(x) == findUnion(y);
    }

    long long getMST(){

        sort(graph.begin(),graph.end());
        long long ans = 0;
        int cnt = 0;
        for(int i = 0;i < graph.size(); i++){
            if(!sameSet(graph[i].u, graph[i].v)){
                ans += graph[i].w;
                cnt++;
                mergeUnion(graph[i].u, graph[i].v);
                ansG.emplace_back(make_tuple(graph[i].u, graph[i].v, graph[i].w));
            }
            if(cnt == n - 1) break;
        }
        return ans;
    }

    void Add(int u, int v, long long w){
        graph.push_back(data(u,v,w));
    }

    vector<tuple<int, int, long long> > returnTree(){
        return ansG;
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

