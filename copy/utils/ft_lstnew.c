/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:42:31 by yukim             #+#    #+#             */
/*   Updated: 2022/07/04 14:39:20 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_envv_node	*ft_lstnew(t_envv_node element)
{
	t_envv_node	*new;

	new = ft_calloc(1, sizeof(t_envv_node));
	if (!new)
		ft_error("ft_lstnew : allocation failed");
	new->key = ft_strdup(element.key);
	new->value = ft_strdup(element.value);
	new->init_flag = element.init_flag;
	return (new);
}
