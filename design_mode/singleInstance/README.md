
主要思想，将涉及到对象创新的函数都设为私有，设置一个公有的静态函数来获取一个静态对象，静态对象只会被初始化一次。

单例模式的适⽤场景（线程安全）
（1）系统只需要⼀个实例对象，或者考虑到资源消耗的太⼤⽽只允许创建⼀个对象。
（2）客户调⽤类的单个实例只允许使⽤⼀个公共访问点，除了该访问点之外不允许通过其它⽅式访问该实例（就
是共有的静态⽅法）
```cpp
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
```