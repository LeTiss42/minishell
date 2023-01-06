/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_redir_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 01:36:25 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 01:37:43 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

void	redir_lst_fst_or_lst(t_redir **redir, int flag)
{
	if (flag == 0)
	{
		while (*redir)
		{
			if ((*redir)->prev == NULL)
				break ;
			*redir = (*redir)->prev;
		}
	}
	else
	{
		while (*redir)
		{
			if ((*redir)->next == NULL)
				break ;
			*redir = (*redir)->next;
		}
	}
}

void	redir_lstadd_next(t_redir **alst, t_redir *next)
{
	if (*alst)
	{
		redir_lst_fst_or_lst(alst, 1);
		(*alst)->next = next;
		redir_lst_fst_or_lst(alst, 1);
	}
	else
		*alst = next;
}

t_redir	*redir_lstnew(struct s_redir *previous)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->op = NULL;
	redir->file = NULL;
	if (previous)
		redir->prev = previous;
	else
		redir->prev = NULL;
	redir->next = NULL;
	return (redir);
}
