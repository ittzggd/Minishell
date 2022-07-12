/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:05 by yukim             #+#    #+#             */
/*   Updated: 2022/07/04 14:25:10 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exit_status_argc_error(void);

void	ft_exit(t_astnode *args_node)
{
	int		cnt;
	char	*str;

	cnt = 0;
	g_data.exit_status = 0;
	while (args_node->prightchild->pvalue_index[cnt] != -1)
		cnt++;
	printf("exit\n");
	if (cnt >= 2)
	{
		str = g_data.lexer.pptokens[args_node->prightchild->pvalue_index[1]];
		g_data.exit_status = ft_atoi(str, args_node->prightchild);
		if (cnt > 2)
		{
			g_data.exit_status = exit_status_argc_error();
			return ;
		}
	}
	exit(g_data.exit_status);
}

void	exit_status_numeric_error(t_astnode *args_node)
{
	char	*str;

	str = g_data.lexer.pptokens[args_node->pvalue_index[1]];
	ft_error_message("exit: minishell: ", 255);
	ft_error_message(str, 255);
	ft_error_message(": numeric argument required", 255);
	exit(255);
}

static int	exit_status_argc_error(void)
{
	ft_error_message("minishell: exit :too many arguments\n", 1);
	return (1);
}
