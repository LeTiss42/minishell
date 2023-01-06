/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:46:13 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 02:36:47 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

void	ft_exit(t_admin *adm)
{
	int	i;
	int	j;

	ft_printf("exit\n");
	exit_no_arg(adm);
	i = 0;
	while (++i < ms_strlen_tab(adm->cmlst->args))
	{
		j = -1;
		while (adm->cmlst->args[1][++j])
		{
			if (!ft_isdigit(adm->cmlst->args[1][j]))
			{
				custom_err(adm, 1, "numeric argument required");
				exit(255);
			}
		}
	}
	if (i > 2)
	{
		custom_err(adm, 0, "too many arguments");
		g_lstpipe_status = 1;
		return ;
	}
	exit(ft_atoi(adm->cmlst->args[1]));
}

void	exit_no_arg(t_admin *adm)
{
	int	i;

	i = ms_strlen_tab(adm->cmlst->args);
	if (i == 1)
		exit(0);
}
