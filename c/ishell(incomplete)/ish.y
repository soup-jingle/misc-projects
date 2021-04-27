%{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pwd.h>

int fileIn;
int fileOut;
char *args = NULL;
int background = 0;

typedef struct command {
	unsigned int job_number;
	unsigned short is_background;
	char *name;
	char *arguments;
} Command;

unsigned int MAX_JOBS = 256; // Assumed that 256 would be sufficient
unsigned int JPTR = 0; // job pointer: new jobs go in this slot
//Command commands[MAX_JOBS]; // Array to hold maximum amount of commands
	
%}

%union
{
    char	*string;
    int		integer;
}

%token 	<string>	WORD
%token 	<string>	COMMAND
%token 	<string>	FILENAME
%token	<int>		BACKGROUND
%token	<int>		PIPE
%token	<int>		PIPE_ERROR
%token	<int>		SEMICOLON
%token	<int>		REDIRECT_IN
%token	<int>		REDIRECT_OUT
%token	<int>		REDIRECT_ERROR
%token	<int>		APPEND
%token	<int>		APPEND_ERROR
%token	<string>	OPTION
%token	<string>	STRING
%token	<int>		LOGICAL_AND
%token	<int>		LOGICAL_OR

%%

cmd_line 	: cmd_line separator COMMAND parameters 
    | COMMAND parameters
 // TODO make use of 'commands array'
    {
			if(strcmp($1, "exit") == 0) {
				printf("goodbye\n");
				exit(0);
			}
			else if(strcmp($1, "cd") == 0) {
				if(chdir(args) != 0) perror("cd error\n");
				
				char pwd[1000]; // arbitrary path length
				getcwd(pwd, 1000);
				printf("Now in: %s\n", pwd);
			}
			// NO JOB CONTROL/ENV:
			/*
			else if(strcmp($1, "bg") == 0) {}
			else if(strcmp($1, "fg") == 0) {}
			else if(strcmp($1, "jobs") == 0) {
				for(int i = 0; i < MAX_JOBS; ++i) {
					//if(commands[i] != NULL)
					//	printf("%-8d%s", commands[i].job_number, commands[i].name);
				}
			}
			else if(strcmp($1, "kill") == 0) {}
			else if(strcmp($1, "setenv") == 0) {}
			else if(strcmp($1, "unsetenv") == 0) {}
			*/
			else {
				
				char * cmd = $1;
				int l = 0;
				if(args != NULL) l = strlen(args);
				char *temp = malloc(strlen(cmd) + 1 + l);
				strcpy(temp, cmd);
				strcat(temp, " ");
				if(args != NULL) strcat(temp, args);
				args = temp;

				//printf("|%s|%s|",cmd,args);
				int r = fork();
				if(r == 0) {
					
					execl(cmd, args, (char*)NULL);  // TODO make separate function which accepts 'Command'
				}
				if(background != 1) // TODO check struct command's value instead
					wait(NULL);
				
				//close(fileIn);
				//close(fileOut);
				//dup2(1,1); //?
				//dup2(2,2); //?
			}
			// RESET VALUES
		  
			background = 0;
			args = NULL;
		}
		| cmd_line BACKGROUND
		{
			background = 1; //set in struct
		}
		| cmd_line SEMICOLON
		|  
		| error
		;

separator 	: BACKGROUND
    {
			background = 1;
		}
		| PIPE
		| PIPE_ERROR
		| SEMICOLON
		;

parameters	: parameters OPTION
    {
			// !! OPTIONs are seen as WORDs !!
			
			printf(":OPTION:\n");
			//args = malloc(strlen($2));
			//args = $2;
		}
		| parameters STRING
    {
			// !! commas in STRINGs cause errors
			
			//printf(":STRING:\n");
			args = malloc(strlen($2));
			args = $2;
			printf("%s\n", args);
		}
		| parameters WORD
		{
			// !! OPTIONs are also seen as WORDs, not options.
			// !! so '-' does nothing to differentiate them
			
			//printf(":WORD:\n");
			
			int l = 0;
			if(args != NULL) l = strlen(args);
		  char *temp = malloc(strlen($2) + 1 + l);
			strcpy(temp, $2);
			strcat(temp, " ");
			if(args != NULL) strcat(temp, args);
			args = temp;

			
			l = strlen(args);
			if(args[l-1] == '\n' || args[l-1] == '\t' || args[l-1] == ' ')
				args[l-1] = '\0';
			
			//printf("%s", args);
		}

    // No redirects work
		| parameters REDIRECT_IN FILENAME
		{
			printf(":REDIRECT IN:\n");
			//fileIn = open($3, O_WRONLY | O_CREAT);
			//dup2(fileIn, 1);
		}
    | parameters REDIRECT_OUT FILENAME
		{
			printf(":REDIRECT OUT:\n");
			fileOut = open($3, O_WRONLY | O_CREAT);
			dup2(1, fileOut);
		}
		| parameters REDIRECT_ERROR FILENAME
		{
			printf(":REDIRECT ERROR:\n");
			//fileOut = open($3, O_WRONLY | O_CREAT);
			//dup2(2, fileOut);
		}
		| parameters APPEND FILENAME
		{
			printf(":APPEND:\n");
			//fileOut = open($3, O_WRONLY | O_CREAT | O_APPEND);
			//dup2(1, fileOut);
		}
		| parameters APPEND_ERROR FILENAME
		{
			printf(":APPEND ERROR:\n");
			//fileOut = open($3, O_WRONLY | O_CREAT | O_APPEND);
			//dup2(2, fileOut);
		}
		|
		;

%%

int yyerror(char *s)
{
    fprintf(stderr, "syntax error\n");
    return 0;
}

int yywrap() {
	return 1;
}

int main() {
	do {
		printf("\n* ");
		int i = yyparse();
	} while(1);
	return 0;
}
