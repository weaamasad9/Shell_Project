#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#define MAX 100

void Error (char* msg) {
  printf("%s\n", msg);
  exit(1);
}

int main(int argc, char* argv[]) {
  int pid, status;
  char command[MAX], new_line[1] = "\n";
  char path[MAX] = "/bin/";
  int fd1 = open("history1.txt",O_WRONLY | O_CREAT, 0644);
  
  if (fd1 == -1)
    Error("Failed to open file");
  
  // we always add more commands to history file at the end of it beacuse we might be 
  // entering the shell with previous history of commands 
  lseek(fd1, 0, SEEK_END);
  
  while (1) {
    printf("Shell1$**");
    fgets(command, MAX, stdin);
    // removing the null character '\0' from the string
    command[strlen(command) - 1] = 0;
    
    if ((pid = fork()) == -1) 
      Error("fork() failed"); 
    
    if (pid == 0) {
      strcat(path, command);
       
      // we check if the character " " is in the command because if there is, the command 
      // is not supported becuase it is a command with parameters 
      if (strcspn(command, " ") < strlen(command))
      	exit(1); 
      if (!strcmp(command, "history"))
      	execl(command, command, "history1.txt", NULL); // runs the history.out file we made from history.c and sends the file name we store the history in as a parameter
      else
      	execl(path, command, NULL);
      	
      exit(1);
    }
    else {
      pid = wait(&status);
      
      // the value of status is zero when the command is supported and the 'execl()' in 
      // the child process ran successfully
      if (status == 0 || !strcmp(command, "Esc")) {
      	write(fd1, command, strlen(command)); 
    	write(fd1, new_line, 1);
      }
      //  if the user didn't enter anything nothing should happen
      else if (strlen(command) != 0 && strcmp(command, "Exit"))
      	printf("Not supported\n");
      
      // if the command is 'Esc' we should return to the main shell
      if (!strcmp(command, "Esc")) {
      	close(fd1);
        exit(1);
      }
    }
  }
  
  return 0;
}
