/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:44:50 by hejang            #+#    #+#             */
/*   Updated: 2022/07/13 14:07:12 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <dirent.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "minishell_define.h"
# include "utils.h"
# include "ast.h"
# include "builtin.h"
# include "minishell_red.h"

extern t_data	g_data;

void		init_setting(char **envp);
int			analyze_input(char *input);

// tokens
int			tokenize_input(char *input, int *tokenize_cnt);
char		**ft_minishell_split(const char *str);
int			ft_wordcount(char const *str);
int			get_wc(char const *str, int *i, int *wc_flag, int *wc);
void		replace_quote_env(void);

//lexer
void		lexical_analysis(int *tokenize_cnt);
char		*get_envv(char *key);
t_envv_node	*get_el_node(t_envv_node *envv_list, char *key);
void		insert_envv(char *key, char *value, int init_flag);
int			init_envp(char *input, char **key, char **value);

int			syntax_analysis(int *tokenize_cnt);
void		syntax_error(int *ret_status);
void		syntax_check_command(int *curr);
void		syntax_check_redirection(int *curr, int *ret_status);
void		syntax_check_pipe(int *curr, int *ret_status);
void		syntax_check_null(int *curr, int *ret_status);

// exec
void		exec_ast(void);
void		exec_cmd(t_astnode *argsnode);
void		execve_cmd(t_astnode *argsnode);
char		**join_filepath(char *execve_cmd);
char		**create_argv(int cnt, t_astnode *argsnode);
void		cmd_without_pipe(char *cmd, int idx, char **argv, char *execve_cmd);
void		fork_before_run_execve(int idx, char **argv, char *execve_cmd);
void		fork_before_run_execve_child(int idx, char *ecve_cmd, char **argv);
char		**allocate_empty_str_in_filepath(char *execve_cmd);
void		command_not_found_error(char *cmd);

// heredoc
void		preprocess_heredoc(void);
void		get_heredoc(char *delimiter, t_heredoc_fd *heredoc_fd);
void		exec_heredoc(int i, int *idx);

// signal
void		ctrl_c(int sig_num);
void		ctrl_bs(int sig_num);
void		ft_sig_handler_in_heredoc_sigint(int sig_num);
void		ft_sig_handler_in_heredoc_sigquit(int sig_num);

// reset, free
void		free_data_heredoc_fd(void);
void		free_data_heredoc_delimiter(void);
void		free_data_lexer(void);
void		reset_data(void);
void		reset_stdfd(void);
void		reset_signal(void);

#endif
