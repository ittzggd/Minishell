/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postorder_travel_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:30:40 by yukim             #+#    #+#             */
/*   Updated: 2022/07/13 17:22:40 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	postorder_travel_command(t_astnode *cmdnode)
{
	int		ret;

	ret = 0;
	if (cmdnode)
	{
		ret = postorder_travel_reds(cmdnode->pleftchild);
		if (ret == ERROR)
			return ;
		if (cmdnode->prightchild->prightchild->pvalue_index)
			exec_cmd(cmdnode->prightchild);
	}
}

int	postorder_travel_reds(t_astnode *reds_node)
{
	int		ret;

	ret = 0;
	if (reds_node->pleftchild)
	{
		ret = goto_redirection(reds_node->pleftchild);
		if (ret == ERROR)
			return (ret);
	}
	if (reds_node->prightchild)
	{
		postorder_travel_reds(reds_node->prightchild);
	}
	return (ret);
}

int	goto_redirection(t_astnode *red_node)
{
	char	*red;
	char	*filename;
	int		ret;

	ret = 0;
	if (!red_node->prightchild->pvalue_index)
		return (ret);
	red = g_data.lexer.pptokens[red_node->pleftchild->pvalue_index[0]];
	filename = g_data.lexer.pptokens[red_node->prightchild->pvalue_index[0]];
	if (ft_strncmp(red, "<", -1))
		ret = in_red(filename);
	else if (ft_strncmp(red, ">", -1))
		out_red(filename);
	else if (ft_strncmp(red, ">>", -1))
		append_red(filename);
	else if (ft_strncmp(red, "<<", -1))
		heredoc(filename);
	return (ret);
}
