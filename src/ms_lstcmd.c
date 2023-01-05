/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:53:44 by mravera           #+#    #+#             */
/*   Updated: 2023/01/05 18:51:47 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

t_cmd	*pa_lstnew(t_cmd *previous)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->com = NULL;
	cmd->path = NULL;
	cmd->args = NULL;
	if (previous)
		cmd->prev = previous;
	else
		cmd->prev = NULL;
	cmd->redir = NULL;
	cmd->is_blt = 0;
	cmd->next = NULL;
	return (cmd);
}

void	pa_lstadd_next(t_cmd **alst, t_cmd *next)
{
	if (*alst)
	{
		pa_lst_fst_or_lst(alst, 1);
		(*alst)->next = next;
		pa_lst_fst_or_lst(alst, 1);
	}
	else
		*alst = next;
}

void	pa_lst_fst_or_lst(t_cmd **pa, int flag)
{
	if (flag == 0)
	{
		while (*pa)
		{
			if ((*pa)->prev == NULL)
				break ;
			*pa = (*pa)->prev;
		}
	}
	else
	{
		while (*pa)
		{
			if ((*pa)->next == NULL)
				break ;
			*pa = (*pa)->next;
		}
	}
}
