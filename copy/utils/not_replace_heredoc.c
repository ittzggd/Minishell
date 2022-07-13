/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_replace_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 19:18:03 by yukim             #+#    #+#             */
/*   Updated: 2022/07/13 19:45:58 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_heredoc(char *str)
{
	if (!str || is_redirection((const char *)str) == ERROR)
		return (FALSE);
	return (ft_strncmp("<<", str, 2)); 
}

void	get_len_case_heredoc_del(int *i, int *ret_len, char *input)
{
	if (ft_strncmp("<<", &input[*i], 2) == TRUE)
	{
		*i = *i + 2;
		*ret_len = *ret_len + 2;
	}
	while (input[*i])
	{
		if (is_ifs(input[*i]) && input[(*i) + 1] != '\0')
		{
			(*i)++;
			(*ret_len)++;
		}
		else
			break ;
	}
	while (input[*i])
	{
		if (is_ifs(input[*i]) || input[*i] == '|' \
				|| input[*i] == '<' || input[*i] == '>')
			break ;
		(*i)++;
		(*ret_len)++;
	}
}

void	replace_case_heredoc_del(char *input, int *i, int *j, char *ret)
{
	if (ft_strncmp("<<", &input[*i], 2) == TRUE)
	{
		copy_char(input, i, j, ret);
		copy_char(input, i, j, ret);
	}
	while (input[*i])
	{
		if (is_ifs(input[*i]) && input[(*i) + 1] != '\0')
			copy_char(input, i, j, ret);
		else
			break ;
	}
	while (input[*i])
	{
		if (is_ifs(input[*i]) || input[*i] == '|' \
				|| input[*i] == '<' || input[*i] == '>')
			break ;
		copy_char(input, i, j, ret);
	}
}

