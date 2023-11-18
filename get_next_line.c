/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilson <wilson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:29:56 by wilson            #+#    #+#             */
/*   Updated: 2023/11/10 13:30:40 by wilson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin_check(char *stash, char *buff)
{
	char	*res;

	if (!stash)
		res = ft_strjoin("", buff);
	else
	{
		res = ft_strjoin(stash, buff);
		free(stash);
	}
	return (res);
}

static char	*read_stash(char *stash, int fd)
{
	int		i;
	char	*buff;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	i = 1;
	while (i != 0 && !ft_strchr(stash, '\n'))
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[i] = '\0';
		stash = ft_strjoin_check(stash, buff);
	}
	free(buff);
	return (stash);
}

static char	*get_line(char *stash)
{
	int		i;
	char	*line;

	if (!stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = -1;
	while (stash[++i] && stash[i] != '\n')
		line[i] = stash[i];
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		++i;
	}
	line[i] = '\0';
	return (line);
}

static char	*new_stash(char *stash)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new = malloc(sizeof(char) * ft_strlen(stash) - i + 1);
	if (!new)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		new[j++] = stash[i++];
	new[j] = '\0';
	free(stash);
	return (new);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		if (stash)
			free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = read_stash(stash, fd);
	if (!stash)
		return (NULL);
	line = get_line(stash);
	stash = new_stash(stash);
	return (line);
}
