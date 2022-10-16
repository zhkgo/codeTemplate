template<typename iter,typename T,typename Compare=std::function<T(const T&,const T&)> >
class SparseTable {
    vector<vector<T>> arr;
    Compare fn;
public: 
    SparseTable(iter begin, iter end,Compare fn) : arr(1),fn(fn){
        int n = distance(begin, end);
        arr.resize(__lg(n | 1) + 1, vector<T>(n));
        arr[0].assign(begin, end);
        for (int k = 0; k + 1 < arr.size(); ++k) {
            for (int i = 0; i + (1 << k) < n; ++i) {
                arr[k + 1][i] = fn(arr[k][i], arr[k][i + (1 << k)]);
            }
        }
    }
    T query(int lPos, int rPos) {
        int k = __lg(rPos - lPos + 1);
        return fn(arr[k][lPos], arr[k][rPos - (1 << k) + 1]);
    }
};
//        SparseTable<decltype(nums.begin()),int> st1(nums.begin(), nums.end(),[](int a,int b){
//           return a>b?a:b;
//        });