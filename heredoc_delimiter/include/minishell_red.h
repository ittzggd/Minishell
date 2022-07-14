/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_red.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:55:50 by yukim             #+#    #+#             */
/*   Updated: 2022/07/13 17:18:21 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_RED_H
# define MINISHELL_RED_H

# include <fcntl.h>

void	out_red(char *filename);
int		in_red(char *filename);
void	append_red(char *filename);
void	heredoc(char *delimiter);

#endif
