/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:46:12 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 02:14:24 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

void	check_special_char(t_admin *adm, char *line, int *ret, int *n)
{
	while (*(line + (*ret)) == ' ')
		(*ret)++;
	if (*(line + *ret))
	{
		if (*(line + *ret) == '\'')
		{
			adm->cmlst->args[*n] = ft_substr(line + *ret, 0,
					pos_n_char(line + *ret, 2, '\''));
			*ret += pos_n_char(line + *ret, 2, '\'');
		}
		else if (*(line + *ret) == '"')
		{
			adm->cmlst->args[*n] = ft_substr(line + *ret, 0,
					pos_n_char(line + *ret, 2, '"'));
			*ret += pos_n_char(line + *ret, 2, '"');
		}
		else
		{
			adm->cmlst->args[*n] = ft_strtrim_free(ft_substr(line + *ret, 0,
						ms_strlen_separator(line + *ret, 0)), " ");
			*ret += ms_strlen_separator(line + *ret, 0);
		}
	}
	*n = *n + 1;
	*ret += ms_fill_redir(adm, line + (*ret));
}

int	ms_count_args(const char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] && s[i] != '|')
	{
		i = ms_skip_between_char(s, i, '\'');
		if (i == -1)
			return (-1);
		i = ms_skip_between_char(s, i, '"');
		if (i == -1)
			return (-1);
		if (!ms_isspace(s[i]) && s[i] != '>' && s[i] != '<'
			&& (ms_isspace(s[i + 1]) || s[i + 1] == '\0'
				|| s[i + 1] == '>' || s[i + 1] == '<' || s[i + 1] == '|'))
			++count;
		if (s[i] == '>' || s[i] == '<')
			i += ms_skip_operator(s + i);
		else
			++i;
	}
	return (count);
}

int	ms_parse_line(t_admin *adm, char *str)
{
	char	*tmp;
	int		pop;

	adm->cmlst = cmd_lstnew(NULL);
	adm->comhd = adm->cmlst;
	tmp = str;
	pop = 0;
	while (*str)
	{
		str += ms_fill_cmd(adm, str, &pop);
		if (pop < 0)
			return (1);
		if (*str == '|')
		{
			++str;
			while (ms_isspace(*str) && *str)
				++str;
			cmd_lstadd_next(&adm->cmlst, cmd_lstnew(adm->cmlst));
		}
	}
	free(tmp);
	return (0);
}

int	ms_fill_cmd(t_admin *adm, char *str, int *pop)
{
	int	n;
	int	ret;

	n = 0;
	ret = ms_fill_redir(adm, str);
	if (ret < 0)
	{
		*pop = -1;
		write(2, "Error : pop_redir\n", 18);
		return (-1);
	}
	adm->cmlst->com = ft_strtrim_free(ft_substr(str + ret, 0,
				ms_strlen_separator(str + ret, 0)), " ");
	if (ms_isbuiltin(adm))
		adm->cmlst->is_blt = 1;
	if (ms_count_args(str) == -1)
	{
		*pop = -1;
		return (-1);
	}
	adm->cmlst->args = malloc(sizeof(char *) * (ms_count_args(str) + 1));
	while ((*(str + ret) != '|' && *(str + ret)))
		check_special_char(adm, str, &ret, &n);
	adm->cmlst->args[n] = NULL;
	return (ret);
}
