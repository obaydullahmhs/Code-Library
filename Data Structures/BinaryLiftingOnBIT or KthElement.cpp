///https://codeforces.com/blog/entry/61364
int kthElement(int v){ ///kTh element or lower_bound or binary lifting on BIT //Complexity per query log(n)
        int sum = 0;
        int pos = 0;
        for(int i=LOGN; i>=0; i--){
            if(pos + (1 << i) < n and sum + tree[pos + (1 << i)] < v){
                sum += tree[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos + 1;
}
