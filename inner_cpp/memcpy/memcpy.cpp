#include<cstdio>
void* memcpy(void* dest,void* src,size_t count){
	char* d=(char*)dest;
	char* s=(char*)src;
	size_t batch = count/sizeof(int); //每次拷贝4个字节 
	size_t rest = count%sizeof(int);
	//目的地址在高位 源地址在低位，可能存在目标区域覆盖源区域的问题，需要倒序存储 
	if(s < d){
		char *es=s+count,*ed=d+count;
		while(rest--){
			*--ed=*--es;
		}
		int *ies=(int*)s+batch,*ied=(int*)d+batch;
		while(batch--){
			*--ied=*--ies;
		}
	}else{
		int *is=(int*)s,*id=(int*)d;
		while(batch--){
			*id++=*is++;
		}
		s=(char*)is;
		d=(char*)id;
		while(rest--){
			*d++=*s++;
		}
	}
	return dest;
}

int main(){
	char s1[30]="abcdefghijklmnopqrstuvwxyz";
	printf("%s\n",s1);
	memcpy(s1,s1+2,23); 
	printf("%s\n",s1);
	char s2[30]="abcdefghijklmnopqrstuvwxyz";
	printf("%s\n",s2);
	memcpy(s2+2,s2,23); 
	printf("%s\n",s2);
	return 0;
} 