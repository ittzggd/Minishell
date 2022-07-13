/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:10:39 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 17:36:20 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	reset_stdfd(void)
{
	dup2(g_data.std_fd[0], STDIN_FILENO);
	dup2(g_data.std_fd[1], STDOUT_FILENO);
}

void	reset_signal(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_bs);
}
