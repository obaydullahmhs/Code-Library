inline T Pow(T p, T e){ ///int and long long long only (p^e)
    T ret = 1;
    for(; e > 0; e >>= 1){
        if(e & 1) ret = ret * p;
        p = p * p;
    }
    return (T)ret;
}
