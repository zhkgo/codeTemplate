typedef unsigned long long ULL;
struct stringHash{
    vector<ULL> h;
    vector<ULL> p;
    int P;
    stringHash(string &s,int P=1331):P(P),h(s.size()+1,0),p(s.size()+1,0){
        p[0]=1;
        for(int i=0;i<s.size();i++){
            h[i+1]=h[i]*P+s[i];
            p[i+1]=p[i]*P;
        }
    }
    ULL getV(int l,int r){//s[l,r]
        return h[r+1]-h[l]*p[r-l+1];
    }
    stringHash()=default;
};
