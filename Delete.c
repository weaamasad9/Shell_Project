#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define MAX 200

int main(int argc, char* argv[]) {
    int pid, file1, status; /* Input and size file */
    char path[MAX] = "/bin/";
    
    /* Open  file */
    file1 = open(argv[1], O_RDONLY);
    if (file1 == -1) {
        perror("Error opening file ");
        exit(1);
    }
    close(file1);
    
    //creating proccess
    if ((pid = fork()) == -1){
      perror("fork() failed");}
      
    if (pid == 0) { /// son's proccess
      
       execl("/bin/rm", "rm", argv[1], NULL);
       perror("execl() failed");
       exit(1);
    }
    else {
      pid = wait(&status);} //parents
      
    printf("File deleted\n");
    execl("shell3", "shell3", NULL); 
    perror("execl() failed");
    
    return 0;
}

