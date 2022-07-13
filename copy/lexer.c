/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:44:47 by hejang            #+#    #+#             */
/*   Updated: 2022/07/13 15:34:04 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	set_lexer_ptype(void);
static int	get_type(char *value);
static void	type_word_to_cmd(int *i, int *cmd_flag);
static void	word_to_option(int *i);

void	lexical_analysis(int *tokenize_cnt)
{
	int	size;

	size = *tokenize_cnt + 1;
	g_data.lexer.ptype = (int *)ft_calloc(size, sizeof(int));
	if (!g_data.lexer.ptype)
		ft_error("lexical_analysis : allocation failed\n");
	set_lexer_ptype();
}

static void	set_lexer_ptype(void)
{
	int		i;
	int		command_flag;

	i = 0;
	command_flag = FALSE;
	while (g_data.lexer.pptokens[i])
	{
		g_data.lexer.ptype[i] = get_type(g_data.lexer.pptokens[i]);
		if (g_data.lexer.ptype[i] == T_WORD)
			type_word_to_cmd(&i, &command_flag);
		if (g_data.lexer.ptype[i] == T_PIPE)
		{
			g_data.pipe_cnt++;
			command_flag = FALSE;
		}
		else if (g_data.lexer.ptype[i] == T_REDIRECTION)
		{
			if (ft_strncmp("<<", g_data.lexer.pptokens[i], -1))
				g_data.hd.heredoc_cnt++;
		}
		else if (g_data.lexer.ptype[i] == T_WORD)
			word_to_option(&i);
		i++;
	}
}

static int	get_type(char *value)
{
	int	type;

	if (!value || *value == '\0')
		type = T_NULL;
	else if (is_pipe(value))
		type = T_PIPE;
	else if (is_redirection(value))
		type = T_REDIRECTION;
	else if (is_quote(*value))
	{
		value++;
		if (*value == '\0')
			return (T_WORD);
		else
			type = get_type(value);
		if (type == T_PIPE || type == T_REDIRECTION || type == T_ENV)
			type = T_WORD;
	}
	else
		type = T_WORD;
	return (type);
}

static void	type_word_to_cmd(int *i, int *cmd_flag)
{
	int	*type;

	type = g_data.lexer.ptype;
	if (*i == 0)
	{
		type[*i] = T_COMMAND;
		*cmd_flag = TRUE;
	}
	else if (*i != 0 && type[*i - 1] == T_PIPE)
	{
		type[*i] = T_COMMAND;
		*cmd_flag = TRUE;
	}
	else if (*cmd_flag == FALSE && (*i > 1) && type[*i - 2] == T_REDIRECTION)
	{
		type[*i] = T_COMMAND;
		*cmd_flag = TRUE;
	}
}

static void	word_to_option(int *i)
{
	int		*type;
	char	**tokens;

	type = g_data.lexer.ptype;
	tokens = g_data.lexer.pptokens;
	if (i != 0 && (type[*i - 1] == T_COMMAND || type[*i - 1] == T_OPTION))
	{
		if (is_option(tokens[*i]))
			type[*i] = T_OPTION;
	}
}
