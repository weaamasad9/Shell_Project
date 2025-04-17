#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#define BUF_SIZE 200

int main(int argc, char* argv[]) {
    int file1, fileSize; /* Input and size file */
    int rbytes1; /* Number of bytes read and written */
    char buffer1[BUF_SIZE]; /* Buffer for first file */
    char buffer2[BUF_SIZE]; /* Buffer for second file */

    /* Open  file */
    file1 = open(argv[1], O_RDONLY);
    if (file1 == -1) {
        perror("Error opening file ");
        exit(1);
    }
    
    fileSize = lseek(file1, 0, SEEK_END);
    
    lseek(file1, 0, SEEK_SET);
    printf("The size of the file is %d \n ", fileSize);
    /* Close file descriptors */
    close(file1);
    execl("shell3", "shell3", NULL); 
    perror("execl() failed");
    return 0;
}

