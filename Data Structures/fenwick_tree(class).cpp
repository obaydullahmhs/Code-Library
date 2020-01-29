class fenwick{
public:
    int tree[100005]={0};
    void Update(int pos, int val, int limit){
        while(pos<=limit){
            tree[pos]+=val;
            pos+=pos&(-pos);
        }
    }
    int Query(int pos){

        int sum=0;
        while(pos>0){
            sum+=tree[pos];
            pos-=pos&(-pos);

        }
        return sum;
    }
};
