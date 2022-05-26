#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX_SIZE 512   
#define MSG_KEY 12345
struct msg_to_student{
    long int type;
    int mark;
};
struct student{
    long int msg_id;
    int msg_key;
    struct msg_to_student data;
};
struct student recive_msg(struct student stu){
    int running=1;
    int msgid;
    struct msg_to_student some_data;
    long int msg_to_rec=0;
    msgid=msgget((key_t)(stu.msg_key),0666|IPC_CREAT);
    while(running)
    {
        msgrcv(msgid,(void *)&some_data,sizeof(struct msg_to_student),msg_to_rec,0);       
        running=0;
    }
    //msgctl(msgid,IPC_RMID,0);
    stu.data=some_data;
    return stu;
}

int main()
{
    struct student students[5];
    printf("\nGetting marks from ci\n");
    for(int i=0;i<5;i++){
        students[i].msg_key=12340+i;
        students[i]=recive_msg(students[i]);
        printf("Mark of %d student is %d \n",i+1,students[i].data.mark);
    }
    int running=0;
    while(running)
    {
        //Do Nothing
    }
}           