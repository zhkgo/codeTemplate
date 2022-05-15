#ifndef SEGMENT_TREE_ADD_H
#define SEGMENT_TREE_ADD_H
//动态开点线段树 操作为区间[l,r]内每个值+v 
class segmentTree{
public:
    int lb,rb;
    long long val,lazy;
    segmentTree *left,*right;
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
        left->val+=1ll*(left->rb-left->lb+1)*lazy;
        right->lazy+=lazy;
        right->val+=1ll*(right->rb-right->lb+1)*lazy;
        lazy=0;
    }
    long long query(int l,int r){
        if(lb>=l&&rb<=r){//当前节点完全在待查区间内
            return val;
        }
        pushdown();
        long long res=0;
        int mid=(lb+rb)/2;//[lb,mid],[mid+1,rb]
        if(l<=mid){
        	if(left==nullptr){
                left=new segmentTree(lb,mid);
            }
            res+=left->query(l,r);
        }
        if(r>mid){
        	if(right==nullptr){
                right=new segmentTree(mid+1,rb);
            }
            res+=right->query(l,r);
        }
        return res;
    }
    void update(int l,int r,int v){//a[l,r] +v
        if(lb>=l&&rb<=r){
            lazy+=v;
            val+=1ll*v*(rb-lb+1);
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
        val=0;
        if(left)val+=left->val;
        if(right)val+=right->val;
    }
//    ~segmentTree(){//析构函数 不加会内存泄露，加了可能会增加大量运行时间，特别是区间范围特别大的时候 
//        delete left;
//        delete right;
//    }
};
#endif
