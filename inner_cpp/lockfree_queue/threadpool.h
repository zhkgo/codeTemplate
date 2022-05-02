#ifndef THREADPOLL_H
#define THREADPOLL_H

#include <thread>
#include "sem.h"
#include "lckfree_queue.h"

template<typename T>
class threadpool{
public:
	threadpool(int thread_num=8,int max_request=10000);
	~threadpool();
	bool append(T* task);
	void run();
	static void worker(threadpool* pool){
		pool->run();
	}
private:
	int thread_num;
	int max_request;
	bool stop;
	sem m_sem;
	lckfree_queue<T*> task_queue;
	std::thread* threads;
};
template<typename T>
threadpool<T>::threadpool(int thread_num,int max_request):
	thread_num(thread_num),max_request(max_request),stop(false),threads(nullptr),task_queue(max_request+1){
	if(thread_num<=0||max_request<=0){
		throw std::exception();
	}
	threads = new std::thread[thread_num];
	for(int i=0;i<thread_num;i++){
		threads[i]=std::thread(worker,this);	
		threads[i].detach(); 
	}
}
template<typename T>
threadpool<T>::~threadpool(){
	stop = true;
	delete []threads;
}
template<typename T>
void threadpool<T>::run(){
	while(!stop){
		m_sem.wait();
		T* task=task_queue.pop();
		if(task!=nullptr){
			task->process(); 
		}
	}
}
template<typename T>
bool threadpool<T>::append(T* task){
	if(!task_queue.push(task))return false; 
	m_sem.post();
	return true;
}
#endif
