#include "city.h"
#include "arm.h"
#include "world.h"
/*
city implements 
*/
void City::warriorReport(){
	for(auto &p:red_warriors){
		p->report();
	}
	for(auto &p:blue_warriors){
		p->report();
	}
} 
void City::addWarrior(Warrior* p){
	if(p->headq=="red"){
		red_warriors.push_back(p);
	}else{
		blue_warriors.push_back(p);
	}
}
void City::report(){
	char message[MESSAGE_LENGTH];
	for(auto &p:red_warriors){
		sprintf(message,"%s marched to city %d with %d elements and force %d"
		,(p->totName()).c_str(),c_id,p->health,p->ack);
		mlog.log(message);
	}
	for(auto &p:blue_warriors){
		sprintf(message,"%s marched to city %d with %d elements and force %d"
		,(p->totName()).c_str(),c_id,p->health,p->ack);
		mlog.log(message);
	}
}
void City::removeWarrior(Warrior* p){
	if(p->headq=="red"){
		red_warriors.remove(p);
	}else{
		blue_warriors.remove(p);
	}
}
void City::lionRun(){
	red_warriors.remove_if([](Warrior* p){
		lion* lp=dynamic_cast<lion*>(p);
		if(lp!=nullptr && lp->loyalty<=0){
			lp->run();//lion run 
			return true;
		}
		return false;
	});
	blue_warriors.remove_if([](Warrior* p){
		lion* lp=dynamic_cast<lion*>(p);
		if(lp!=nullptr && lp->loyalty<=0){
			lp->run();//lion run 
			return true;
		}
		return false;
	});
}
list<Warrior*> City::battle(Warrior* w1,Warrior* w2){
	w1->prepare();
	w2->prepare();
	while(true){
		if(!w1->isDead()){
			w1->attack(w2);
		}else{
			break;
		}
		if(!w2->isDead()){
			w2->attack(w1);
		}else{
			break;
		}
		if(w1->noMoreChange()&&w2->noMoreChange()){
			break;
		}
	}
	char message[MESSAGE_LENGTH];
	//����������ʿʹ�ú���ʿ��ǰ
	if(c_id%2==0){
		swap(w1,w2);
	}
	list<Warrior*> ans;
	if(!w1->isDead())ans.push_back(w1);
	if(!w2->isDead())ans.push_back(w2);
	if(!w1->isDead()&&!w2->isDead()){
		sprintf(message,"both %s and %s were alive in city %d"
		,(w1->totName()).c_str(),(w2->totName()).c_str(),c_id);
	}else if(w1->isDead()&&!w2->isDead()){
		sprintf(message,"%s killed %s in city %d remaining %d elements"
		,(w2->totName()).c_str(),(w1->totName()).c_str(),c_id,w2->health);
		w2->getArmFrom(w1);
	}else if(!w1->isDead()&&w2->isDead()){
		sprintf(message,"%s killed %s in city %d remaining %d elements"
		,(w1->totName()).c_str(),(w2->totName()).c_str(),c_id,w1->health);
		w1->getArmFrom(w2);
	}else{
		sprintf(message,"both %s and %s died in city %d"
		,(w1->totName()).c_str(),(w2->totName()).c_str(),c_id);
	}
	mlog.log(message);
	return ans;
}
void City::judge(){
	if(red_warriors.size()==0||blue_warriors.size()==0){
		return;
	}
	dragon* dra=nullptr;
	list<Warrior*> res;
	if(c_id%2==1){
		res=battle(*red_warriors.begin(),*blue_warriors.begin());
		blue_warriors.pop_front();
		red_warriors.pop_front();
	}else{
		res=battle(*blue_warriors.begin(),*red_warriors.begin());
		blue_warriors.pop_front();
		red_warriors.pop_front();
	}
	for(auto &p:res){
		if(dra=dynamic_cast<dragon*>(p)){
			dra->yelled(c_id);
		}
		addWarrior(p);
	}
}
void City::wolfPlunder(){
	if(red_warriors.size()==0||blue_warriors.size()==0){
		return;
	}
	Warrior *w1=nullptr,*w2=nullptr;
	w1=*(red_warriors.begin());
	w2=*(blue_warriors.begin());
	wolf *l1=nullptr,*l2=nullptr;
	l1=dynamic_cast<wolf*>(w1);
	l2=dynamic_cast<wolf*>(w2);
	if(l1==nullptr&&l2!=nullptr){
		l2->wolfgetArmFrom(w1,c_id);
	}else if(l2==nullptr&&l1!=nullptr){
		l1->wolfgetArmFrom(w2,c_id);
	}
}

