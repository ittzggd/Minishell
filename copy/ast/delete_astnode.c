/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_astnode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 03:38:03 by yukim             #+#    #+#             */
/*   Updated: 2022/07/02 17:17:24 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	delete_astnode(t_astnode *node)
{
	if (node)
	{
		free(node->pvalue_index);
		delete_astnode(node->pleftchild);
		delete_astnode(node->prightchild);
		free(node);
	}
}
