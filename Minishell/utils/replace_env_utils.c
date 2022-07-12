/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:56:21 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 15:49:08 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_len_case_exit_status(int *i, int *ret_len)
{
	char	*value;

	value = ft_itoa(g_data.exit_status);
	*ret_len = *ret_len + ft_strlen(value);
	*i = *i + 2;
	free(value);
}

void	get_len_case_replace_env(int *i, int *ret_len, char *input)
{
	char	*key;
	char	*value;
	int		key_len;

	(*i)++;
	if (!ft_is_alpha(input[*i]))
		key_len = 1;
	else
		key_len = ft_key_len(input, *i);
	key = ft_calloc(key_len + 1, sizeof(char));
	if (!key)
		ft_error("get_len_case_replace_env : allocation failed\n");
	ft_strlcpy(key, &input[*i], key_len + 1);
	value = get_envv(key);
	if (!value)
		value = ft_strdup("");
	*i = *i + key_len;
	*ret_len = *ret_len + ft_strlen(value);
	free(key);
	free(value);
}

void	replace_env_case_exit_status(int *i, int *j, char *ret)
{
	char	*value;

	value = ft_itoa(g_data.exit_status);
	ft_strlcpy(&ret[*j], value, ft_strlen(value) + 1);
	*j = *j + ft_strlen(value);
	*i = *i + 2;
	free(value);
}

void	replace_env_case_replace(int *i, int *j, char *input, char *ret)
{
	char	*key;
	char	*value;
	int		key_len;

	(*i)++;
	if (!ft_is_alpha(input[*i]))
		key_len = 1;
	else
		key_len = ft_key_len(input, *i);
	key = ft_calloc(key_len + 1, sizeof(char));
	if (!key)
		ft_error("replace_env_case_replace : allocation failed\n");
	ft_strlcpy(key, &input[*i], key_len + 1);
	value = get_envv(key);
	if (!value)
		value = ft_strdup("");
	ft_strlcpy(&ret[*j], value, ft_strlen(value) + 1);
	*i = *i + key_len;
	*j = *j + ft_strlen(value);
	free(key);
	free(value);
}

void	copy_char(char *input, int *i, int *j, char *ret)
{
	ret[*j] = input[*i];
	(*i)++;
	(*j)++;
}
