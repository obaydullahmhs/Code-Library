template<typename T>
class RMQ2D{  ///'max' for MAX Query and 'min' for MIN Query
private:
    int n, m, logn, logm;
    vector<int> calLog;
    vector<vector<vector<vector<T> >> > sparse;
public:
    RMQ2D(int _n, int _m):n(_n), m(_m), logn(log2(n) + 1), logm(log2(m) + 1), calLog(max(n, m) + 5, 0),
    sparse(logn + 1, vector<vector<vector<T>> >(n + 5, vector<vector<T> >(logm + 1, vector<T>(m + 5, 0)))){};

    void init(int _n, int _m){n = _n, m = _m, logn = 1 + log2(n), calLog.assign(max(n, m) + 5, 0),
    sparse.assign(logn + 1,vector<vector<vector<T>>>(n + 5, vector<vector<T> >(logm + 1, vector<T>(m + 5, 0))));}

    void preProcess(const vector<vector<T> >& given){
        for(int i = 2; i <= max(n, m); i++) calLog[i] = 1 + calLog[i/2];
        for(int ir = 0;ir < n; ir++){
            for(int ic = 0; ic < m; ic++)
                sparse[0][ir][0][ic] = given[ir][ic];

            for(int jc = 1; jc <= logm; jc++)
                for(int ic = 0; ic + (1 << (jc - 1)) < m; ic++)
                     sparse[0][ir][jc][ic] = max(sparse[0][ir][jc - 1][ic], sparse[0][ir][jc - 1][ic + (1 << (jc - 1))]);
        }


        for(int jr = 1; jr <= logn; jr++)
          for(int ir = 0; ir + (1 << (jr - 1)) < n; ir++)
            for(int jc = 0; jc <= logm; jc++)
              for(int ic = 0; ic < m; ic++)
                sparse[jr][ir ][jc][ic] = max(sparse[jr - 1][ir][jc][ic], sparse[jr - 1][ir + (1 <<(jr - 1))][jc][ic]);
    }
    T getValue(int x1, int y1, int x2, int y2){
        int kx = calLog[(x2 - x1 + 1)];
        int ky = calLog[(y2 - y1 + 1)];
        T min_R1 = max(sparse[kx][x1][ky][y1], sparse[kx][x1][ky][y2 + 1 - (1 << ky)]);
        T min_R2 = max(sparse[kx][x2 + 1 - (1 << kx)][ky][y1], sparse[kx][x2 + 1 - (1 << kx)][ky][y2 + 1 - (1 << ky)]);
        return max(min_R1, min_R2);
    }
};
