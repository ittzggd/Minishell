/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 23:22:36 by hejang            #+#    #+#             */
/*   Updated: 2022/07/13 15:41:55 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	analyze_input(char *input)
{
	char	*replaced_str;
	int		tokens_cnt;

	replaced_str = replace_env_to_value(input);
	if (tokenize_input(replaced_str, &tokens_cnt) == ERROR)
	{
		free(replaced_str);
		return (ERROR);
	}
	lexical_analysis(&tokens_cnt);
	if (syntax_analysis(&tokens_cnt) != 0)
	{
		free(replaced_str);
		return (ERROR);
	}
	replace_quote_env();
	free(replaced_str);
	return (TRUE);
}

int	tokenize_input(char *input, int *tokens_cnt)
{
	int		split_index;
	int		size;

	*tokens_cnt = ft_wordcount(input);
	if (*tokens_cnt == ERROR)
	{
		g_data.exit_status = 258;
		return (ERROR);
	}
	size = *tokens_cnt + 1;
	g_data.lexer.pptokens = ft_calloc(size, sizeof(char *));
	if (!g_data.lexer.pptokens)
		ft_error("tokenize_input : allocation failed\n");
	split_index = ft_split_str((char *)input, g_data.lexer.pptokens);
	if (split_index == ERROR)
		return (ERROR);
	return (TRUE);
}
