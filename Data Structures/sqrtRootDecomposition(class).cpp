class composition{
public:
    int segment[1000]={0},segmentSize;
    // 0 Base
    void pre_process(vector<int> &v,int n){
        int cur_pos=-1;
        segmentSize=sqrt(n);
        for(int i=0;i<n;i++){
            if(i%segmentSize==0) cur_pos++;
            segment[cur_pos]+=v[i];
        }
    }
    // 0 Base Update
    void Update(vector<int> &v,int index,int val){
        int segment_num=index/segmentSize;
        segment[segment_num]-=v[index];
        segment[segment_num]+=val;
        v[index]=val;
    }
    //0 Base Query
    int Query(vector<int> &v,int l,int r){
        int sum=0;
        while(l<r && l%segmentSize!=0){
            sum+=v[l];
            l++;
        }
        while(l+segmentSize <=r){
            sum+=(segment[l/segmentSize]);
            l+=segmentSize;
        }
        while(l<=r){
            sum+=v[l];
            l++;
        }
        return sum;
    }
};
