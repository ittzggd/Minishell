/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:36:09 by yukim             #+#    #+#             */
/*   Updated: 2022/07/08 18:26:25 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_ifs(const char c)
{
	return ((c == '\n' || c == '\t' || c == ' '));
}

int	is_redirection(const char *s)
{
	int	r_cnt;

	r_cnt = 0;
	while (*s == '<' || *s == '>')
	{
		r_cnt++;
		if (r_cnt > 2 || (r_cnt == 2 && *s != *(s - 1)))
			return (ERROR);
		s++;
	}
	return (r_cnt);
}

int	is_quote(const char c)
{
	if (c == '\'')
		return (SINGLE_QUOTE);
	else if (c == '\"')
		return (DOUBLE_QUOTE);
	return (FALSE);
}

int	is_pipe(const char *s)
{
	int	p_cnt;

	p_cnt = 0;
	while (*s == '|')
	{
		p_cnt++;
		if (p_cnt > 1)
			return (ERROR);
		s++;
	}
	return (p_cnt);
}
