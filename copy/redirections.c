/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:55:52 by yukim             #+#    #+#             */
/*   Updated: 2022/07/13 17:33:12 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	out_red(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0666);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	in_red(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_error_message("nanoshell: ", 1);
		ft_error_message(filename, 1);
		ft_error_message(": No such file or directory\n", 1);
		return (ERROR);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (TRUE);
}

void	append_red(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0666);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	heredoc(char *delimiter)
{
	int	i;
	int	read_fd;

	i = 0;
	while (i < g_data.hd.heredoc_cnt)
	{
		if (ft_strncmp(g_data.hd.heredoc_delimiter[i], delimiter, -1))
			break ;
		i++;
	}
	read_fd = g_data.hd.heredoc_fd[i].fd[0];
	dup2(read_fd, STDIN_FILENO);
	close(read_fd);
}
