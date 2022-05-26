#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX_SIZE 512   
#define MSG_KEY 12345
struct grade{
    int id;
    char value;
};
struct msg_to_student{
    long int type;
    int mark;
    char grade;
};
struct student{
    long int msg_id;
    int msg_key;
    struct msg_to_student data;
};
struct msg_from_ta{
    long int type;
    float avg;
    struct grade grades[5];
};
char getgrade(int mark){
    mark=2*mark;
    if(mark>=90)
        return 'S';
    if(mark>=80)
        return 'A';
    if(mark>=70)
        return 'B';
    if(mark>=60)
        return 'C';
    if(mark>=50)
        return 'D';
    return 'E';
}
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
    msgctl(msgid,IPC_RMID,0);
    some_data.grade=getgrade(some_data.mark);
    stu.data=some_data;
    return stu;
}

void sent_report(int totalmark,struct grade* grades){
    struct msg_from_ta msg;
    msg.avg=(float)totalmark/5;
    for(int i=0;i<5;i++){
        msg.grades[i]=grades[i];
        //printf("%c",grades[i].value);
    }
    int msg_id=msgget((key_t)54321,0666|IPC_CREAT);
    if(msg_id==-1){
        printf("Error in creating queue\n");
        exit(0);
    }
    if(msgsnd(msg_id,(void *)&(msg), sizeof(struct msg_from_ta),0)==-1) 
    {
        printf("Msg not sent\n");
    }
}
int main()
{
    struct student students[5];
    int totalmark=0;
    struct grade grades[5];
    printf("\nGetting student marks\n");
    for(int i=0;i<5;i++){
        students[i].msg_key=12340+i;
        students[i]=recive_msg(students[i]);
        totalmark+=students[i].data.mark;
        grades[i].id=i;
        grades[i].value=getgrade(students[i].data.mark);
    }
    printf("\nSending report to ci\n");
    sent_report(totalmark,grades);
    //printf("OK");
}           