//Program to encrypt and decrypt plaintext using Caesar cipher
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Server.h"

char userChoice();

int main(void) { 

  clrscr();
  int menuChoice;
  unsigned char message[1023];
  char choiceEntered;
  int shift;
  Heading:
  //Menu Section
  printf("\n Encryption and Decryption using Caesar Cipher");
  printf("\n ---------------------------------------------");
  printf("\n\n 1. Encrypt a Message\n 2. Decrypt a Message\n 3. Decrypt using Brute Force method\n 4. Quit\n");
  printf("\n Enter your choice : ");
  scanf("%d",&menuChoice);
  switch(menuChoice){
    case 1:   //Encryption
              clrscr();
              memset(message,0,sizeof message);
              printf(" Caesar Encryption\n -----------------\n Enter the message to be Encrypted : ");
              readInput(message,&shift);
              encryptMessage(message,shift);
              printf("\n Encrypted Message\n -----------------\n");
              displayMessage(message);
              putchar('\n');
              //Checking if the entered message will be same as output message or not.
              if(abs(shift)%52==0 || shift==0)
                printf(" The Encrypted Message is same as the message entered.\n");
              fileWriter("bin/EncryptedMessage.txt",message,"w");
              //The below if statement is used to check the operating system that the user is using.
              //This is done as only MacOS and Windows support the feature implemented below.
              #if defined(__APPLE__) || defined(_WIN64)
                copyToClipboard("bin/EncryptedMessage.txt");
              #endif
              printf(" The Encrypted Message has been stored in a text file.\n\n ");
              #if defined(__APPLE__) || defined(_WIN64)
                printf("NOTE : The Encrypted Message has also been copied onto to your clipboard!\n\n ");
              #endif
              choiceEntered = userChoice();
              if(choiceEntered == '1'){
                //Making the program cross platform compatible 
                //Used to open the default text editor in windows, macOS and linux 
                //operating systems
                open("bin/EncryptedMessage.txt");
                sleep(1000);
              }
              cleanSTDIN();
              menuChoice=0;
              clrscr();
              //Used for error handling
              //Mimicking try and execpt functionality of python
              goto Heading;
              break;
    case 2:   //Decryption
              clrscr();
              memset(message,0,sizeof message);
              printf(" Caesar Decryption\n -----------------\n Enter the message to be Decrypted : ");
              readInput(message,&shift);
              decryptMessage(message,shift);
              printf("\n Decrypted Message\n -----------------\n");
              displayMessage(message);
              putchar('\n');
              fileWriter("bin/DecryptedMessage.txt",message,"w");
              //Checking if the entered message will be same as output message or not.
              if(abs(shift)%52==0 || shift==0)
                printf(" The Decrypted Message is same as the message entered.\n");
              #if defined(__APPLE__) || defined(_WIN64)
                copyToClipboard("bin/DecryptedMessage.txt");
              #endif
              printf(" The Decrypted Message has been stored in a text file.\n\n ");
              #if defined(__APPLE__) || defined(_WIN64)
                printf("NOTE : The Decrypted Message has also been copied onto to your clipboard!\n\n ");
              #endif
              // #ifdef _WIN64
              //   printf(" NOTE : The Decrypted Message has also been copied onto to your clipboard!\n\n ");
              // #endif            
              choiceEntered = userChoice();
              if(choiceEntered == '1'){
                open("bin/DecryptedMessage.txt");
                sleep(1000);
              }
              cleanSTDIN();
              menuChoice=0;
              clrscr();
              goto Heading;
              break;
    case 3:   //Decryption using Brute Force method
              clrscr();
              memset(message,0,sizeof message);
              printf(" Caesar Decryption (BRUTE FORCE)\n -------------------------------\n Enter the message to be Decrypted : ");
              readInput(message,0);
              //Dynamically allocating memory for the array bruteForceCombinations
              //bruteForceCombinations stores all possible variations of the message
              int lengthOfMessage = strlen((const char*)message);
              unsigned char ** bruteForceCombinations = (unsigned char **)malloc(52 * sizeof(unsigned char *));
              for(int i=0;i<52;i++)
                bruteForceCombinations[i] = (unsigned char *)malloc(lengthOfMessage * sizeof(unsigned char *));
              bruteForce(message,bruteForceCombinations);
              printf("\n Decrypted Message Combinations\n ------------------------------\n");
              displayMessageBF(bruteForceCombinations,strlen((const char *)message));
              for(int i=0;i<52;i++){
                if(i==0){
                  fileWriter("bin/BruteForceCombinations.txt",(unsigned char*)strcat((char*)bruteForceCombinations[i],"\n"),"w");
                  continue;
                }
                fileWriter("bin/BruteForceCombinations.txt",(unsigned char*)strcat((char*)bruteForceCombinations[i],"\n"),"a");
              } 
              putchar('\n');
              //To free the allocated memory for bruteForceCombinations
              free(bruteForceCombinations);
              printf(" All combinations of the message have been stored in a text file.\n\n ");
              choiceEntered = userChoice();
              if(choiceEntered == '1'){
                open("bin/BruteForceCombinations.txt");
                sleep(1000);
              }
              menuChoice=0;
              clrscr();
              goto Heading;
              break;
    case 4:   clrscr();
              printf(" Thank You for using our services!\n");
              sleep(2500); //Used to create a time delay. Mimicks thread.sleep() in Java
              clrscr();
              exit(0);
              //Exits the program with a success.
              break;
    default:  //Error Handling
              cleanSTDIN();
              printf("\n Please choose the correct option\n ");
              sleep(1700);
              clrscr();
              goto Heading;    
  }
  return 0;
}
char userChoice() {
  //Function used to check if the user wants to open a file or not
  printf("Would you like to open the file?");
  choice:
  printf("\n Press :\n 1. Open text file\n 2. Skip and continue\n ");
  int pressed;
  scanf("%d",&pressed);
  switch(pressed){
    case 1 : return '1';
               break;
    case 2 : return '2';
               break;
    default : printf("\n Please enter a valid option\n ");
              sleep(1500);
              cleanSTDIN();
              goto choice;
              break;
  }
}