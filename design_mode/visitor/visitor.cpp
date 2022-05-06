#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
class Cat;
class Dog;
class Mouse;
class Animal{
public:
    class IVisitor{//�ӿ���
		public:
        	virtual ~IVisitor(){}
      		virtual void Visit(Cat* animal)=0;
        	virtual void Visit(Dog* animal)=0;
        	virtual void Visit(Mouse* animal)=0;
    };
private:
    string name;
	
public:
    Animal(const string& theName):name(theName){
    }

    virtual ~Animal(){
    }
    const string& GetName()const{
        return name;
    }
    virtual string Introduce()const = 0;
    virtual void Accept(IVisitor* visitor)=0;
};

class Cat : public Animal
{
public:
    Cat(const string& theName):Animal(theName){
    }

    string Introduce()const override
    {
        return "����һֻè���ҵ����ֽ�\"" + GetName() + "\"��";
    }
    void Accept(IVisitor* visitor)override{
    	visitor->Visit(this);
    }
};

class Dog : public Animal{
public:
    Dog(const string& theName):Animal(theName){
    }

    string Introduce()const override{
        return "����һֻ�����ҵ����ֽ�\"" + GetName() + "\"��";
    }
    void Accept(IVisitor* visitor)override{
    	visitor->Visit(this);
    }
};

class Mouse : public Animal{
public:
    Mouse(const string& theName):Animal(theName)
    {
    }

    string Introduce()const override{
        return "����һֻ�����ҵ����ֽ�\"" + GetName() + "\"��";
    }
    void Accept(IVisitor* visitor)override{
    	visitor->Visit(this);
    }
};
class CatPrinter:public Animal::IVisitor{ //ͨ���̳�Visitor��ʵ�ֶԲ�ͬ����Ĳ�ͬ�߼���д 
	void Visit(Cat* animal){
		cout<<animal->Introduce()<<endl;	
	}
    void Visit(Dog* animal){
		
	}
    void Visit(Mouse* animal){
    
	}
}; 
int main(){
    auto tom = make_shared<Cat>("Tom");
    auto jerry = make_shared<Mouse>("Jerry");
    auto spike = make_shared<Dog>("Spike");
    auto butch = make_shared<Cat>("Butch");
    auto lightning = make_shared<Cat>("Lightning");
    vector<shared_ptr<Animal>> friends{ tom, jerry, spike, butch, lightning };
	CatPrinter catprinter;
    for (auto animal : friends){
        animal->Accept(&catprinter) ;
    }
    return 0;
}
