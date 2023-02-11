#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("test file\n");
	char	*argv[] = {"ls", "-a", 0};
	char	*argv2[] = {"/bin/ls", 0};


	execv("/bin/ls", argv2);
}
