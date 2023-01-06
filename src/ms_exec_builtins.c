/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 23:12:15 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 12:14:49 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	exec_blt(t_admin *adm)
{
	adm->cmlst->com = ft_strtolower(adm->cmlst->com);
	if (!ft_strcmp("echo", adm->cmlst->com))
		return (ms_echo(&adm->cmlst->args[1]));
	else if (!ft_strcmp("cd", adm->cmlst->com))
		return (ms_cd(adm));
	else if (!ft_strcmp("pwd", adm->cmlst->com))
		return (ms_pwd());
	else if (!ft_strcmp("env", adm->cmlst->com))
		return (ms_env(adm));
	else if (!ft_strcmp("export", adm->cmlst->com))
		return (ms_export(adm));
	else if (!ft_strcmp("unset", adm->cmlst->com))
		return (ms_unset(adm));
	else if (!ft_strcmp("exit", adm->cmlst->com))
		ft_exit(adm);
	return (1);
}

int	ms_exec_builtins(t_admin *adm, t_admpipe *admpipe, int i)
{
	if (!adm->cmlst->next)
		admpipe->pipe_bltin[1] = dup(1);
	if (adm->cmlst->next)
		dup2(admpipe->pipe_bltin[1], 1);
	if (adm->cmlst->next)
		my_close2(admpipe->fd, admpipe->nbcmd, i, 1);
	ms_exec_redir(adm);
	if (!exec_blt(adm))
	{
		if (!adm->cmlst->next)
			dup2(admpipe->pipe_bltin[1], 1);
		return (0);
	}
	return (1);
}
