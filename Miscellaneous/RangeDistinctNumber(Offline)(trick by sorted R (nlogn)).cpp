#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 1e5 + 5;
vector<pair<int, int> > adj[N];
int ar[N];
int Idex[N];

int tree[N], ans[N];

void update(int pos, int val, int n){
    for(int i = pos;i<=n;i += i&(-i))
        tree[i] += val;
}
int query(int l, int r, int n){

    int sum1 = 0, sum2 = 0;
    for(int i = l;i > 0; i -= i&(-i))
        sum1 += tree[i];
    for(int i = r;i > 0; i -= i&(-i))
        sum2 += tree[i];

    return sum2 - sum1;
}
int cs;
void solve(){
    int n; cin>>n;
    int q; cin>>q;

    for(int i = 0;i<=n;i++) adj[i].clear();
    for(int i = 1;i<=n;i++)  cin>>ar[i];


    for(int i = 0;i<q;i++){
        int l, r; cin>>l>>r;
        adj[r].emplace_back(l, i);
    }
    memset(tree, 0, sizeof tree);
    memset(Idex, 0, sizeof Idex);

    for(int i = 1; i <= n; i++){
        if(Idex[ar[i]]) update(Idex[ar[i]], -1, n);
        update(i, 1, n);
        Idex[ar[i]] = i;

        for(auto it: adj[i]){
            ans[it.second] = (query(it.first - 1, i, n));
        }
    }

    cout<<"Case "<<++cs<<":\n";
    for(int i = 0;i<q;i++){
        cout<<ans[i]<<"\n";
    }


}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc = 1; cin>>tc;
    while(tc--){
        solve();
    }

    return 0;
}
