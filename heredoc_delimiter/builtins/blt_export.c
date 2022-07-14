/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:35 by yukim             #+#    #+#             */
/*   Updated: 2022/07/13 17:33:12 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_variables_ft_export(t_astnode *argsnode, int i, char **input);
static void	export_with_args(t_astnode *args_node);
static void	is_valid_env__error_msg(char *key);

int	ft_export(t_astnode *args_node)
{
	g_data.exit_status = 0;
	if (args_node->prightchild->pvalue_index[1] == END)
		ft_env(TRUE);
	else
		export_with_args(args_node);
	return (g_data.exit_status);
}

static void	export_with_args(t_astnode *args_node)
{
	char	*input;
	char	*key;
	char	*value;
	int		init_flag;
	int		i;

	i = 1;
	while (args_node->prightchild->pvalue_index[i] != END)
	{
		init_variables_ft_export(args_node, i, &input);
		init_flag = init_envp(input, &key, &value);
		if (is_valid_env(key) == ERROR)
		{
			is_valid_env__error_msg(key);
			free(key);
			free(value);
		}
		else if (is_valid_env(key) == TRUE)
			insert_envv(key, value, init_flag);
		i++;
	}
}

static void	init_variables_ft_export(t_astnode *argsnode, int i, char **input)
{
	int		index;

	index = argsnode->prightchild->pvalue_index[i];
	*input = g_data.lexer.pptokens[index];
}

static void	is_valid_env__error_msg(char *key)
{
	ft_error_message("nanoshell: export: ", 1);
	ft_error_message(key, 1);
	ft_error_message(": not a valid identifier\n", 1);
}
