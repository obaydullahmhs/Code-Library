#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
namespace Mo{       /// 0 Base
    int k = 345, sum = 0, l = 0, r = -1;
    vector<int> input, ans;
    struct info{
        int l, r, id;
        info():l(0),r(0),id(0){}
        info(int _l, int _r, int _id):l(_l),r(_r),id(_id){}
        bool operator <(const info& a)const{
            if(a.l/k == l/k) return a.r>r;
            return a.l>l; ///non decreasing
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
int main(){
    int n; cin>>n;
    for(int i=0;i<n;i++){
        int in; cin>>in;
        Mo::input.push_back(in);
    }
    Mo::k = sqrt(n);
    int q; cin>>q;
    for(int i=0;i<q;i++){
        int l, r; cin>>l>>r;
        Mo::query.emplace_back(Mo::info(l,r,i));
        Mo::ans.push_back(0);
    }
    sort(Mo::query.begin(),Mo::query.end());
    Mo::l=0, Mo::r = -1, Mo::sum = 0;
    for(int i=0;i<q;i++){
        while(Mo::r<Mo::query[i].r) Mo::add(++Mo::r);
        while(Mo::r>Mo::query[i].r) Mo::remove(Mo::r--);
        while(Mo::l<Mo::query[i].l) Mo::remove(Mo::l++);
        while(Mo::l>Mo::query[i].l) Mo::add(--Mo::l);
        Mo::ans[Mo::query[i].id] = Mo::sum;
    }
    using namespace Mo;
    for(int i = 0;i<q;i++){
        if(i) cout<<" "<<ans[i];
        else cout<<ans[i];
    }
    cout<<"\n";

    return 0;
}

