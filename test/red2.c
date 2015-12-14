#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

main(){
	int f1,f2;
	f2 = open("out.txt", O_WRONLY|O_TRUNC|O_CREAT, 0644);
	close(1);
	dup(f2);
	execlp("ls","ls","-l",0);
}
