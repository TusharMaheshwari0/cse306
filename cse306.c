//importing libraries for we need 
#include <string.h> 
#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>
#include <iostream> 

using namespace std;

int main()
{
    pid_t pid;
    //declaring an array of characters with size 4096 
   //in case the user's input is long
    char buffer[1024];
    //fdOne[0] will be used for reading
    //fdOne[1] will be for writing
    //declaring variable for storing the two ends of first pipe
    int fdOne[2];
    //declaring variable for storing the two ends of second pipe 
    int fdTwo[2];
    //pipe() system call is used for passing information from one process to another
    pipe(fdOne);
    if (pipe(fdOne)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    pipe(fdTwo);
    if (pipe(fdTwo)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    }
    //forking the process
    pid = fork();
     if (pid < 0) 
    { 
        fprintf(stderr, "Fork Failed" ); 
        return 1; 
    } 
    // fork returns to parent the pid of the child
    if (pid > 0) 
    {
       
        int i;
        // Close writing end of first pipe
        close(fdOne[1]); 
        //read from the pipe 
        read(fdOne[0], buffer, sizeof(buffer));
        for(i = 0; i<sizeof(buffer); i++) {
            if(islower(buffer[i]))
                buffer[i] = toupper(buffer[i]);
            else
                buffer[i] = tolower(buffer[i]);
        }
        write(fdTwo[1], buffer, strlen(buffer) + 1);
       // Wait for child to send a string 
        wait(NULL); 
        
    }else if (pid == 0){
 
        
        // Close reading end of first pipe 
        close(fdOne[0]); 

        //ask user input */
        printf("input: ");
        fgets(buffer, sizeof(buffer), stdin);
        printf("The original message is %s", buffer);

        //write to the pipe 
        write(fdOne[1], buffer, strlen(buffer) + 1);
        read(fdTwo[0], buffer, sizeof(buffer));
        printf("The inverted message is %s",buffer);

        exit(0);
    }

    return 0;
}
