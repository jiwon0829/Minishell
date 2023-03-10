/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:49:14 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:51:20 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "t_exec.h"

# define ERR -1
# define STDIN 0
# define STDOUT 0
# define STDERR 0
# define SUCCESS 0
# define SYNTAXERROR 1
# define UNEXPTOKEN 2
# define NOCOMMAND 127
# define NOEXECUTE 126
# define REDIRERROR 139

int		check_arg_type(t_minishell *minishell, t_arg *arg);
void	execute_and_node(t_minishell *minishell, t_parse_tree *parse_tree, \
						t_pipe **pipe, int fd[2]);
void	execute_or_node(t_minishell *minishell, t_parse_tree *parse_tree, \
						t_pipe **pipe, int fd[2]);
void	execute_pipe_node(t_minishell *minishell, t_parse_tree *parse_tree, \
						t_pipe **pipes, int fd[2]);
void	handle_iteration(t_minishell *minishell, t_parse_tree *parse_tree, \
						t_pipe **pipe);
void	free_n_move_pipe(t_minishell *minishell, t_pipe **pipe);
void	run_program(t_arg *arg, char **envp);
void	child_process(t_minishell *minishell, t_parse_tree *parse_tree, \
					t_pipe **pipe);
void	parent_process(t_minishell *minishell, t_parse_tree *parse_tree, \
					t_pipe **pipe);
void	exec_cmd(t_minishell *minishell, t_parse_tree *parse_tree, \
				t_pipe **pipe);
t_pipe	*setting_pipe(t_parse_tree *parse_tree);
void	iterate_tree(t_minishell *minishell, t_parse_tree *parse_tree, \
					t_pipe **pipe);
void	executor(t_minishell *minishell, t_parse_tree *parse_tree);
void	is_wildcard(t_token *token);
t_pipe	*lstlast(t_pipe *lst);
void	lstadd_front(t_pipe **head, t_pipe *new);
t_pipe	*lstnew(int *fd);
int		lstsize(t_pipe *lst);
int		arr_size(t_token *token);
char	**make_cmd_arg(t_parse_tree *parse_tree);
int		check_cur_exec(t_minishell *minishell, t_arg *arg);
char	**get_path_envp(char *envp[]);
char	*get_cmd_argv(char **path, char *cmd);
void	get_cmd(t_minishell *minishell, t_arg *arg, t_parse_tree *parse_tree, \
				char **envp);
void	shell_err(t_minishell *minishell, int status, char *msg);
void	shell_exit(t_minishell *minishell, int status, char *msg);
void	redir_open_error_message(t_minishell *minishell, int status, char *msg);
void	exit_value_set(t_minishell *minishell, int exit_status);
void	permission_error_message(t_minishell *minishell, int status, char *msg);
void	set_cmd(t_minishell *minishell, t_parse_tree *parse_tree);
int		exec_builtin_scmd(t_minishell *minishell, t_parse_tree *parse_tree);
void	exec_multi_cmd(t_minishell *minishell, t_parse_tree *parse_tree, \
					t_pipe **pipes);
void	exec_scmd(t_minishell *minishell, t_parse_tree *parse_tree, \
				t_pipe **pipes);
int		exec_builtin(t_minishell *minishell, t_parse_tree *parse_tree);
int		exec_child_logical(t_minishell *minishell, t_parse_tree *parse_tree, \
							t_pipe **pipe, char **envp);
int		exec_child_scmd(t_minishell *minishell, t_parse_tree *parse_tree, \
						t_pipe **pipe, char **envp);

#endif
