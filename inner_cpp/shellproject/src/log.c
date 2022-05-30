/** @file log.c */
#include <stdlib.h>
#include <string.h>
#include "log.h"

/**
对log进行初始化，log的“构造函数”
 */

void log_init(log_t *l) {
    l->head = NULL;
    l->tail = NULL;
}

/**
销毁一个log，释放所有内存空间，log的“析构函数”
 */

void log_destroy(log_t* l) {
    node *p=l->head;
    node *nxt;
    while(p){
        nxt=p->next;
        free(p->cmd);
        free(p);
        p=nxt;
    }
    l->tail = l->head = NULL;
}

/**
向log中推入一个字符串，你可以将log视为一个由链表组成的栈
 */

void log_push(log_t* l, const char *item) {
    node *cur = (node*) malloc(sizeof(node));
    cur->cmd = malloc(strlen(item)+1);
    strcpy(cur->cmd,item);
    cur->next = NULL;
    if(l->head == NULL){
        l->head = l->tail = cur;
    }else{
        l->tail->next = cur;
        l->tail = cur;
    }
}

int match(const char *str,const char *prefix){
    while(*str != '\0' && *prefix != '\0'){
        if(*str != *prefix)
            return 0;
        ++str;
        ++prefix;
    }
    return *prefix == '\0';
}
/**
搜索log中是否含有对应前缀的字符串
 */
char *log_search(log_t* l, const char *prefix) {
    node *cur = l->head;
    while(cur){
        if(match(cur->cmd,prefix)){
            return cur->cmd;
        }
        cur=cur->next;
    }
    return NULL;
}
