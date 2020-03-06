#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

template<typename T>
using ordered_multiset=tree<T, null_type, less_equal<T>, rb_tree_tag,tree_order_statistics_node_update>;

int main(){

    ordered_set<int> st;
    ordered_multiset<int> ml;

    st.insert(1);
    st.insert(3);

    cout<<st.order_of_key(3)<<endl; /// 1
    cout<<*st.find_by_order(1)<<endl; /// 3

    {   ///erase
        st.erase(st.find_by_order(1));
        st.erase(3);
    }


    ml.insert(1); ml.insert(1); ml.insert(3); ml.insert(3);
                       ml.insert(5);

    cout<<ml.order_of_key(3)<<endl; /// first index of '3' -> 2
    cout<<*ml.find_by_order(4)<<endl; /// 5

    {   ///erase
        ml.erase(ml.find_by_order(ml.order_of_key(1))); /// erase the first element of a particular number
    }

}
