#include<iostream>
#include<string>
#include<cstdio>
#include<list>
#include<map> 
#include<algorithm>
#include<vector>
#include<assert.h>
#include "arm.h"
#include "world.h"
#include "warriors.h"
#include "headquater.h" 
#include "city.h"
using namespace std;


int main(){
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int T;
	cin>>T;
	for(int cs=1;cs<=T;cs++){
		int M,N,K,TIME;
		cin>>M>>N>>K>>TIME;
		for(int i=0;i<5;i++){
			cin>>HP[i];
		}
		for(int i=0;i<5;i++){
			cin>>ACK[i];
		}
		cout<<"Case "<<cs<<":"<<endl;
		vector<int> o1={2,3,4,1,0};
		vector<int> o2={3,0,1,2,4};
		Headquarter h1(o1,"red",M,0,K,1);
		Headquarter h2(o2,"blue",M,N+1,K,-1);
		mlog.reset(&h1,&h2,N);
		TIME++;
		while(TIME--){
			if(mlog.addTime())
				break;
		}
	}
	return 0;
}
