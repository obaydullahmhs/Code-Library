#include<bits/stdc++.h>
using namespace std;
vector<int> primes;
void sieve(int n){
    vector<bool> mark(n+2,false);
    primes.push_back(2);
    for(int p=3;p*p<=n;p=p+2){
        if(mark[p]==0){
            for(int i=p*p;i<=n;i+=p*2){
                mark[i]=1;
            }
        }
    }
    for(int i=3;i<=n;i=i+2){
        if(!mark[i]){
            primes.push_back(i);
        }
    }
}
int main()
{
    int n;
    cin>>n;
    sieve(n);

    return 0;
}

