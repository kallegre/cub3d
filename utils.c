/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilson <wilson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:39:26 by wilson            #+#    #+#             */
/*   Updated: 2023/11/17 22:56:47 by wilson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_msg(char *str, char **map)
{
	if (map)
		double_free(map);
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(str, 2);
	return (0);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	double_free(char **str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
			free(str[i]);
		free(str);
	}
}

char	*ft_substrf(char *str, int start, int len)
{
	char *new;

	new = ft_substr(str, start, len);
	free(str);
	return (new);
}

char	**dupntab(char **tab, int start, int len)
{
	int		i;
	char	**new;

	new = malloc(sizeof(char *) * len - start + 1);
	i = 0;
	while (start < len)
	{
		new[i] = ft_strdup(tab[start]);
		start++;
		i++;
	}
	new[i] = NULL;
	return (new);
}