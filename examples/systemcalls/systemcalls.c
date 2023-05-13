#include "systemcalls.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{

/*
 * TODO  add your code here
 *  Call the system() function with the command set in the cmd
 *   and return a boolean true if the system() call completed with success
 *   or false() if it returned a failure
*/
int process_status = -1; // default value to error state
bool system_status = false;
process_status = system(cmd);
if (cmd != NULL)
{
    if (process_status != -1)
    {
        if (WIFEXITED(process_status))
        {
            if (WEXITSTATUS(process_status) != 127)
            {
                system_status = true;
                printf("process successfully terminated\n");
            }
        }
        else
        {
            printf("process abnormaly terminated\n");
        }
    }
    else
    {
        printf("child process could not be created or its status could not  be retrieved\n");
    }
}
else
{
    if (process_status == 0)
    {
        system_status = true;
        printf("shell is available\n");
    }
    else
    {
        printf("no shell is available\n");
    }   
}

    return system_status;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int process_status = -1; // default value to error state
    int exit_status = 127; // default value to error state
    pid_t pid;
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
        printf("command[%d] is %s\n",i,command[i]);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];
    
    

/*
 * TODO:
 *   Execute a system command by calling fork, execv(),
 *   and wait instead of system (see LSP page 161).
 *   Use the command[0] as the full path to the command to execute
 *   (first argument to execv), and use the remaining arguments
 *   as second argument to the execv() command.
 *
*/
    
    fflush(stdout);
     pid = fork();

	if (pid == -1){
        printf("no child process is created\n"); 
	    return false;
    }
	else if (pid == 0) {
        int ret_value = 0;
		ret_value = execv(command[0], command);
        if (ret_value != -1){
            printf("no error occured at exec\n");
        }
        else
        {
            printf("Error happened in exec\n");
        }
        printf("from child that pid is %d\n",pid); 
        exit(-1);
	}

    va_end(args);

	if (waitpid(pid, &process_status, 0) == -1){
        printf("in error wait pid is %d\n", pid);
	    return false;
    }
	else if (WIFEXITED(process_status)) {
	    exit_status = WEXITSTATUS(process_status);
        printf("pid is %d\n", pid);
        printf("exit_status is %d\n",exit_status);
		if (exit_status == 0){
            printf("process successfully terminated with waitpid with pid %d\n", pid); 
		    return true;
        }
		else{
            printf("Abnormal termination\n");
		    return false;
        }
        
	} 
	else 
		return false;


    return true;
}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int process_status = -1; // default value to error state
    int exit_status = 127; // default value to error state
    pid_t pid;
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];


/*
 * TODO
 *   Call execv, but first using https://stackoverflow.com/a/13784315/1446624 as a refernce,
 *   redirect standard out to a file specified by outputfile.
 *   The rest of the behaviour is same as do_exec()
 *
*/

    int fd = open(outputfile, O_WRONLY|O_TRUNC|O_CREAT, 0644);
    if (fd < 0){
        printf("error in opening outpfile\n");
        return false;
    }
    fflush(stdout);
    pid = fork();

	if (pid == -1){
        printf("no child process is created\n"); 
	    return false;
    }
	else if (pid == 0) {
        int ret_value = 0;
        if (dup2(fd,1) < 0){
            printf("error in dup2\n");
        }
        close(fd);
		ret_value = execv(command[0], command);
        if (ret_value != -1){
            printf("no error occured at exec\n");
        }
        else
        {
            printf("Error happened in exec\n");
        }
        printf("from child that pid is %d\n",pid);
        exit(-1); 
	}

    va_end(args);

	if (waitpid(pid, &process_status, 0) == -1){
        printf("in error wait pid is %d\n", pid);
	    return false;
    }
	else if (WIFEXITED(process_status)) {
	    exit_status = WEXITSTATUS(process_status);
        printf("pid is %d\n", pid);
        printf("exit_status is %d\n",exit_status);
		if (exit_status == 0){
            printf("process successfully terminated with waitpid with pid %d\n", pid); 
		    return true;
        }
		else{
            printf("Abnormal termination\n");
		    return false;
        }
        
	} 
	else 
		return false;


    return true;

    return true;
}
