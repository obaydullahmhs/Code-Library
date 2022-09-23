#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
vector<T> cntSort(vector<T>& v) {

  int n = v.size();
  vector<T> ans(n);
  int mx = 0;

  for(int i = 0; i < n; i++) mx = max(mx, v[i]);
  vector<int> cnt(mx + 1, 0);

  for (int i = 0; i < n; i++) cnt[v[i]]++;
  for (int i = 1; i <= mx; i++) cnt[i] += cnt[i - 1];
  for (int i = n - 1; i >= 0; i--){
    ans[cnt[v[i]] - 1] = v[i];
    cnt[v[i]]--;
  }

  return ans;
}

int main(){
  vector<int> v;
  srand(time(0));
  for(int i = 0; i < 100; i++) v.push_back(rand() % 100000);
  for(auto it: v) cout << it << " " ;
  cout << endl;
  cout << endl;
  v = cntSort(v);
  for(auto it: v) cout << it << " " ;
  cout << endl;

  return 0;
}

