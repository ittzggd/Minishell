/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 03:33:21 by yukim             #+#    #+#             */
/*   Updated: 2022/07/04 14:24:35 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tree_cmd(t_astnode *ast_node, int index)
{
	char	**tokens;
	int		*type;

	if (ast_node->nodetype != A_COMMAND)
		return ;
	tokens = g_data.lexer.pptokens;
	type = g_data.lexer.ptype;
	ast_node->pleftchild = insert_leftchildnode_ast(ast_node, 0);
	ast_node->prightchild = insert_rightchildnode_ast(ast_node, A_ARGUMENTS);
	tree_args(ast_node->prightchild, index);
	while (type[index] != T_PIPE && tokens[index])
	{
		if (type[index] == T_REDIRECTION)
		{
			ast_node->pleftchild->nodetype = A_REDIRECTIONS;
			tree_reds(ast_node->pleftchild, index);
			break ;
		}
		index++;
	}
}
