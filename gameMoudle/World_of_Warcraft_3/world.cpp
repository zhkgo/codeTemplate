#include "world.h"
#include "headquater.h"
#include "city.h"

World mlog;
/*
World implement
*/

void World::reset(Headquarter* _h1,Headquarter *_h2,int N){
	h1=_h1;
	h2=_h2;
	citys.clear();
	for(int i=0;i<N;i++){
		citys.emplace_back(City(i+1));
	}
	now=0;
}
bool World::addTime(){
	int c=now%60;
	if(c==0){
		h1->bornNext();
		h2->bornNext();
	}else if(c==5){
		for(int i=0;i<citys.size();i++){
			citys[i].lionRun();
		}
		h1->lionRun();
		h2->lionRun();
	}else if(c==10){
		h1->goAhead();
		h2->goAhead();
		bool r1=h1->enemyReport();
		for(int i=0;i<citys.size();i++){
			citys[i].report();
		}
		bool r2=h2->enemyReport();
		if(r1||r2)
			return true;
	}else if(c==35){
		for(int i=1;i<=citys.size();i++){
			citys[i-1].wolfPlunder();
		}
	}else if(c==40){
		//battle
		for(int i=1;i<=citys.size();i++){
			citys[i-1].judge();
		}
		h1->clearDead();
		h2->clearDead();
	}else if(c==50){
		h1->report();
		h2->report();
	}else if(c==55){
//		h1->warriorReport();
//		h2->warriorReport();
		//battle
		for(int i=1;i<=citys.size();i++){
			citys[i-1].warriorReport();
		}
	}
	++now;
	return false;
}
void World::log(const string &message,bool timer){//flg ��ʾ�Ƿ����ʱ�� 
	if(timer)
		printf("%03d:%02d %s\n",now/60,now%60,message.c_str());
	else
		printf("%s\n",message.c_str());
}