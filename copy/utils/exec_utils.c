/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:53:00 by hejang            #+#    #+#             */
/*   Updated: 2022/07/13 15:39:08 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_argv(int cnt, t_astnode *argsnode)
{
	t_astnode	*argnode;
	char		**argv;
	int			i;

	i = 0;
	argnode = argsnode->prightchild;
	argv = (char **)ft_calloc(cnt + 1, sizeof(char *));
	while (i < cnt)
	{
		argv[i] = ft_strdup(g_data.lexer.pptokens[argnode->pvalue_index[i]]);
		i++;
	}
	return (argv);
}

void	command_not_found_error(char *cmd)
{
	add_history(cmd);
	ft_error_message("nanoshell : command not found : ", 127);
	ft_error_message(cmd, 127);
	ft_error_message("\n", 127);
	exit(g_data.exit_status);
}

char	**allocate_empty_str_in_filepath(char *execve_cmd)
{
	char	**filepath;

	if (!execve_cmd)
	{
		filepath = ft_calloc(2, sizeof(char *));
		if (!filepath)
			ft_error("allocate_empty_str_in_filepath : allocation failed\n");
		filepath[0] = ft_strdup("");
		filepath[1] = NULL;
		return (filepath);
	}
	else
	{
		filepath = ft_calloc(2, sizeof(char *));
		if (!filepath)
			ft_error("allocate_empty_str_in_filepath : allocation failed\n");
		filepath[0] = ft_strdup(execve_cmd);
		filepath[1] = NULL;
		return (filepath);
	}
}

void	free_argv(char **argv, int cnt)
{
	int	i;

	i = 0;
	if (argv)
	{
		while (i < cnt)
		{
			free(argv[i]);
			i++;
		}
		free(argv);
	}
}
