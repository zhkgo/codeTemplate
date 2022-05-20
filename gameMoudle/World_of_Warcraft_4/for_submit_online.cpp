#include<iostream>
#include<string>
#include<cstdio>
#include<list>
#include<map> 
#include<algorithm>
#include<typeinfo>
#include<vector>
#include<assert.h>
#include<set>
#define MESSAGE_LENGTH 300
using namespace std;

string armNames[3]={"sword","bomb","arrow"}; 
string names[5]={"dragon","ninja","iceman","lion","wolf"};
int HP[5];
int ACK[5];
class Headquarter;
class Warrior;
class City;

/*
2
2 10 10 1000
10 10 10 10 10
2 2 2 2 2

6 9 10 6000
120 20 30 10 20
150 50 20 50 150
*/
//全局日志 
class World{
public:
	int now;
	Headquarter *h1,*h2;
	vector<City> citys;
	int N,R;
	World():now(0){
	}
	void reset(Headquarter* _h1,Headquarter *_h2,int N,int R);
	void log(const string &message,bool timer=true){//flg 表示是否输出时间 
		if(timer)
			printf("%03d:%02d %s\n",now/60,now%60,message.c_str());
		else
			printf("%s\n",message.c_str());
	}
	bool addTime();
}mlog;

class Arm{
public:
	int arm_id;
	int ackp;//伤害占攻击的百分比
	int used;
	Arm(int arm_id=0,int ackp=20,int used=1000):arm_id(arm_id),ackp(ackp),used(used){
	}
//	static bool arm_cmp(Arm* a1,Arm* a2);//武器比较函数 
	//武器比较函数 
	static bool arm_cmp_use(Arm* a1,Arm* a2){
		if(a1->arm_id!=a2->arm_id)
			return a1->arm_id<a2->arm_id;
		if(a1->arm_id==2){
			return a1->used<a2->used;
		}
		return true;
	}
	static bool arm_cmp_get(Arm* a1,Arm* a2){
		if(a1->arm_id!=a2->arm_id)
			return a1->arm_id<a2->arm_id;
		if(a1->arm_id==2){
			return a1->used>a2->used;
		}
		return true;
	}
	static bool arm_cmp_report(Arm* a1,Arm* a2){
		return a1->arm_id>a2->arm_id;
	}
	virtual bool attack(Warrior* owner,Warrior* enemy,bool first);
	virtual bool isDestory(); 
	virtual string introduce();
	virtual ~Arm(){
	}
};
//剑 
class sword:public Arm{
public:
	int ack;
	sword(int ack=0):Arm(0,20,10000000),ack(ack){
	}
	bool attack(Warrior* owner,Warrior* enemy,bool first);
	bool isDestory();
	string introduce();
};
//炸弹 
class bomb:public Arm{
public:
	bomb():Arm(1,40,1){
	}
//	bool attack(Warrior* owner,Warrior* enemy);
};
//弓箭 
class arrow:public Arm{
public:
	int ack;
	arrow(int ack):Arm(2,30,3),ack(ack){
	}
	string introduce();
	virtual bool attack(Warrior* owner,Warrior* enemy,bool first=false);
};
class ArmFactory{
public:
	static Arm* product(int id,int swordAck=0){
		Arm* arm=nullptr; 
		switch(id){
			case 0:
				arm = static_cast<Arm*> (new sword(swordAck));
				break;
			case 1:
				arm = static_cast<Arm*> (new bomb());
				break;
			case 2:
				arm = static_cast<Arm*> (new arrow(mlog.R));
				break;
		}
		return arm;
	}
};

class City{
public:
	int c_id;
	int power;//生命元 
	int banner;//旗帜 banner 0 无旗帜 banner 1 红旗 banner 2 蓝旗 
	int winCnt;//胜利计数，如果达2 则红方占领 如果达-2则蓝方占领 
	list<Warrior*> red_warriors,blue_warriors;
	City(int c_id):c_id(c_id){
//		cout<<blue_warriors.size()<<endl; 
		power=0;
		banner=0;
		winCnt=0;
	}
	void addWarrior(Warrior* p);
	void removeWarrior(Warrior* p);
	list<Warrior*> battle(Warrior* w1,Warrior* w2);//战斗 w1先攻击  返回生还者 
	void judge();
	void wolfPlunder();//wolf 抢夺武器 
	void away(Warrior *p);
	void report(); 
	void warriorReport();
	void lionRun();
	void generatePower(); 
	void transPower();
	void useArrow();
	void useBomb();
	Warrior* getRedWarrior();
	Warrior* getBlueWarrior();
};
//武士类 
class Warrior{ 
public:
	static int MAX_ARMS;
	int id;//编号 
	string name;//名字 
	int health;//生命 
	int ack;//攻击力 
	list<Arm*> arms;//所有持有武器 
	int pos;
	string headq;
	int stopGo; 
	Warrior(int id=1,const string &name="warrior",int health=10,int ack=5,const string& headq="red",int num=1)
	:id(id),name(name),health(health),ack(ack),headq(headq){
		string message=headq+" "+name+" "+to_string(id)+" born";
		mlog.log(message);
		pos=0;
		stopGo=false;
	}
	void place(int x){//武士放置在x的位置 
		pos=x;
	}
	virtual bool goAhead(int dir);
	void prepare(){//武士准备战斗，武器排序 
		if(arms.size()==0){
			return;
		}
		arms.sort(Arm::arm_cmp_use);
	}
	bool isDead(){
		return health<=0;
	}
	bool hasArms(){
		return arms.size()!=0;
	}
	void getArmFrom(Warrior* enemy){
		enemy->arms.sort(Arm::arm_cmp_get);
		enemy->arms.remove_if([&](Arm *arm){
			if(arms.size()>=MAX_ARMS)return false;
			arms.push_back(arm);
			return true;
		});
	}
	string totName(){
		return headq+" "+name+" "+to_string(id);
	}
	bool noMoreChange(){//表示武士不会造成任何伤害，武器也不会变化了 
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
	void transpower(int power,bool log=false);
	void useArrow();
	void clearArms();
	void getPower();
	void getPower(int power);
	void report(){// 武士报告武器 
		clearArms(); 
		arms.sort(Arm::arm_cmp_report);
		string message=totName()+" has ";
		bool first=true; 
		for(Arm* p:arms){
			if(!first){
				message+=","+p->introduce(); 
			}else{
				message+=p->introduce();
				first=false;
			}
		}
		if(first){
			message+="no weapon";
		}
		mlog.log(message);
	}
	arrow* getArrow(){
		for(Arm* arm:arms){
			if(arm->arm_id==2){
				return dynamic_cast<arrow*>(arm);
			}
		}
		return nullptr;
	}
	bomb* getBomb();
	sword* getSword();
	virtual bool attack(Warrior* enemy,bool first=false);
	virtual bool beAttacked(int harm);
	virtual ~Warrior(){
		for(auto &p:arms){
			delete p;//删除每件武器 
		}
	}
};

class dragon:public Warrior{
public:
	double morale;//士气 
	dragon(int id=1,int health=10,int ack=5,double morale=1,const string& headq="red",int num=1)
	:Warrior(id,"dragon",health,ack,headq,num),morale(morale){
		arms.push_back(ArmFactory::product(id%3,ack/5));
		char message[MESSAGE_LENGTH];
		sprintf(message,"Its morale is %.2lf",morale);
		mlog.log(message,false);
	}
	void moraleUp(){
		morale+=0.2;
	}
	void moraleDown(){
		morale-=0.2;
	}
	void yelled(int c_id=1){
		if(morale<=0.8)return;
		char message[MESSAGE_LENGTH];
		sprintf(message,"%s yelled in city %d"
		,totName().c_str(),c_id);
		mlog.log(message);
	}
};
class ninja:public Warrior{
public:
	ninja(int id=1,int health=10,int ack=5,const string& headq="red",int num=1)
	:Warrior(id,"ninja",health,ack,headq,num){
		arms.push_back(ArmFactory::product(id%3,ack/5));
		arms.push_back(ArmFactory::product((id+1)%3,ack/5));
//		char message[100];
//		sprintf(message,"It has a %s and a %s",arms[leftArm].c_str(),arms[rightArm].c_str());
//		mlog.log(message,false);
	}
};

class iceman:public Warrior{
public:
	int steps;
	iceman(int id=1,int health=10,int ack=5,const string& headq="red",int num=1)
	:Warrior(id,"iceman",health,ack,headq,num){
		arms.push_back(ArmFactory::product(id%3,ack/5));
//		char message[100];
//		sprintf(message,"It has a %s",arms[arm].c_str());
//		mlog.log(message,false);
		steps=0;
	}
	virtual bool goAhead(int dir){//武士朝前走 
//		health -= health/10;
		bool res=Warrior::goAhead(dir);
		if(steps){
			if(health>9)health-=9;
			else health=1;
			ack+=20;//需要注意这里 生命值在无法减少时是否需要加攻击 
		}
		steps^=1;
		return res;
	}
};
class lion:public Warrior{
public:
	int loyalty;
	int lionk;
	lion(int id=1,int health=10,int ack=5,int loyalty=1,const string& headq="red",int num=1,int lionk=1)
	:Warrior(id,"lion",health,ack,headq,num),loyalty(loyalty),lionk(lionk){
		char message[MESSAGE_LENGTH];
		sprintf(message,"Its loyalty is %d",loyalty);
		mlog.log(message,false);
	}
	virtual bool goAhead(int dir){//武士朝前走 
		bool res=Warrior::goAhead(dir);
//		loyalty-=lionk;
		return res;
	}
	void loyalDown(){
		loyalty-=lionk;
	}
	void run(){
		mlog.log(totName()+" ran away");
//		if(pos>0&&pos<=mlog.citys.size())
//			mlog.citys[pos-1].removeWarrior(this);
	}
};

class wolf:public Warrior{
public:
	wolf(int id=1,int health=10,int ack=5,const string& headq="red",int num=1)
	:Warrior(id,"wolf",health,ack,headq,num){
	}
	void wolfgetArmFrom(Warrior* enemy,int c_id){
		if(enemy->arms.size()==0)
			return;
		bool hasArm[3]={0};
		for(Arm* arm:arms){
			hasArm[arm->arm_id]=true;
		}
		enemy->arms.remove_if([&](Arm *arm){
			if(hasArm[arm->arm_id])
				return false; 
			hasArm[arm->arm_id]=true; 
			arms.push_back(arm);
			return true;
		});
	}
};

//司令部 
class Headquarter{
private:
	int power;//生命元
	vector<int> order;//生产单位顺序 
	vector<int> count;//某单位的生产数量 
	int bound;//停止生成的能量边界 
	list<Warrior*> warriors; //已经生成的所有武士 
	int w_id;//生成武士的编号 
	int cur; //下一个生产武士的类型 
	int pos;//城市位置 
	int lionk;//lion每走一步下降 
	int dir;//武士走的方向 
	list<Warrior*> enemys; //已经到达总部的敌人 
	set<Warrior*> reported; //报告过的敌人 
public:
	string name;
	bool stop;
	Headquarter(vector<int>& order,const string &name="headquarter",int power=100,int pos=0,int lionk=1,int dir=-1)
	:name(name),power(power),order(order),w_id(1),count(order.size(),0),pos(pos),lionk(lionk),dir(dir){
		bound=1e9+7;
		stop=false;
		for(auto &p:order){
			bound=min(bound,HP[p]);
		}
		cur=0;
	}
	void enemysReach(Warrior* wa){
//		cout<<"========enemysReach========"<<endl;
		enemys.push_back(wa);
	}
	Warrior* born(int hero_id){//制造武士 
		if(power>=HP[hero_id]){
			power-=HP[hero_id];
			count[hero_id]+=1;
			Warrior* hero=nullptr;
			switch (hero_id){
				case 0:
					hero =static_cast<Warrior*>(new dragon(w_id++,HP[hero_id],ACK[hero_id],1.0*power/HP[hero_id],name,count[hero_id]));
					break;
				case 1:
					hero =static_cast<Warrior*>(new ninja(w_id++,HP[hero_id],ACK[hero_id],name,count[hero_id]));
					break;
				case 2:
					hero =static_cast<Warrior*>(new iceman(w_id++,HP[hero_id],ACK[hero_id],name,count[hero_id]));
					break;
				case 3:
					hero =static_cast<Warrior*>(new lion(w_id++,HP[hero_id],ACK[hero_id],power,name,count[hero_id],lionk));
					break;
				case 4:
					hero =static_cast<Warrior*>(new wolf(w_id++,HP[hero_id],ACK[hero_id],name,count[hero_id]));
					break;
			}
			hero->clearArms();
			return hero;
		}
		return nullptr;
	}
	void lionRunReport(){
		warriors.remove_if([&](Warrior* p){
			lion* lp=dynamic_cast<lion*>(p);
			if(lp!=nullptr && lp->loyalty<=0&&lp->pos==pos){
				lp->run();
				delete p;
				return true;
			}
			return false;
		});
	}
	void lionRun(){//lion 逃跑 
		warriors.remove_if([](Warrior* p){
			lion* lp=dynamic_cast<lion*>(p);
			if(lp!=nullptr && lp->loyalty<=0&&!lp->stopGo){
				delete p;
				return true;
			}
			return false;
		});
	}
	void clearDead(){
		warriors.remove_if([](Warrior* p){
			if(p->isDead()){
				delete p;
				return true;
			}
			return false;
		});
	}
	void goAhead(){//所有武士前进一步 
		for(auto &p:warriors){
			if(!p->stopGo)p->goAhead(dir);
		}
	}
	void report(){//报告基地情况 
		string message=to_string(power)+" elements in "+name+" headquarter";
		mlog.log(message);
	}
	void warriorReport(){//报告武士情况
		warriors.sort([](Warrior* a,Warrior* b){
			return a->pos < b->pos;	
		});
		for(auto &p:warriors){
			p->report();
		}
	}
	bool enemyReport(){
//		cout<<"here"<<stop<<endl;
		for(auto &p:enemys){
			if(reported.count(p))continue;
			reported.insert(p);
			char message[MESSAGE_LENGTH];
			sprintf(message,"%s reached %s headquarter with %d elements and force %d"
			,p->totName().c_str(),name.c_str(),p->health,p->ack);
			mlog.log(message);
		}
		if(enemys.size()>=2){
			mlog.log(name+" headquarter was taken");
			return true;
		}
		return false;
	}
	bool bornNext(){//孕育下一个武士 
		Warrior* war;
		war=born(order[cur]);
		if(war==nullptr){
			return false;
		}
		cur=(cur+1)%order.size();
		war->place(pos);
		warriors.push_back(war);
		return true;
	}
	~Headquarter(){
		for(auto &wa:warriors){
			delete wa;
		}
	}
	void getPower(int _power){
		power+=_power; 
	}
	bool tranpower(Warrior* w){
		if(power>=8){
			power-=8;
			w->health+=8;
			return true;
		}
		return false;
	}
};
/*
Warrior implements
*/
int Warrior::MAX_ARMS=10;
bool Warrior::beAttacked(int harm){
	this->health-=harm;
	return true;
}
bool Warrior::goAhead(int dir){//武士朝前走
	if(pos==0&&dir==-1){
		cout<<"ERROR GO AHEAD"<<endl;
		assert(false);
	}
	int N=mlog.citys.size();
	if(pos==N+1&&dir==1){
		cout<<"ERROR GO AHEAD"<<endl;
		assert(false);
		}
	if(pos>0&&pos<=N)
		mlog.citys[pos-1].removeWarrior(this);
	pos+=dir;
//	cout<<typeid(this).name()<<endl;
	if(pos>0&&pos<=N){
		mlog.citys[pos-1].addWarrior(this);
	}else if(pos==0){
		(mlog.h1)->enemysReach(this);
		stopGo=true;
	}else if(pos==N+1){
		(mlog.h2)->enemysReach(this);
		stopGo=true;
	}
	return true; 
}
void Warrior::transpower(int power,bool log){
	if(headq=="red"){
		(mlog.h1)->getPower(power);
	}else if(headq=="blue"){
		(mlog.h2)->getPower(power);
	}
	if(log){
		char message[MESSAGE_LENGTH]; 
		sprintf(message,"%s earned %d elements for his headquarter",
			totName().c_str(),power);
		mlog.log(message); 
	}
}
bomb* Warrior::getBomb(){
	for(Arm* arm:arms){
		if(arm->arm_id==1){
			return dynamic_cast<bomb*>(arm);
		}
	}
	return nullptr;
}
sword* Warrior::getSword(){
	for(Arm* arm:arms){
		if(arm->arm_id==0){
			return dynamic_cast<sword*>(arm);
		}
	}
	return nullptr;
}
void Warrior::useArrow(){
	int dir=1;
	if(headq=="blue")dir=-1;
	int nxt=pos+dir;
	if(nxt==mlog.N+1||nxt==0){
		return;
	}
	arrow *arm=getArrow(); 
	if(arm==nullptr)return; //没有弓箭则返回 
	Warrior* war=nullptr;
	if(headq=="blue"){
		war=mlog.citys[nxt-1].getRedWarrior();
	}else if(headq=="red"){
		war=mlog.citys[nxt-1].getBlueWarrior();
	}
	if(war==nullptr)return;//没有敌人则返回 
	arm->attack(this,war);
	char message[MESSAGE_LENGTH];
	if(war->isDead()){
		sprintf(message,"%s shot and killed %s",this->totName().c_str(),war->totName().c_str());
		 
	}else{
		sprintf(message,"%s shot",this->totName().c_str());
//		cout<<nxt<<endl;
	}
	mlog.log(message); 
	clearArms();//清理武器 
}
void Warrior::clearArms(){
	arms.remove_if([](Arm* arm){
		if(arm->isDestory()){
			delete arm;
			return true;
		}
		return false;
	});
}
void Warrior::getPower(){
	if(headq=="red"){
		(mlog.h1)->tranpower(this);
	}else{
		(mlog.h2)->tranpower(this);
	}
}
bool Warrior::attack(Warrior* enemy,bool first){
	//武器如果是剑 
	sword* arm=getSword(); 
	bool tmpArm=false;
	if(arm==nullptr){
		tmpArm=true;
		arm=new sword(0);
	}
	arm->attack(this,enemy,first);
	this->clearArms();
	if(tmpArm){
		delete arm;
	}
	return true;
}
void Warrior::getPower(int power){
	if(power<=0)return;
	health+=power;
}
/*
arm implements
*/


bool Arm::attack(Warrior* owner,Warrior* enemy,bool first){
	int harm=owner->ack*ackp/100;
	if(this->arm_id!=0)
		--this->used;
	enemy->beAttacked(harm);
	if(this->arm_id==1&&owner->name!="ninja"){
		owner->beAttacked(harm/2);
	}
	return true;
}
bool Arm::isDestory(){
	return this->used==0;
} 
bool sword::isDestory(){
	return this->ack==0;
}
string Arm::introduce(){
	return armNames[arm_id];
}
string arrow::introduce(){
	return Arm::introduce()+"("+to_string(used)+")";
}
string sword::introduce(){
	return Arm::introduce()+"("+to_string(ack)+")";
}

bool sword::attack(Warrior* owner,Warrior* enemy,bool first){
	char message[MESSAGE_LENGTH];
	if(first){
		sprintf(message,"%s attacked %s in city %d with %d elements and force %d",
		owner->totName().c_str(),enemy->totName().c_str(),owner->pos,owner->health,owner->ack);
	}else{
		sprintf(message,"%s fought back against %s in city %d",
		owner->totName().c_str(),enemy->totName().c_str(),owner->pos);
	}
	mlog.log(message);
	int harm=owner->ack+this->ack;
	if(!first){
		harm=owner->ack/2+this->ack;
	}
	//dosome 
	this->ack *= 4;
	this->ack /= 5;
	enemy->beAttacked(harm);
	return true;
}
bool arrow::attack(Warrior* owner,Warrior* enemy,bool first){
	enemy->beAttacked(ack); 
	--this->used;
	return true;
}
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
//		cout<<blue_warriors.size()<<endl;
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
	if(w1->isDead()&&w2->isDead())return {};
	int hal1=w1->health,hal2=w2->health;
	w1->prepare();
	w2->prepare();
//	if(mlog.now/60==3){
//		printf("here");
//	}
	bool hasAck=false;
	if(!w1->isDead()&&!w2->isDead()){
		hasAck=true;
		w1->attack(w2,true);
		if(!w2->isDead()&&w2->name!="ninja"){
			w2->attack(w1,false);
		}
	}
	char message[MESSAGE_LENGTH];
	//死亡判断 
	if(hasAck&&w1->isDead()&&!w2->isDead()){
		sprintf(message,"%s was killed in city %d"
		,(w1->totName()).c_str(),c_id);
		mlog.log(message);

	}else if(hasAck&&!w1->isDead()&&w2->isDead()){
		sprintf(message,"%s was killed in city %d"
		,(w2->totName()).c_str(),c_id);
		mlog.log(message);
	}
	
	//处理dragon 
	dragon* dra1=dynamic_cast<dragon*>(w1);
	dragon* dra2=dynamic_cast<dragon*>(w2);
	//dragon士气变化 
	if(dra1!=nullptr&&!dra1->isDead()){
		if(w2->isDead()){
			dra1->moraleUp();
		}else{
			dra1->moraleDown();
		}
	}
	if(dra2!=nullptr&&!dra2->isDead()){
		if(w1->isDead()){
			dra2->moraleUp();
		}else{
			dra2->moraleDown();
		}
	}
	//dragon欢呼 
	if(!w1->isDead()&& dra1!=nullptr){
		dra1->yelled(c_id); 
	}
	// lion 降低忠诚
	lion *ln1=dynamic_cast<lion*>(w1),*ln2=dynamic_cast<lion*>(w2);
	if(ln1!=nullptr && !ln1->isDead()){
		if(!w2->isDead()){
			ln1->loyalDown();
		}
	}
	if(ln2!=nullptr && !ln2->isDead()){
		if(!w1->isDead()){
			ln2->loyalDown();
		}
	}
	//奖励武士 -> 生命元传递 ->  缴获武器
	wolf* wf=nullptr;
	if(w1->isDead()&&!w2->isDead()){ 
		//wolfgetArmFrom
		w2->getPower();
		w2->transpower(power,true);
		power=0;
		wf = dynamic_cast<wolf*>(w2);
		if(wf){
			wf->wolfgetArmFrom(w1,c_id); 
		} 
		if(ln1){//lion战死 
			w2->getPower(hal1);
		} 
	}else if(!w1->isDead()&&w2->isDead()){
		w1->getPower();
		w1->transpower(power,true);
		power=0;
		wf = dynamic_cast<wolf*>(w1);
		if(wf){
			wf->wolfgetArmFrom(w2,c_id);
		}
		if(ln2){//lion战死 
			w1->getPower(hal2);
		} 
	}
	list<Warrior*> ans;
	if(!w1->isDead())ans.push_back(w1);
	if(!w2->isDead())ans.push_back(w2);
	return ans;
}
void City::judge(){
	if(red_warriors.size()==0||blue_warriors.size()==0){
		red_warriors.remove_if([](Warrior* war){
			return war->isDead();
		});
		blue_warriors.remove_if([](Warrior* war){
			return war->isDead();
		});
		return;
	}
	list<Warrior*> res;
	if(banner==1||(banner==0&&c_id%2==1)){
		res=battle(red_warriors.front(),blue_warriors.front());
		blue_warriors.pop_front();
		red_warriors.pop_front();
	}else{
		res=battle(blue_warriors.front(),red_warriors.front());
		blue_warriors.pop_front();
		red_warriors.pop_front();
	}
	if(res.size()==2){
		winCnt=0;
	}else if(res.size()==1){
		Warrior* wa=res.front();
		if(wa->headq == "red"){
			if(winCnt>=0)winCnt++;
			else winCnt=1;
			if(winCnt==2&&banner!=1){
				banner=1;
				mlog.log("red flag raised in city "+to_string(c_id)); 
			}
		}else{
			if(winCnt<0)winCnt--;
			else winCnt=-1;
			if(winCnt==-2&&banner!=2){
				banner=2;
				mlog.log("blue flag raised in city "+to_string(c_id));  
			}
		}
	}
	for(Warrior* wa:res){
		addWarrior(wa);
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

void City::generatePower(){
	power+=10;
} 
void City::transPower(){
	int tot=red_warriors.size()+blue_warriors.size();
	if(tot==1){
		Warrior* war=nullptr;
		if(red_warriors.size()==1){
			war=red_warriors.front();
		}else{
			war=blue_warriors.front();
		}
		war->transpower(power,true);
		power=0;
	}
}
void City::useArrow(){
	for(auto &p:red_warriors){
		p->useArrow();
	}
	for(auto &p:blue_warriors){
		p->useArrow();
	}
}
void City::useBomb(){
	if(red_warriors.empty()||blue_warriors.empty()){
		return;
	}
	Warrior* w1=red_warriors.front(),*w2=blue_warriors.front();
	if(w1->isDead() || w2->isDead())
		return;
	bomb* b1=w1->getBomb(),*b2=w2->getBomb();
	if(b1 == nullptr && b2 == nullptr)
		return;
	sword *s1=w1->getSword(),*s2=w2->getSword();
	sword ts1(0),ts2(0);//临时武器
	if(s1==nullptr)s1=&ts1; 
	if(s2==nullptr)s2=&ts2;
	int winner=-1;
	if(banner==1||(banner==0&&c_id%2==1)){
		int harm=w1->ack+s1->ack;
		if(w2->health<=harm){
			winner=1;
		}else if(w2->name!="ninja"){
			harm=w2->ack/2+s2->ack;
			if(w1->health<=harm){
				winner=2;
			}
		}
	}else{
		int harm=w2->ack+s2->ack;
		if(w1->health<=harm){
			winner=2;
		}else if(w1->name!="ninja"){
			harm=w1->ack/2+s1->ack;
			if(w2->health<=harm){
				winner=1;
			}
		}
	}
	char message[MESSAGE_LENGTH];
	if(winner==1&&b2!=nullptr){
		sprintf(message,"%s used a bomb and killed %s",w2->totName().c_str(),w1->totName().c_str());	
	}else if(winner==2&&b1!=nullptr){
		sprintf(message,"%s used a bomb and killed %s",w1->totName().c_str(),w2->totName().c_str());	
	}
	if((winner==1&&b2!=nullptr)||(winner==2&&b1!=nullptr)){
		w1->health=w2->health=0;
		mlog.log(message);
	}
}
Warrior* City::getRedWarrior(){
	if(red_warriors.empty())
		return nullptr;
	return red_warriors.front();
}

Warrior* City::getBlueWarrior(){
	if(blue_warriors.empty())
		return nullptr;
	return blue_warriors.front();
}
/*
World implement
*/
void World::reset(Headquarter* _h1,Headquarter *_h2,int N,int R){
	h1=_h1;
	h2=_h2;
	citys.clear();
	this->N=N;
	this->R=R;
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
		h1->lionRunReport();
		for(int i=0;i<citys.size();i++){
			citys[i].lionRun();
		}
		h2->lionRunReport();
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
	}else if(c==20){
		for(int i=0;i<citys.size();i++){
			citys[i].generatePower();
		}
	}else if(c==30){
		for(int i=0;i<citys.size();i++){
			citys[i].transPower();
		}
	}else if(c==35){
		for(int i=0;i<citys.size();i++){
			citys[i].useArrow();
		}
	}else if(c==38){
		for(int i=0;i<citys.size();i++){
			citys[i].useBomb();
		} 
	}else if(c==40){
		//battle
		for(int i=0;i<citys.size();i++){
			citys[i].judge();
		}
		h1->clearDead();
		h2->clearDead();
	}else if(c==50){
		h1->report();
		h2->report();
	}else if(c==55){
		h1->warriorReport();
		h2->warriorReport();
		//battle
	}
	++now;
	return false;
}

/*
2
200 4 5 1000
24 50 30 190 4
89 7 23 67 4

*/
int main(){
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);

	int T;
	cin>>T;
	for(int cs=1;cs<=T;cs++){
		int M,N,K,R,TIME;
		cin>>M>>N>>R>>K>>TIME;
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
		mlog.reset(&h1,&h2,N,R);
		TIME++;
		while(TIME--){
			if(mlog.addTime())
				break;
		}
//		break;
	}
	return 0;
}
