#include "shell.h"
/**
 * shell的入口
 */
void prefix() {
    char *cwd=getcwd(NULL,0);
    printf("%s$ ",cwd);
    free(cwd);
}
void list_log(log_t *log){
    node *p=log->head;
    while(p){
        printf("%s\n",p->cmd);
        p = p->next;
    }
}
void parse_cd(){
    char *arg = strtok(NULL," ");
    if(strtok(NULL," ") != NULL){
        printf("bash: cd: too many arguments\n");
    }else{
        int res=chdir(arg);
        if(res){
           printf("%s: No such file or directory\n",arg); 
        }
    }
}
void parse_ls(char *cmd){
    system(cmd);
}
void parse_outer(char *path){
    int pid = fork();
    if(pid){
        waitpid(pid,NULL,0);
    }else{
        char* args[100];
        args[0] = path;
        int c=1;
        while((args[c]=strtok(NULL," ")) != NULL)c++;
        execv(path,args);
        printf("%s: no such command\n",path);
        exit(-1);
    }
}
int execute(char* buffer) {
    if(buffer==NULL || buffer[0]=='\0')
        return 1;
    if(buffer[0] == '!'){
        if(buffer[1] == '#'){
            list_log(&Log);
        }else{
            char *res=log_search(&Log,buffer+1);
            if(res==NULL){
                printf("No Match\n");
            }else{
                return execute(res);
            }
        }
    }else{
        log_push(&Log,buffer);
        char *tmp=strtok(buffer," ");
        if(match(tmp,"cd")){
            parse_cd();
        }else if(match(tmp,"exit")){
            return 0;
        }else if(match(tmp,"ls")){
            parse_ls(Log.tail->cmd);
        }else{
            parse_outer(tmp);
        }
    }
    return 1;
}
