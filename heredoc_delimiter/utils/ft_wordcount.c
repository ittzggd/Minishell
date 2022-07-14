/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:21:32 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 14:35:52 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_wordcount(char const *str)
{
	int	ret;
	int	i;
	int	wc;
	int	wc_flag;
	int	quote;

	quote = 0;
	wc_flag = 1;
	i = 0;
	wc = 0;
	while (str[i])
	{
		ret = get_wc(str, &i, &wc_flag, &wc);
		if (ret == CONTINUE)
			continue ;
		else if (ret == ERROR)
		{
			syntax_error(&g_data.exit_status);
			return (ERROR);
		}
	}
	return (wc);
}
