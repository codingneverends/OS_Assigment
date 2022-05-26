# Pipe

    Problem     
        String ? Weak or Strong
        number of alphanum > Number of special characters --> Weak

    To execute

        gcc pipc.c
        ./a.out

    Functions used

        int pipe(int pipefd[2]);

            Parameters :
                fd[0] will be the fd(file descriptor) for the 
                read end of pipe.
                fd[1] will be the fd for the write end of pipe.
            Returns : 
                0 on Success
                -1 on error.
        int fork()

            Returns :
                Negative Value  : creation of a child process was unsuccessful.
                Zero            : Returned to the newly created child process.
                Positive value  : Returned to parent or caller. The value contains process ID of newly created child process. 