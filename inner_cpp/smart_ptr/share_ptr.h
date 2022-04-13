#ifndef SHARE_PTR_H
#define SHARE_PTR_H
template<typename T>
class share_ptr{
private:
	T* data;
	int* num;
public:
	//���캯��
	share_ptr(T* ptr=nullptr):data(ptr){
		if(ptr==nullptr){
			num=nullptr;
			return;
		}
		num=new int;
		*num=1;
	}
	
	//�������� 
	//��num��    
	~share_ptr(){
		if(num==nullptr)return;
		--(*num);
		if(*num==0){
			delete num;
			delete data;
			data=nullptr;
		}
	}
	
	//���ù��캯��
	//����ָ�벢�Ҽ���+1 
	share_ptr(share_ptr<T> &rhs){
		data=rhs.data;
		num=rhs.num;
		if(num!=nullptr)++(*num);
	}
	
	//��ֵ���ù��캯�� 
	share_ptr(share_ptr<T> &&rhs){
		data=rhs.data;
		num=rhs.num;
		rhs.data=nullptr;
		rhs.num=nullptr;
	}
	
	share_ptr<T>& operator=(share_ptr<T>& rhs)noexcept{
		this->release();
		data=rhs.data;
		num=rhs.num;
		if(num!=nullptr)++(*num);
		return *this;
	}
	share_ptr<T>& operator=(share_ptr<T>&& rhs)noexcept{
		this->release();
		data=rhs.data;
		num=rhs.num;
		rhs.data=nullptr;
		rhs.num=nullptr;
		return *this;
	}
	T& operator*(){
		return *data;
	}
	T* operator->(){
		return data;
	}
	T* get(){
		return data;
	}
	void reset(T* ptr=nullptr)noexcept{
		this->release();
		if(ptr==nullptr){
			return;
		}
		data=ptr;
		num=new int;
		*num=1;
	}
	int use_count(){
		if(num==nullptr)return 0;
		return *num;
	}
	void release()noexcept{
		if(num!=nullptr){
			--(*num);
			if(*num==0){
				delete num;
				delete data;
			}
			num=nullptr;
			data=nullptr;
		}
	}
};
#endif
