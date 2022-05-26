#include<stdio.h>
#include<stdlib.h>
int main(){
    int p,r,**allocated,**maxresoursesforprocess,*maxresourses;
    int *remainingresourses,*solvedremainingresourses,**remainingresoursesneedforprocess,*initialremainingresourses;
    printf("Enter no of process : ");
    scanf("%d",&p);
    printf("Enter no of resourses : ");
    scanf("%d",&r);
    allocated=(int**)malloc(p*sizeof(int*));
    maxresoursesforprocess=(int**)malloc(p*sizeof(int*));
    maxresoursesforprocess=(int**)malloc(p*sizeof(int*));
    remainingresoursesneedforprocess=(int**)malloc(p*sizeof(int*));
    maxresourses=(int*)malloc(sizeof(int)*r);
    remainingresourses=(int*)malloc(sizeof(int)*r);
    solvedremainingresourses=(int*)malloc(sizeof(int)*r);
    initialremainingresourses=(int*)malloc(sizeof(int)*r);
    int* initialmaxused=(int*)malloc(r*sizeof(int));
    int *track=(int*)malloc(p*sizeof(int));
    int *order=(int*)malloc(p*sizeof(int));
    int *_order=(int*)malloc(p*sizeof(int));
    for(int i=0;i<p;i++){
        allocated[i]=(int*)malloc(r*sizeof(int));
        maxresoursesforprocess[i]=(int*)malloc(r*sizeof(int));
        remainingresoursesneedforprocess[i]=(int*)malloc(r*sizeof(int));
        track[i]=0;
    }
    for(int i=0;i<p;i++){
        printf("Enter allocated no of resourses need for process %d seperated by space: ",i+1);
        for(int j=0;j<r;j++){
            scanf("%d",&allocated[i][j]);
        }
        printf("Enter max no of resourses need for process %d seperated by space: ",i+1);
        for(int j=0;j<r;j++)
            scanf("%d",&maxresoursesforprocess[i][j]);
    }
    printf("Enter max resourses of system seperated by space : ");
    for(int i=0;i<r;i++){
        initialmaxused[i]=0;
        scanf("%d",&maxresourses[i]);
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<p;j++){
            initialmaxused[i]+=allocated[j][i];
        }
        remainingresourses[i]=maxresourses[i]-initialmaxused[i];
        //printf("%d ",remainingresourses[i]);
    }
    for(int i=0;i<p;i++){
        //printf("\nprocess %d - ",i+1);
        for(int j=0;j<r;j++){
            remainingresoursesneedforprocess[i][j]=maxresoursesforprocess[i][j]-allocated[i][j];
            //printf("%d ",remainingresoursesneedforprocess[i][j]);
        }
    }
    for(int i=0;i<r;i++){
        initialremainingresourses[i]=remainingresourses[i];
    }
    int safe_sequece_test=1,safe_sequece=0;
    int order_=0;
    while(safe_sequece_test){
        for(int i=0;i<p;i++){
            int completion=0;
            for(int j=0;j<p;j++){
                completion+=track[j];
            }
            if(completion==p){
                safe_sequece=1;
                safe_sequece_test=0;
                break;
            }
            if(track[i]==1)
                continue;
            int _execute=0;
            for(int j=0;j<r;j++){
                //printf("\ncheck -- %d -- %d %d",j+1,remainingresoursesneedforprocess[i][j],remainingresourses[j]);
                if(remainingresoursesneedforprocess[i][j]>remainingresourses[j]){
                    _execute=0;
                    break;
                }
                if(j==r-1){
                    _execute=1;
                }
            }
            if(_execute==1){
                track[i]=1;
                order[order_]=i+1;
                order_++;
                //printf("\nprocess %d executing ",i+1);
                for(int j=0;j<r;j++){
                    //printf("%d %d ",remainingresourses[j],allocated[i][j]);
                    remainingresourses[j]+=allocated[i][j];
                    //printf("%d - ",remainingresourses[j]);
                }
                break;
            }
            else{
                if(i==p-1){
                    safe_sequece_test=0;
                }
            }
        }
    }
    if(!safe_sequece){
        printf("\nNot Safe State\n");
        exit(0);
    }
    for(int i=0;i<r;i++){
        solvedremainingresourses[i]=remainingresourses[i];
    }
    int run=1;
    while (run)
    {
        char option;
        printf("\n\n\t-----Bank Algo Menu-----\n\ta)print safe state\n\tb)check sequence\n\tc)request new process\n\td)terminate\n\nEnter choice : ");
        scanf("\n%c",&option);
        printf("\n");
        if(option=='a'||option=='A'){
            if(safe_sequece){
                printf("Safe state is : ");
                for(int i=0;i<p;i++)
                    printf("%d ",order[i]);
            }
            else{
                printf("No safe sequence");
            }
            printf("\n");
        }
        else if (option=='b'||option=='B')
        {
            for(int i=0;i<r;i++){
                remainingresourses[i]=initialremainingresourses[i];
            }
            printf("Enter your sequence order to be checked seperated by space : ");
            for(int i=0;i<p;i++){
                scanf("%d",&_order[i]);
            }
            int _safe_sequece_test=1,_safe_sequece=1;
            for(int i=0;i<p;i++){
                int _index=_order[i]-1;
                int _execute=0;
                for(int j=0;j<r;j++){
                    if(remainingresoursesneedforprocess[_index][j]>remainingresourses[j])
                        break;
                    if(j==r-1){
                        _execute=1;
                    }
                }
                if(_execute==1){
                    //printf("\nprocess %d executing ",i+1);
                    for(int j=0;j<r;j++){
                        //printf("%d %d ",remainingresourses[j],allocated[i][j]);
                        remainingresourses[j]+=allocated[_index][j];
                        //printf("%d - ",remainingresourses[j]);
                    }
                }
                else{
                    _safe_sequece=0;
                    break;
                }
            }
            
            if(_safe_sequece){
                printf("It is Safe State");
            }
            else{
                printf("It is not Safe State");
            }   
        }
        else if (option=='c'||option=='C')
        {
            for(int i=0;i<r;i++){
                remainingresourses[i]=solvedremainingresourses[i];
            }
            int deadlock=0;
            int *n_alloc=(int*)malloc(sizeof(int)*r);
            int *n_max=(int*)malloc(sizeof(int)*r);
            printf("Enter allocated no of resoures for new process seperated by space : ");
            for(int i=0;i<r;i++){
                scanf("%d",&n_alloc[i]);
                remainingresourses[i]-=n_alloc[i];
                //printf("%d ",remainingresourses[i]);
            }
            printf("Enter max no of resoures for new process seperated by space : ");
            for(int i=0;i<r;i++){
                scanf("%d",&n_max[i]);
                if(n_max[i]>remainingresourses[i]){
                    deadlock=1;
                }
            }
            if(deadlock){
                printf("Cannot be granted");
            }
            else{
                printf("It can be Granted");
            }
        }
        else if(option=='d'||option=='D'){
            run=0;
            break;
        }
        else{
            printf("Invalid option ..!\n");
        }
    }
    return 0;
}

/*

5
3
0 1 0
7 5 3
2 0 0
3 2 2
3 0 2
9 0 2
2 1 1
4 2 2
0 0 2
5 3 3
10 5 7

*/
/*

5
4
0 0 1 2
0 0 1 2
1 0 0 0
1 7 5 0
1 3 5 4
2 3 5 6
0 6 3 2
0 6 5 2
0 0 1 4
0 6 5 6
3 14 12 12

*/