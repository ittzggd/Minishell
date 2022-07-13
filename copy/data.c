/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:31:33 by yukim             #+#    #+#             */
/*   Updated: 2022/07/13 13:29:45 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

t_data	g_data;

void	free_data_lexer(void)
{
	int	i;

	i = 0;
	if (g_data.lexer.ptype)
		free(g_data.lexer.ptype);
	if (g_data.lexer.pptokens)
	{
		while (g_data.lexer.pptokens[i])
		{
			free(g_data.lexer.pptokens[i]);
			i++;
		}
		free(g_data.lexer.pptokens);
	}
	ft_bzero(&g_data.lexer, sizeof(t_lexer));
}

void	free_data_heredoc_delimiter(void)
{
	int	i;

	i = 0;
	if (g_data.hd.heredoc_delimiter)
	{
		while (g_data.hd.heredoc_delimiter[i])
		{
			free(g_data.hd.heredoc_delimiter[i]);
			i++;
		}
		free(g_data.hd.heredoc_delimiter);
		g_data.hd.heredoc_delimiter = NULL;
	}
}

void	free_data_heredoc_fd(void)
{
	int	i;

	i = 0;
	if (!g_data.hd.heredoc_fd)
		return ;
	while (i < g_data.hd.heredoc_cnt)
	{
		close(g_data.hd.heredoc_fd[i].fd[0]);
		close(g_data.hd.heredoc_fd[i].fd[1]);
		i++;
	}
	free(g_data.hd.heredoc_fd);
	g_data.hd.heredoc_fd = NULL;
}

void	reset_data(void)
{
	g_data.cnt.tokens_cnt = 0;
	g_data.cnt.redirection_cnt = 0;
	g_data.cnt.pipe_cnt = 0;
	g_data.p_flag = 0;
	free_data_heredoc_fd();
	free_data_heredoc_delimiter();
	g_data.hd.heredoc_cnt = 0;
	free_data_lexer();
	free_data_ast();
}
