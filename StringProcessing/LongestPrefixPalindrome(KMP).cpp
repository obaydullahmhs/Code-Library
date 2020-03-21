#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
class PrefixPalindrome{
private:
    int n;
    int sz;
    string pal,str;
    vector<int> lps;
public:
    PrefixPalindrome(){
        n=1e5;str="";
        sz=0;pal="";
    }
    PrefixPalindrome(int _n){
        n=_n;str="";
        sz=0;pal="";
    }
    void Assign(){
        pal="";sz=0;
        lps.assign(n,0);
    }
    void preProcess(){  ///pre process for lps
        Assign();
        int i=0,j=1;
        while(j<n){
            if(str[i]==str[j]){
                lps[j]=i+1;
                i++,j++;
            }else{
                if(i!=0){
                    i=lps[i-1];
                }else{
                    lps[j]=0;
                    j++;
                }
            }
        }
        sz=lps[n-1]; ///longest prefix palindrome length is the last value of lps
    }
    void makeString(string str){
        (this->str)=str;
        (this->str)+='#';
        reverse(str.begin(),str.end());
        (this->str)+=str;
        n=(this->str).size();
        preProcess();
    }
    string longestPrefixPalindrome(const string& str){
        makeString(str);
        for(int i=0;i<sz;i++){
            pal+=str[i];
        }
        return pal;
    }
    string shorteshStringForPalindrome(const string& str){
        string s=longestPrefixPalindrome(str);
        string t=str.substr(sz);
        reverse(t.begin(),t.end());
        return t+str;   ///minimum character making the string palindrome

    }


}kmp;
int main() {
    string x="abbaax";
    cout<<kmp.longestPrefixPalindrome(x)<<endl;
    cout<<kmp.shorteshStringForPalindrome(x)<<endl;
}


