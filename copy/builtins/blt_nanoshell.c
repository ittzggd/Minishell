/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_nanoshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:13:42 by hejang            #+#    #+#             */
/*   Updated: 2022/07/13 15:39:03 by hejang           ###   ########.fr       */
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
		ft_error_message("nanoshell : command not found : ", 1);
		ft_error_message(filepath, 1);
		ft_error_message("\n", 1);
		exit(g_data.exit_status);
	}
	envp = envvlist_to_envp();
	argv[0] = "./minishell";
	argv[1] = NULL;
	execve(argv[0], argv, envp);
}
