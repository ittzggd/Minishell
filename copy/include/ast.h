/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 03:26:41 by hejang            #+#    #+#             */
/*   Updated: 2022/07/13 17:35:13 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell_define.h"

int			init_idx(int index, t_astnode *node);
t_astnode	*insert_leftchildnode_ast(t_astnode *p_parentnode, int nodetype);
t_astnode	*insert_rightchildnode_ast(t_astnode *p_parentnode, int nodetype);

void		init_ast(void);
int			recur_pipe(t_astnode *ast_node, int index);
void		tree_cmd(t_astnode *ast_node, int index);
void		tree_reds(t_astnode *ast_node, int index);
int			tree_args(t_astnode *ast_node, int index);

int			goto_redirection(t_astnode *red_node);
int			postorder_travel_reds(t_astnode *reds_node);
void		postorder_travel_command(t_astnode *cmdnode);
void		postorder_travel_ast(t_astnode *ast_node);

void		delete_astnode(t_astnode *node);
void		free_data_ast(void);

#endif
