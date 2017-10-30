#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int rand() {
  int fd = open("/dev/random", O_RDONLY);

  if(fd) {
    int random;
    read(fd, &random, sizeof(int));
    return random;
  }
  return 0;
}

int main() {
  int i;

  printf("Generating numbers.\n");
  int arr[10];
  for (i = 0; i < 10; i++) {
    arr[i] = rand();
    printf("array1[%d] is %d\n", i, arr[i]);
  }

  printf("Writing array to file\n");
  int fd = open("random_ints", O_CREAT | O_WRONLY | O_TRUNC, 0600);

  if(fd){
    write(fd, arr, sizeof(arr));
  }
  else strerror(errno);
  
  close( fd );
  printf("Read from file\n");
  fd = open( "random_ints", O_RDONLY, 0 );
  int arr2[10];
  if( fd ){
    read( fd, arr2, sizeof(arr2));
    for( i = 0; i < 10; i++ ){
      printf("array2[%d] is %d\n", i, arr2[i]);
        }
  }
  else  strerror(errno);
  return 0;
}
