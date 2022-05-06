#ifndef CITY_H
#define CITY_H
#include "warriors.h"
#include "arm.h"
#include "world.h"
class Warrior;
class City{
public:
	int c_id;//城市编号
	list<Warrior*> red_warriors,blue_warriors;//红蓝阵营的武士
	City(int c_id):c_id(c_id){
	}
	void addWarrior(Warrior* p);//武士进入该城市
	void removeWarrior(Warrior* p);//武士离开该城市
	list<Warrior*> battle(Warrior* w1,Warrior* w2);//两个武士在该城市展开战斗，返回存活的武士
	void judge();//判断该城市是否有战斗发生，如果有则展开战斗
	void wolfPlunder();//如果该城市有wolf，则他可以开始抢夺武器
	void report(); //该城市报告有哪些武士到达了此城市
	void warriorReport();//在该城市的武士报告自己的武器持有情况
	void lionRun();//在该城市的lion若忠诚度不够，则可以逃跑了！
};
#endif
