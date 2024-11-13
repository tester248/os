//Inter process communication in Linux using Pipes
//Pipes: Full duplex communication between parent and child processes. Parent process writes
//a pathname of a file (the contents of the file are desired) on one pipe to be read by child
//process and child process writes the contents of the file on second pipe to be read by parent
//process and displays on standard output.
#include<stdio.h>
#include<unistd.h>
#include<iostream>
using namespace std;


int main() {
   int pipefds1[2],pipefds2[2];
   int returnstatus1, returnstatus2;
   int pid;
   char pipe1writemessage[20]="Hi";
   char pipe2writemessage[20]="Hello";
 
   char readmessage[20];
   returnstatus1 = pipe(pipefds1);
   
   if (returnstatus1 == -1) {
      cout << "Unable to create pipe 1\n";
      return 1;
   }
     returnstatus2 = pipe(pipefds2);
   if (returnstatus2 == -1) {
      cout << "Unable to create pipe 2\n";
      return 1;
   }
    pid=fork();
    if(pid!=0) //parent process
    {
    	close(pipefds1[0]); // Close the unwanted pipe1 read side
      	close(pipefds2[1]); // Close the unwanted pipe2 write side
    	
   		cout << "In Parent Process: writing to pipe1 – Message  is :  " << pipe1writemessage <<"\n";
		write(pipefds1[1], pipe1writemessage, sizeof(pipe1writemessage));
		read(pipefds2[0], readmessage, sizeof(readmessage));
  		cout << "In Parent Process: Reading from pipe 2– Message  is :" << readmessage << "\n";
	} else //child process
	{
		close(pipefds1[1]); // Close the unwanted pipe1 read side
      	close(pipefds2[0]); // Close the unwanted pipe2 write side
	   
	   read(pipefds1[0], readmessage, sizeof(readmessage));
	   cout <<"In child Process: Reading from pipe1 - Message is :" << readmessage <<"\n";
   	     
  	   cout << "In Child Process : Writing to pipe 2 - Message is : "<< pipe2writemessage << "\n";
   	   write(pipefds2[1], pipe2writemessage, sizeof(pipe2writemessage));
    }
   return 0;
}
