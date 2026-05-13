#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAXLINE 1024

int main(int argc, char* argv[]){

    char input[MAXLINE];
    char* args[MAXLINE/2+1];

    while(1){
        printf("shell> ");
        fflush(stdout);

        if(fgets(input, sizeof(input), stdin)==NULL){
            printf("\n");
            break;
        }   

        input[strcspn(input, "\n")] = '\0';

        if(strcmp(input, "exit")==0){
            break;
        }

        int i = 0;
        char *token = strtok(input, " ");

        while(token!=NULL){
            args[i++] = token;
            token = strtok(NULL," ");
        }
        args[i] = NULL;

        if(args[0]==NULL){
            continue;
        }

        if(strcmp(args[0], "cd")==0){
            char path[1024];
            if(args[1]==NULL || strcmp(args[1],"~")==0){
                snprintf(path, sizeof(path), "%s", getenv("HOME"));
            }else if(args[1][0]=='~'){
                snprintf(path, sizeof(path),"%s%s", getenv("HOME"), args[1]+1);
            }else{
                snprintf(path, sizeof(path), "%s", args[1]);
            }
            if(chdir(path)!=0){
                perror("cd failed");
            }
            continue;
        }

        pid_t pid = fork();

        if(pid<0){
            perror("Fork Failed\n");
            exit(1);
        }else if(pid ==0){
           if(execvp(args[0], args)<0){
                perror("Error");
                exit(1);
            }
        }else{
            wait(NULL);
        }


    }

    return 0;
}