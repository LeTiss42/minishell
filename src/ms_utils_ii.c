/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_ii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <trerolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:07:34 by mravera           #+#    #+#             */
/*   Updated: 2023/01/05 19:38:29 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

char	*ft_strtrim_free(char *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (i < j && ft_strchr(set, s1[j]))
		j--;
	res = ft_substr(s1, i, j - i + 1);
	free(s1);
	return (res);
}

char	*ms_new_pwd(char *old_pwd)
{
	char	*buff;
	char	*new_pwd;

	buff = getcwd(NULL, 0);
	if (old_pwd != NULL)
		free(old_pwd);
	new_pwd = ft_strjoin("PWD=", buff);
	free(buff);
	return (new_pwd);
}

char	*ms_new_oldpwd(char *old_pwd)
{
	char	*buff;
	char	*new_pwd;

	buff = getcwd(NULL, 0);
	if (old_pwd != NULL)
		free(old_pwd);
	new_pwd = ft_strjoin("OLDPWD=", buff);
	free(buff);
	return (new_pwd);
}

int	ms_lstcomp(t_list *a, t_list *b)
{
	char	*buf;
	int		res;

	buf = ms_trimenv((char *)a->content);
	if (ft_strncmp((char *)a->content, (char *)b->content,
			ft_strlen(buf) + 1) > 0)
		res = 1;
	else if (ft_strncmp((char *)a->content, (char *)b->content,
			ft_strlen(buf) + 1) < 0)
		res = -1;
	else
		res = 0;
	free(buf);
	return (res);
}

int	ms_lento(char *str, char x)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != x))
		i ++;
	return (i);
}
