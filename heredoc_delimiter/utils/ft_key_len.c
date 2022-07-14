/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:36:35 by yukim             #+#    #+#             */
/*   Updated: 2022/07/11 14:36:40 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_key_len(char *token, int j)
{
	int		key_len;

	key_len = 0;
	while (token[j + key_len])
	{
		if (!ft_is_alpha(token[j + key_len]) && (token[j + key_len] != '_') \
			&& !ft_is_digit(token[j + key_len]) && (token[j + key_len] != '?'))
			break ;
		key_len++;
	}
	return (key_len);
}
