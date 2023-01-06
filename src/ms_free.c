/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <trerolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:12:42 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 12:11:56 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

void	free_all(t_admin *adm)
{
	free_env(adm);
	if (adm->cmlst)
		free_cmd(adm);
}

void	free_tab(char **tabs)
{
	int	i;

	i = -1;
	while (tabs[++i])
		free(tabs[i]);
	free(tabs);
}

void	free_com(t_admin *adm)
{
	free(adm->readline);
	free_cmd(adm);
	adm->cmlst = NULL;
	adm->comhd = NULL;
}

void	free_redir(t_admin *adm)
{
	t_redir	*next;

	redir_lst_fst_or_lst(&adm->cmlst->redir, 0);
	while (adm->cmlst->redir)
	{
		next = adm->cmlst->redir->next;
		free(adm->cmlst->redir->op);
		free(adm->cmlst->redir->file);
		free(adm->cmlst->redir);
		adm->cmlst->redir = next;
	}
}

void	free_cmd(t_admin *adm)
{
	int		n;
	t_cmd	*next;

	adm->cmlst = adm->comhd;
	while (adm->cmlst)
	{
		next = adm->cmlst->next;
		free(adm->cmlst->com);
		free(adm->cmlst->path);
		n = -1;
		if (adm->cmlst->args)
			while (adm->cmlst->args[++n])
				free(adm->cmlst->args[n]);
		free(adm->cmlst->args);
		free_redir(adm);
		free(adm->cmlst);
		adm->cmlst = next;
	}
}
