/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:40:41 by yukim             #+#    #+#             */
/*   Updated: 2022/07/04 20:03:59 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_not_ifs(int i, char **str, char **tokens);

int	ft_split_str(char *str, char **tokens)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str && is_ifs(*str))
		{
			while (*str && is_ifs(*str))
				str++;
			if (*str == '\0')
				break ;
		}
		if (is_not_ifs(i, &str, tokens) == ERROR)
			return (ERROR);
		i++;
	}
	tokens[i] = NULL;
	return (i);
}

static int	is_not_ifs(int i, char **str, char **tokens)
{
	int	j;
	int	wlen;
	int	wc_flag;
	int	quote;

	j = 0;
	wc_flag = 0;
	quote = 0;
	wlen = ft_wordlen(*str, i, wc_flag, quote);
	if (wlen == ERROR)
		return (ERROR);
	tokens[i] = ft_calloc(wlen + 1, sizeof(char));
	if (!tokens[i])
		ft_error("ft_split_str : allocation failed\n");
	while (j < wlen)
	{
		tokens[i][j] = **str;
		j++;
		(*str)++;
	}
	tokens[i][j] = '\0';
	return (TRUE);
}
