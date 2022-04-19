/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 04:08:59 by darakely          #+#    #+#             */
/*   Updated: 2022/04/15 20:50:50 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	get_for_read(int fd, char *buffer, char **str)
{
	int		j;
	char	*str2;

	if (!str[fd] || !ft_strchr(str[fd], '\n'))
	{
		j = read(fd, buffer, BUFFER_SIZE);
		while (j > 0)
		{
			buffer[j] = 0;
			if (!str[fd])
				str[fd] = ft_substr(buffer, 0, j);
			else
			{
				str2 = str[fd];
				str[fd] = ft_strjoin(str[fd], buffer);
				free(str2);
			}
			if (ft_strchr(buffer, '\n'))
				break ;
			j = read(fd, buffer, BUFFER_SIZE);
		}
	}
	free(buffer);
}

static char	*get_for_process(int fd, char **str)
{
	int		i;
	int		j;
	char	*for_substr;
	char	*tmp_str;

	if (!ft_strchr(str[fd], '\n'))
	{
		for_substr = ft_substr(str[fd], 0, ft_strlen(str[fd]));
		free(str[fd]);
		str[fd] = 0;
		return (for_substr);
	}
	i = ft_strlen(str[fd]);
	j = ft_strlen(ft_strchr(str[fd], '\n'));
	for_substr = ft_substr(str[fd], 0, (i - j) + 1);
	tmp_str = str[fd];
	str[fd] = ft_substr(ft_strchr(str[fd], '\n'), 1, j - 1);
	free(tmp_str);
	return (for_substr);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	char		*buffer;
	static char	*str[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	get_for_read(fd, buffer, str);
	if (!str[fd])
		return (0);
	if (!*str[fd])
	{
		tmp = str[fd];
		str[fd] = 0;
		free(tmp);
		return (0);
	}
	return (get_for_process(fd, str));
}
