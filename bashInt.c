/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Tenth Edition
 * Written by Logan Dawkins FALL - 2018
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "string.h"
#include "da.h"

#define MAX_LINE		80 /* 80 chars per line, per command */

int parseCommand(char *,char**);// seperates command parameters into an array of strings
void processControl(char **,int);// handles the execution of the parent and child processes
void terminateArgs(char **args,int j);// sets empty array spots to NULL

int main(void){
	char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
    	int should_run = 1;
        int backgrnd;   //flag to signify concurrency
        char *command;  //temp string to hold each command before it is parsed and stored in history
        STRING *temp;   //temp object to wrap each command string
        DA *history = newDA(displaySTRING,freeSTRING); // holds each command entered into bash interpreter
    	while (should_run){   
            printf("osh>");
            fflush(stdout);
            
            command = readLine(stdin);          //get command from stdin

	    

            
            if(strcmp(command,"exit") == 0){    //exit interpreter
                    return 0;
            }
            else if(strcmp(command,"history") == 0){    //display history of commands
                if(sizeDA(history) == 0){
                    printf("No commands in history.\n");
                }
                else{
                    displayDA(stdout,history);
                    printf("\n");
                }
            }
            else if(strcmp(command,"!!") == 0){     //execute the last command ran, stored in history DA(dynamic array)
                if(sizeDA(history) == 0){
                    printf("No commands in history.\n");
                }
                else{
                    displaySTRING(stdout,getDA(history,sizeDA(history)-1));
                    printf("\n");
                    backgrnd = parseCommand(getSTRING(getDA(history,sizeDA(history) - 1)),args);
                    temp = newSTRING(getSTRING(getDA(history,sizeDA(history)-1)));
                    insertDA(history,temp);
                    processControl(args,backgrnd);
                }
            }   
            else if(command[0] == '!' && isdigit(command[1])){  //execute the Nth command stored in history DA
                if(atoi(command+1) > sizeDA(history) || atoi(command+1) < 1){
                    printf("No such command in history.\n");
                }
                else{
                    displaySTRING(stdout,getDA(history,atoi(&command[1]) - 1));
                    printf("\n");
                    backgrnd = parseCommand(getSTRING(getDA(history,atoi(&command[1]) - 1)),args);
                    temp = newSTRING(getSTRING(getDA(history,atoi(&command[1])-1)));
                    insertDA(history,temp);
                    processControl(args,backgrnd);
                }
            }
            else{   //run command entered at prompt
                backgrnd = parseCommand(command,args);
                temp = newSTRING(command);
                insertDA(history,temp);
                processControl(args,backgrnd);
            }

            memset(command,0,strlen(command));  //reset command array
            
    	}
    
	return 0;
}

//handles parent and child execution
void processControl(char **args,int backgrnd){
    int pid = fork();
    if(pid < 0){    //fork failed
        fprintf(stderr,"Fork Failed.\n");
        exit(1);
    }
    else if(pid == 0){ // execute the child process
        execvp(args[0],args);
        exit(0);
    }
    else if(pid > 0 && backgrnd == 0){      //parent process should wait for child finish
        wait(NULL);
    }
    //if backgrnd == 1 then parent process continues without waiting
    
    int i = 0;           
    while(args[i] != 0){    //reset args array for next command
        memset(args[i],0,strlen(args[i]));
        args[i++] = 0;
    }
}

//function takes full command and makes each token a parameter
int parseCommand(char *src,char **dest){
    int i = 0;      //cursor for command string
    int j = 0;      //cursor for args array
    int k = 0;      //cursor for x string
    char *x = malloc(sizeof(char) * strlen(src));   //x max size is src size
    for(i = 0;i < (int)strlen(src);i++){
        if(src[i] == '&' && isspace(src[i-1])){
   	    terminateArgs(dest,j);
            return 1;       //return 1 to signify run in background
        }
        else if(src[i] == ' '){
            if(strlen(x) != 0){ //command was actually typed
                dest[j] = malloc(sizeof(char) * strlen(x));     //put token in args array
		x[strlen(x)] = 0;
                strcpy(dest[j++],x);
                memset(x,0,strlen(x));    //reset x string
                k = 0;          
            }
        }
        else{
            x[k++] = src[i];    //put character in x string
            if(i == (int)strlen(src) - 1){ //finished parsing cammand
                dest[j] = malloc(sizeof(char) * strlen(x));
		x[strlen(x)] = 0;
                strcpy(dest[j++],x);
                memset(x,0,strlen(x));    //reset x string
                k = 0;          
            }
        }
    }
    terminateArgs(dest,j);
    return 0;
}

void terminateArgs(char **args,int j){
    int i;
    for(i=j;i < MAX_LINE/2 + 1;i++){
	   args[i] = 0;
    }
} 
