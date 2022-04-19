/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:28:21 by darakely          #+#    #+#             */
/*   Updated: 2022/04/15 20:49:46 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	get_for_read(int fd, char *buffer, char **str)
{
	int		j;
	char	*str2;

	if (!*str || !ft_strchr(*str, '\n'))
	{
		j = read(fd, buffer, BUFFER_SIZE);
		while (j > 0)
		{
			buffer[j] = 0;
			if (!*str)
				*str = ft_substr(buffer, 0, j);
			else
			{
				str2 = *str;
				*str = ft_strjoin(*str, buffer);
				free(str2);
			}
			if (ft_strchr(buffer, '\n'))
				break ;
			j = read(fd, buffer, BUFFER_SIZE);
		}
	}
	free(buffer);
}

static char	*get_for_process(char **str)
{
	int		i;
	int		j;
	char	*for_substr;
	char	*tmp_str;

	if (!ft_strchr(*str, '\n'))
	{
		for_substr = ft_substr(*str, 0, ft_strlen(*str));
		free(*str);
		*str = 0;
		return (for_substr);
	}
	i = ft_strlen(*str);
	j = ft_strlen(ft_strchr(*str, '\n'));
	for_substr = ft_substr(*str, 0, (i - j) + 1);
	tmp_str = *str;
	*str = ft_substr(ft_strchr(*str, '\n'), 1, j - 1);
	free(tmp_str);
	return (for_substr);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	char		*buffer;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	get_for_read(fd, buffer, &str);
	if (!str)
		return (0);
	if (!*str)
	{
		tmp = str;
		str = 0;
		free(tmp);
		return (0);
	}
	return (get_for_process(&str));
}
