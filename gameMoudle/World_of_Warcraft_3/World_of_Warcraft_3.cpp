#include<iostream>
#include<string>
#include<cstdio>
#include<list>
#include<map> 
#include<algorithm>
#define MESSAGE_LENGTH 300
using namespace std;

string arms[3]={"sword","bomb","arrow"}; 
string names[5]={"dragon","ninja","iceman","lion","wolf"};
int HP[5];
int ACK[5];
class Headquarter;
//ȫ����־ 
class World{
private:
	int now;
	Headquarter *h1,*h2;
public:
	World():now(0){
	}
	void reset(Headquarter* _h1,Headquarter *_h2){
		h1=_h1;
		h2=_h2;
		now=0;
	}
	void log(const string &message,bool timer=true){//flg ��ʾ�Ƿ����ʱ�� 
		if(timer)
			printf("%03d:%02d %s\n",now/60,now%60,message.c_str());
		else
			printf("%s\n",message.c_str());
	}
	void addTime();
//	{

//	}
}mlog;

class Warrior;
class Arm{
public:
	int arm_id;
	int ackp;//�˺�ռ�����İٷֱ�
	int used;
	Arm(int arm_id=0,int ackp=20,int used=1000):arm_id(arm_id),ackp(ackp),used(used){
	}
//	static bool arm_cmp(Arm* a1,Arm* a2);//�����ȽϺ��� 
	//�����ȽϺ��� 
	static bool arm_cmp(Arm* a1,Arm* a2){
		if(a1->arm_id!=a2->arm_id)
			return a1->arm_id<a2->arm_id;
		if(a1->arm_id==2){
			return a1->used<a2->used;
		}
		return true;
	}
	virtual ~Arm(){
	}
};
//�� 
class sword:public Arm{
public:
	sword():Arm(0,20,10000000){
	}
	bool attack(Warrior* enemy);
};
//ը�� 
class bomb:public Arm{
public:
	bomb():Arm(1,40,1){
	}
	bool attack(Warrior* owner,Warrior* enemy);
};
//���� 
class arrow:public Arm{
public:
	arrow():Arm(2,30,2){
	}
	bool attack(Warrior* enemy);
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


//��ʿ�� 
class Warrior{ 
public:
	int id;//��� 
	string name;//���� 
	int health;//���� 
	int ack;//������ 
	list<Arm*> arms;
	int pos;
	string headq;
	Warrior(int id=1,const string &name="warrior",int health=10,int ack=5,const string& headq="red",int num=1)
	:id(id),name(name),health(health),ack(ack),headq(headq){
		string message=headq+" "+name+" "+to_string(id)+" born";
		mlog.log(message);
		pos=0;
	}
	void place(int x){//��ʿ������x��λ�� 
		pos=x;
	}
	virtual void goAhead(int dir){//��ʿ��ǰ�� 
		pos+=dir;
		mlog.log(headq+" "+name+" "+to_string(id)+"city "+to_string(pos)+" with "+to_string(health)
		+" elements and force "+to_string(ack));
	}
	void prepare(){//��ʿ׼��ս������������ 
		arms.sort(Arm::arm_cmp);
	}
	void report(){// 
		vector<int> cnt(3,0);
		for(Arm* p:arms){
			cnt[p->arm_id]++;
		}
		char message[MESSAGE_LENGTH];
		sprintf(message,"%s %s %d has %d sword %d bomb %d arrow and %d elements"
		,headq.c_str(),name.c_str(),id,cnt[0],cnt[1],cnt[2],health);
		mlog.log(message);
	}
	virtual ~Warrior(){
		for(auto &p:arms){
			delete p;//ɾ��ÿ������ 
		}
	} 
};

class dragon:public Warrior{
public:
	double morale;//ʿ�� 
	dragon(int id=1,int health=10,int ack=5,double morale=1,const string& headq="red",int num=1)
	:Warrior(id,"dragon",health,ack,headq,num),morale(morale){
		arms.push_back(ArmFactory::product(id%3));
//		char message[100];
//		sprintf(message,"It has a %s,and it's morale is %.2lf",arms[arm].c_str(),morale);
//		mlog.log(message,false);
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
	virtual void goAhead(int dir){//��ʿ��ǰ�� 
		Warrior::goAhead(dir);
		loyalty-=lionk;
	}
	void run(){
		mlog.log(headq+" lion "+to_string(id)+" ran away");
	}
};

class wolf:public Warrior{
public:
	wolf(int id=1,int health=10,int ack=5,const string& headq="red",int num=1)
	:Warrior(id,"wolf",health,ack,headq,num){
	}
};


void battle(Warrior* w1,Warrior* w2){//w1�ȷ������� 
	w1->prepare();
	w2->prepare();
} 
//˾� 
class Headquarter{
private:
	int power;//����Ԫ
	vector<int> order;//������λ˳�� 
	vector<int> count;//ĳ��λ���������� 
	int bound;//ֹͣ���ɵ������߽� 
	list<Warrior*> warriors; //�Ѿ����ɵ�������ʿ 
	int w_id;//������ʿ�ı�� 
	int cur; //��һ��������ʿ������ 
	int pos;//����λ�� 
	int lionk;//lionÿ��һ���½� 
	int dir;//��ʿ�ߵķ��� 
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
	Warrior* born(int hero_id){//������ʿ 
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
	void lionRun(){//lion ���� 
		warriors.remove_if([](Warrior* p){
			lion* lp=dynamic_cast<lion*>(p);
			if(lp!=nullptr && lp->loyalty<=0){
				lp->run();//lion run 
				delete p;
				return true;
			}
			return false;
		});
	}
	void goAhead(){//������ʿǰ��һ�� 
		for(auto &p:warriors){
			p->goAhead(dir);
		}
	}
	void report(){//���������� 
		string message=to_string(power)+" elements in "+name+" headquarter";
		mlog.log(message);
	}
	void warriorReport(){//������ʿ��� 
		for(auto &p:warriors){
			p->report();
		}
	}
	bool bornNext(){//������һ����ʿ 
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

void World::addTime(){
	int c=now%60;
	if(c==0){
		h1->bornNext();
		h2->bornNext();
	}else if(c==5){
		h1->lionRun();
		h2->lionRun();
	}else if(c==10){
		h1->goAhead();
		h2->goAhead();
	}else if(c==35){
//		h1->wolfPlunder();
//		h2->wolfPlunder();
	}else if(c==40){
		//battle
	}else if(c==50){
		h1->report();
		h2->report();
	}else if(c==55){
		h1->warriorReport();
		h2->warriorReport();
	}
	++now;
}
int main(){
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
		cout<<"Case:"<<cs<<endl;
		
		vector<int> o1={2,3,4,1,0};
		vector<int> o2={3,0,1,2,4};
		Headquarter h1(o1,"red",M,0,K,1);
		Headquarter h2(o2,"blue",M,N+1,K,-1);
		mlog.reset(&h1,&h2);
		while(TIME--){
			mlog.addTime();
		}
	}
	return 0;
}
