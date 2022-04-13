#include "share_ptr.h"
#include <iostream>
using namespace std;
struct Node{
	Node(){
		cout<<"New Node"<<endl;
	}	
	~Node(){
		cout<<"Del Node"<<endl;
	}
}; 
int main(){
	share_ptr<Node> tmp(nullptr);
	{
		share_ptr<Node> ptr(new Node);
		tmp=ptr;
		cout<<tmp.use_count()<<endl;
		cout<<ptr.use_count()<<endl;
	}
	cout<<tmp.use_count()<<endl;
	{
		share_ptr<Node> ptr(new Node);
		tmp=move(ptr);
		cout<<tmp.use_count()<<endl;
	}
	{
		share_ptr<Node> ptr(tmp);
		cout<<tmp.use_count()<<endl;
	}
	{
		share_ptr<Node> ptr(move(tmp));
		cout<<tmp.use_count()<<endl;
		cout<<ptr.use_count()<<endl;
	}
	cout<<"out"<<endl;
	return 0;
}
