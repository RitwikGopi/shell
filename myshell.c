#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

void child_p(char **);
void read_args(char *, char **, char *);
int check_in(char **);
main(){

	while(1){
		printf("$");
		char s[100];
		char *args[10];
		read_args(s, args," \n");
		pid_t pid = fork();
		if(pid==0){
			child_p(args);
		}
		else{
			wait(NULL);
		}
	}
}

void child_p(char **args){
	//printf("******%d****\n",check_in(args));
	int r = check_in(args);
	if(r < 0)
		execvp(args[0], args);
	else{
		char *args1[10], *args2[10], *op;
		int i = 0;
		op = args[r];
		for(i = 0; i < r; i++)
			args1[i] = args[i];
		args1[i] = NULL;
		for( i = 0, ++r; args[r] != NULL; r++, i++)
			args2[i] = args[r];
		if( *op == '<'){
			int fd = open(args2[0], O_RDONLY);
			close(0);
			dup(fd);
		}
		else if( strcmp(op,">") == 0){
			int fd = open(args2[0], O_WRONLY|O_CREAT|O_TRUNC , 0644);
			close(1);
			dup(fd);
		}
		else if( strcmp(op,">>") == 0){
			int fd = open(args2[0], O_WRONLY|O_CREAT|O_APPEND , 0644);
			close(1);
			dup(fd);
		}
		else if( *op == '|'){
			int p[2];
			pipe(p);
			pid_t pid2=fork();
			if(pid2 == 0){
				close(1);
				dup(p[1]);
				execvp(args1[0],args1);
			}
			else{
				wait(NULL);
				close(p[1]);
				close(0);
				dup(p[0]);
				execvp(args2[0],args2);
			}
		}
		execvp(args1[0],args1);
	}
}
				

void read_args(char *s, char **args, char *delim){
	int i = 0,j = 0, k = 0;
	while(!fgets(s,100,stdin));
	args[i] = strtok(s,delim);
	while(args[i] != NULL){
		//printf("%s",args[i]);
		args[++i] = strtok(NULL,delim);
	}
}

int check_in(char **args){
	int i = 0;
	for( i = 0; args[i] != NULL; i++)
		if(*args[i] == '<' || *args[i] == '>' || *args[i] == '|')
			return i;
	return -1;
}
