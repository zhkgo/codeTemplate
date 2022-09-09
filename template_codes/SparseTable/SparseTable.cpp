auto Fn=[](int a,int b){
    return a>b?a:b;
};
template<typename iter,typename T>
class SparseTable {
    vector<vector<T>> arr;
public:
    SparseTable(iter begin, iter end) : arr(1){
        int n = distance(begin, end);
        arr.resize(__lg(n | 1) + 1, vector<T>(n));
        arr[0].assign(begin, end);
        for (int k = 0; k + 1 < arr.size(); ++k) {
            for (int i = 0; i + (1 << k) < n; ++i) {
                arr[k + 1][i] = Fn(arr[k][i], arr[k][i + (1 << k)]);
            }
        }
    }
    T query(int lPos, int rPos) {
        int k = __lg(rPos - lPos + 1);
        return Fn(arr[k][lPos], arr[k][rPos - (1 << k) + 1]);
    }
};
//SparseTable<decltype(chargeTimes.begin()),int> st(chargeTimes.begin(), chargeTimes.end());