/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <trerolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:15:43 by trerolle          #+#    #+#             */
/*   Updated: 2023/01/05 20:22:59 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	ms_skip_between_char(const char *s, int i, char c)
{
	if (s[i] == c)
	{
		i++;
		while (s[i])
		{
			i++;
			if (s[i] == c)
				return (i);
		}
		write(2, "error\n", ft_strlen("error\n"));
		return (-1);
	}
	return (i);
}

int	ms_strlen_operator(const char *s)
{
	int		i;

	i = 0;
	while (s[i] == '>' || s[i] == '<')
	{
		++i;
	}
	return (i);
}

int	ms_skip_operator(const char *s)
{
	int	i;

	i = 0;
	while (s[i] == '>' || s[i] == '<')
	{
		while (s[i] == '>' || s[i] == '<')
			++i;
		while (ft_isspace(s[i]) && s[i])
			++i;
		while (!ft_isspace(s[i]) && s[i]
			&& s[i] != '>' && s[i] != '<' && s[i] != '|')
			++i;
		while (ft_isspace(s[i]) && s[i])
			++i;
	}
	return (i);
}

int	ms_strlen_separator(const char	*s, int flag)
{
	int	i;

	i = 0;
	while (ft_isspace(s[i]) && s[i])
		++i;
	while (!ft_isspace(s[i]) && s[i])
	{
		if (flag == 0 && (s[i] == '>' || s[i] == '<' || s[i] == '|'))
			break ;
		if (flag == 1 && s[i] == '|')
			break ;
		if (flag == 2 && (s[i] == '>' || s[i] == '<' || s[i] == '|'))
			break ;
		++i;
	}
	if (flag == 2 && (s[i] == '>' || s[i] == '<'))
		i += ms_skip_operator(s + i);
	while (ft_isspace(s[i]) && s[i])
		++i;
	if (flag == 2 && (s[i] == '>' || s[i] == '<'))
		i += ms_skip_operator(s + i);
	return (i);
}
