/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strlen_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 00:20:42 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 02:54:06 by mravera          ###   ########.fr       */
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
		write(2, "error\n", 6);
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
		while (ms_isspace(s[i]) && s[i])
			++i;
		while (!ms_isspace(s[i]) && s[i]
			&& s[i] != '>' && s[i] != '<' && s[i] != '|')
			++i;
		while (ms_isspace(s[i]) && s[i])
			++i;
	}
	return (i);
}

int	ms_strlen_separator(const char	*s, int flag)
{
	int	i;

	i = 0;
	while (ms_isspace(s[i]) && s[i])
		++i;
	while (!ms_isspace(s[i]) && s[i])
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
	while (ms_isspace(s[i]) && s[i])
		++i;
	if (flag == 2 && (s[i] == '>' || s[i] == '<'))
		i += ms_skip_operator(s + i);
	return (i);
}
