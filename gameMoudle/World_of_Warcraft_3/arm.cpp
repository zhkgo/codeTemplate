#include "arm.h" 
#include "warriors.h"
#include "city.h"
#include <string>
using namespace std;
string armNames[3]={"sword","bomb","arrow"}; 
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
bool Arm::arm_cmp_get(Arm* a1,Arm* a2){
	if(a1->arm_id!=a2->arm_id)
		return a1->arm_id<a2->arm_id;
	if(a1->arm_id==2){
		return a1->used>a2->used;
	}
	return true;
}
bool Arm::arm_cmp_use(Arm* a1,Arm* a2){
	if(a1->arm_id!=a2->arm_id)
		return a1->arm_id<a2->arm_id;
	if(a1->arm_id==2){
		return a1->used<a2->used;
	}
	return true;
}
Arm* ArmFactory::product(int id){
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

