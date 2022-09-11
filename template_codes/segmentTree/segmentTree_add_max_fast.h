#ifndef SEGMENT_TREE_ADD_FAST_H
#define SEGMENT_TREE_ADD_FAST_H
//动态开点线段树 操作为区间[l,r]内每个值+v  查询max
//加速版本—重载new运算符 预分配内存，存在内存泄露，只适用于算法竞赛，勿用于工程代码。 
#include<climits>
class segmentTree{
public:
    int lb,rb;
    long long val,lazy;
    segmentTree *left,*right;
    static void *SEG_MEMEORY;
    static void *DEST;
    static int CHUNK;
    static void *operator new(size_t size){//重载类的operator new 改变new的行为
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
        if(lb>=l&&rb<=r){//当前节点完全在待查区间内
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
