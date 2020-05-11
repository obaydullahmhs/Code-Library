#include<bits/stdc++.h>
using namespace std;
int ar[10000];
vector<int> primes;
void sieve(int n){
    vector<bool> mark(n+2,false);
    primes.push_back(2);
    for(int p=3;p*p<=n;p=p+2)
        if(mark[p]==0)
            for(int i=p*p;i<=n;i+=p*2)
                mark[i]=1;

    for(int i=3;i<=n;i=i+2)
        if(!mark[i])
            primes.push_back(i);

}
int NOD(long long n){
    int div = 1;
    for(int i=0; (long long)primes[i]*(long long)primes[i]<=n; i++){
        int cnt = 0;
        while(n%primes[i]==0){
            n=n/primes[i];
            cnt++;
        }
        div*=(cnt+1);
    }
    if(n>1)
        div*=2;

    return div;
}
int main(){
    sieve(1000000);
    int n;
    cin>>n;
    cout<<NOD(n)<<endl;

    return 0;
}

