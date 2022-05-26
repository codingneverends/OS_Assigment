#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<ctype.h>
int main()
{
    int fd[2][2],n;
    char buffer[100],buffer_[100];
    for(int i=0;i<2;i++)
        if(pipe(fd[i])<0){
            printf("Error in create pipe %d",i);
            return 0;
        }
    pid_t pid1=fork();
    if(pid1<0){
        printf("Error in first fork");
        return 0;
    }
    if(pid1==0){
        close(fd[0][0]);
        close(fd[1][0]);
        close(fd[1][1]);
        //printf("Child process 1\n");
        printf("Enter string : ");
        scanf("%s",buffer);
        write(fd[0][1],buffer,strlen(buffer));
        close(fd[0][1]);
        return 0;
    }
    pid_t pid2=fork();
    if(pid2<0){
        printf("Error in second fork");
        return 0;
    }
    if(pid2==0){
        waitpid(pid1,NULL,0);
        close(fd[0][1]);
        close(fd[1][0]);
        //printf("Child process 2\n");
        n=read(fd[0][0],buffer,100);
        int x=strlen(buffer);
        int _alnum,_special;
        for(int i=0;i<x;i++){
            if(isalnum(buffer[i]))
                _alnum++;
            else
                _special++;
        }
        write(fd[1][1],&_alnum,sizeof(int));
        write(fd[1][1],&_special,sizeof(int));
        close(fd[1][1]);
        close(fd[0][0]);
        return 0;
    }

    //Parent Process
    close(fd[0][0]);
    close(fd[0][0]);
    close(fd[1][1]);
    int p_alnum,p_special;
    read(fd[1][0],&p_alnum,sizeof(int));
    read(fd[1][0],&p_special,sizeof(int));
    if(p_alnum>=p_special){
        printf("Weak\n");
    }
    else{
        printf("Strong\n");
    }
    close(fd[1][0]);
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);
}