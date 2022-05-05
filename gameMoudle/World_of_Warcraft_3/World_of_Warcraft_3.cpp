#include<iostream>
#include<string>
#include<cstdio>
#include<list>
#include<map> 
#include<algorithm>
//#include<typeinfo>
#include<vector>
#include<assert.h>
#define MESSAGE_LENGTH 300
using namespace std;

string armNames[3]={"sword","bomb","arrow"}; 
string names[5]={"dragon","ninja","iceman","lion","wolf"};
int HP[5];
int ACK[5];
class Headquarter;
class Warrior;
class City;

//全局日志 
class World{
public:
	int now;
	Headquarter *h1,*h2;
	vector<City> citys;
	World():now(0){
	}
	void reset(Headquarter* _h1,Headquarter *_h2,int N);
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
	virtual bool attack(Warrior* owner,Warrior* enemy);
	virtual ~Arm(){
	}
};
//剑 
class sword:public Arm{
public:
	sword():Arm(0,20,10000000){
	}
//	bool attack(Warrior* owner,Warrior* enemy);
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
	arrow():Arm(2,30,2){
	}
//	bool attack(Warrior* owner,Warrior* enemy);
};
class ArmFactory{
public:
	static Arm* product(int id){
		Arm* arm=nullptr;
		switch(id){
			case 0:
				arm = static_cast<Arm*> (new sword());
				break;
			case 1:
				arm = static_cast<Arm*> (new bomb());
				break;
			case 2:
				arm = static_cast<Arm*> (new arrow());
				break;
		}
		return arm;
	}
};

class City{
public:
	int c_id;
	list<Warrior*> red_warriors,blue_warriors;
	City(int c_id):c_id(c_id){
//		cout<<blue_warriors.size()<<endl; 
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
	decltype(arms.begin()) curArm;//当前使用武器 
	Warrior(int id=1,const string &name="warrior",int health=10,int ack=5,const string& headq="red",int num=1)
	:id(id),name(name),health(health),ack(ack),headq(headq),curArm(nullptr){
		string message=headq+" "+name+" "+to_string(id)+" born";
		mlog.log(message);
		pos=0;
	}
	void place(int x){//武士放置在x的位置 
		pos=x;
	}
	virtual bool goAhead(int dir);
	void prepare(){//武士准备战斗，武器排序 
		if(arms.size()==0){
			curArm = arms.end();
			return;
		}
		arms.sort(Arm::arm_cmp_use);
		curArm = arms.begin();
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
	void report(){// 武士报告武器 
		vector<int> cnt(3,0);
		for(Arm* p:arms){
			cnt[p->arm_id]++;
		}
		char message[MESSAGE_LENGTH];
		sprintf(message,"%s %s %d has %d sword %d bomb %d arrow and %d elements"
		,headq.c_str(),name.c_str(),id,cnt[0],cnt[1],cnt[2],health);
		mlog.log(message);
	}
	virtual bool attack(Warrior* enemy){
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
		arms.push_back(ArmFactory::product(id%3));
//		char message[100];
//		sprintf(message,"It has a %s,and it's morale is %.2lf",arms[arm].c_str(),morale);
//		mlog.log(message,false);
	}
	void yelled(int c_id=1){
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
		arms.push_back(ArmFactory::product(id%3));
		arms.push_back(ArmFactory::product((id+1)%3));
//		char message[100];
//		sprintf(message,"It has a %s and a %s",arms[leftArm].c_str(),arms[rightArm].c_str());
//		mlog.log(message,false);
	}
};

class iceman:public Warrior{
public:
	iceman(int id=1,int health=10,int ack=5,const string& headq="red",int num=1)
	:Warrior(id,"iceman",health,ack,headq,num){
		arms.push_back(ArmFactory::product(id%3));
//		char message[100];
//		sprintf(message,"It has a %s",arms[arm].c_str());
//		mlog.log(message,false);
	}
	virtual bool goAhead(int dir){//武士朝前走 
		health -= health/10;
		Warrior::goAhead(dir);
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
		arms.push_back(ArmFactory::product(id%3));
	}
	virtual bool goAhead(int dir){//武士朝前走 
		bool res=Warrior::goAhead(dir);
		loyalty-=lionk;
		return res;
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
			return hero;
		}
		return nullptr;
	}
	void lionRun(){//lion 逃跑 
		warriors.remove_if([](Warrior* p){
			lion* lp=dynamic_cast<lion*>(p);
			if(lp!=nullptr && lp->loyalty<=0){
//				lp->run();//lion run 
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
			p->goAhead(dir);
		}
	}
	void report(){//报告基地情况 
		string message=to_string(power)+" elements in "+name+" headquarter";
		mlog.log(message);
	}
	void warriorReport(){//报告武士情况 
		for(auto &p:warriors){
			p->report();
		}
	}
	bool enemyReport(){
//		cout<<"here"<<stop<<endl;
		for(auto &p:enemys){
			char message[MESSAGE_LENGTH];
			sprintf(message,"%s reached %s headquarter with %d elements and force %d"
			,p->totName().c_str(),name.c_str(),p->health,p->ack);
			mlog.log(message);
		}
		if(enemys.size()!=0){
			mlog.log(name+" headquarter was taken");
			return true;
		}
		return false;
	}
	bool bornNext(){//孕育下一个武士 
		if(stop){
//			mlog.log(name+" headquarter stops making warriors");
//			stop=true;
			return false;
		}
		Warrior* war;
		war=born(order[cur]);
		cur=(cur+1)%order.size();
		if(war==nullptr){
			stop=true;
			return false;
		}
		war->place(pos);
		warriors.push_back(war);
		return true;
	}
	~Headquarter(){
		for(auto &wa:warriors){
			delete wa;
		}
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
	}else if(pos==N+1){
		(mlog.h2)->enemysReach(this);
	}
	return true; 
}
/*
arm implements
*/
bool Arm::attack(Warrior* owner,Warrior* enemy){
	int harm=owner->ack*ackp/100;
	if(this->arm_id!=0)
		--this->used;
	enemy->beAttacked(harm);
	if(this->arm_id==1&&owner->name!="ninja"){
		owner->beAttacked(harm/2);
	}
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
	//交换两个武士使得红武士在前
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


int main(){
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);

	int T;
	cin>>T;
	for(int cs=1;cs<=T;cs++){
		int M,health,N,K,TIME;
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
