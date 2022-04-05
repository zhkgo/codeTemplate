//设计一个字符串类String，通过运算符重载实现字符串的输入、输出以及+=、==、!=、<、>、>=、[ ]等运算。

#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
class String{
    char *data;
    int len;
public:
    String(const char *s=""){
        len=strlen(s);
        data=new char[len+1];
        strcpy(data,s);
    }
    ~String(){
        delete []data;
    }
    friend ostream& operator<<(ostream& os,const String &s){
        os<<s.data;
    }
    friend istream& operator>>(istream& is,const String &s){
        is>>s.data;//存在溢出风险
    }
    int size()const{
        return len;
    }
    bool operator<(const String &b)const{
        int e=min(len,b.len);
        for(int i=0;i<e;i++){
            if(data[i]!=b.data[i])return data[i]<b.data[i];
        }
        return len<b.len;
    }
    bool operator>=(const String &b)const{
        return !(*this<b);
    }
    bool operator==(const String &b)const{
        return !(*this<b)&&!(b<*this);
    }
    bool operator!=(const String &b)const{
        return !(*this==b);
    }
    bool operator>(const String &b)const{
        return b<*this;
    }
    bool operator<=(const String &b)const{
        return !(b<*this);
    }
    bool operator!()const {
        return len==0;
    }
    bool empty()const{
        return len==0;
    }
    String& operator=(const String &b){
        delete []data;
        len=b.len;
        data=new char[len+1];
        strcpy(data,b.data);
        return *this;
    } 
    String& operator=(String &&b){
        swap(data,b.data);
        swap(len,b.len);
        return *this;
    }
    String& operator+=(const String &b){
        char *tmp=new char[len+b.len+1];
        strcpy(tmp,data);
        strcpy(tmp+len,b.data);
        len+=b.len;
        delete data;
        data=tmp;
    }
    char& operator[](int idx){
        return data[idx];
    }
};
int main()
{
    //测试用例
    String s1("happy"), s2("new year"), s3;
    cout << "s1 is " << s1 << "\ns2 is " << s2 << "\ns3 is " << s3
         << "\n比较s2和s1:"
         << "\ns2 ==s1结果是 " << (s2 == s1 ? "true" : "false")
         << "\ns2 != s1结果是 " << (s2 != s1 ? "true" : "false")
         << "\ns2 >  s1结果是 " << (s2 > s1 ? "true" : "false")
         << "\ns2 <  s1结果是 " << (s2 < s1 ? "true" : "false")
         << "\ns2 >= s1结果是 " << (s2 >= s1 ? "true" : "false");
    cout << "\n\n测试s3是否为空: ";
    if (!s3)
    {
        cout << "s3是空串" << endl; //L3
        cout << "把s1赋给s3的结果是：";
        s3 = s1;
        cout << "s3=" << s3 << "\n"; //L5
    }
    cout << "s1 += s2 的结果是：s1="; //L6
    s1 += s2;
    cout << s1; //L7

    cout << "\ns1 +=  to you 的结果是："; //L8
    s1 += " to you";
    cout << "s1 = " << s1 << endl; //L9
    s1[0] = 'H';
    s1[5] = 'N';
    s1[9] = 'Y';
    cout << "s1 = " << s1 << "\n"; //L10
    system("pause");
    return 0;
}
