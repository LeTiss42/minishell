/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_close_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 01:09:49 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 01:59:34 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

void	free_pipe(t_admin *adm, t_admpipe *admpipe)
{
	int	n;

	n = -1;
	cmd_lst_first_or_last(&adm->cmlst, 0);
	while (++n < ms_get_nbcmd(adm) - 1)
	{
		free(admpipe->fd[n]);
		if (n == ms_get_nbcmd(adm) - 2)
			free(admpipe->fd);
	}
	free(admpipe->pid);
	free(admpipe->pipe_bltin);
	cmd_lst_first_or_last(&adm->cmlst, 0);
}

void	my_close(t_admin *adm, t_admpipe *admpipe, int n)
{
	if (n >= 1)
	{
		if (!adm->cmlst->next)
			my_close2(admpipe->fd, admpipe->nbcmd, n, 1);
		else
			my_close2(admpipe->fd, admpipe->nbcmd, n, 0);
	}
	if (admpipe->pipe_bltin[1])
	{
		close(admpipe->pipe_bltin[0]);
		close(admpipe->pipe_bltin[1]);
	}
}

void	my_close2(int **fd, int n_pa, int n, int flag)
{
	int	i;

	i = 0;
	while (i <= n && flag == 0)
	{
		if (i != n)
			close(fd[i][0]);
		close(fd[i][1]);
		++i;
	}
	while (i < n_pa - 1 && flag == 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		++i;
	}
}

void	wait_pipe(t_admin *adm, t_admpipe *admpipe)
{
	int	n;

	n = 0;
	cmd_lst_first_or_last(&adm->cmlst, 0);
	while (n < admpipe->nbcmd)
	{
		if (adm->cmlst->com)
		{
			waitpid(admpipe->pid[n], &g_lstpipe_status, 0);
			if (WIFSIGNALED(g_lstpipe_status) && !adm->cmlst->is_blt)
				g_lstpipe_status = 128 + g_lstpipe_status;
			if (WIFEXITED(g_lstpipe_status))
				g_lstpipe_status = WEXITSTATUS(g_lstpipe_status);
		}
		if (adm->cmlst->next)
			adm->cmlst = adm->cmlst->next;
		else
			break ;
		n++;
	}
}
