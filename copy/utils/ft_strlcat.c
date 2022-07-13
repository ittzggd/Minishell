/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:57:47 by hejang            #+#    #+#             */
/*   Updated: 2022/06/04 20:36:23 by hejang           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	result;

	i = 0;
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
	{
		result = ft_strlen(src) + size;
		return (result);
	}
	while (src[i] && (dst_len + i + 1 < size))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	result = ft_strlen(src) + dst_len;
	return (result);
}
