/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:45:14 by trerolle          #+#    #+#             */
/*   Updated: 2023/01/06 02:52:58 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

void	ms_redir_lst_first_or_last(t_redir **redir, int flag)
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

void	ms_redir_lstadd_next(t_redir **alst, t_redir *next)
{
	if (*alst)
	{
		ms_redir_lst_first_or_last(alst, 1);
		(*alst)->next = next;
		ms_redir_lst_first_or_last(alst, 1);
	}
	else
		*alst = next;
}

t_redir	*ms_redir_lstnew(struct s_redir *previous)
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

int	ms_fill_redir(t_admin *adm, const char *l)
{
	int	ret;

	ret = 0;
	while (*(l + ret) == ' ')
		ret++;
	while (*(l + ret) == '>' || *(l + ret) == '<')
	{
		if (!adm->cmlst->redir)
			adm->cmlst->redir = ms_redir_lstnew(NULL);
		else
			ms_redir_lstadd_next(&adm->cmlst->redir,
				ms_redir_lstnew(adm->cmlst->redir));
		adm->cmlst->redir->op = ft_strtrim_free(
				ft_substr(l + ret, 0, ms_strlen_operator(l + ret)), " ");
		ret += ms_strlen_operator(l + ret);
		adm->cmlst->redir->file = ft_strtrim_free(
				ft_substr(l + ret, 0, ms_strlen_separator(l + ret, 0)), " ");
		ret += ms_strlen_separator(l + ret, 0);
	}
	return (ret);
}
