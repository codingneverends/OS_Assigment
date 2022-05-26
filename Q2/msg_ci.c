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
struct student sent_msg(struct student stu){
    stu.msg_id=msgget((key_t)stu.msg_key,0666|IPC_CREAT);
    if(stu.msg_id==-1){
        printf("Error in creating queue\n");
        exit(0);
    }
    if(msgsnd(stu.msg_id,(void *)&(stu.data), sizeof(struct msg_to_student),0)==-1) 
    {
        printf("Msg not sent\n");
    }
    if(msgsnd(stu.msg_id,(void *)&(stu.data), sizeof(struct msg_to_student),0)==-1) 
    {
        printf("Msg not sent\n");
    }
    return stu;
}
void get_report(){
    int running=1;
    int msgid;
    struct msg_from_ta some_data;
    long int msg_to_rec=0;
    msgid=msgget((key_t)54321,0666|IPC_CREAT);
    while(running)
    {
        msgrcv(msgid,(void *)&some_data,sizeof(struct msg_from_ta),msg_to_rec,0);                 
        printf("\nClass Average : %f\nGrades : ",some_data.avg);
        for(int i=0;i<5;i++){
            printf("\n\tGrade of student %d is %c ",i+1,some_data.grades[i].value);
        }
        printf("\n");
        running=0;   
    }
    msgctl(msgid,IPC_RMID,0);
}
int main()
{
    struct student students[5];
    printf("\nSending marks to students ..\n\n");
    for(int i=0;i<5;i++){
        students[i].msg_key=12340+i;
        students[i].data.mark=32+4*i;
        students[i].data.type=1;
        students[i]=sent_msg(students[i]);
    }
    printf("\nGetting report from tr\n");
    get_report();
}           