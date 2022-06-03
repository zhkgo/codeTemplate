#include<cstdio>
using namespace std;

typedef long long ll;
/* 
矩阵类模板及矩阵快速幂

示例代码,是对https://codeforces.com/problemset/problem/209/A的解答
*/


//T 表示数据类型 N表示矩阵维度
template<typename T,int N>
struct Matrix{
    T a[N][N];
    static T mod;
    
    //矩阵构造函数
    Matrix(T v=0){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                a[i][j]=v;
            }
        }
    }
    //直接访问内部数组
    T* operator[](int idx){
        return a[idx];
    }
    //获取单位矩阵
    Matrix getE(){
        Matrix<T,N> e;
        for(int i=0;i<2;i++){
            e.a[i][i]=1;
        }
        return e;
    }
    //矩阵乘法
    Matrix operator*(const Matrix<T,N> &b)const{
        Matrix<T,N> ans;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                for(int k=0;k<N;k++){
                    ans.a[i][j]+=1ll*a[i][k]*b.a[k][j]%mod;
                    ans.a[i][j]%=mod;
                }
            }
        }
        return ans;
    }
};

//设置静态变量取余的值
template<typename T,int N>
T Matrix<T,N>::mod=1e9+7;


//给要用的矩阵类型加个名字
// typedef Matrix<int,2> mat;
using mat=Matrix<int,2>;

//矩阵快速幂
mat powermi(mat in,int n){
    mat ans=in.getE();
    while(n){
        if(n&1){
            ans=ans*in;
        }
        in=in*in;
        n>>=1;
    }
    return ans;
}

const int maxn=1e6+10;
int n;
int main(){
    scanf("%d",&n);
    mat m(1),s;
    m[0][0]=0;
    s[0][0]=1;s[0][1]=1;
    m=powermi(m,n);
    s=s*m;
    const int mod=1e9+7;
    printf("%d\n",((s[0][1]+s[0][0])%mod-2+mod)%mod);
    return 0;
}