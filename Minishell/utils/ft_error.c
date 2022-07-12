/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:48:55 by hejang            #+#    #+#             */
/*   Updated: 2022/07/03 17:46:28 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error_message(char *message, int exit_status)
{
	int	len;

	len = ft_strlen(message);
	write(2, message, len);
	g_data.exit_status = exit_status;
}

void	ft_error(char *error_msg)
{
	ft_error_message(error_msg, 1);
	exit(g_data.exit_status);
}
