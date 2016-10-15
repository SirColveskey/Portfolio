/*
 *Name: Benjamin Cooper
 *Date: 9.15.2016
 *Course: Operating Systems
 *Assignment: 1 - Make a shell
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
//Help prints usage and returns 1 for error handling.
int help(){
  printf("Usage: <executable> [optional: script file]\n");
  return 1;
}
//Process parses and runs given commands
int process(char* input){
	int ret = 1;	//return value, set to 0 to end
	int i = 0;	//loop flag
	int j = 0;	//loop flag
	pid_t pid;	//process id number
	int status;	//recieves value of wait
	char * tasks[200];	//holds all tasks to be run
	char ** command = (char **) malloc(1*sizeof(char * ));	//holds the command (flags etc)
	long command_len = 1;
	tasks[0] = strtok(input, ";");	//tokenizes by semicolon to parse commands
	if(!strcmp(input,"\n"))		//returns for new line to handle the error
		return 1;
	while (tasks[i] != NULL)	//continues task processing
	{
		//printf("Running...\n");
		i++;
		tasks[i] = strtok(NULL, ";");
	}
	for(j=0; j<i; j++)	//for each task breaks down into a command and runs it
	{
		//printf("Run %d\n",j);
		int k = 0;	//k tracks command
		tasks[j] = strtok(tasks[j], "\n");	//clears newline
		if(tasks[j] == NULL)
			continue;
		command[k] = strtok(tasks[j], " ");	//tokenizes by and clears whitespace
		if(command[k] == NULL)
			continue;
		if(!strcmp(command[0],"quit"))	//processes "quit"
		{	
			perror("Quit Received\n");
			ret = 0;
			continue;
		}
		while(command[k] != NULL)	//processes flags for the command
		{
			k++;
			command = realloc(command, (command_len + 1) * sizeof(char *));
			command_len++;
			command[k] = strtok(NULL, " ");
		/*	if(k==9)
			{
				perror("Too many arguments or missing semicolon on a command.\n");
				break;
			}*/
		}
		//char * altcommand[2] = {"ls","-l"};
		pid = fork();	//forks a new process
		if((pid) < 0){perror("fork\n");}
		else if(pid == 0){	//runs the command
			if(execvp(command[0],command))
				perror("The command does not exist.\n");
			exit(1);
		};
	}
	j = 0;
	for(j=0;j<=i;j++)
	{
		wait(&status);	//waits for completion
	}
	return ret;	//1 is continue, 0 is complete
}
//called for interactive commands
int interactive(){
	int j=0;	//collects the return
	int end = 0;	//if end is 1 break
	char c=' ';	//character to read for dumping
	char response[514]="";	//holds responses up to 514 chars
	while(1){
		printf("Prompt> ");
		if(NULL == fgets(response,514,stdin))
		{
			end = 1;
		//	printf("Did you hit ctrl+D?\n");
		}
		if(response[strlen(response)-1] != '\n' && end==0)
		{
			perror("Warning: Line Overflow (>512 Characters) dumping remaining commands.\n"); //Handles oversized lines
			while((c = getchar()) != '\n' && c != EOF)
				c=' ';
		}
		j=process(response); //returns 1 for continue, 0 for stop
		if(j==0 || end == 1)
			break;
	}
	return 0;
}
//called to process a script - operates similar to above
int script(FILE *file){
	int i=0;	//counters...
	int j=0;
	int end = 0;	//end flag
	char c=' ';	//char dump
	char response[514]= "";	//responses
	do{		
		if(NULL == fgets(response,514,file)){
			end = 1;
		};
		printf("%s",response); //echo print
		if(response[strlen(response)-1] != '\n' && end ==0)
		{
			perror("Warning: Line Overflow (>512 Characters) dumping remaining commands.\n"); //handles oversized lines
			while((c = getchar()) != '\n' && c != EOF)
				c=' ';
		}
		j=process(response); //returns 1 for continue, 0 for stop
		if(j==0 || end == 1)
			break;
	}while(!feof(file));
	i--;
	return 0;
}

int main(int argc, char *argv[])
{
	FILE *input = stdin;
	int ret = 0;
	if (argc > 2){ //handles improper input
	  return help();
	}
	//Opens the file: if applicable	
	if (argc != 1)
	{
		input = NULL;
		input = fopen(argv[1],"r");
		if(input == NULL)
		{
			perror("Error: File does not exist!\n");
			return help();  //handles a bad file name
		}
		ret = script(input); //calls script processing
		fclose(input);
		return ret;
	}
	return interactive(); //calls interactive mode
}
