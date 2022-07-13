/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:03:00 by yukim             #+#    #+#             */
/*   Updated: 2022/07/13 13:18:32 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# include <termios.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define END -1
# define NOT_USED -1
# define ALLOCATE_FAILED -2
# define CONTINUE -3

typedef struct s_astnode
{
	int					visited;
	int					nodetype;
	int					*pvalue_index;
	struct s_astnode	*pleftchild;
	struct s_astnode	*prightchild;
}			t_astnode;

typedef struct s_ast
{
	struct s_astnode	*prootnode;
}			t_ast;

typedef struct s_lexer
{
	char	**pptokens;
	int		*ptype;
}			t_lexer;

typedef struct s_heredoc_fd
{
	int	fd[2];
}			t_heredoc_fd;

typedef struct s_data
{
	int						std_fd[2];
	t_heredoc_fd			*heredoc_fd;
	char					**heredoc_delimiter;
	int						heredoc_cnt;
	int						heredoc_flag;
	struct termios			origin_term;
	struct termios			changed_term;
	struct s_envv_node		*envv_list;
	int						envv_cnt;
	int						exit_status;
	int						tokens_cnt;
	int						redirection_cnt;
	int						pipe_cnt;
	struct s_lexer			lexer;
	struct s_ast			ast;
	int						p_flag;
	char					*current_path;
}			t_data;

typedef struct s_envv_node
{
	char				*key;
	char				*value;
	int					init_flag;
	struct s_envv_node	*p_link;
}			t_envv_node;

typedef struct s_cmd
{
	char	*cmd[9];
}			t_cmd;

enum e_ast_node_type
{
	A_PIPE = 1,
	A_COMMAND,
	A_REDIRECTIONS,
	A_REDIRECTION,
	A_REDIRECTION_TYPE,
	A_ARGUMENTS,
	A_ARGUMENT,
	A_FILEPATH,
	A_FILENAME
};

enum e_type
{
	T_COMMAND = 1,
	T_WORD,
	T_OPTION,
	T_PIPE,
	T_REDIRECTION,
	D_QUOTE,
	S_QUOTE,
	T_NULL,
	T_ENV
};

enum e_quote_flag
{
	SINGLE_QUOTE = 1,
	DOUBLE_QUOTE
};

#endif
