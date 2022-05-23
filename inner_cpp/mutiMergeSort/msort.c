#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
typedef struct QSortNode{
    int *a;
    int n;
}QSortNode;

typedef struct MergeNode{
    QSortNode l,r;
}MergeNode;
int cmp(const void* a,const void *b){
    return *(int*)a-*(int*)b;
}
void *multQsort(void *arg){
    QSortNode* qnode=(QSortNode*)(arg);
    qsort(qnode->a,qnode->n,sizeof(int),cmp);
    fprintf(stderr,"Sorted %d elements\n",qnode->n);
    return NULL;
}

void* multMerge(void *arg){
    MergeNode* mnode=(MergeNode*)(arg);
    int *a=(mnode->l).a,*b=(mnode->r).a;
    int n=(mnode->l).n,m=(mnode->r).n;
    int *c=(int*)malloc(sizeof(int)*(n+m));
    int k=0,i=0,j=0;
    while(i<n && j<m){
        if(a[i]<b[j]){
            c[k]=a[i++];
        }else{
            c[k]=b[j++];
        }
        if(k==0 || c[k]!=c[k-1]){
            k++;
        }
    }
    while(i<n){
        c[k]=a[i++];
        if(k==0 || c[k]!=c[k-1]){
            k++;
        }
    }
    while(j<m){
        c[k]=b[j++];
        if(k==0 || c[k]!=c[k-1]){
            k++;
        }
    }
    memcpy(a,c,sizeof(int)*k);
    free(c);
    fprintf(stderr,"Merged %d and %d elements into %d elements\n",n,m,k);
    (mnode->l).n=k;
    return NULL;
}
int main(int argc, char **argv) {
    int fd=open(argv[2],O_RDONLY,S_IRUSR);
    dup2(fd,0);
    //读入所有元素
    int n=64,cnt=0;//n表示预分配数组大小，cnt表示当前元素数量
    int *arr=(int*) malloc(sizeof(int)*n);
    while(scanf("%d",&arr[cnt])!=EOF){
        cnt++;
        if(cnt==n){
            n<<=1;
            arr=(int*)realloc(arr,sizeof(int)*n);
        }
    }
    //分块
    int count;
    sscanf(argv[1],"%d",&count);
    int x=cnt%count,block=cnt/count;
    pthread_t* threads=(pthread_t*) malloc(sizeof(pthread_t)*count);
    QSortNode* qnodes=(QSortNode*) malloc(sizeof(QSortNode)*count);
    int* arrp=arr; //位置偏移
    //多线程排序
    for(int i=0;i<count;i++){
        if(i<x){
            qnodes[i].a=arrp;
            qnodes[i].n=block+1;
            arrp+=block+1;
            pthread_create(threads+i,NULL,multQsort,&qnodes[i]);
        }else{
            qnodes[i].a=arrp;
            qnodes[i].n=block;
            arrp+=block;
            pthread_create(threads+i,NULL,multQsort,&qnodes[i]);
        }
    }
    for(int i=0;i<count;i++){
        pthread_join(threads[i],NULL);
    }
    fprintf(stderr,"Finish firstly sorting\n");

    
    //归并
    MergeNode *mnodes=(MergeNode*) malloc(sizeof(MergeNode)*count);
    for(int i=0;i<count;i++){
        mnodes[i].l=qnodes[i];
        // printf("%d\n",mnodes)
    }
    int round=0;
    while(count>1){
        round++;
        int ncount=0;
        for(int i=0;i<count;i+=2){
            if(i+1<count){
                mnodes[ncount].l=mnodes[i].l;
                mnodes[ncount].r=mnodes[i+1].l;
                pthread_create(threads+ncount,NULL,multMerge,&mnodes[ncount]);
            }else{
                mnodes[ncount].l=mnodes[i].l;
            }
            ncount++;
        }
        for(int i=0;i<count;i+=2){
            if(i+1<count){
                pthread_join(threads[i/2],NULL);
            }
        }
        fprintf(stderr,"Finish round %d merging\n",round);
        count=ncount;
    }
    cnt=mnodes[0].l.n;
    for(int i=0;i<cnt;i++){
        printf("%d\n",arr[i]);
    }
    //释放内存
    free(mnodes);
    free(qnodes);
    free(arr);
    free(threads);
    return 0;
}
