/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 22:34:31 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 17:15:14 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		s_len;
	int		i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s) + 1;
	ptr = ft_calloc(s_len, sizeof(char));
	if (!ptr)
		ft_error("ft_strdup : allocation failed\n");
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
