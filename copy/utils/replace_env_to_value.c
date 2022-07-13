/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_to_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:40:32 by yukim             #+#    #+#             */
/*   Updated: 2022/07/13 18:58:49 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	get_replaced_str(int i, int j, char **ret, char *input);
static void	case_double_quote(char *input, int *i, int *j, char *ret);
static void	case_not_quote(char *input, int *i, int *j, char *ret);
static void	case_quote(char *input, int *i, int *j, char *ret);

char	*replace_env_to_value(char *input)
{
	int		len;
	char	*replaced_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = get_len_replaced_str(input);
	replaced_str = ft_calloc(len + 1, sizeof(char));
	if (!replaced_str)
		ft_error("replace_env_to_value : allocation failed\n");
	get_replaced_str(i, j, &replaced_str, input);
	return (replaced_str);
}

static void	get_replaced_str(int i, int j, char **ret, char *input)
{
	int	quote;

	while (input[i])
	{
		quote = is_quote(input[i]);
		if (input[i] && quote == FALSE)
		{
			case_not_quote(input, &i, &j, *ret);
			continue ;
		}
		case_quote(input, &i, &j, *ret);
	}
	(*ret)[j] = '\0';
}

static void	case_quote(char *input, int *i, int *j, char *ret)
{
	int	quote;

	quote = is_quote(input[*i]);
	copy_char(input, i, j, ret);
	while (input[*i] && quote != is_quote(input[*i]))
	{
		if (quote == DOUBLE_QUOTE)
			case_double_quote(input, i, j, ret);
		else if (quote == SINGLE_QUOTE)
			copy_char(input, i, j, ret);
	}
	if (input[*i])
		copy_char(input, i, j, ret);
}

static void	case_double_quote(char *input, int *i, int *j, char *ret)
{
	if (input[*i] == '$' && input[*i + 1] == '?')
		replace_env_case_exit_status(i, j, ret);
	else if (input[*i] == '$' && !is_quote(input[*i + 1]))
		replace_env_case_replace(i, j, input, ret);
	else
		copy_char(input, i, j, ret);
}

static void	case_not_quote(char *input, int *i, int *j, char *ret)
{
	if (input[*i] == '$' && input[*i + 1] == '?')
		replace_env_case_exit_status(i, j, ret);
	else if (input[*i] == '$' && input[*i + 1] != '\0')
		replace_env_case_replace(i, j, input, ret);
	else
		copy_char(input, i, j, ret);
}
