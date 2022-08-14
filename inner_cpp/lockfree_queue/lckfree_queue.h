#ifndef LCKFREE_QUEUE
#define LCKFREE_QUEUE
#include<atomic> 

template<typename T>
class lckfree_queue{
private:
	std::atomic<int> head;
	std::atomic<int> tail;
	int cap;
	T* data;
public:
	lckfree_queue(int cap=1000):cap(cap),head(0),tail(0){
		data = new T[cap];
	}
	~lckfree_queue(){
		delete []data;
	}
	bool push(T node){
		int oldv;
		do{
			oldv=tail.load(std::memory_order_relaxed);
			if(size()==cap-1)return false;
		}while(!tail.compare_exchange_weak(oldv,(oldv+1)%cap));
		data[oldv]=node;
		return true;
	}
	T pop(){
		int oldv;
		do{
			oldv=head.load(std::memory_order_relaxed);
			if(head==tail)return nullptr;
		}while(!head.compare_exchange_weak(oldv,(oldv+1)%cap));
		return data[oldv];
	}
	int size(){
		return (tail+cap-head)%cap;
	}
	bool empty(){
		return tail==head;
	}
	T front(){
		return data[head];
	}
};
#endif 
