/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_atoi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:01:46 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 16:55:32 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

long long	ft_atoi(const char *str, t_astnode *args_node)
{
	long long	n;
	int			negative;

	n = 0;
	negative = 1;
	if (*str == '-')
		negative = negative * (-1);
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_is_digit(*str))
		exit_status_numeric_error(args_node);
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		n = (n * 10) + (*str - '0');
		str++;
	}
	if ((n * negative) > LLONG_MAX || (n * negative) < LLONG_MIN)
		exit_status_numeric_error(args_node);
	if ((*str <= '0' || *str >= '9') && *str != '\0')
		exit_status_numeric_error(args_node);
	return ((n * negative));
}
