/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 11:23:13 by yukim             #+#    #+#             */
/*   Updated: 2022/06/05 14:27:31 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*save;

	save = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
		{
			save = (char *)s + i;
			return (save);
		}
		i++;
	}
	if ((char )c == '\0')
		save = (char *)s + i;
	return (save);
}
