/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:46:30 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 16:56:02 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (ERROR);
	while (i < n)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (TRUE);
		if (s1[i] != s2[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}
