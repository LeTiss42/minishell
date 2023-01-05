/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:03:11 by mravera           #+#    #+#             */
/*   Updated: 2023/01/05 19:51:04 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	ms_get_nbcmd(t_admin *adm)
{
	int	i;

	i = 0;
	pa_lst_fst_or_lst(&adm->comlist, 0);
	while (adm->comlist)
	{
		++i;
		if (adm->comlist->next)
			adm->comlist = adm->comlist->next;
		else
			break ;
	}
	pa_lst_fst_or_lst(&adm->comlist, 0);
	return (i);
}

void	ms_setpipid(t_admin *adm, t_admpipe *admpipe)
{
	int	i;

	i = -1;
	admpipe->nbcmd = ms_get_nbcmd(adm);
	if (admpipe->nbcmd > 1)
	{
		admpipe->fd = malloc(sizeof(int *) * (admpipe->nbcmd - 1));
		while (++i < admpipe->nbcmd - 1)
			admpipe->fd[i] = malloc(sizeof(int) * 2);
	}
	admpipe->pid = malloc(sizeof(int) * admpipe->nbcmd);
	i = -1;
	while (++i < admpipe->nbcmd - 1)
	{
		if (pipe(admpipe->fd[i]) == -1)
			my_exit(adm, write(2, "Error: pipe\n", 12));
	}
	admpipe->pipe_bltin = malloc(sizeof(int) * 2);
	if (pipe(admpipe->pipe_bltin) == -1)
		my_exit(adm, write(2, "Error: builtins pipe\n", 21));
}

int	ms_execheck(t_admin *adm)
{
	if (adm->comlist->redir && adm->comlist->com && adm->comlist->redir->op
		&& !adm->comlist->redir->file[0])
		return (ms_return_error("Error : syntax NL\n", 130, 1));
	if ((adm->comlist->prev || adm->comlist->next)
		&& (!adm->comlist->com || !adm->comlist->com[0]))
		return (ms_return_error("Error : syntax PIPE\n", 2, 1));
	if ((!adm->comlist->com || !adm->comlist->com[0]))
	{
		if (adm->comlist->redir)
		{
			if (!adm->comlist->redir->file[0])
			{
				g_lstpipe_status = 130;
				return (write(2, "Error : syntax NL\n", 18));
			}
			else if (!ft_strcmp(adm->comlist->redir->op, ">"))
				return (open(adm->comlist->redir->file, O_RDWR
						| O_CREAT, 0644));
			else if (!ft_strcmp(adm->comlist->redir->op, "<<"))
				return (fake_heredoc(adm));
		}
		return (1);
	}
	return (0);
}

int	fake_heredoc(t_admin *adm)
{
	char	*tmp;

	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
		{
			write(2, "warning: here-document end-of-file (wanted `", 50);
			write(2, adm->comlist->redir->file,
				ft_strlen(adm->comlist->redir->file));
			write(2, "')\n", 3);
			break ;
		}
		if (!ft_strcmp(adm->comlist->redir->file, tmp))
			break ;
		if (tmp)
			free(tmp);
	}
	if (tmp)
		free(tmp);
	return (42);
}

int	ms_return_error(char *str, int status, int ret)
{
	g_lstpipe_status = status;
	write(2, str, ft_strlen(str));
	return (ret);
}
