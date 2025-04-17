#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define SIZE 200

int main(int argc, char* argv[]) {
    char commandChoice[SIZE];
    int pid, status;
     
    while(1) {
		//showing list
        printf("Enter <shell1> to run linux commands without parameters\n");
		printf("Enter <shell2> to run linux commands with parameters\n");
		printf("Enter <shell3> to run commands to file editing\n");
		printf("Shell$**");
		fgets(commandChoice, SIZE, stdin);
		// removing the null character '\0' from the string
        commandChoice[strlen(commandChoice) - 1] = 0;
	 
	 
		if( (pid = fork()) == -1)
			perror("Fork failed"); //check if the proccess succefuly created
		if (pid == 0) {
			// son's proccess check which shill was chosen else it's not supported
			if (!strcmp(commandChoice, "shell1") || !strcmp(commandChoice, "shell2") || !strcmp(commandChoice, "shell3")) {
				execl(commandChoice, commandChoice, NULL);
                perror("execl() failed");}
				//  if the user didn't enter anything nothing should happen and the command
				//  Exit should be supported
            else if (strlen(commandChoice) > 0 && strcmp(commandChoice, "Exit")){
				printf("Not Supported\n"); } 
      	    exit(1);  
		}
		else{
			pid = wait(&status);  //parent proccess
			if (!strcmp(commandChoice, "Exit")) 
				exit(1);      
		}
    }
     
     return 0;  
}

