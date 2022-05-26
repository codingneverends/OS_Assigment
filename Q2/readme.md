# Message Queue

    Problem
        Course Instructor will send mark to students and Teaching Assistants
        Student will recive marks
        Teaching Assistant sends back Grades of each student and total mark to Course Instuctor

    To Execute

        msg_ci.c - Course Instutor code
        msg_tr.c - Teaching Assistant Code
        msg_stu.c - Students Combined code
                    Each entries in a loop is a student
        
        gcc msg_ci.c -o ci.out
        gcc msg_stu.c -o stu.out
        gcc msg_tr.c -o tr.out
        
        After compiling ci.out,tr.out,stu.out will be generated

        ./ci.out
        Run ci.out in a terminal which will wait for tr to send report back.

        ./stu.out
        Run stu.out in another terminal , which will exectue completly by reciving data from ci.out.
        ./tr.out
        Run tr.out in the same terminal which ran stu.out , tr will send back grades to ci.
        Also ci.out will be terminated.

    Functions used

        int msgget(key_t key, int msgflg);
            Create and access a message queue, we use the msgget function.
            Parameters
                key     -   names a message queue in the system
                msgflg  -   assign permission to the message queue and is ORed with IPC_CREAT to create the queue if it doesn’t already exist.
            Returns
                1 on success
                -1 on failure

        int msgsnd(int msgid, const void *msg_ptr, size_t msg_sz, int msgflg);
            Allows us to add a message to the message queue
            Parameters
                msgid   -   message queue identifier returned by the msgget function.
                msg_ptr -   pointer to the message to be sent, which must start with a long int type.
                msg_sz  -   size of the message. It must not include the long int message type.
                msgflg  -   controls what happens if either the message queue is full or the system limit on queued messages is reached
            Returns
                0 on success and place the copy of message data on the message queue.
                -1 on failure
            
        int msgrcv(int msgid, void *msg_ptr, size_t msg_sz, long int msgtype, int msgflg);
            Retrieves messages from a message queue.
            Parameters
                msgid   -   message queue identifier returned by the msgget function.
                msg_ptr -   pointer to the message to be received, which must start with a long int type.
                msg_sz  -   size of the message. It must not include the long int message type.
                msgtype -   allows implementing priority.
                msgflg  -   controls what happens if either the message queue is full or the system limit on queued messages is reached
            Returns
                0 on success
                -1 on failure

        int msgctl(int msgid, int command, struct msgid_ds *buf);
            Control function
            Parameters
                msgid   -   parameter is the identifier returned by msgget function. The second parameter can have one out of the below three values
                Commands
                    IPC_STAT	Sets the data in the msqid_ds structure to reflect the values associated with the message queue.
                    IPC_SET	If the process has permission to do so, this sets the values associated with the message queue to those provided in the msqid_ds data structure.
                    IPC_RMID	Deletes the message queue.

            Returns
                0 on success
                -1 on error
