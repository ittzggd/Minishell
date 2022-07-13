/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvlist_to_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:08:28 by yukim             #+#    #+#             */
/*   Updated: 2022/07/13 14:25:49 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_envv_cnt(t_envv_node *envv_list);

char	**envvlist_to_envp(void)
{
	int			cnt;
	int			i;
	char		**envp;
	t_envv_node	*curr;

	cnt = get_envv_cnt(g_data.envv_list);
	envp = (char **)ft_calloc((cnt + 1), sizeof(char *));
	if (!envp)
		ft_error("envvlist_to_envp : alloction failed\n");
	curr = g_data.envv_list;
	i = 0;
	while (curr)
	{
		envp[i] = envv_join(curr->key, curr->value);
		i++;
		curr = curr->p_link;
	}
	envp[i] = NULL;
	return (envp);
}

char	*envv_join(char *key, char *value)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	if (!key)
		return (NULL);
	len1 = ft_strlen(key);
	len2 = ft_strlen(value);
	if (value && *value)
		len2++;
	new_str = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!new_str)
		ft_error("envv_join : allocation failed\n");
	ft_strlcpy(new_str, key, len1 + 1);
	if (value && *value)
	{
		*(new_str + len1) = '=';
		ft_strlcat(new_str + len1 + 1, value, len2 + 1);
	}
	return (new_str);
}

static int	get_envv_cnt(t_envv_node *envv_list)
{
	t_envv_node	*curr;
	int			cnt;

	cnt = 0;
	curr = envv_list;
	while (curr)
	{
		cnt++;
		curr = curr->p_link;
	}
	return (cnt);
}
