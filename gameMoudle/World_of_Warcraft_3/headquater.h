#ifndef HEADQUATER_H
#define HEADQUATER_H
#include "arm.h"
#include "world.h"
#include "warriors.h"
extern int HP[5];
extern int ACK[5];

class Headquarter{
private:
	int power;//司令部生命元
	vector<int> order;//武士生产顺序
	vector<int> count;//武士数量
	int bound;//ֹͣ停止生成边界，保留使用
	list<Warrior*> warriors;//武士列表 
	int w_id;//下一个生成武士的编号
	int cur; //指向武士生产顺序，表示下一个生产的武士所在下标
	int pos;//总部所在位置
	int lionk;//武士lion每前进一步下降的忠诚度
	int dir;// 该总部武士的前进方向
	list<Warrior*> enemys; //到达该总部的敌人，当前最多只有一个，保留为列表
public:
	string name;//总部名称
	bool stop;//总部是否停止生产武士
	Headquarter(vector<int>& order,const string &name="headquarter",int power=100,int pos=0,int lionk=1,int dir=-1)
	:name(name),power(power),order(order),w_id(1),count(order.size(),0),pos(pos),lionk(lionk),dir(dir){
		bound=1e9+7;
		stop=false;
		for(auto &p:order){
			bound=min(bound,HP[p]);
		}
		cur=0;
	}
	void enemysReach(Warrior* wa){//敌人抵达总部
		enemys.push_back(wa);
	}
	Warrior* born(int hero_id){//总部生产指定编号的武士
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
	void lionRun(){//lion 逃跑，移除指定武士
		warriors.remove_if([](Warrior* p){
			lion* lp=dynamic_cast<lion*>(p);
			if(lp!=nullptr && lp->loyalty<=0){
				delete p;
				return true;
			}
			return false;
		});
	}
	void clearDead(){//清理死去的武士
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
	void report(){//报告总部自身生命元情况
		string message=to_string(power)+" elements in "+name+" headquarter";
		mlog.log(message);
	}
	void warriorReport(){//该总部的武士报告自身武器情况，（保留使用，原题要求按照城市顺序报告）
		for(auto &p:warriors){
			p->report();
		}
	}
	bool enemyReport(){//该总部如果存在敌人则被占领并播报。若被占领则返回true结束此局游戏
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
	bool bornNext(){//生产下一个武士
		if(stop){
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
#endif 
