/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tntini <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:23:43 by tntini            #+#    #+#             */
/*   Updated: 2018/06/27 09:25:33 by tntini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	end(char *buf)
{
	int i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		return (1);
	return (0);
}

int	get_line(const int fd, char *buf, char *strs[fd])
{
	int		tm;
	char	*tmp;

	while ((end(buf) != 1) && ((tm = read(fd, buf, BUFF_SIZE)) > 0))
	{
		buf[tm] = '\0';
		tmp = strs[fd];
		strs[fd] = ft_strjoin(tmp, buf);
		ft_strdel(&tmp);
	}
	ft_strdel(&buf);
	if (tm < 0)
		return (-1);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	int			tm;
	static char	*strs[2147483647];
	char		*buf;
	char		*str;
	char		*tmp;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	buf = ft_strnew(BUFF_SIZE);
	if (!strs[fd])
		strs[fd] = ft_strnew(0);
	if ((tm = get_line(fd, buf, strs)) == -1)
		return (-1);
	if ((str = ft_strchr(strs[fd], '\n')))
	{
		*line = ft_strsub(strs[fd], 0, str - strs[fd]);
		tmp = strs[fd];
		strs[fd] = ft_strdup(str + 1);
		ft_strdel(&tmp);
		return (1);
	}
	*line = ft_strdup(strs[fd]);
	ft_strdel(&strs[fd]);
	return (ft_strlen(*line) > 0 ? 1 : 0);
}
