/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:36:07 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 15:47:47 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_len_without_quote(char *quote_str);
static void	get_len_case_quote(int quote, int *i, int *ret_len, char *quotestr);
static void	get_removed_str(int i, int j, char **ret, char *quote_str);

char	*remove_quote(char *quote_str)
{
	char	*removed_str;
	size_t	removed_str_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	removed_str_len = get_len_without_quote(quote_str);
	removed_str = ft_calloc(removed_str_len + 1, sizeof(char));
	if (!removed_str)
		ft_error("remove_quote : allocation failed\n");
	get_removed_str(i, j, &removed_str, quote_str);
	return (removed_str);
}

static int	get_len_without_quote(char *quote_str)
{
	int	i;
	int	ret_len;
	int	quote;

	if (!quote_str)
		return (0);
	i = 0;
	ret_len = 0;
	while (quote_str[i])
	{
		quote = is_quote(quote_str[i]);
		if (quote_str[i] && quote == FALSE)
		{
			i++;
			ret_len++;
			continue ;
		}
		get_len_case_quote(quote, &i, &ret_len, quote_str);
		i++;
	}
	return (ret_len);
}

static void	get_len_case_quote(int quote, int *i, int *ret_len, char *quotestr)
{
	(*i)++;
	while (quotestr[*i] && quote != is_quote(quotestr[*i]))
	{
		(*i)++;
		(*ret_len)++;
	}
}

static void	get_removed_str(int i, int j, char **ret, char *quote_str)
{
	int	quote;

	while (quote_str[i])
	{
		quote = is_quote(quote_str[i]);
		if (quote_str[i] && quote == FALSE)
		{
			copy_char(quote_str, &i, &j, *ret);
			continue ;
		}
		i++;
		while (quote_str[i] && quote != is_quote(quote_str[i]))
			copy_char(quote_str, &i, &j, *ret);
		i++;
	}
	(*ret)[j] = '\0';
}
