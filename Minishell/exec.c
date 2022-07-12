/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:07:14 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 20:12:46 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	exec_ast(void)
{
	if (g_data.pipe_cnt > 0)
		postorder_travel_ast(g_data.ast.prootnode);
	else
		postorder_travel_command(g_data.ast.prootnode);
}

void	exec_cmd(t_astnode *argsnode)
{
	t_astnode	*argnode;
	char		*blt_cmd;

	argnode = argsnode->prightchild;
	blt_cmd = g_data.lexer.pptokens[argnode->pvalue_index[0]];
	if (ft_strncmp(blt_cmd, "cd", -1))
		ft_cd(argsnode);
	else if (ft_strncmp(blt_cmd, "echo", -1))
		ft_echo(argsnode);
	else if (ft_strncmp(blt_cmd, "env", -1))
		ft_env(FALSE);
	else if (ft_strncmp(blt_cmd, "exit", -1))
		ft_exit(argsnode);
	else if (ft_strncmp(blt_cmd, "export", -1))
		ft_export(argsnode);
	else if (ft_strncmp(blt_cmd, "pwd", -1))
		ft_pwd();
	else if (ft_strncmp(blt_cmd, "unset", -1))
		ft_unset(argsnode);
	else
		execve_cmd(argsnode);
}

void	execve_cmd(t_astnode *argsnode)
{
	int			cnt;
	char		*execve_cmd;
	char		**argv;

	g_data.exit_status = 0;
	cnt = 0;
	execve_cmd = g_data.lexer.pptokens[argsnode->prightchild->pvalue_index[0]];
	while (argsnode->prightchild->pvalue_index[cnt] != END)
		cnt++;
	argv = create_argv(cnt, argsnode);
	if (g_data.pipe_cnt == 0)
		cmd_without_pipe(execve_cmd, 0, argv, execve_cmd);
	else
	{
		if (ft_strnstr(execve_cmd, "minishell", ft_strlen(execve_cmd)))
			ft_nanoshell(execve_cmd);
		else
			fork_before_run_execve(0, argv, execve_cmd);
	}
	free_argv(argv, cnt);
}

void	cmd_without_pipe(char *cmd, int idx, char **argv, char *execve_cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("[FORK ERROR] execve failed\n");
	g_data.p_flag = TRUE;
	if (pid == 0)
	{
		if (ft_strnstr(cmd, "minishell", ft_strlen(cmd)))
			ft_nanoshell(cmd);
		else
		{
			fork_before_run_execve(idx, argv, execve_cmd);
			printf("errno : %d\n", errno);
		}
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &g_data.exit_status, 0);
	}
	if (WIFEXITED(g_data.exit_status))
		g_data.exit_status = WEXITSTATUS(g_data.exit_status);
	else if (WIFSIGNALED(g_data.exit_status))
		g_data.exit_status = WTERMSIG(g_data.exit_status) + 128;
}

void	fork_before_run_execve(int idx, char **argv, char *execve_cmd)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 < 0)
		ft_error("[FORK ERROR] fork_before_run_execve failed\n");
	if (pid2 == 0)
		fork_before_run_execve_child(idx, execve_cmd, argv);
	else
	{
		printf("exit status %d\n", g_data.exit_status);
		waitpid(pid2, &(g_data.exit_status), 0);
		if (WIFEXITED(g_data.exit_status))
			g_data.exit_status = WEXITSTATUS(g_data.exit_status);
		else if (WIFSIGNALED(g_data.exit_status))
			g_data.exit_status = WTERMSIG(g_data.exit_status) + 128;
		exit(g_data.exit_status);
	}
}
