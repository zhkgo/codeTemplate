//#include<string>
//#include<algorithm>
//using namespace std; 
typedef unsigned int uint;
typedef pair<uint,uint> puu;
struct doubleHash{
    vector<uint> h1,h2;
    vector<uint> p1,p2;
    uint P1,P2; 
    uint mod1=805306457,mod2=1610612741;
    doubleHash(string &s,uint P1=1331,uint P2=13331):P1(P1),P2(P2),
	h1(s.size()+1,0),h2(s.size()+1,0),p1(s.size()+1,0),p2(s.size()+1,0){
        p1[0]=p2[0]=1;
        for(uint i=0;i<s.size();i++){
            h1[i+1]=(1ll*h1[i]*P1+s[i])%mod1;
            p1[i+1]=(1ll*p1[i]*P1)%mod1;
            
            h2[i+1]=(1ll*h2[i]*P2+s[i])%mod2;
            p2[i+1]=(1ll*p2[i]*P2)%mod2;
        }
    }
    puu getV(int l,int r){//s[l,r]
        uint ta= (1ll*h1[r+1]+mod1-(1ll*h1[l]*p1[r-l+1]%mod1))%mod1;
        uint tb= (1ll*h2[r+1]+mod2-(1ll*h2[l]*p2[r-l+1]%mod2))%mod2;
		return {ta,tb};
    }
    doubleHash()=default;
};

