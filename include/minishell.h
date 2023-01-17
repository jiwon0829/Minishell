#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "lexer.h"

#define FALSE 0
#define TRUE 1

#define AC_ZERO		200		//명령어 인자 개수가 0인 경우
#define AC_LESS_1	201		// 명령어 인자 개수가 0 또는 1인 경우
#define AC_ANY		202		// 명령어 인자 개수가 제한 없는 경우(echo)

typedef	struct s_redir t_redir;
typedef struct s_envp t_envp;
typedef struct s_minishell t_minishell;

typedef struct s_cmd
{
	char	*cmd;
	void (*func)(t_minishell *minishell, char **arr);
	int		argc;
	char	*opt;
}				t_cmd;

typedef struct s_cmd_tbl
{
	int		max_element;
	t_cmd	*cmd;
}				t_cmd_tbl;



struct s_redir
{
	int		in;
	int		out;
	t_redir	*next;
	t_redir *prev;
};

struct s_envp
{
	char	*key;
	char	*value;
	t_envp	*next;
	int		cnt;
};

struct s_minishell
{
	char 		**path;
	t_envp		*envp;
	t_redir		*redir;
	int			status;
	t_cmd_tbl	*cmd_tbl;
};

void	setting_signal(void);
void 	main_loop(t_minishell *minishell);
void	init(t_minishell *minishell, char *envp[]);
void	check_arg(int ac, char *av[]);


#endif
