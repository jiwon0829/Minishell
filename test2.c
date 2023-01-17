#include <stdio.h>

int main(void)
{
    char    *str;
    int i = 0;
    if (!(i))
        perror("ret = 0");

    str = "apple";

    printf("%s\n", str);
    printf("%d\n", (int)(&str[2]-&str[0]));
}