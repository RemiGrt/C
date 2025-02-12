#include <stdio.h>

void main(){
  FILE *fptr;

  // Open a file in read mode
  fptr = fopen("./test.log", "r");

  //
  static long const max_len = 200;


 
  // Store the content of the file
  char myString[max_len];

  // If the file exist
  if(fptr != NULL) {

  // Read the content and print it
  //  while(fgets(myString, 100, fptr)) {
  //  printf("%s", myString);
  // }
  fseek(fptr,-max_len, SEEK_END);
  //ssize_t len = read(fptr,  myString, max_len);
  myString[max_len]='\0';
    // Read the content and print it
  while(fgets(myString, max_len, fptr)) {

    if(myString == "iter")
      printf("trouve");

    

    //printf("%s", myString);
    for(int i=0;i<10;i++)
      printf("%c", myString[i]);
    
    printf("\n");
  }
  
  
  // If the file does not exist
 } else {
  printf("Not able to open the file.");
 }

// Close the file
 fclose(fptr);
}
