#include "warriors.h"
#include "city.h"
#include "world.h"
#include "headquater.h"

const string names[5]={"dragon","ninja","iceman","lion","wolf"};

/*
Warrior implements
*/
int Warrior::MAX_ARMS=10;
bool Warrior::beAttacked(int harm){
	this->health-=harm;
	return true;
}
void Warrior::prepare(){
	if(arms.size()==0){
		curArm = arms.end();
		return;
	}
	arms.sort(Arm::arm_cmp_use);
	curArm = arms.begin();
}
void Warrior::getArmFrom(Warrior* enemy){
	enemy->arms.sort(Arm::arm_cmp_get);
	enemy->arms.remove_if([&](Arm *arm){
		if(arms.size()>=MAX_ARMS)return false;
		arms.push_back(arm);
		return true;
	});
}
bool Warrior::goAhead(int dir){
	int N=mlog.citys.size();
	if(pos>0&&pos<=N)
		mlog.citys[pos-1].removeWarrior(this);
	pos+=dir;
	if(pos>0&&pos<=N){
		mlog.citys[pos-1].addWarrior(this);
	}else if(pos==0){
		(mlog.h1)->enemysReach(this);
	}else if(pos==N+1){
		(mlog.h2)->enemysReach(this);
	}
	return true; 
}
void wolf::wolfgetArmFrom(Warrior* enemy,int c_id){
	if(enemy->arms.size()==0)
		return;
	enemy->arms.sort(Arm::arm_cmp_get);
	int arm_id=(*(enemy->arms).begin())->arm_id,num=0;
	enemy->arms.remove_if([&](Arm *arm){
		if(arm_id<arm->arm_id)return false;
		if(arms.size()>=MAX_ARMS)return false; 
		++num;
		arms.push_back(arm);
		return true;
	});
	if(num>0){
		char message[MESSAGE_LENGTH];
		sprintf(message,"%s took %d %s from %s in city %d"
		,totName().c_str(),num,armNames[arm_id].c_str(),enemy->totName().c_str(),c_id);
		mlog.log(message);
	}
}
void lion::run(){
	mlog.log(totName()+" ran away");
}
bool lion::goAhead(int dir){
	bool res=Warrior::goAhead(dir);
	loyalty-=lionk;
	return res;
}
lion::lion(int id=1,int health=10,int ack=5,int loyalty=1,const string& headq="red",int num=1,int lionk=1)
:Warrior(id,"lion",health,ack,headq,num),loyalty(loyalty),lionk(lionk){
	char message[MESSAGE_LENGTH];
	sprintf(message,"Its loyalty is %d",loyalty);
	mlog.log(message,false);
	arms.push_back(ArmFactory::product(id%3));
}
void dragon::yelled(int c_id=1){
	char message[MESSAGE_LENGTH];
	sprintf(message,"%s yelled in city %d"
	,totName().c_str(),c_id);
	mlog.log(message);
}
dragon::dragon(int id=1,int health=10,int ack=5,double morale=1,const string& headq="red",int num=1)
:Warrior(id,"dragon",health,ack,headq,num),morale(morale){
	arms.push_back(ArmFactory::product(id%3));
}
void Warrior::report(){
	vector<int> cnt(3,0);
	for(Arm* p:arms){
		cnt[p->arm_id]++;
	}
	char message[MESSAGE_LENGTH];
	sprintf(message,"%s %s %d has %d sword %d bomb %d arrow and %d elements"
	,headq.c_str(),name.c_str(),id,cnt[0],cnt[1],cnt[2],health);
	mlog.log(message);
}
Warrior::Warrior(int id=1,const string &name="warrior",int health=10,int ack=5,const string& headq="red",int num=1)
:id(id),name(name),health(health),ack(ack),headq(headq),curArm(nullptr){
	string message=headq+" "+name+" "+to_string(id)+" born";
	mlog.log(message);
	pos=0;
}

bool Warrior::attack(Warrior* enemy){
	if(curArm==arms.end())return false;
	Arm* arm=*curArm;
	arm->attack(this,enemy);
	++curArm;
	if(arm->used==0){
		delete arm;
		arms.remove(arm);
	}
	if(curArm==arms.end()){
		curArm=arms.begin();
	}
	return true;
}
bool Warrior::noMoreChange(){
	if(!hasArms()){
		return true;
	}
	vector<int> cnt(3,0);
	for(Arm* p:arms){
		cnt[p->arm_id]++;
	}
	sword swd;
	if(cnt[1]==0&&cnt[2]==0&&ack*swd.ackp/100==0){
		return true;
	}
	return false;
}