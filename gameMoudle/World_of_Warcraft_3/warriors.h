#ifndef WARRIORS_H
#define WARRIORS_H

#include "world.h" 
#include "arm.h" 
extern const string names[5];
//武士类
class Warrior{ 
public:
	static int MAX_ARMS;//武士最多持有武器数量
	int id;//武士编号
	string name;//武士类型 
	int health;//武士生命值
	int ack;//武士攻击力
	list<Arm*> arms;//武士持有的武器
	int pos;//武士所在位置
	string headq;//所属司令部
	decltype(arms.begin()) curArm;//武士下一个要使用的武器 
	Warrior(int id,const string &name,int health,int ack,const string& headq,int num);
	void place(int x){//放置武士
		pos=x;
	}
	virtual bool goAhead(int dir);//前进
	void prepare();//准备战斗
	bool isDead(){//是否死亡
		return health<=0;
	}
	bool hasArms(){//是否拥有武器
		return arms.size()!=0;
	}
	void getArmFrom(Warrior* enemy);//从死亡的敌人那边抢夺武器
	string totName(){//武士全名 总部+自身类别+编号
		return headq+" "+name+" "+to_string(id);
	}
	bool noMoreChange();//表示武士不会再造成任何伤害，并且武器状态不会变化
	void report();//武士报告自身武器持有情况
	virtual bool attack(Warrior* enemy);//武士攻击敌人
	virtual bool beAttacked(int harm);//武士受到伤害
	virtual ~Warrior(){
		for(auto &p:arms){
			delete p;
		}
	}
};

class dragon:public Warrior{
public:
	double morale;//士气
	dragon(int id,int health,int ack,double morale,const string& headq,int num);
	void yelled(int c_id);//武士欢呼
};
class ninja:public Warrior{
public:
	ninja(int id=1,int health=10,int ack=5,const string& headq="red",int num=1)
	:Warrior(id,"ninja",health,ack,headq,num){
		arms.push_back(ArmFactory::product(id%3));
		arms.push_back(ArmFactory::product((id+1)%3));
	}
};

class iceman:public Warrior{
public:
	iceman(int id=1,int health=10,int ack=5,const string& headq="red",int num=1)
	:Warrior(id,"iceman",health,ack,headq,num){
		arms.push_back(ArmFactory::product(id%3));
	}
	virtual bool goAhead(int dir){//iceman前进 减少生命值
		health -= health/10;
		return Warrior::goAhead(dir);
	}
};
class lion:public Warrior{
public:
	int loyalty;
	int lionk;
	lion(int id,int health,int ack,int loyalty,const string& headq,int num,int lionk);
	virtual bool goAhead(int dir);//lion前进 减少忠诚度
	void run();
};

class wolf:public Warrior{
public:
	wolf(int id,int health,int ack,const string& headq,int num)
	:Warrior(id,"wolf",health,ack,headq,num){
	}
	void wolfgetArmFrom(Warrior* enemy,int c_id);//wolf在某城市抢夺武器
};
#endif
