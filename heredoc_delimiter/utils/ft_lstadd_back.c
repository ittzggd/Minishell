/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:43:07 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 17:46:43 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstadd_back(t_envv_node *new)
{
	t_envv_node	*curr;

	if (!new)
		return ;
	curr = g_data.envv_list;
	if (!curr)
		g_data.envv_list = new;
	else
	{
		while (curr->p_link)
			curr = curr->p_link;
		curr->p_link = new;
	}
}
