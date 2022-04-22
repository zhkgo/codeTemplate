#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
class Element {
private:
    int number;
public:
	Element() :number(0) {
	    cout << "ctor" << endl;
	}
  	Element(int num):number(num) {
  		cout << "ctor" << endl;
  	}
  	Element(const Element& e):number(e.number) {
  		cout << "copy ctor" << endl;
  	}
  	Element(Element&& e):number(e.number) {
  		cout << "right value ctor" << endl;
  	}
  	~Element() {
  		cout << "dtor" << endl;
  	}
  	void operator=(const Element& item) {
  		number = item.number;
  	}
  	bool operator==(const Element& item) {
  		return (number == item.number);
  	}
  	void operator()() {
  		cout << number ;
  	}
  	int GetNumber() {
  		return number;
  	}
};
template<typename T>
class Vector {
private:
  	T* items;
  	int count;
public:
  	Vector() :count{ 0 }, items{nullptr} {

  	}
  	Vector(const Vector& vector) :count{vector.count} {
  		items = static_cast<T*>(malloc(sizeof(T) * count));
  		memcpy(items, vector.items, sizeof(T) * count);
  	}
    //构造函数
  	Vector(Vector&& vector) :count{ vector.count }, items{ vector.items } {
  		vector.items = nullptr;
        vector.count = 0;
  	}
    //析构函数
  	~Vector() {
  		this->Clear();
  	}
    T& operator[](int index){
    	if (index<0||index>=count) {
    		cout<<"invalid index"<<endl;
    		return items[0];
    	}
    	return items[index];
    }
    int returnCount(){
    	return count;
    }
    //析构全部元素
  	void Clear() {
  		for(int i=0;i<count;i++){
            items[i].~T();
        }
        count = 0;
        free(items);
        items = nullptr;
  	}
    //push_back实现
  	void Add(const T& item) {
  		T* nitems = static_cast<T*>(malloc(sizeof(T)*(count+1)));
        for(int i=0;i<count;i++){
            new (nitems+i) T(move(items[i]));
        }
        new (nitems+count) T(item);
        int ncount = count+1;
        this->Clear();
        count = ncount;
        items = nitems;
  	}
    //插入元素
  	bool Insert(const T& item,int index) {
  		if(index<0||index>count)return false;
        T* nitems = static_cast<T*>(malloc(sizeof(T)*(count+1)));
        for(int i=0;i<index;i++){
            new (nitems+i) T(move(items[i]));
        }
        new (nitems+index) T(item);
        for(int i=index;i<count;i++){
            new (nitems+i+1) T(move(items[i]));
        }
        int ncount = count+1;
        this->Clear();
        count = ncount;
        items = nitems;
        return true;
  	}
    //移除下标为index的元素
  	bool Remove(int index) {
  		if(index<0||index>=count)return false;
        T* nitems = static_cast<T*>(malloc(sizeof(T)*(count-1)));
        for(int i=0;i<index;i++){
            new (nitems+i) T(move(items[i]));
        }
        for(int i=index+1;i<count;i++){
            new (nitems+i-1) T(move(items[i]));
        }
        int ncount = count-1;
        this->Clear();
        count = ncount;
        items = nitems;
        return true;
  	}
    //查看是否包含元素item，如果包含则返回索引
  	int Contains(const T& item) {
  		for(int i=0;i<count;i++){
            if(items[i]==item)
                return i;
        }
        return -1;
  	}
};
template<typename T>
void PrintVector(Vector<T>& v){
	  int count=v.returnCount();
	  for (int i = 0; i < count; i++)
	  {
		  v[i]();
		  cout << " ";
	  }
	  cout << endl;
}
int main() {
  	Vector<Element>v;
  	for (int i = 0; i < 4; i++) {
  		Element e(i);
  		v.Add(e);
  	}
  	PrintVector(v);
  	Element e2(4);
  	if (!v.Insert(e2, 10))
  	{
  		v.Insert(e2, 2);
  	}
  	PrintVector(v);
  	if (!v.Remove(10))
  	{
  		v.Remove(2);
  	}
  	PrintVector(v);
  	Element e3(1), e4(10);
  	cout << v.Contains(e3) << endl;
  	cout << v.Contains(e4) << endl;
  	Vector<Element>v2(v);
  	Vector<Element>v3(move(v2));
  	PrintVector(v3);
  	v2.Add(e3);
  	PrintVector(v2);
  	return 0;
}

