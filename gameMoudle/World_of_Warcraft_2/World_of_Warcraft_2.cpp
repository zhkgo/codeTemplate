#include<iostream>
#include<string>
#include<cstdio>
#include<map> 
#include<algorithm>
using namespace std;
string arms[3]={"sword","bomb","arrow"}; 
string names[5]={"dragon","ninja","iceman","lion","wolf"};
int HP[5];

//ȫ����־ 
class Log{
private:
	int now;
public:
	Log():now(0){
	}
	void reset(){
		now=0;
	}
	void log(const string &message,bool timer=true){//flg ��ʾ�Ƿ����ʱ�� 
		if(timer)
			printf("%03d %s\n",now,message.c_str());
		else
			printf("%s\n",message.c_str());
	}
	void addTime(){
		++now;
	}
}mlog;

//��ʿ�� 
class Warrior{ 
public:
	int id;//��� 
	string name;//���� 
	int health;//���� 
	int ack;//������ 
	Warrior(int id=1,const string &name="warrior",int health=10,int ack=5,const string& headq="red",int num=1):id(id),name(name),health(health),ack(ack){
		string message=headq+" "+name+" "+to_string(id)+" born with strength "+to_string(health)+","
			+to_string(num)+" "+name+" in "+headq+" headquarter";
		mlog.log(message);
	}
};

class dragon:Warrior{
public:
	int arm;
	double morale;//ʿ�� 
	dragon(int id=1,int health=10,int ack=5,double morale=1,const string& headq="red",int num=1)
	:Warrior(id,"dragon",health,ack,headq,num),arm(id%3),morale(morale){
		char message[100];
		sprintf(message,"It has a %s,and it's morale is %.2lf",arms[arm].c_str(),morale);
		mlog.log(message,false);
	}
};
class ninja:Warrior{
public:
	int leftArm;
	int rightArm;
	ninja(int id=1,int health=10,int ack=5,const string& headq="red",int num=1)
	:Warrior(id,"ninja",health,ack,headq,num),leftArm(id%3),rightArm((id+1)%3){
		char message[100];
		sprintf(message,"It has a %s and a %s",arms[leftArm].c_str(),arms[rightArm].c_str());
		mlog.log(message,false);
	}
};

class iceman:Warrior{
public:
	int arm;
	iceman(int id=1,int health=10,int ack=5,const string& headq="red",int num=1)
	:Warrior(id,"iceman",health,ack,headq,num),arm(id%3){
		char message[100];
		sprintf(message,"It has a %s",arms[arm].c_str());
		mlog.log(message,false);
	}
};
class lion:Warrior{
public:
	int loyalty;
	lion(int id=1,int health=10,int ack=5,int loyalty=1,const string& headq="red",int num=1)
	:Warrior(id,"lion",health,ack,headq,num),loyalty(loyalty){
		char message[100];
		sprintf(message,"It's loyalty is %d",loyalty);
		mlog.log(message,false);
	}
};

class wolf:Warrior{
public:
	wolf(int id=1,int health=10,int ack=5,const string& headq="red",int num=1)
	:Warrior(id,"wolf",health,ack,headq,num){
	}
};

//˾� 
class Headquarter{
private:
	int power;//����Ԫ
	vector<int> order;//������λ˳�� 
	vector<int> count;//ĳ��λ���������� 
	int bound;//ֹͣ���ɵ������߽� 
	vector<Warrior*> warriors; //�Ѿ����ɵ�������ʿ 
	int w_id;//������ʿ�ı�� 
	int cur; //��һ��������ʿ������ 
public:
	string name;
	bool stop;
	Headquarter(vector<int>& order,const string &name="headquarter",int power=100)
	:name(name),power(power),order(order),w_id(1),count(order.size(),0){
		bound=1e9+7;
		stop=false;
		for(auto &p:order){
			bound=min(bound,HP[p]);
		}
		cur=0;
	}
	Warrior* born(int hero_id){
		if(power>=HP[hero_id]){
			power-=HP[hero_id];
			count[hero_id]+=1;
			Warrior* hero=nullptr;
			switch (hero_id){
				case 0:
					hero =(Warrior*) new dragon(w_id++,HP[hero_id],-1,1.0*power/HP[hero_id],name,count[hero_id]);
					break;
				case 1:
					hero =(Warrior*) new ninja(w_id++,HP[hero_id],-1,name,count[hero_id]);
					break;
				case 2:
					hero =(Warrior*) new iceman(w_id++,HP[hero_id],-1,name,count[hero_id]);
					break;
				case 3:
					hero =(Warrior*) new lion(w_id++,HP[hero_id],-1,power,name,count[hero_id]);
					break;
				case 4:
					hero =(Warrior*) new wolf(w_id++,HP[hero_id],-1,name,count[hero_id]);
					break;
			}
			return hero;
		}
		return nullptr;
	}
	bool bornNext(){
		if(power<bound){
			mlog.log(name+" headquarter stops making warriors");
			stop=true;
			return false;
		}
		Warrior* war;
		do{
			war=born(order[cur]);
			cur=(cur+1)%order.size();
		}while(war==nullptr);
		warriors.push_back(war);
		return true;
	}
	~Headquarter(){
		for(auto &wa:warriors){
			delete wa;
		}
	}
};
int main(){
	int T;
	cin>>T;
	for(int cs=1;cs<=T;cs++){
		int M,health;
		cin>>M;
		cout<<"Case:"<<cs<<endl;
		for(int i=0;i<5;i++){
			cin>>HP[i];
		}
		vector<int> o1={2,3,4,1,0};
		vector<int> o2={3,0,1,2,4};
		Headquarter h1(o1,"red",M);
		Headquarter h2(o2,"blue",M);
		mlog.reset();
		while(true){
			if(!h1.stop){
				h1.bornNext();
			}
			if(!h2.stop){
				h2.bornNext();
			}
			mlog.addTime();
			if(h1.stop&&h2.stop)break;
		}
	}
	return 0;
}
