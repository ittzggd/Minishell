/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len_replaced_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:52:01 by yukim             #+#    #+#             */
/*   Updated: 2022/07/13 19:26:37 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	case_quote(int quote, int *i, int *ret_len, char *input);
static void	case_double_quote(int quote, int *i, int *ret_len, char *input);
static void	case_single_quote(int quote, int *i, int *ret_len, char *input);
static void	case_not_quote(int *i, int *ret_len, char *input);

int	get_len_replaced_str(char *input)
{
	int	i;
	int	ret_len;
	int	quote;

	if (!input)
		return (0);
	i = 0;
	ret_len = 0;
	while (input[i])
	{
		quote = is_quote(input[i]);
		if (input[i] && quote == FALSE)
		{
			if (is_heredoc(&input[i]) == TRUE)
			{
				get_len_case_heredoc_del(&i, &ret_len, input);
				continue ;
			}
			case_not_quote(&i, &ret_len, input);
			continue ;
		}
		case_quote(quote, &i, &ret_len, input);
	}
	return (ret_len);
}

static void	case_quote(int quote, int *i, int *ret_len, char *input)
{
	if (input[*i] && quote == DOUBLE_QUOTE)
		case_double_quote(quote, i, ret_len, input);
	else if (input[*i] && quote == SINGLE_QUOTE)
		case_single_quote(quote, i, ret_len, input);
	if (input[*i])
	{
		(*i)++;
		(*ret_len)++;
	}
}

static void	case_double_quote(int quote, int *i, int *ret_len, char *input)
{
	(*i)++;
	(*ret_len)++;
	while (input[*i] && quote != is_quote(input[*i]))
	{
		if (input[*i] == '$' && input[*i + 1] == '?')
			get_len_case_exit_status(i, ret_len);
		else if (input[*i] == '$' && !is_quote(input[*i + 1]))
			get_len_case_replace_env(i, ret_len, input);
		else
		{
			(*i)++;
			(*ret_len)++;
		}
	}
}

static void	case_single_quote(int quote, int *i, int *ret_len, char *input)
{
	(*i)++;
	(*ret_len)++;
	while (input[*i] && quote != is_quote(input[*i]))
	{
		(*i)++;
		(*ret_len)++;
	}
}

static void	case_not_quote(int *i, int *ret_len, char *input)
{
	if (input[*i] == '$' && input[*i + 1] == '?')
		get_len_case_exit_status(i, ret_len);
	else if (input[*i] == '$' && input[*i + 1] != '\0')
		get_len_case_replace_env(i, ret_len, input);
	else
	{
		(*i)++;
		(*ret_len)++;
	}
}
