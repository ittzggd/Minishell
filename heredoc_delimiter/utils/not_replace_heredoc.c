/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_replace_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 19:18:03 by yukim             #+#    #+#             */
/*   Updated: 2022/07/13 19:56:34 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	get_len_heredoc_loop(int *i, int *ret_len, char *input);
static void	replace_heredoc_loop(char *input, int *i, int *j, char *ret);

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
	get_len_heredoc_loop(i, ret_len, input);
}

static void	get_len_heredoc_loop(int *i, int *ret_len, char *input)
{
	int	quote;

	while (input[*i])
	{
		quote = is_quote(input[*i]);
		if (quote)
		{
			(*i)++;
			(*ret_len)++;
			while (input[*i] && quote != is_quote(input[*i]))
			{
				(*i)++;
				(*ret_len)++;
			}
		}
		else if (is_ifs(input[*i]) || input[*i] == '|' \
				|| input[*i] == '<' || input[*i] == '>')
			break ;
		if (input[*i])
		{
			(*i)++;
			(*ret_len)++;
		}
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
	replace_heredoc_loop(input, i, j, ret);
}

static void	replace_heredoc_loop(char *input, int *i, int *j, char *ret)
{
	int	quote;

	while (input[*i])
	{
		quote = is_quote(input[*i]);
		if (quote)
		{
			copy_char(input, i, j, ret);
			while (input[*i] && quote != is_quote(input[*i]))
				copy_char(input, i, j, ret);
		}
		else if (is_ifs(input[*i]) || input[*i] == '|' \
				|| input[*i] == '<' || input[*i] == '>')
			break ;
		if (input[*i])
			copy_char(input, i, j, ret);
	}
}
