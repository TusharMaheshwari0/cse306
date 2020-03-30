//Design a program using concepts of inter-process communication ordinary pipes in which
one process sends a string message to a second process, and the second process reverses
the case of each character in the message and sends it back to the first process. For example,
if the first process sends the message Hi There, the second process will return hI tHERE.
This will require using two pipes, one for sending the original message from the first to the 
second process and the other for sending the modified message from the second to the first
process. You can write this program using either UNIX or Windows pipes.//


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
	char str[100];
	printf("enter the string :");
	int i=0;
	while(i<10){
	scanf("%c",&str[i]);
	i++;}
	int fd[2];	
	write(fd[1],str,strlen(str));
	printf("pid is %d for wiring in pipe - ",getpid());
	int y=strlen(str);
	printf("\n\n we have Written in pipe :%s\n",str);	
	for(i=0;i<strlen(str);i++)
		{
		if((int)str[i]>=65 && (int)str[i]<=90)
			{
				str[i]=(int)str[i]+32;
			
			}
		else if((int)str[i]>=97 && (int)str[i]<=122)
			{
				str[i]=(int)str[i]-32;
			
			}
		}
	close(fd[0]);
	read(fd[0],str,strlen(str));
	printf("\n\npid is %d for reading in pipe ",getpid());
	printf("\n\nreading from the file  :%s\n",str);
	
}
