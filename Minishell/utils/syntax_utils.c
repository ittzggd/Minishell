/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:08:14 by yukim             #+#    #+#             */
/*   Updated: 2022/07/11 19:11:27 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	syntax_check_command(int *curr)
{
	int	*type;
	int	prev;

	type = g_data.lexer.ptype;
	prev = *curr - 1;
	if (*curr != 0 && (type[prev] == T_REDIRECTION || type[prev] == T_OPTION \
			|| type[prev] == T_COMMAND))
		type[*curr] = T_WORD;
}

void	syntax_check_redirection(int *curr, int *ret_status)
{
	int		*type;
	int		prev;

	type = g_data.lexer.ptype;
	prev = *curr - 1;
	if (type[*curr + 1] != T_WORD \
			|| (*curr != 0 && (type[prev] == T_REDIRECTION)))
		syntax_error(ret_status);
}

void	syntax_check_pipe(int *curr, int *ret_status)
{
	int		*type;
	int		prev;

	prev = *curr - 1;
	type = g_data.lexer.ptype;
	if ((type[*curr + 1] != T_COMMAND && type[*curr + 1] != T_REDIRECTION) \
			|| (*curr != 0 && type[prev] == T_REDIRECTION))
		syntax_error(ret_status);
}

void	syntax_check_null(int *curr, int *ret_status)
{
	int		*type;
	int		prev;

	prev = *curr - 1;
	type = g_data.lexer.ptype;
	if (*curr != 0 && (type[prev] == T_REDIRECTION || type[prev] == T_PIPE))
	{
		ft_error_message("NULL_ERROR\n", 1);
		*ret_status = 0;
	}
}
