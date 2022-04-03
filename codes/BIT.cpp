#include<cstring>
#include<vector>
using std::vector;
template<typename T>
class BIT{
    int n;
    vector<T> c;
public:
    BIT(int n=200010):n(n){
        c=vector<T>(n+1,0);
    }
    //add value x,default is 1
    void add(int i,T x=1){
        for(;i<=n;i+=i&(-i)){
            c[i]+=x;
        }
    }
    //get sum of [1,i]
    T sum(int i){
        T res=0;
        while(i){
            res+=c[i];
            i-=i&(-i);
        }
        return res;
    }
};
