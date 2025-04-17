#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#define MAX 100

int main() {
  int pid, status;
  char command[MAX];
  char *args[5]; 
  int argc;
  while (1) {
    printf("Shell3$**");
    fgets(command, MAX, stdin);
    // removing the null character '\0' from the string
    command[strlen(command) - 1] = 0;
    char *token = strtok(command, " ");
    while (token && argc < 5) {  //in algortim to split string with spaces into list of words
        args[argc++] = token;
        token = strtok(NULL, " ");
    }
	 	 
    if ((pid = fork()) == -1)  // check the son's procces status 
        perror("Fork failed");
    
    if (pid == 0) {
        if (!strcmp(args[0], "Merge")) {   /* son's proccess check accroading to the input Merge(2 files or 3 files, Size of the file, Delete an file else it's not supported*/
            if (args[4] != NULL)
             	printf("Too much parameters"); 
            else if (args[3]!= NULL) {
				execl("Merge", "Merge", args[1], args[2], args[3],  NULL);
				perror("execl() failed");
			}
			else if (args[2] != NULL) {
				execl("Merge", "Merge", args[1], args[2],  NULL);
				perror("execl() failed");
			}
			else
				printf("Missing parameters!!!");
		}
        else if (!strcmp(args[0], "Size")) {
			if (args[1] != NULL && args[2] == NULL)
				execl("Size", "Size", args[1],  NULL);
			else
				printf("Invalid parameters");
        }
        else if (!strcmp(args[0], "Delete")) {
			if (args[1] != NULL && args[2] == NULL)
				execl("Delete", "Delete", args[1],  NULL);
            else
				printf("Invalid parameters");
        }    
        else if (strcmp("Esc", command))
            printf("Not Supported\n");
            
        exit(1);
    }
    else {
		pid = wait(&status); //parent's proccess
		printf("\n");
      
		// clearing the array
		for (int i = 0; i < 5; i++)
			args[i] = NULL;
      	 
      
		if(!strcmp("Esc", command))  // if the command is 'Esc' we should return to the main shell
			exit(1);
	  
		argc = 0;
    }
  }
  
  return 0;
}
