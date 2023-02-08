#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

int main(void)
{
	int a =0;
	int b =0;
	int c =0;
	int fd[2];
	int fd2[2];
	int fd3[2];

	pipe(fd);
	pipe(fd2);

	printf("fd[0] : %d, fd[1] : %d \n",fd[0],fd[1]);
	printf("fd[0] : %d, fd[1] : %d \n",fd2[0],fd2[1]);

	int ret =	dup2(fd[0],STDIN_FILENO);
	close(fd[0]);
	printf ("after dup2 ret : %d\n",ret);

	pipe(fd3);
	printf("fd[0] : %d, fd[1] : %d \n",fd3[0],fd3[1]);
	int ret2 =	dup2(fd3[0],STDIN_FILENO);
	close(fd3[0]);
	printf ("after dup2 ret : %d\n",ret2);


}