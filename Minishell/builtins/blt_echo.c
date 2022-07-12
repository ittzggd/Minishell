/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:17 by yukim             #+#    #+#             */
/*   Updated: 2022/07/08 18:19:01 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	do_echo(t_astnode *args_node);
static void	do_echo_print(int *arg, char *rm_quote_str);

int	ft_echo(t_astnode *args_node)
{
	int	*arg;
	int	option_flag;

	option_flag = FALSE;
	arg = args_node->prightchild->pvalue_index;
	while (*arg != END)
	{
		if (g_data.lexer.ptype[*arg] == T_OPTION)
			option_flag = TRUE;
		arg++;
	}
	do_echo(args_node);
	if (option_flag != TRUE)
		printf("\n");
	g_data.exit_status = 0;
	return (TRUE);
}

static int	do_echo(t_astnode *args_node)
{
	int		*arg;
	char	*str;

	arg = args_node->prightchild->pvalue_index;
	arg++;
	while (*arg != END)
	{
		if (g_data.lexer.ptype[*arg] == T_OPTION)
		{
			arg++;
			continue ;
		}
		str = g_data.lexer.pptokens[*arg];
		do_echo_print(arg, str);
		arg++;
	}
	return (TRUE);
}

static void	do_echo_print(int *arg, char *rm_quote_str)
{
	if (!rm_quote_str)
		printf ("\n");
	else
		printf("%s", rm_quote_str);
	if (*(arg + 1) != END)
		printf(" ");
}
