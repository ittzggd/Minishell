/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 03:32:01 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 17:07:48 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

static int	args_utils(int *index, t_astnode *args_rightchild);

int	tree_args(t_astnode *ast_node, int index)
{
	t_astnode	*args_leftchild;
	t_astnode	*args_rightchild;

	if (ast_node->nodetype != A_ARGUMENTS)
		return (ERROR);
	args_leftchild = insert_leftchildnode_ast(ast_node, A_FILEPATH);
	while (g_data.lexer.pptokens[index] && g_data.lexer.ptype[index] != T_PIPE)
	{
		if (g_data.lexer.ptype[index] == T_COMMAND)
			break ;
		index++;
	}
	init_idx(index, args_leftchild);
	args_rightchild = insert_rightchildnode_ast(ast_node, A_ARGUMENT);
	while (g_data.lexer.pptokens[index] && g_data.lexer.ptype[index] != T_PIPE)
		args_utils(&index, args_rightchild);
	return (TRUE);
}

static int	args_utils(int *index, t_astnode *args_rightchild)
{
	int	*type;

	type = g_data.lexer.ptype;
	if (type[*index] == T_REDIRECTION)
		(*index)++;
	else
		init_idx(*index, args_rightchild);
	(*index)++;
	return (TRUE);
}
