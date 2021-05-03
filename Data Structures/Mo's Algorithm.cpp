#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
namespace Mo{       /// 0 Base
    int k = 345, sum = 0, l = 0, r = -1;
    vector<int> input, ans;
    struct info{
        int l, r, id;
        info(): l(0), r(0), id(0){}
        info(int _l, int _r, int _id): l(_l), r(_r), id(_id){}
            bool operator < (const info& a) const {
            if(a.l / k == l / k) return (r < a.r) ^ (l / k & 1);;
            return a.l > l; ///non decreasing
        }
    };
    vector<info> query;
    void add(int ind){
        sum += input[ind];
    }
    void remove(int ind){
        sum -= input[ind];
    }
    void clear(){
        input.clear();ans.clear();
        query.clear();
    }
    ///clear if multiple test case
}
using namespace Mo;
int main(){
    int n; cin>>n;
    for(int i=0;i<n;i++){
        int in; cin>>in;
        input.push_back(in);
    }
    k = 3 * sqrt(n);
    int q; cin>>q;
    for(int i=0;i<q;i++){
        int l, r; cin>>l>>r;
        query.emplace_back(info(l,r,i));
        ans.push_back(0);
    }
    sort(query.begin(), query.end());
    l=0, r = -1, sum = 0;
    for(int i=0;i<q;i++){
        while(r<query[i].r) add(++r);
        while(r>query[i].r) remove(r--);
        while(l<query[i].l) remove(l++);
        while(l>query[i].l) add(--l);
        ans[query[i].id] = sum;
    }
    for(int i = 0;i<q;i++){
        if(i) cout<<" "<<ans[i];
        else cout<<ans[i];
    }
    cout<<"\n";

    return 0;
}

