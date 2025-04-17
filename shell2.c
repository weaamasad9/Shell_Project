#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
#define MAX 256
#define MAX_ARGS 20

// Function that prints an error massage and exits the program
void Error (char* msg) {
	fprintf (stderr, "%s\n", msg);
	exit (1);
}

int main(int argc, char* argv[]){
	int pid, status;
	char command[MAX], original[MAX] , *firstComm, new_line[1] = "\n";
	char *args[MAX_ARGS];
	char path[MAX] = "/bin/";
	int fd2;
	// Open history2 file or create it if it does not exist
	if ((fd2=open("history2.txt",O_WRONLY | O_CREAT, 0644)) == -1)
		Error ("Failed to open file history 2");

	// we always add more commands to history file at the end of it beacuse we might be 
  	// entering the shell with previous history of commands 
	lseek(fd2, 0, SEEK_END);
	
	while (1) {
		// The prompt
		printf ("Shell2$**");
		fgets (command, MAX, stdin);
		command [strlen(command) - 1] = 0; // Removing the null character '\0' from the string
		strcpy(original, command); // Save original input to use later
		// Exteract the first word (the command) from the input
		firstComm = strtok(command, " ");
		// If the user didn't type anything - show prompt again
		if (strlen(original) == 0){
			continue;
		}
		// To check if the input have no parameters
		/*if (strcmp(firstComm, "Esc") != 0 && strcmp(firstComm, "history") != 0) {
			printf ("!!!Missing parametrs\n");
			continue;
		}*/
		// Split the input into command and it's parameters, and store them in an array
		args[0] = firstComm;
		int i=1;
		char *help = strtok(NULL, " ");
		while ((help !=NULL) && (i<MAX_ARGS - 1)) {
			args[i++] = help;
			help = strtok(NULL, " ");
		}
		args[i] = NULL; // To end the args array with NULL

		if ((pid = fork()) == -1)
			Error("fork() failed");
		// Child process
		if (pid == 0) {
			strcpy(path, "/bin/");
			strcat(path, firstComm);
			// If command is "history", execute with parameter "history2.txt"
			if (!strcmp(firstComm, "history"))
				execl(firstComm, firstComm, "history2.txt", NULL);
			// Execute the command using the args array
			else if (strchr(original , ' ') != NULL)
				execv( path, args);
			// If exec fails, then exit the child process with error code 3
			exit (3);
		}
		// Parent process
		else {
			pid = wait(&status);
			for (int i = MAX_ARGS; i < MAX_ARGS; i++)
				args[i] = NULL;
			// If the command ran successfully or it was "Esc", then write it to the history file
			if (WEXITSTATUS(status) != 3 || !strcmp(firstComm, "Esc") || strchr(original , ' ') != NULL) {
				write(fd2, original, strlen(original));
				write(fd2, new_line, 1);
			}
			// If the command is not supported or didn't work
			else
				printf("Not supported\n");
     		// If the command is 'Esc' we should return to the main shell
			if (!strcmp(firstComm,"Esc")) {
				close(fd2);
				exit(1);
			}
		}	
		
	}
	return 0;
}
