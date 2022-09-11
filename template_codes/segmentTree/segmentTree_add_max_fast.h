#ifndef SEGMENT_TREE_ADD_FAST_H
#define SEGMENT_TREE_ADD_FAST_H
//��̬�����߶��� ����Ϊ����[l,r]��ÿ��ֵ+v  ��ѯmax
//���ٰ汾������new����� Ԥ�����ڴ棬�����ڴ�й¶��ֻ�������㷨�����������ڹ��̴��롣 
#include<climits>
class segmentTree{
public:
    int lb,rb;
    long long val,lazy;
    segmentTree *left,*right;
    static void *SEG_MEMEORY;
    static void *DEST;
    static int CHUNK;
    static void *operator new(size_t size){//�������operator new �ı�new����Ϊ
        if(SEG_MEMEORY==nullptr||(char*)SEG_MEMEORY+CHUNK*size==(char*)DEST){
            SEG_MEMEORY=malloc(size*CHUNK);
            DEST=SEG_MEMEORY;
        }
        char *v=(char*)DEST;
        DEST=(void*)((char*)DEST+size);
        return (void*)v;
	}
    segmentTree(int l,int r):lb(l),rb(r),left(nullptr),right(nullptr){
            val=lazy=0;
    } 
    void pushdown(){
    	if(lazy==0)return; 
        int mid=(lb+rb)/2;
        if(left==nullptr){
            left=new segmentTree(lb,mid);
        }
        if(right==nullptr){
            right=new segmentTree(mid+1,rb);
        }
        left->lazy+=lazy;
        left->val+=lazy;
        right->lazy+=lazy;
        right->val+=lazy;
        lazy=0;
    }
    long long query(int l,int r){
        if(lb>=l&&rb<=r){//��ǰ�ڵ���ȫ�ڴ���������
            return val;
        }
        pushdown();
        long long res=LLONG_MIN;
        int mid=(lb+rb)/2;//[lb,mid],[mid+1,rb]
        if(l<=mid){
        	if(left==nullptr){
                left=new segmentTree(lb,mid);
            }
            res=max(left->query(l,r),res);
        }
        if(r>mid){
        	if(right==nullptr){
                right=new segmentTree(mid+1,rb);
            }
            res=max(right->query(l,r),res);
        }
        return res;
    }
    void update(int l,int r,int v){//a[l,r] +v
        if(lb>=l&&rb<=r){
            lazy+=v;
            val+=v;
            return;
        }
        pushdown();
        int mid=(lb+rb)/2;//[lb,mid],[mid+1,rb]
        if(l<=mid){
            if(left==nullptr){
                left=new segmentTree(lb,mid);
            }
            left->update(l,r,v);
        }
        if(r>mid){
            if(right==nullptr){
                right=new segmentTree(mid+1,rb);
            }
            right->update(l,r,v);
        }
        pushup();
    }
    void pushup(){
        val=LLONG_MIN;
        if(left)val=max(val,left->val);
        if(right)val=max(right->val,val);
    }
};
void *segmentTree::SEG_MEMEORY=nullptr;
void *segmentTree::DEST=nullptr;
int segmentTree::CHUNK=2048;
#endif
