/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postorder_travel_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:30:40 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 17:07:38 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	postorder_travel_command(t_astnode *cmdnode)
{
	if (cmdnode)
	{
		postorder_travel_reds(cmdnode->pleftchild);
		if (cmdnode->prightchild->prightchild->pvalue_index)
			exec_cmd(cmdnode->prightchild);
	}
}

void	postorder_travel_reds(t_astnode *reds_node)
{
	if (reds_node->pleftchild)
	{
		goto_redirection(reds_node->pleftchild);
	}
	if (reds_node->prightchild)
	{
		postorder_travel_reds(reds_node->prightchild);
	}
}

void	goto_redirection(t_astnode *red_node)
{
	char	*red;
	char	*filename;

	if (!red_node->prightchild->pvalue_index)
		return ;
	red = g_data.lexer.pptokens[red_node->pleftchild->pvalue_index[0]];
	filename = g_data.lexer.pptokens[red_node->prightchild->pvalue_index[0]];
	if (ft_strncmp(red, "<", -1))
		in_red(filename);
	else if (ft_strncmp(red, ">", -1))
		out_red(filename);
	else if (ft_strncmp(red, ">>", -1))
		append_red(filename);
	else if (ft_strncmp(red, "<<", -1))
		heredoc(filename);
}
