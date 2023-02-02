#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"
#include "t_exec.h"

#define ERR -1
//fd
#define STDIN 0
#define STDOUT 0
#define STDERR 0

//exit code
#define SUCCESS 0
#define SYNTAXERROR 1
#define UNEXPTOKEN 2
#define NOCOMMAND 127
#define NOEXECUTE 126
#define REDIRERROR 139

// command_list.c
void	execute_and_node(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe);
void	execute_or_node(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe);
void	execute_pipe_node(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipes, int fd[2]);
void	handle_iteration(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe);

// exec_cmd.c
void	run_program(t_arg *arg, char **envp);
void	child_process(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe);
void	parent_process(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe);
void	exec_cmd(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe);

// executor.c
t_pipe *setting_pipe(t_parse_tree *parse_tree);
void iterate_tree(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe);
void executor(t_minishell *minishell, t_parse_tree *parse_tree);

// pipe_list.c
t_pipe	*lstlast(t_pipe *lst);
void	lstadd_front(t_pipe **head, t_pipe *new);
t_pipe	*lstnew(int *fd);
int	lstsize(t_pipe *lst);
 
//pipe_util.c
char	**get_path_envp(char *envp[]);
char	*get_cmd_argv(char **path, char *cmd);
void	get_cmd(t_minishell *minishell, t_arg *arg, char *av, char **envp);

//shell_exit.c
void shell_err(t_minishell *minishell, int status, char *msg);
void shell_exit(t_minishell *minishell, int status, char *msg);
void	exit_value_set(t_minishell *minishell, int exit_status);



#endif