#ifndef SEGMENT_TREE_UPDATE_MAX_FAST_H
#define SEGMENT_TREE_UPDATE_MAX_FAST_H
//动态开点线段树 操作为 区间[l,r]内每个值赋值为v
//注意这边lazy标记设置为0 赋值为0时会出现无法更新情况 需要修改表示lazy不更新的LAZY值 
//加速版本—重载new运算符 预分配内存，存在内存泄露，只适用于算法竞赛，勿用于工程代码。 

class segmentTree{
public:
    int lb,rb;
    long long val,lazy;
    static long long LAZY;
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
        val=lazy=LAZY;
    } 
    void pushdown(){
    	if(lazy==LAZY)return; 
        int mid=(lb+rb)/2;
        if(left==nullptr){
            left=new segmentTree(lb,mid);
        }
        if(right==nullptr){
            right=new segmentTree(mid+1,rb);
        }
        left->lazy=lazy;
        left->val=lazy;
        right->lazy=lazy;
        right->val=lazy;
        lazy=LAZY;
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
            res=max(left->query(l,r),res);
        }
        if(r>mid){
        	if(right==nullptr){
                right=new segmentTree(mid+1,rb);
            }
            res=max(res,right->query(l,r));
        }
        return res;
    }
    void update(int l,int r,int v){//a[l,r]=v
        if(lb>=l&&rb<=r){
            lazy=v;
            val=v;
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
        val=LAZY; //注意最小值 
        if(left)val=max(left->val,val);
        if(right)val=max(right->val,val);
    }
};
long long segmentTree::LAZY=-1e9-7;
void *segmentTree::SEG_MEMEORY=nullptr;
void *segmentTree::DEST=nullptr;
int segmentTree::CHUNK=2048;
#endif  
