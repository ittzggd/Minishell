/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:44:36 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 14:35:53 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	create_delimiter_list(void);
static void	heredoc_do_child(void);
static void	heredoc_do_parent(int pid);

void	preprocess_heredoc(void)
{
	int		count;
	pid_t	pid;

	g_data.heredoc_flag = TRUE;
	g_data.exit_status = 0;
	count = g_data.heredoc_cnt;
	g_data.heredoc_delimiter = ft_calloc(count + 1, sizeof(char *));
	if (!g_data.heredoc_delimiter)
		ft_error("[preprocess_heredoc] heredoc_delimiter: allocation failed\n");
	g_data.heredoc_fd = ft_calloc(count, sizeof(t_heredoc_fd *));
	if (!g_data.heredoc_fd)
		ft_error("[preprocess_heredoc] heredoc_fd : allocation failed\n");
	create_delimiter_list();
	pid = fork();
	if (pid == 0)
		heredoc_do_child();
	else
		heredoc_do_parent(pid);
	
	g_data.heredoc_flag = FALSE;
}

static void	create_delimiter_list(void)
{
	int		hd_idx;
	int		t_idx;
	char	**tokens;

	hd_idx = 0;
	t_idx = 0;
	tokens = g_data.lexer.pptokens;
	while (hd_idx < g_data.heredoc_cnt)
	{
		if (g_data.lexer.ptype[t_idx] == T_REDIRECTION)
		{
			if (ft_strncmp("<<", tokens[t_idx], -1))
			{
				if (pipe(g_data.heredoc_fd[hd_idx].fd) < 0)
					ft_error("[Pipe ERROR] Heredoc failed\n");
				g_data.heredoc_delimiter[hd_idx] = ft_strdup(tokens[t_idx + 1]);
				hd_idx++;
			}
		}
		t_idx++;
	}
}

static void	heredoc_do_child(void)
{
	int	i;
	int	idx;

	i = 0;
	idx = 0;
	g_data.p_flag = TRUE;
	signal(SIGINT, ft_sig_handler_in_heredoc_sigint);
	signal(SIGQUIT, ft_sig_handler_in_heredoc_sigquit);
	while (idx < g_data.heredoc_cnt)
	{
		if (g_data.lexer.ptype[i] == T_REDIRECTION)
			exec_heredoc(i, &idx);
		i++;
	}
	g_data.heredoc_delimiter[idx] = NULL;
	g_data.heredoc_flag = FALSE;
	exit(g_data.exit_status);
}

static void	heredoc_do_parent(int pid)
{
	int	i;

	i = 0;
	waitpid(pid, &(g_data.exit_status), 0);
	if (WIFEXITED(g_data.exit_status))
		g_data.exit_status = WEXITSTATUS(g_data.exit_status);
	g_data.p_flag = FALSE;
	i = 0;
	while (i < g_data.heredoc_cnt)
	{
		close(g_data.heredoc_fd[i].fd[1]);
		i++;
	}
}
