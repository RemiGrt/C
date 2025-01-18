#include <stdio.h>
#include <string.h>

int main(){

  char str[]="Hello, my name is what";
  char *pb;
  puts(str);
  
  
  pb=memset(str,'A',sizeof(int));

  puts(pb);


}
