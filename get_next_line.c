/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:03:44 by flolefeb          #+#    #+#             */
/*   Updated: 2020/01/03 12:01:03 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_check(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*ft_crop_line(char *line, char *stat)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i] != '\n' && line[i])
		i++;
	j = i;
	i++;
	while (line[i])
		*stat++ = line[i++];
	if (j == 0)
	{
		free(line);
		line = ft_strdup("");
	}
	else
		while (line[j])
			line[j++] = 0;
	return (line);
}

int		get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			ret;
	static char	stat[BUFFER_SIZE];

	if (!(line) || fd < 0 || buf <= 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (ft_check(stat) == 0)
	{
		if ((ret = read(fd, buf, BUFFER_SIZE)) < 0)
			return (-1);
		buf[ret] = '\0';
	}
	*line = ft_strdup(stat);
	ft_bzero(stat, BUFFER_SIZE);
	while (ft_check(*line) == 0)
	{
		*line = ft_strjoin(*line, buf);
		ft_bzero(buf, (BUFFER_SIZE + 1));
		if ((ft_check(*line) == 0) && ((ret = read(fd, buf, BUFFER_SIZE)) <= 0))
			return (0);
		buf[ret] = '\0';
	}
	ft_bzero(buf, (BUFFER_SIZE + 1));
	*line = ft_crop_line(*line, stat);
	return (1);
}
