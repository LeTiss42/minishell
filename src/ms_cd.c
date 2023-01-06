/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:11:14 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 00:02:52 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	ms_cd(t_admin *adm)
{
	char	buf[1024];

	free(get_env(adm, get_i_env(adm, "OLDPWD"))->val);
	add_env(adm, 0, "OLDPWD", ft_strdup(getcwd(buf, 1024)));
	if (!adm->cmlst->args[1])
	{
		chdir(get_env(adm, get_i_env(adm, "HOME"))->val);
	}
	else if (chdir(adm->cmlst->args[1]))
	{
		g_lstpipe_status = 1;
		if (access(adm->cmlst->args[1], F_OK))
			custom_err(adm, 1, "No such file or directory");
		else
			custom_err(adm, 1, "Permission denied");
		return (0);
	}
	free(get_env(adm, get_i_env(adm, "PWD"))->val);
	add_env(adm, 0, "PWD", ft_strdup(getcwd(buf, 1024)));
	g_lstpipe_status = 0;
	return (0);
}

// int	ms_cd_update_env(t_list *env, char *old)
// {
// 	int	x;

// 	x = 0;
// 	while (env)
// 	{
// 		if (ft_strncmp((char *)env->content, "OLDPWD", 7) == 0
// 			|| ft_strncmp((char *)env->content, "OLDPWD=", 7) == 0)
// 		{
// 			free(env->content);
// 			env->content = old;
// 			x = 1;
// 		}
// 		else if (ft_strncmp((char *)env->content, "PWD", 4) == 0
// 			|| ft_strncmp((char *)env->content, "PWD=", 4) == 0)
// 			env->content = (void *)ms_new_pwd(env->content);
// 		env = env->next;
// 	}	
// 	if (x != 1)
// 		free(old);
// 	return (0);
// }
