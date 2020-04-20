
#include<bits/stdc++.h>

using namespace std;

int LIS(vector<int>& v){ ///LIS O(nlogn)
    if (v.size() == 0)
        return 0;

    vector<int> lis(v.size(), 0);
    int ln = 1;
    lis[0] = v[0];
    for (int i = 1; i < v.size(); i++) {
        auto it = lower_bound(lis.begin(), lis.begin()+ln, v[i]);
        if (it == lis.begin() + ln)
            lis[ln++] = v[i];
        else
            *it = v[i];
    }
    return ln;
}
int main(){
    int n;cin>>n;
    vector<int> a(n),b(n);
    for(int& in:a) cin>>in;
    for(int& in:b) cin>>in;
    vector<int> index(n+1,-1);

    for(int i=0;i<n;i++){
        index[a[i]]=i;
    }
    vector<int> ind;
    for(int i=0;i<n;i++){
        ind.push_back(index[b[i]]); /// index of element b[i], in the 'a'
    }

    cout<<LIS(ind)<<endl; ///LIS will be the LCS of two permutation

}

