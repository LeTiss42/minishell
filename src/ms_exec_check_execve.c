/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_check_execve.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <trerolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 02:19:42 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 14:58:09 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	ms_exec_check_execve(t_admin *adm)
{
	char	**path;
	int		is_cmd;

	if (access(adm->cmlst->com, X_OK) == 0)
	{
		if (!ms_exec_redir(adm))
			execve(adm->cmlst->com, adm->cmlst->args, get_env2d(adm->env));
	}
	else if (get_i_env(adm, "PATH") == -1)
		return (1);
	else
	{
		path = ft_split(get_env(adm, get_i_env(adm, "PATH"))->val, ':');
		is_cmd = create_cmd(path, &adm->cmlst->com);
		free_tab(path);
		if (is_cmd == 0)
			return (1);
		if (!ms_exec_redir(adm))
			execve(adm->cmlst->com, adm->cmlst->args, get_env2d(adm->env));
	}
	return (0);
}

char	**get_env2d(t_env *env)
{
	char	**env2d;
	int		size;
	int		i;
	char	*tmp;

	size = count_t_node(env);
	env2d = ft_calloc(sizeof(char **), size + 1);
	i = -1;
	while (++i < size)
	{
		tmp = ft_strjoin(env->name, "=");
		env2d[i] = ft_strjoin(tmp, env->val);
		free(tmp);
	}
	return (env2d);
}

int	create_cmd(char **path, char **cmd)
{
	char	*npath;
	char	*tmp_cmd;
	int		i;
	int		arr_i;

	arr_i = -1;
	tmp_cmd = ft_strdup(*cmd);
	while (++arr_i < (int)ms_strlen_tab(path))
	{
		i = ft_strlen(path[arr_i]);
		if (path[arr_i][i - 1] != '/' && *cmd[0] != '/')
		{
			npath = ft_strjoin(path[arr_i], "/");
			*cmd = ft_strjoin_f(npath, *cmd, 3);
		}
		else
			*cmd = ft_strjoin_f(path[arr_i], *cmd, 2);
		if (access(*cmd, X_OK) == 0)
			return (1);
		free(*cmd);
		*cmd = ft_strdup(tmp_cmd);
	}
	return (0);
}
