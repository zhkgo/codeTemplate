#ifndef SEM_H
#define SEM_H
#include<pthread.h>
#include<semaphore.h>
#include<exception> 

class sem{
public:
	sem(){
		if(sem_init(&m_sem,0,0)!=0){
			throw std::exception();
		}
	}
	~sem(){
		sem_destroy(&m_sem);
	}
	bool post(){
		return sem_post(&m_sem);
	}
	bool wait(){
		return sem_wait(&m_sem);
	}
private:
	sem_t m_sem;
};
#endif