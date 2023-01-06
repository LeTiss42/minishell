/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:23:28 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 00:49:59 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	ms_unset(t_admin *adm)
{
	t_env	*tmp;
	int		size;
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (adm->cmlst->args[++i])
	{
		if (ms_isunset(adm->cmlst->args[i]))
		{
			size = get_i_env(adm, adm->cmlst->args[i]);
			if (size == -1)
				continue ;
			tmp = get_env(adm, size);
			delete_t_node(&adm->env, tmp);
		}
		else
		{
			status = 1;
			custom_err(adm, i, "Not a valid identifier");
		}
	}
	g_lstpipe_status = status;
	return (0);
}

int	ms_isunset(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '_')
			continue ;
		return (0);
	}
	return (1);
}

void	delete_t_node(t_env **head_ref, t_env *del)
{
	if (*head_ref == NULL || del == NULL)
		return ;
	if (*head_ref == del)
		*head_ref = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	free(del->name);
	free(del->val);
	free(del);
}
