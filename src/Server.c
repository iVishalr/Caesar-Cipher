//Program which contains functions for encryption and decryption using ceaser cipher algorithm
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<ctype.h>
#include "Server.h"
//To use terminal commands we create a function called system
int system(const char* command);

void readInput(unsigned char * message, int * shift){
  //reads the input message for encryption or decryption
  char character=' '; //Used for error handling
  int index = 0;
  int isAlphabet=0;
  cleanSTDIN();
  Message:
  while(character){
    character=getchar();
    if(isAlphabet==0 && isalpha(character))
      isAlphabet=1;
    //Checks if the user has entered a message
    if(character=='\n' && index==0){ 
      printf("\n Please enter a valid message\n\n ");
      sleep(1500);
      printf("Message : ");
      //If the user has not entered any messsage then we re-execute this section
      //so that user is forced to enter a message before proceeding.
      goto Message; 
    }
    else if(character=='\n')
      break;
    message[index++] = character; 
  }
  if(!isAlphabet){
    printf("\n NOTE : The message entered has no alphabets in it.\n\tTherefore there will be no changes in the final message.\n ");
  }
  //message[strlen((const char *)message)] = '\0';
  Shift:
  //Asks the user to enter the shift or the off-set which is needed for encryption or decryption
  /*
    For decryption using brute force method, we call this function by passing
    a 0 for the shift argument. This is because brute force method automatically 
    shifts the characters. So there's no need for the user to enter shift.
  */
  if(shift){
    printf("\n Enter the Shift : ");
    if(scanf("%d",shift)!=1) {
      printf("\n Please enter a numeric value.\n ");
      sleep(1500);
      cleanSTDIN();
      goto Shift;
    }
  }
}

void displayMessage(unsigned char * message){
  //To display the encrypted/decrypted message
  putchar(' ');
  for(int i=0;i<strlen((const char*)message);i++)
    putchar(message[i]);
  putchar('\n');
}

void displayMessageBF(unsigned char ** bruteForceCombinations,int messageSize){
  //To display all possible combinations of the message.
  //Used only for brute force method. 
  printf("\n All possible combination of the message have been listed below : \n\n");
  for(int i=0;i<52;i++){
    printf(" Pass %d -> Message : ",i+1);
    for(int j=0;j<messageSize;j++){
      printf("%c",bruteForceCombinations[i][j]);
    }
    putchar('\n');
  }
  putchar('\n');
}

void sleep(int milliseconds) {
  //Function to create a time delay. Mimicks thread.sleep() of Java
  unsigned int duration = time(0) + (milliseconds/1000);
  while(time(0)<duration);
}

void encryptMessage(unsigned char * message, int shift) {
  //Function to Encrypt the message based on the shfit entered by user.
  unsigned char alphabetSet[52];
  getAlphabetSet(alphabetSet); //Generates an alphabet set from a to z including uppercase and lowercase.
  int lengthOfMessage = strlen((const char*)message);
  /*
  Encryption
  ----------
  A message is taken as input.
  We then iterate through the message
  If the character is an alphabet
    - We get the position of that alphabet in the alphabet set we generated
      and we add the shift entered by the user.
    - On adding the shift, if the (aplhabet index + shift) goes out of range i.e 52,
      we need to come to the first position of the alphabet set and add the remaining shift
    - That's why we perform MOD 52. This gives the remainder of (aplhabet index + shift)
    - Now we replace the character with a character from the alphabet set using the new
      position.
  If the character is not an aplhabet
    - We just add it to the output message as it is.
  */
  for(int i=0; i<lengthOfMessage;i++){
    if((message[i]>='A' && message[i]<='Z') || (message[i]>='a' && message[i]<='z')){
      int characterPosition = getAlphabetIndex(alphabetSet,message[i]);
      int shiftedPosition = (characterPosition + shift) % 52;
      if(shiftedPosition<0 && shift<0)
        shiftedPosition += 52;
      message[i] = alphabetSet[shiftedPosition];
    }
    else
      continue;
  }
}

void decryptMessage(unsigned char * message, int shift) {
  //Function to decrypt a message
  //Decryption
  /*
  This process is same as encryption
  During decryption we just perform downsift of characters.
  So we just make the shift negative.
  */
  shift = shift * -1;
  encryptMessage(message,shift);
}

void bruteForce(unsigned char * message, unsigned char ** bruteForceCombinations) {
  //Function to decrypt using brute force
  int shift = 0;
  for(int i=0;i<52;i++){
    if(i>0)
      shift=1;
    decryptMessage(message,shift);
    parseMessageBF(message,bruteForceCombinations[i]);//Used to store the message in 2d array
  }
}

void getAlphabetSet(unsigned char * alphabetSet){
  //Function to generate Alphabet Set
  int index = 0;
  for(int i = 0; i<26 ; i++)
    alphabetSet[index++] = (char)(97+i);
  for(int i = 0; i<26 ; i++)
    alphabetSet[index++] = (char)(65+i);
}

int getAlphabetIndex(unsigned char * alphabetSet,unsigned char ch){
  //Function to get the index of character in alphabet set
  for(int i=0;i<strlen((const char * )alphabetSet);i++){
    if(ch == alphabetSet[i]){
      return i;
    }
  }
  return 0;
}

void parseMessageBF(unsigned char * message, unsigned char * bruteForceCombinations) {
  //Function used to store the decrypted message in 2D array
  int lengthOfMessage = strlen((const char*)message);
  for(int j=0;j<lengthOfMessage;j++){
    bruteForceCombinations[j] = message[j];
  }
}

void clrscr() {
  //Used to clear terminal screen
  #ifdef _WIN64 //If OS is Windows
    system("cls");
    return;
  #endif
  //If the operating system is other than Windows, we use the below system command.
  system("clear"); // If OS is MacOS or Linux
}

void cleanSTDIN() {
  //This function is used instead of fflush(stdin) as it is a bad practice to use it 
  //due to undefined behaviour.
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF){}
}

void fileWriter(char filePath[50], unsigned char * message, char * mode) {
  //Used for writing the Encrypted/Decrypted Message to a file.
  FILE *filePointer;
  filePointer = fopen(filePath,mode);
  fprintf(filePointer,"%s",message);
  fclose(filePointer);
}

void copyToClipboard(char filePath[]){
  //Function used to copy the Encrypted/Decrypted message onto the clipboard
  //so that the user can paste it where ever needed.
  //NOTE : This feature is only avaliable on MacOS and Windows Operating Systems
  #ifdef __linux__
    char command[1]=" "; //Initialising dummy variables for linux. This is done inorder to prevent a warning.
    char clip[1]=" ";
  #endif
  #ifdef _WIN64
    char command[100]="type ";
    char clip[]=" | clip";
  #endif
  #ifdef __APPLE__
    char command[100]="cat ";
    char clip[]=" | pbcopy";
  #endif
  
  strcat(command,filePath);
  strcat(command,clip);
  system(command);
}

void open(char filePath[]){
  //Function to open a particular file
  //This can be used only on Windows, MacOS and Linux Operating Systems
  #ifdef _WIN64
    char command[100]="notepad ";
  #endif
  #ifdef __APPLE__
    char command[100]="open -e ";
  #endif
  #ifdef __linux__
    char command[100]="gedit ";
  #endif
  strcat(command,filePath);
  system(command);
}