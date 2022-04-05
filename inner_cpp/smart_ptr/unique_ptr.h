#ifndef UNIQUE_PTR
#define UNIQUE_PTR
#include <algorithm>
#include <iostream>
template<typename T>
class unique_ptr{
    T* ptr;
public:
    unique_ptr(T* dat=nullptr):ptr(dat){
    }
    unique_ptr(unique_ptr<T> &&src)noexcept{
        ptr=src.ptr;
        src.ptr=nullptr;
    }
    ~unique_ptr()noexcept{
        delete ptr;
    }
    unique_ptr<T>& operator =(unique_ptr<T> &&src)noexcept{
        std::swap(ptr,src.ptr);
        return *this;
    }
    T* operator ->()const{
        return ptr;
    }
    T& operator *()const{
        return *ptr;
    }
    bool operator !()const{
        return ptr==nullptr;
    }
    explicit operator bool()const{
        return ptr!=nullptr;
    }
private:
    unique_ptr(unique_ptr<T> &src)=delete;
    unique_ptr<T>& operator =(unique_ptr<T> &src)=delete;
};
#endif
