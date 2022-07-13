/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postorder_travel_ast.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:51:54 by yukim             #+#    #+#             */
/*   Updated: 2022/07/13 15:34:04 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

static void	while_pipe_or_command(t_astnode *ast_node, pid_t *pid);
static void	c_in_while(int i, int *prev_fd, int *pipe_line, t_astnode *astnode);
static void	parent_in_while_pipe_or_cmd(int i, int *prev_fd, int *pipe_line);

void	postorder_travel_ast(t_astnode *ast_node)
{
	pid_t	*pid;
	int		i;

	g_data.p_flag = TRUE;
	pid = ft_calloc(g_data.pipe_cnt + 1, sizeof(int));
	if (!pid)
		ft_error("postorder_travel_ast : allocation failed\n");
	while_pipe_or_command(ast_node, pid);
	i = 0;
	while (i < g_data.pipe_cnt + 1)
	{
		waitpid(pid[i], &g_data.exit_status, 0);
		write(g_data.std_fd[1], "child parent pid\n", 17);
		i++;
	}
	if (WIFEXITED(g_data.exit_status))
		g_data.exit_status = WEXITSTATUS(g_data.exit_status);
	else if (WIFSIGNALED(g_data.exit_status))
		g_data.exit_status = WTERMSIG(g_data.exit_status) + 128;
	free(pid);
	exit(g_data.exit_status);
}

static void	while_pipe_or_command(t_astnode *ast_node, pid_t *pid)
{
	int		i;
	int		pipe_line[2];
	int		prev_fd;

	i = 0;
	prev_fd = NOT_USED;
	while (ast_node->nodetype == A_PIPE || ast_node->nodetype == A_COMMAND)
	{
		if (i < g_data.pipe_cnt)
		{
			if (pipe(pipe_line) < 0)
				ft_error("[Pipe ERROR] ast failed\n");
		}
		pid[i] = fork();
		g_data.p_flag = TRUE;
		if (pid[i] < 0)
			ft_error("[Fork ERROR] ast failed\n");
		if (pid[i] == 0)
			c_in_while(i, &prev_fd, pipe_line, ast_node);
		parent_in_while_pipe_or_cmd(i, &prev_fd, pipe_line);
		i++;
		ast_node = ast_node->prightchild;
	}
}

static void	c_in_while(int i, int *prev_fd, int *pipe_line, t_astnode *astnode)
{
	reset_signal();
	if (*prev_fd != NOT_USED)
	{
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
	}
	close(pipe_line[0]);
	if (i < g_data.pipe_cnt)
		dup2(pipe_line[1], STDOUT_FILENO);
	close(pipe_line[1]);
	if (astnode->nodetype == A_PIPE)
		postorder_travel_command(astnode->pleftchild);
	else
		postorder_travel_command(astnode);
	exit(g_data.exit_status);
}

static void	parent_in_while_pipe_or_cmd(int i, int *prev_fd, int *pipe_line)
{
	if (*prev_fd != NOT_USED)
		close(*prev_fd);
	if (i == g_data.pipe_cnt)
		close(pipe_line[0]);
	else
		*prev_fd = pipe_line[0];
	close(pipe_line[1]);
}
