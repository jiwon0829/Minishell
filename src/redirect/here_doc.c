#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "error_message.h"

static char	*get_nextline(int fd)
{
	char	str[8000000];
	int		i;
	char	buff[1];
	int		byte;

	byte = read(fd, buff, 1);
	i = 0;
	if (fd < 0)
	{
		return (NULL);
	}
	while (byte > 0)
	{
		if (buff[0] == '\n')
			break ;
		str[i++] = buff[0];
		byte = read(fd, buff, 1);
	}
	str[i] = '\0';
	if (str[0] == '\0')
		return (ft_strdup(str));
	return (ft_strdup(str));
}

void	here_doc(t_minishell *minishell)
{
	int		fd;
	char	*buf;
	char	limit;

	limit = minishell->redirect->file_name;

	minishell->redirect->fd[0] = open("/dev/urandom", O_CREAT | O_RDWR | O_TRUNC, 0666);
	while (1)
	{
		write(1, "here_doc>", 9);
		buf = get_next_line(0);
		if (ft_strcmp(buf, limit) == 0)
			break ;
		write(fd, buf, ft_strlen(buf));
		if (ft_strcmp(buf, "\n") != 0)
			write(minishell->redirect->fd[0], "\n", 1);
		free (buf);
	}
	if (minishell->redirect->fd[0] < 0)
		err_massage(minishell, 1, "heredoc_error"); //히어독 실패에러메세지 확인
}