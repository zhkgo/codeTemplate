#include<iostream>
using namespace std;
class singleInstance{
public: 
	static singleInstance* getInstance(){
		static singleInstance ins;
		return &ins;
	}
	~singleInstance(){
	};
private:
	singleInstance(){
		cout<<"construct "<<endl;
	}
	singleInstance(const singleInstance& s){
	}
	singleInstance& operator =(const singleInstance &s){
		return *this;
	}
}; 
int main(){
	singleInstance* ins = singleInstance::getInstance();
	return 0;
}
