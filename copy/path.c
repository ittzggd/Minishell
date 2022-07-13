/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:12:15 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 17:29:35 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static int	get_path_len(char **path)
{
	int	i;

	i = 0;
	if (!path || !*path)
		return (0);
	if (path)
	{
		while (path[i])
			i++;
	}
	return (i);
}

static char	*path_join(char *path_env, char *path_cmd)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	if (!path_env)
		return (NULL);
	len1 = ft_strlen(path_env);
	len2 = ft_strlen(path_cmd);
	len2++;
	new_str = (char *)ft_calloc(((len1 + len2) + 1), sizeof(char));
	if (!new_str)
		ft_error("path_join : allocation failed\n");
	ft_strlcpy(new_str, path_env, len1 + 1);
	*(new_str + len1) = '/';
	ft_strlcat(new_str + len1 + 1, path_cmd, len2 + 1);
	return (new_str);
}

char	**join_filepath(char *execve_cmd)
{
	int		i;
	int		len;
	char	**path;
	char	**filepath;

	i = 0;
	path = ft_split(get_envv("PATH"), ':');
	if (!path)
		return (NULL);
	len = get_path_len(path);
	filepath = ft_calloc(len + 1, sizeof(char *));
	if (!filepath)
		ft_error("join_filepath : allocation failed\n");
	while (path[i])
	{
		filepath[i] = path_join(path[i], execve_cmd);
		i++;
	}
	filepath[i] = NULL;
	return (filepath);
}
