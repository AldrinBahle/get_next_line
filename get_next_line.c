/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 11:31:14 by agama             #+#    #+#             */
/*   Updated: 2018/06/19 13:22:08 by agama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_read_line(char **buff, char **line)
{
	char		*buffer;

	if ((*buff)[0] == '\0')
		return (0);
	if (ft_strchr(*buff, '\n') != NULL)
	{
		*(ft_strchr(*buff, '\n')) = '\0';
		*line = ft_strdup(*buff);
		buffer = ft_strdup(ft_strchr(*buff, '\0') + 1);
		free(*buff);
		if (buffer)
		{
			*buff = ft_strdup(buffer);
			free(buffer);
		}
	}
	else
	{
		*line = ft_strdup(*buff);
		ft_memdel((void **)buff);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	int			rd;
	static char	*temp[FD_LIMIT];
	char		buff[BUFF_SIZE + 1];
	char		*join;

	if (fd < 0 || read(fd, buff, 0) < 0 || line == NULL)
		return (-1);
	if (!(temp[fd]))
		temp[fd] = ft_strnew(0);
	while (ft_strchr(temp[fd], '\n') == NULL)
	{
		rd = read(fd, buff, BUFF_SIZE);
		buff[rd] = '\0';
		if (rd == 0)
			break ;
		join = ft_strjoin(temp[fd], buff);
		free(temp[fd]);
		temp[fd] = ft_strdup(join);
		if (!(temp[fd]))
			temp[fd] = ft_strnew(0);
		free(join);
	}
	return (ft_read_line(&temp[fd], line));
}
