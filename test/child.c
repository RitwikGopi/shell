#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
main(){
	int i = 0;
	printf("starting process: %d\n", i++);
	pid_t pid = fork();
	int p[2];
	if(pipe(p) == -1){
		perror("pipe:");
		exit(0);
	}
	if(pid == -1){
		perror("Nopid");
	}
	else if(pid == 0){
		printf("Childe process : %d\n",i++);
		pid_t pid2 = fork();
		if(pid2 == 0){
			printf("in child 2\n");
			close(1);
			dup(p[1]);
			execlp("ls","ls",0);
		}
		else{
			wait(NULL);
			printf("child 1 continue\n");
			close(p[1]);
			close(0);
			dup(p[0]);
			execlp("grep","grep","shell", 0);
		}
		
		//printf("kiduuu");
		//printf("Message from otherside is : %s \n",s);
	}
	else{
		wait(NULL);
		printf("Parent process : %d, pid of child : %d\n",i++,pid);
	}
	/*pid_t pid2 = fork();
	if(pid2 == -1){
		perror("Nopid");
	}
	else if(pid2 == 0){
		printf("Childe process2 : %d\n",i++);
	}
	else{
		printf("Parent process2 : %d, pid2 of child : %d\n",i++,pid2);
	}*/

}
