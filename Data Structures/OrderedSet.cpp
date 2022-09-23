#include<bits/stdc++.h>
using namespace std;

///
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<typename T>
class ordered_set{
private:

  tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update> st;

public:
  ordered_set(){}

  void insert(T val){
    st.insert(val);
  }
  int get_index(T val){
    return st.order_of_key(val); ///lower_bound or number of element less than this val
  }
  T operator[](const int& id){
    assert(id >= 0 && id < st.size());
    return *st.find_by_order(id);
  }
  void erase(T val){
    auto it = st.find(val);
    if(it != st.end()){
      st.erase(it);
    }
  }
  size_t size(){
    return st.size();
  }
  T front(){
    return *st.begin();
  }
  T back(){
    return *st.rbegin();
  }
};


template<typename T>
class ordered_multiset{
private:

  tree<T, null_type, less_equal<T>, rb_tree_tag,tree_order_statistics_node_update> st;

public:
  ordered_multiset(){}

  void insert(T val){
    st.insert(val);
  }
  int get_index(T val){
    return st.order_of_key(val); ///lower_bound or number of element less than this val
  }
  T operator[](const int& id){
    assert(id >= 0 && id < st.size());
    return *st.find_by_order(id);
  }
  void erase(T val){
    auto it = st.find_by_order(st.order_of_key(val));
    if(it != st.end() && *it == val){
      st.erase(it);
    }
  }
  size_t size(){
    return st.size();
  }
  T front(){
    return *st.begin();
  }
  T back(){
    return *st.rbegin();
  }
};
///

int main(){

    ordered_set<int> st;
    ordered_multiset<int> ml;
    srand(time(0));
//    for(int i = 0; i < 10; i++){
//      st.insert(rand() % 10);
//      ml.insert(rand() % 10);
//    }
//    for(int i = 0; i < st.size(); i++) cout << st[i] << endl;
//    cout << "no" << endl;
//    for(int i = 0; i < ml.size(); i++) cout << ml[i] << endl;
//    cout << st.size() << endl;
//    cout << ml.size() << endl;

  ml.insert(1);
  ml.insert(1);
  ml.insert(2);
  cout << ml.size() << endl;
  ml.erase(1);
  ml.erase(1);
  for(int i = 0; i < ml.size(); i++) cout << ml[i] << endl;
  cout << ml.front() << endl;
  cout << ml.back() << endl;
  return 0;
}
