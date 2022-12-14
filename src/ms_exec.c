/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:15:49 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 02:30:36 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	ms_exec(t_admin	*adm)
{
	t_admpipe	admpipe;
	int			i;

	ms_setpipid(adm, &admpipe);
	i = 0;
	cmd_lst_first_or_last(&adm->cmlst, 0);
	while (adm->cmlst)
	{
		if (ms_exec_main(adm, &admpipe, i))
			break ;
		if (adm->cmlst->next)
		{
			++i;
			adm->cmlst = adm->cmlst->next;
		}
		else
			break ;
	}
	wait_pipe(adm, &admpipe);
	free_pipe(adm, &admpipe);
	return (0);
}

int	ms_exec_main(t_admin *adm, t_admpipe *admpipe, int i)
{
	if (ms_execheck(adm))
		return (1);
	else if (ms_isbuiltin(adm) && !adm->cmlst->next)
		return (ms_exec_builtins(adm, admpipe, i));
	else
	{
		admpipe->pid[i] = fork();
		handle_child_signal();
		if (admpipe->pid[i] == -1)
			my_exit(adm, write(2, "Error: fork\n", 12));
		if (admpipe->pid[i] == 0)
		{
			if (adm->cmlst->prev && !adm->cmlst->is_blt)
				dup2(admpipe->fd[i - 1][0], STDIN_FILENO);
			if (adm->cmlst->next)
				dup2(admpipe->fd[i][1], STDOUT_FILENO);
			if ((adm->cmlst->prev
					&& !adm->cmlst->is_blt) || adm->cmlst->next)
				my_close2(admpipe->fd, admpipe->nbcmd, i, 1);
			if (ms_exec_check_execve(adm))
				custom_err_exit(adm, 0, "cmd not found", 127);
		}
		my_close(adm, admpipe, i);
		return (0);
	}
}

void	my_exit(t_admin *adm, int flag)
{
	free_all(adm);
	exit(flag);
}

void	custom_err_exit(t_admin *adm, int arg, char *str, int ret)
{
	write(2, "minishell", 9);
	if (arg != 0)
	{
		write(2, ": ", 2);
		write(2, adm->cmlst->com, ft_strlen(adm->cmlst->com));
	}
	write(2, ": ", 2);
	write(2, adm->cmlst->args[arg], ft_strlen(adm->cmlst->args[arg]));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(ret);
}

// int	ms_exectrash(void)
// {
// 	int	fd[3][2];
// 	int	i;
// 	int	pid1;
// 	int	pid2;
// 	int	x;

// 	i = 0;
// 	while (i < 3)
// 		if (pipe(fd[i++]) < 0)
// 			return (1);
// 	pid1 = fork();
// 	if (pid1 < 0)
// 		return (2);
// 	if (pid1 == 0)
// 	{
// 		close(fd[0][1]);
// 		close(fd[1][0]);
// 		close(fd[2][0]);
// 		close(fd[2][1]);
// 		if (read(fd[0][0], &x, sizeof(int)) < 0)
// 			return (3);
// 		x += 5;
// 		if (write(fd[1][1], &x, sizeof(int)) < 0)
// 			return (4);
// 		close(fd[0][0]);
// 		close(fd[1][1]);
// 		return (0);
// 	}
// 	pid2 = fork();
// 	if (pid2 == 0)
// 	{
// 		close(fd[0][0]);
// 		close(fd[0][1]);
// 		close(fd[1][1]);
// 		close(fd[2][0]);
// 		if (read(fd[1][0], &x, sizeof(int)) < 0)
// 			return (5);
// 		x += 5;
// 		if (write(fd[2][1], &x, sizeof(int)) < 0)
// 			return (6);
// 		close(fd[1][0]);
// 		close(fd[2][1]);
// 		return (0);
// 	}
// 	close(fd[0][0]);
// 	close(fd[1][0]);
// 	close(fd[1][1]);
// 	close(fd[2][1]);
// 	x = 0;
// 	if (write(fd[0][1], &x, sizeof(int)) < 0)
// 		return (7);
// 	if (read(fd[2][0], &x, sizeof(int)) < 0)
// 		return (8);
// 	printf("result is %d\n", x);
// 	close(fd[0][1]);
// 	close(fd[2][0]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return (0);
// }

// int	ms_exec2(void)
// {
// 	int	fd[2];
// 	int	pid1;
// 	int	pid2;

// 	if (pipe(fd) == -1)
// 		return (1);
// 	pid1 = fork();
// 	if (pid1 < 0)
// 		return (2);
// 	if (pid1 == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execlp("ping", "ping", "-c", "5", "google.com", NULL);
// 	}
// 	pid2 = fork();
// 	if (pid2 < 0)
// 		return (3);
// 	if (pid2 == 0)
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execlp("grep", "grep", "rtt", NULL);
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	printf("fini\n");
// 	return (0);
// }
