#ifndef THREADPOLL_H
#define THREADPOLL_H

#include <thread>
#include <queue>
#include <mutex>
#include "sem.h"
/*
threadpool 线程池
通过生产者消费者模型+队列来实现任务的同步
*/
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
	std::mutex m_locker;
	sem m_sem;
	std::queue<T*> task_queue; 
	std::thread* threads;
};
template<typename T>
threadpool<T>::threadpool(int thread_num,int max_request):
	thread_num(thread_num),max_request(max_request),stop(false),threads(nullptr){
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
		m_locker.lock();
		T* task = nullptr;
		task = task_queue.front();
		task_queue.pop();
		m_locker.unlock(); 
		if(task!=nullptr){
			task->process(); 
		}
	}
}
template<typename T>
bool threadpool<T>::append(T* task){
	m_locker.lock();
	if(task_queue.size()>=max_request){
		m_locker.unlock();
		return false;
	}
	task_queue.push(task);
	m_locker.unlock();
	m_sem.post();
	return true;
}
#endif