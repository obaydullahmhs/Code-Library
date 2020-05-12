#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
string a, b, p;
const int N = 1005;
int lena, lenb, dp[N][N];
int LCS(){
    ///Iterating
    for(int i = 1;i<=lena;i++){
        for(int j=1;j<=lenb;j++){
            if(a[i-1]==b[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
            }else{
                if(dp[i-1][j]>dp[i][j-1]) dp[i][j] = dp[i-1][j];
                else dp[i][j] = dp[i][j-1];
            }
        }
    }
    int n = lena, m = lenb;
    while(n>0 && m>0){              ///printing LCS
        if(a[n-1]==b[m-1]){
            p.push_back(a[n-1]);
            n--,m--;
        }else{
            if(dp[n-1][m]>dp[n][m-1]) n--;
            else m--;
        }
    }
    reverse(p.begin(), p.end());    ///we were iterating from the last

    return dp[lena][lenb]; ///length of LCS
}
int main() {
    a = "abcdhwoene", b = "bcdaabdhksjkoejkfdne";
    lena = a.size(), lenb = b.size();

    cout<<"LCS is length of = "<<LCS()<<endl;
    cout<<"LCS string is = "<<p<<endl;

    return 0;
}
