/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:04:31 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 14:30:18 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	case_is_quote_next(int *wc_flag, int *i, char *str);
static int	case_is_quote(int *i, char *str, int quote);
static int	case_else_in_while(int *i, char *str);

int	case_redirection(char const *str, int *i)
{
	if (is_redirection(&str[*i]) == ERROR)
		return (ERROR);
	while (str[*i] && is_redirection(&str[*i]))
		(*i)++;
	return (TRUE);
}

int	ft_wordlen(char const *str, int i, int wc_flag, int quote)
{
	int	ret;

	i = 0;
	wc_flag = 1;
	while (str[i])
	{
		quote = is_quote(str[i]);
		if (str[i] && quote)
		{
			ret = case_is_quote(&i, (char *)str, quote);
			if (ret == ERROR)
				return (ERROR);
			else if (ret == CONTINUE)
				continue ;
		}
		ret = case_is_quote_next(&wc_flag, &i, (char *)str);
		if (ret == ERROR || ret == TRUE)
			return (ret);
		else if (ret == CONTINUE)
			continue ;
		if (wc_flag == 1)
			break ;
	}
	return (i);
}

static int	case_is_quote_next(int *wc_flag, int *i, char *str)
{
	int	ret;

	ret = 0;
	if (str[*i] && is_redirection(&str[*i]))
	{
		case_redirection(str, i);
		*wc_flag = 1;
	}
	else if (str[*i] && is_pipe(&str[*i]))
		return (TRUE);
	else if (str[*i] && is_ifs(str[*i]))
		*wc_flag = 1;
	else
	{
		ret = case_else_in_while(i, str);
		if (ret == ERROR || ret == CONTINUE)
			return (ret);
	}
	return (0);
}

static int	case_is_quote(int *i, char *str, int quote)
{
	int	ret_status;

	ret_status = 0;
	(*i)++;
	while (str[*i] && quote != is_quote(str[*i]))
		(*i)++;
	if (str[*i] == '\0' && quote != is_quote(str[*i]))
	{
		syntax_error(&ret_status);
		return (ERROR);
	}
	if (is_quote(str[*i + 1]))
	{
		(*i)++;
		return (CONTINUE);
	}
	return (0);
}

static int	case_else_in_while(int *i, char *str)
{
	int	quote;
	int	ret;

	quote = 0;
	while (str[*i] && !is_ifs(str[*i]) && !is_redirection(&str[*i]) \
						&& !is_pipe(&str[*i]))
	{
		(*i)++;
		quote = is_quote(str[*i]);
		if (str[*i] && quote)
		{
			ret = case_is_quote(i, str, quote);
			if (ret == ERROR || ret == CONTINUE)
				return (ret);
		}
	}
	return (0);
}
