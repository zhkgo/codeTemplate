#ifndef World_H
#define World_H
#include<vector>
#include<string>
#include<cstdio>
#include<list>
using namespace std;

#define MESSAGE_LENGTH 300
#include "city.h"
class Headquarter;
class City;
//世界类
class World{
public:
	int now;
	Headquarter *h1,*h2;
	vector<City> citys;
	World():now(0){
	}
	void reset(Headquarter* _h1,Headquarter *_h2,int N);//重启世界，h1为红阵营，h2为蓝阵营，N为中间城市数量
	void log(const string &message,bool timer=true);//世界日志
	bool addTime();//时间流逝 返回true代表有总部被占领
};
extern World mlog;
#endif
