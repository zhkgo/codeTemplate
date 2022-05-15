#ifndef SEGMENT_TREE_UPDATE_H
#define SEGMENT_TREE_UPDATE_H
//��̬�����߶��� ����Ϊ ����[l,r]��ÿ��ֵ��ֵΪv
//ע�����lazy�������Ϊ0 ��ֵΪ0ʱ������޷�������� ��Ҫ�޸ı�ʾlazy�����µ�LAZYֵ 
class segmentTree{
public:
    int lb,rb;
    long long val,lazy;
    static long long LAZY;
    segmentTree *left,*right;
    segmentTree(int l,int r):lb(l),rb(r),left(nullptr),right(nullptr){
        val=lazy=0;
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
        left->val=1ll*(left->rb-left->lb+1)*lazy;
        right->lazy=lazy;
        right->val=1ll*(right->rb-right->lb+1)*lazy;
        lazy=LAZY;
    }
    long long query(int l,int r){
        if(lb>=l&&rb<=r){//��ǰ�ڵ���ȫ�ڴ���������
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
    void update(int l,int r,int v){//a[l,r]=v
        if(lb>=l&&rb<=r){
            lazy=v;
            val=1ll*v*(rb-lb+1);
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
//   ~segmentTree(){//�������� ���ӻ��ڴ�й¶�����˿��ܻ����Ӵ�������ʱ�䵼�³�ʱ���ر������䷶Χ�ر���ʱ�� 
//       delete left;
//       delete right;
//   }
};
long long segmentTree::LAZY=0;
#endif 
