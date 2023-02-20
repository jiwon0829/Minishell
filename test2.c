#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void change(char *str)
{
	char *tmp;

	tmp = strdup("hi");
	free(str);
	str = strdup(tmp);
	free(tmp);
}

int main (void)
{
	char *str;

	str = strdup("test now");
	printf("[%p]%s\n", str, str);
	change(str);
	printf("[%p]%s\n", str, str);
}