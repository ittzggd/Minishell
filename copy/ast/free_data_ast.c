/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 03:30:35 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 17:06:53 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	free_data_ast(void)
{
	if (g_data.ast.prootnode)
	{
		delete_astnode(g_data.ast.prootnode);
		ft_bzero(&g_data.ast, sizeof(t_ast));
	}
}
