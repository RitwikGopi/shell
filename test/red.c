#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

main(){
	int f1,f2;
	f1 = open("child.c", O_RDONLY);
	f2 = open("out.txt", O_WRONLY|O_TRUNC|O_CREAT, 0644);
	close(0);
	dup(f1);
	execlp("./a.out","./a.out",0);
}
