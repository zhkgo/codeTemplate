#ifndef ARM_H
#define ARM_H

#include <string>
using namespace std;
extern string armNames[3];

class Warrior;
class Arm{
public:
	int arm_id;//武器编号
	int ackp;//武器伤害百分比
	int used;//武器耐久度
	Arm(int arm_id=0,int ackp=20,int used=1000):arm_id(arm_id),ackp(ackp),used(used){
	}
	static bool arm_cmp_use(Arm* a1,Arm* a2);//武器使用优先级 优先编号最小的 优先使用耐久度较低的
	static bool arm_cmp_get(Arm* a1,Arm* a2);//武器抢夺优先级 优先编号最小的 优先抢夺耐久度较高的
	virtual bool attack(Warrior* owner,Warrior* enemy);//使用该武器进攻
	virtual ~Arm(){}
};
//宝剑
class sword:public Arm{
public:
	sword():Arm(0,20,10000000){
	}
};
//炸弹
class bomb:public Arm{
public:
	bomb():Arm(1,40,1){
	}
};
//弓箭
class arrow:public Arm{
public:
	arrow():Arm(2,30,2){
	}
};
//武器生产工厂
class ArmFactory{
public:
	static Arm* product(int id);//生产编号为id的武器
};
#endif
