/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:24:31 by yukim             #+#    #+#             */
/*   Updated: 2022/07/07 22:28:26 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	ft_pnb(int n, int *sign, size_t *len)
{
	size_t	pnb;

	if (n < 0)
	{
		*len = 1;
		*sign = -1;
		pnb = (long long)n * -1;
	}
	else
	{
		*len = 0;
		*sign = 1;
		pnb = n;
	}
	return (pnb);
}

static size_t	ft_pnblen(size_t pnb)
{
	size_t	len;

	if (pnb == 0)
		return (1);
	len = 0;
	while (pnb)
	{
		pnb = pnb / 10;
		len++;
	}
	return (len);
}

static char	*ft_cnb(size_t pnb, int sign, size_t len)
{
	char	*new;
	int		i;

	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		ft_error("ft_itoa : allocation failed\n");
	i = len;
	while (i > -1)
	{
		if ((size_t)i == len)
			new[i] = '\0';
		else if (i == 0 && sign == -1)
			new[i] = '-';
		else
		{
			new[i] = (pnb % 10) + '0';
			pnb = pnb / 10;
		}
		i--;
	}
	return (new);
}

char	*ft_itoa(int n)
{
	char	*new;
	size_t	len;
	size_t	pnb;
	int		sign;

	pnb = ft_pnb(n, &sign, &len);
	len = len + ft_pnblen(pnb);
	new = ft_cnb(pnb, sign, len);
	return (new);
}
