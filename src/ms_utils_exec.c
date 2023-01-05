/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:03:11 by mravera           #+#    #+#             */
/*   Updated: 2023/01/05 14:00:04 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	ms_get_nbcmd(t_admin *adm)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = adm->comlist;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	ms_initpid(t_admin *adm)
{
	t_cmd	*cmd;

	cmd = adm->comlist;
	if (adm->in)
	{
		if (pipe(cmd->fd) == -1)
			return (1);
	}
	return (0);
}

int	ms_setpid(t_admin *adm)
{
	(void)adm;
	return (0);
}