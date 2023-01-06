/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:29:39 by mravera           #+#    #+#             */
/*   Updated: 2023/01/05 23:30:41 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

//Prend un tableau de string en entree, check si l'option -n est presente
//en premiere position dans le tableau puis ecrit sur la sortie standard chacune
//des trings du tableau separee par un espace.
//la repetition de -n est accepte ainsi que qu'un nombre arbitraire de n.
//Exemple (-nnn -n -n).
//Un retour a la ligne est ajoute a la fin, sauf si l'option -n est detecte.
//ligne suivante fausse dans bash, vraie dans zsh.
//Le premier '-' seul est ignore puis la fonction n'accepte plus d'option.

int	ms_echo(t_admin *adm)
{
	int	opt;
	int	i;
	int	j;

	opt = 0;
	if (adm->cmlst->args[1])
		if (!ft_strcmp(adm->cmlst->args[1], "-n")
			|| ft_strcmp(adm->cmlst->args[1], "-n") == 110)
			opt = 1;
	i = 1 + opt;
	j = (int)ms_strlen_tab(adm->cmlst->args);
	while (i < j)
	{
		ft_printf("%s", adm->cmlst->args[i]);
		if (i < j - 1)
			ft_printf(" ");
		i++;
	}
	if (!opt)
		ft_printf("\n");
	g_lstpipe_status = 0;
	return (0);
}

// int	ms_pre_echo(char **str, int *opt)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		j = 0;
// 		if ((str[i][j] == '-') && (str[i][j + 1] == 'n'))
// 		{
// 			j++;
// 			while (str[i][j] && (str[i][j] == 'n'))
// 				j++;
// 		}
// 		if (str[i][j] == '\0')
// 			*opt = 1;
// 		else
// 			return (i);
// 		i++;
// 	}
// 	return (i);
// }
