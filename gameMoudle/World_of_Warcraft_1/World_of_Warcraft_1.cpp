#include<iostream>
#include<string>
#include<cstdio>
#include<map> 
#include<algorithm>
using namespace std;
//��ʿ�� 
class Warrior{ 
public:
	int id;//��� 
	string name;//���� 
	int health;//���� 
	int ack;//������ 
	Warrior(int id=1,const string &name="warrior",int health=10,int ack=5):id(id),name(name),health(health),ack(ack){
	}
};
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
	void log(const string &message){
		printf("%03d %s\n",now,message.c_str());
	}
	void addTime(){
		++now;
	}
}mlog;
//˾� 
class Headquarter{
private:
	int power;//����Ԫ
	map<string,Warrior> canProduct; //���ɵ�λģ�� 
	vector<string> order;//������λ˳�� 
	map<string,int>count;//ĳ��λ���������� 
	int bound;//ֹͣ���ɵ������߽� 
	vector<Warrior*> warriors; //�Ѿ����ɵ�������ʿ 
	int w_id;//������ʿ�ı�� 
	int cur; //��һ��������ʿ������ 
public:
	string name;
	bool stop;
	Headquarter(map<string,Warrior>& canProduct,vector<string>& order,const string &name="headquarter",int power=100)
	:name(name),power(power),canProduct(canProduct),order(order),w_id(1){
		bound=1e9+7;
		stop=false;
		for(auto &p:canProduct){
			bound=min(bound,p.second.health);
		}
		cur=0;
	}
	Warrior* born(const Warrior &wa){
		if(power>=wa.health){
			power-=wa.health;
			count[wa.name]+=1;
			string message=name+" "+wa.name+" "+to_string(w_id)+" born with strength "+to_string(wa.health)+","
			+to_string(count[wa.name])+" "+wa.name+" in "+name+" headquarter";
			mlog.log(message);
			return new Warrior(w_id++,wa.name,wa.health,wa.ack);
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
			war=born(canProduct[order[cur]]);
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
	string names[5]={"dragon","ninja","iceman","lion","wolf"}; 
	int T;
	cin>>T;
	for(int cs=1;cs<=T;cs++){
		int M,health;
		cin>>M;
		cout<<"Case:"<<cs<<endl;
		map<string,Warrior> mp; 
		for(int i=0;i<5;i++){
			cin>>health;
			mp[names[i]]=Warrior(-1,names[i],health);
		}
		vector<string> o1={"iceman","lion","wolf","ninja","dragon"};
		vector<string> o2={"lion","dragon","ninja","iceman","wolf"};
		Headquarter h1(mp,o1,"red",M);
		Headquarter h2(mp,o2,"blue",M);
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
