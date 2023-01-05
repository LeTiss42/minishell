/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:15:49 by mravera           #+#    #+#             */
/*   Updated: 2023/01/05 11:23:26 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	ms_exec(t_admin	*adm)
{
	t_cmd	*cmd;

	cmd = adm->comlist;
	ms_initpid(adm);
	while (cmd)
	{
		ms_bin_execution(cmd);
		cmd = cmd->next;
	}
	return (0);
}

int	ms_bin_execution(t_cmd *cmd)
{
	int	pid;

	if (pipe(cmd->fd) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
	{
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	return (0);
}

int	ms_exectrash(void)
{
	int	fd[3][2];
	int	i;
	int	pid1;
	int	pid2;
	int	x;

	i = 0;
	while (i < 3)
		if (pipe(fd[i++]) < 0)
			return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		if (read(fd[0][0], &x, sizeof(int)) < 0)
			return (3);
		x += 5;
		if (write(fd[1][1], &x, sizeof(int)) < 0)
			return (4);
		close(fd[0][0]);
		close(fd[1][1]);
		return (0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		if (read(fd[1][0], &x, sizeof(int)) < 0)
			return (5);
		x += 5;
		if (write(fd[2][1], &x, sizeof(int)) < 0)
			return (6);
		close(fd[1][0]);
		close(fd[2][1]);
		return (0);
	}
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][1]);
	x = 0;
	if (write(fd[0][1], &x, sizeof(int)) < 0)
		return (7);
	if (read(fd[2][0], &x, sizeof(int)) < 0)
		return (8);
	printf("result is %d\n", x);
	close(fd[0][1]);
	close(fd[2][0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int	ms_exec2(void)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	printf("fini\n");
	return (0);
}
