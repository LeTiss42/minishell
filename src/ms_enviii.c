/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_enviii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:04:15 by mravera           #+#    #+#             */
/*   Updated: 2023/01/05 20:04:53 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

void	append_t_node(t_env **head_ref, char *name, char *val)
{
	t_env	*new_node;
	t_env	*last;

	new_node = (t_env *)malloc(sizeof(t_env));
	new_node->name = name;
	new_node->val = val;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		new_node->prev = NULL;
		*head_ref = new_node;
		return ;
	}
	last = *head_ref;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}

void	free_env(t_admin *adm)
{
	t_env	*next;

	while (adm->env)
	{
		next = adm->env->next;
		free(adm->env->name);
		free(adm->env->val);
		free(adm->env);
		adm->env = next;
	}
}

int	count_t_node(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	print_node(t_env *env, int opt)
{
	while (env)
	{
		if (opt)
		{
			if (!ft_strcmp(env->val, "NULL"))
				ft_printf("declare -x %s\n", env->name);
			else
				ft_printf("declare -x %s=\"%s\"\n", env->name, env->val);
		}
		else
		{
			if (ft_strcmp(env->val, "NULL"))
				ft_printf("%s=%s\n", env->name, env->val);
		}
		env = env->next;
	}
}
