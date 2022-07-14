/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:46:06 by hejang            #+#    #+#             */
/*   Updated: 2022/07/13 20:22:21 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_path_env(char	*execve_cmd);
static void	dir_without_path_env(char *execve_cmd);
static void	loop_in_fork(int idx, char *ecve_cmd, char **argv, char **filepath);

void	fork_before_run_execve_child(int idx, char *ecve_cmd, char **argv)
{
	char	**filepath;

	reset_signal();
	if (check_path_env(ecve_cmd) == ERROR)
		exit(g_data.exit_status);
	if (check_path_env(ecve_cmd) == TRUE && (*ecve_cmd) == '\0')
		command_not_found_error(ecve_cmd);
	if (ft_strchr(ecve_cmd, '/'))
	{
		filepath = ft_calloc(2, sizeof(char *));
		filepath[0] = ft_strdup(ecve_cmd);
		filepath[1] = NULL;
	}
	else
		filepath = join_filepath(ecve_cmd);
	if (!filepath)
		filepath = allocate_empty_str_in_filepath(ecve_cmd);
	loop_in_fork(idx, ecve_cmd, argv, filepath);
}

static int	check_path_env(char	*execve_cmd)
{
	t_envv_node	*path_node;
	struct stat	buf;

	path_node = get_el_node(g_data.envv_list, "PATH");
	if (!path_node || ft_strchr(execve_cmd, '/'))
	{
		lstat(execve_cmd, &buf);
		if (errno == ENOENT)
		{
			ft_error_message("nanoshell : ", 127);
			ft_error_message(execve_cmd, 127);
			ft_error_message(": No such file or directory\n", 127);
			return (ERROR);
		}
		if (S_ISDIR(buf.st_mode))
		{
			dir_without_path_env(execve_cmd);
			return (ERROR);
		}
		else if (S_ISREG(buf.st_mode))
			return (FALSE);
	}
	return (TRUE);
}

static void	dir_without_path_env(char *execve_cmd)
{
	ft_error_message("nanoshell : ", 126);
	ft_error_message(execve_cmd, 126);
	ft_error_message(": is a directory\n", 126);
}

static void	loop_in_fork(int idx, char *ecve_cmd, char **argv, char **filepath)
{
	char	**envp;

	envp = envvlist_to_envp();
	while (filepath[idx])
	{
		execve(filepath[idx], argv, envp);
		if (errno == ENOENT)
			idx++;
		else if (errno == EACCES)
		{
			ft_error_message("nanoshell : ", 126);
			ft_error_message(ecve_cmd, 126);
			ft_error_message(": Permission denied\n", 126);
			exit(g_data.exit_status);
		}
		else
			break ;
	}
	if (!filepath[idx])
		command_not_found_error(argv[0]);
}
