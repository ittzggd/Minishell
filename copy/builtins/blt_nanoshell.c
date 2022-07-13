/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_nanoshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:13:42 by hejang            #+#    #+#             */
/*   Updated: 2022/07/13 14:19:08 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_nanoshell(char *filepath)
{
	char		**envp;
	char		*argv[2];
	struct stat	*buf;

	buf = NULL;
	reset_stdfd();
	g_data.exit_status = 0;
	if (ft_strncmp(filepath, "minishell", -1) && stat(filepath, buf) == -1)
	{
		ft_error_message("minishell : command not found : ", 1);
		ft_error_message(filepath, 1);
		ft_error_message("\n", 1);
		exit(g_data.exit_status);
	}
	envp = envvlist_to_envp();
	argv[0] = "./minishell";
	argv[1] = NULL;
	execve(argv[0], argv, envp);
}
