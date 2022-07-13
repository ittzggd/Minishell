/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:19:44 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 14:35:51 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	replace_quote_env(void)
{
	int		i;

	i = 0;
	while (g_data.lexer.pptokens[i] != NULL)
	{
		if (g_data.lexer.ptype[i] == T_REDIRECTION)
		{
			i++;
			if (g_data.lexer.pptokens[i] == NULL)
				break ;
			if (ft_strncmp("<<", g_data.lexer.pptokens[i - 1], -1) == FALSE)
				rm_argument_quote(i);
		}
		if (g_data.lexer.ptype[i] == T_COMMAND \
				|| g_data.lexer.ptype[i] == T_WORD)
			rm_argument_quote(i);
		i++;
	}
}

void	rm_argument_quote(int i)
{
	char	*tokens;
	char	*rm_quote;

	tokens = g_data.lexer.pptokens[i];
	rm_quote = remove_quote(tokens);
	g_data.lexer.pptokens[i] = rm_quote;
	free(tokens);
}
