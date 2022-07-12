/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:01:08 by hejang            #+#    #+#             */
/*   Updated: 2022/07/12 15:43:30 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "limits.h"
# include <stdlib.h>
# include "minishell_define.h"

void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t number, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
int			ft_split_str(char *str, char **tokens);
int			case_redirection(char const *str, int *i);
int			ft_wordlen(char const *str, int i, int wc_flag, int quote);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		**ft_split(char const *s, char c);
long long	ft_atoi(const char *str, t_astnode *args_node);
char		*ft_itoa(int n);
t_envv_node	*ft_lstnew(t_envv_node element);
void		ft_lstadd_back(t_envv_node *new);
void		remove_ll_element(t_envv_node **p_list, char *key);
void		free_argv(char **argv, int cnt);

void		clear_linked_list(t_envv_node **p_list);
void		delete_linked_list(t_envv_node **p_list);

//is_utils
int			is_ifs(const char c);
int			is_redirection(const char *s);
int			is_quote(const char c);
int			is_pipe(const char *s);
int			is_option(char *value);
int			is_valid_env(char *str);
int			is_env(char *value);
int			ft_is_alpha(char c);
int			ft_is_digit(int c);

void		ft_error_message(char *message, int exit_status);
void		ft_error(char *error_msg);

// replace_env_to_value
int			ft_key_len(char *token, int j);
int			get_len_replaced_str(char *input);
void		get_len_case_exit_status(int *i, int *ret_len);
void		get_len_case_replace_env(int *i, int *ret_len, char *input);
char		*replace_env_to_value(char *input);
void		replace_env_case_replace(int *i, int *j, char *input, char *ret);
void		copy_char(char *input, int *i, int *j, char *ret);
void		replace_env_case_exit_status(int *i, int *j, char *ret);

// remove_quote
void		rm_argument_quote(int i);
char		*remove_quote(char *quote_str);

// heredoc_utils
void		heredoc_replace_env_loop(char *origin, char	*ret, char *value);
void		heredoc_replace_env(char *origin, char *ret, int *i, int *j);
void		heredoc_exit_status(char *value, int *ret_len, int *i);
void		len_loop_in_heredoc(char *origin, char *value, int *i, int *retlen);

#endif
