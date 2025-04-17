#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX 100

int main(int argc, char* argv[]) { 
  char buff[MAX];
  // if shell1 ran execl() on 'history' then we need to open history1.txt file which shell1 will 
  // send as a parameter to 'history' if it's shell2 it will be history2.txt file
  int fd = open(argv[1],O_RDONLY);
  
  while(read(fd, buff, MAX))
    printf("%s", buff);
  
  // the last command that was made is 'history' and it will be added to the text file after
  // the child process ends in the present shell but for now it is still not added so we print it.
  printf("history\n");
 
  return 0;
}
