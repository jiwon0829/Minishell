#include <stdio.h>
#include <unistd.h>

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}


static char *make_err_msg(char *str1, char *str2, char *str3)
{
	char	ret_str[100];
	int		len;
	int		i;
	int		j;

	printf("11\n");
	if (str1)
	{
		i = 0;
		while (str1[i])
		{
			printf("u\n");
			ret_str[i] = str1[i];
			i++;
		}
	}
	ret_str[i] == NULL;
	printf("str:%s\n",ret_str);

	printf("22\n");

	if (str2)
	{
		len = ft_strlen(ret_str);
		i = 0;
		while (str2[i])
		{
			ret_str[len + i] = str2[i];
			i++;
		}
	}
	i--;

	printf("str:%s\n",ret_str);

	printf("33\n");

	if (str3)
	{
		len = ft_strlen(ret_str);
		i = 0;
		while (str3[i])
		{
			ret_str[len + i] = str3[i];
			i++;
		}
	}
	printf("str:%s\n",ret_str);

	return (ret_str);
}

int main(void)
{
	// printf("test file\n");
	// char	*argv[] = {"ls", "-a", 0};
	// char	*argv2[] = {"/bin/ls", 0};


	// execv("/bin/ls", argv2);
	char *str = make_err_msg("abc ", "de ", "fg");
	printf("str:%s\n",str);

	
}
