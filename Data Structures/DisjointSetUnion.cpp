#include <bits/stdc++.h>
using namespace std;

class DSU{
private:
  int n;
  int comp;
  vector<int> path;
public:
  DSU(int _n){
    init(_n);
  }
  void init(int _n){
    n = _n;
    comp = n;
    path.resize(n + 5);
    iota(path.begin(), path.end(), 0);
  }
  int findUnion(int x) {
    return path[x] = (path[x] == x? x : findUnion(path[x]));
  }
  bool sameSet(int x, int y) {
    return findUnion(x)==findUnion(y);
  }
  bool mergeUnion(int x, int y) {
    int px = findUnion(x);
    int py = findUnion(y);
    if(px == py) return false;
    path[px] = py;
    --comp;
    return true;
  }
  int totalComp(){
    return comp;
  }
};

int main(){

  int n, m;
  cin>> n >> m;
  DSU dsu(n);
  for(int i = 0; i < m; i++){
    int u, v;
    cin>> u >> v;
    cout<< dsu.sameSet(u, v) << endl;
    if(!dsu.sameSet(u, v)) dsu.mergeUnion(u,v);
  }
  return 0;
}


