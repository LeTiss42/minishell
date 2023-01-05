/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:12:42 by mravera           #+#    #+#             */
/*   Updated: 2023/01/05 20:20:12 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

void	free_all(t_admin *adm)
{
	free_env(adm);
	if (adm->comlist)
		free_pa(adm);
}

void	free_tab(char **tabs)
{
	int	i;

	i = -1;
	while (tabs[++i])
		free(tabs[i]);
	free(tabs);
}

void	free_cmd(t_admin *adm)
{
	free(adm->readline);
	free_pa(adm);
	adm->comlist = NULL;
	adm->comhd = NULL;
}

void	free_redir(t_admin *adm)
{
	t_redir	*next;

	redir_lst_fst_or_lst(&adm->comlist->redir, 0);
	while (adm->comlist->redir)
	{
		next = adm->comlist->redir->next;
		free(adm->comlist->redir->op);
		free(adm->comlist->redir->file);
		free(adm->comlist->redir);
		adm->comlist->redir = next;
	}
}

void	free_pa(t_admin *adm)
{
	int		n;
	t_cmd	*next;

	adm->comlist = adm->comhd;
	while (adm->comlist)
	{
		next = adm->comlist->next;
		free(adm->comlist->com);
		free(adm->comlist->path);
		n = -1;
		if (adm->comlist->args)
			while (adm->comlist->args[++n])
				free(adm->comlist->args[n]);
		free(adm->comlist->args);
		free_redir(adm);
		free(adm->comlist);
		adm->comlist = next;
	}
}
