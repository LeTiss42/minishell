/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utilsiii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:56:27 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 02:49:16 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*ft_strtolower(char *str)
{
	int	i;

	if (str)
	{
		i = ft_strlen(str);
		while (i--)
			str[i] = ft_tolower(str[i]);
	}
	else
		str = "";
	return (str);
}

char	*ft_strsubreplace(const char *s, const char *set, const char *sub)
{
	char	*result;
	int		i;
	int		cnt;
	int		sub_len;
	int		set_len;

	cnt = 0;
	sub_len = ft_strlen(sub);
	set_len = ft_strlen(set);
	i = result_len(s, set, &cnt);
	result = (char *)malloc(i + cnt * (sub_len - set_len) + 1);
	i = 0;
	while (*s)
	{
		if (ft_strnstr(s, set, ft_strlen(s)) == s)
		{
			s += set_len;
			while (*sub)
				result[i++] = *sub++;
		}
		else
			result[i++] = *s++;
	}
	result[i] = '\0';
	return (result);
}

int	result_len(const char *s, const char *set, int *cnt)
{
	int	i;
	int	set_len;

	i = -1;
	set_len = ft_strlen(set);
	while (s[++i] != '\0')
	{
		if (ft_strnstr(&s[i], set, ft_strlen(&s[i])) == &s[i])
		{
			(*cnt)++;
			i += set_len - 1;
		}
	}
	return (i);
}
