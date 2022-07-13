/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:20:15 by hejang            #+#    #+#             */
/*   Updated: 2022/07/03 17:07:07 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_ast(void)
{
	t_astnode	*root_node;

	root_node = ft_calloc(1, sizeof(t_astnode));
	if (!root_node)
		ft_error("init ast : allocation failed\n");
	g_data.ast.prootnode = root_node;
	recur_pipe(root_node, 0);
}

int	recur_pipe(t_astnode *astnode, int index)
{
	char	**tokens;
	int		c_index;

	tokens = g_data.lexer.pptokens;
	c_index = index;
	while (tokens[index])
	{
		if (g_data.lexer.ptype[index] == T_PIPE)
		{
			astnode->nodetype = A_PIPE;
			init_idx(index, astnode);
			astnode->pleftchild = insert_leftchildnode_ast(astnode, A_COMMAND);
			tree_cmd(astnode->pleftchild, c_index);
			astnode->prightchild = insert_rightchildnode_ast(astnode, 0);
			if (recur_pipe(astnode->prightchild, index + 1))
				return (TRUE);
		}
		index++;
	}
	astnode->nodetype = A_COMMAND;
	tree_cmd(astnode, c_index);
	return (TRUE);
}
