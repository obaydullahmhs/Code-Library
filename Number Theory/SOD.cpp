#include<bits/stdc++.h>
using namespace std;
int ar[10000];
vector<int> primes;
void sieve(int n){
    bool mark[n+2]={0};
    primes.push_back(2);
    for(int p=3; p*p<=n; p=p+2)
        if(mark[p]==0)
            for(int i=p*p; i<=n; i+=2*p)
                mark[i]=1;
    for(int i=3; i<=n; i=i+2)
        if(!mark[i])
            primes.push_back(i);

}
long long SOD(long long n){
    long long sum=1;
    for(int i=0; (long long)primes[i]*(long long)primes[i]<=n; i++){
        long long pow=1,temp=1;
        while(n%primes[i]==0){
            n=n/primes[i];
            pow*=primes[i];
            temp+=pow;
        }
        sum*=temp;
    }
    if(n>1) {
        sum*=(n+1);
    }
    return sum;
}
int main(){
    sieve(1000000);
    int n;
    cin>>n;
    cout<<SOD(n)<<endl;

    return 0;
}

