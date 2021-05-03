#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const long long MOD [] = {1000000007LL, 2117566807LL, 1000000007LL, 1000000037LL};
const long long BASE[] = {1572872831LL, 1971536491LL, 1000003LL, 31};

class FrontHash{    /// For Front Hash
private:
    long long base, M, len;
    vector<long long> hashing, P; /// P for base power table

public:

    void init(const string& s, const long long& _base, const long long _M){ /// 0 based

        this->base = _base;
        this->M = _M;
        this->len = s.size();
        this->P.assign(len + 5, 0);
        this->hashing.assign(len + 5, 0);

        long long calculateHash = 0;
        P[0] = 1;
        for(int i = 1; i <=len; i++)
            P[i] = (P[i - 1] * this->base) % this->M;   /// Power of base

        for(int i = 0; i < len; i++){       ///front hashing array of string s

            calculateHash = (calculateHash * this->base) + s[i];
            calculateHash %= this->M;
            this->hashing[i] = calculateHash;
        }

    }

    long long getFrontHash(int l, int r){   ///0 based

        long long ret = this->hashing[r];
        if(l > 0){
            ret = (ret - this->P[r - l + 1] * this->hashing[l - 1]) % this->M;  /// (r - l  + 1) length of the substring
            if(ret < 0) ret += this->M;
        }

        return ret;
    }
};

class BackHash{     /// For Back Hash
private:
    long long base, M, len;
    vector<long long> hashing, P; /// P for base power table

public:

    void init(const string& s, const long long& _base, const long long _M){ /// 0 based

        this->base = _base;
        this->M = _M;
        this->len = s.size();
        this->P.assign(len + 5, 0);
        this->hashing.assign(len + 5, 0);

        long long calculateHash = 0;
        P[0] = 1;
        for(int i = 1; i <=len; i++)
            P[i] = (P[i - 1] * this->base) % this->M;   /// Power of base

        for(int i = len - 1; i >= 0; i--){       ///back hashing array of string s

            calculateHash = (calculateHash * this->base) + s[i];
            calculateHash %= this->M;
            this->hashing[i] = calculateHash;
        }

    }

    long long getBackHash(int l, int r){   ///0 based

        long long ret = this->hashing[l];
        if(r + 1 < len){
            ret = (ret - this->P[r - l + 1] * this->hashing[r + 1]) % this->M;  /// (r - l  + 1) length of the substring
            if(ret < 0) ret += this->M;
        }

        return ret;
    }
};
void solve(){
    string s = "xxabcbadajhdkdk";
    FrontHash F;
    BackHash B;
    F.init(s, BASE[0], MOD[0]);
    B.init(s, BASE[0], MOD[0]);

    ///for "xxabc"
    cout << (F.getFrontHash(0, 4) == B.getBackHash(0, 4)) << endl;
    ///for "abcba"
    cout << (F.getFrontHash(2, 6) == B.getBackHash(2, 6)) << endl;

    FrontHash sub;
    string ss = "adajhdk";
    sub.init(ss, BASE[0], MOD[0]);

    /// substring of s(6, 12) and ss
    cout << (F.getFrontHash(6, 12) == sub.getFrontHash(0, ss.size() - 1)) << endl;

    cout << F.getFrontHash(1, 7) << endl;
    cout << B.getBackHash(1, 7) << endl;

}
int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc = 1;
    while(tc--){
        solve();
    }

    return 0;
}
/**

**/
