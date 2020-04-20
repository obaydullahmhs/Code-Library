
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
    vector<int> a(n);
    for(int& in:a) cin>>in;

    cout<<LIS(a)<<endl;
}

