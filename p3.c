/*
	Here when we execute, the parent will create a pointer to the file
	and when the child in created it will create a copy of that pointer
	to the child also. 

	We will at this point have two pointers to the file. When we unlink
	it the child's pointer to the file will be gone. But the parent 
	will still have the pointer to the file so we will get the 
	follwing output: 

	I'm the child
	I'm the parent
	contents: "Data from the file"

	After the the program finishes executing the pointer will be gone
	and because of the unlink, the file will be lost in memory and
	you will not be able to access it anymore. 

 */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	FILE *fp;
	char buff[255];
	pid_t cpid;
	fp = fopen (argv[1], "r");
	if(fp == NULL){
		printf("This file does not exist, errno = %d\n", errno);
		return 1;
	}
	fscanf(fp, "%s", buff);

	if (fork() == 0){
		printf("I'm the child\n");
		unlink(argv[1]);
	}
	else{
		cpid = wait(NULL);
		printf("I'm the parent\n");
		fscanf(fp, "%s", buff);
		printf("contents: %s\n", buff);
	}
	return 0;
}
