#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define BUF_SIZE 200


//this function just for readinf a word it's stop in a new line or space
int readFromFile(int file, char * word){
    char oneChar;
    int len = 0;
    while (read(file, &oneChar, 1) == 1) { // this loop to chek one index 
        if (oneChar == ' ' || oneChar == '\n') {
            if (len > 0){ break;} 
            else{ continue;}      
        }
        if (len < BUF_SIZE - 1) {
            word[len++] = oneChar;
        }
    }
    word[len] = '\0';
    return len;
}
int main(int argc, char* argv[]) {
    int file1, file2, file3; /* Input and size file */
    int rbytes1, rbytes2; /* Number of bytes read and written */
    char wordFile1[BUF_SIZE], wordFile2[BUF_SIZE]; /* Buffers for  files */
   
    /* Open  file */
    file1 = open(argv[1], O_RDONLY);
    if (file1 == -1) {
        perror("Error opening file ");
        exit(1);
    }
    
    /* Open  file  2*/
    file2 = open(argv[2], O_RDONLY);
    if (file2 == -1) {
    	close(file1);
        perror("Error opening file ");
        exit(1);
    }
    
    if(argc == 4){
		file3 = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0664); // if 4 paramets we have 3 files!
		
		if(file3 == -1){
			close(file1);
			close(file2);
			perror("Error opening file ");
			exit(1);
		}
    }

    while(1)
    {
		rbytes1 = readFromFile(file1, wordFile1); //reading word from file1
		rbytes2 = readFromFile(file2, wordFile2);//reading word from file2
		
		if (rbytes1 > 0) {
			if(argc == 4){
				/*if we have 3 files we should write to file3 word from file1, and from file 2 one by one */
				write(file3, wordFile1, rbytes1); 
				write(file3, " ", 1);
			}
			else 
				printf("%s ", wordFile1);
		}

		if (rbytes2 > 0) {
			if(argc == 4){
				/*if we have 3 files we should write to file3 word from file1, and from file 2 one by one */
				write(file3, wordFile2, rbytes2);
				write(file3, " ", 1);
			}
			else
				printf("%s ", wordFile2);
		}


		if (rbytes1 <= 0 && rbytes2 <= 0) //end of the both files
			break;
    }
    


    /* Close file descriptors */
    close(file1);
    close(file2);
    if(argc == 4)
		close(file3);
	
    return 0;
}

