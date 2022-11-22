/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:30:49 by rarraji           #+#    #+#             */
/*   Updated: 2022/11/19 17:55:37 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_line(int fd, char *str)
{
	char	*s1;
	int		i;

	i = 1;
	s1 = (char *)malloc(BUFFER_SIZE + 1);
	if (!s1)
		return (NULL);
	while (i != 0)
	{
		i = read(fd, s1, BUFFER_SIZE);
		if (i < 0)
		{
			free(str);
			free(s1);
			return (NULL);
		}
		s1[i] = '\0';
		str = ft_strjoin(str, s1);
		if (ft_strchr(str, '\n'))
			break ;
	}
	free(s1);
	return (str);
}

char	*p1_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	line = ft_substr(str, 0, i + 1);
	return (line);
}

char	*last_line(char *str)
{
	char	*line;
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\0' || (str[i] == '\n' && str[i + 1] == '\0'))
	{
		free(str);
		return (NULL);
	}
	line = ft_substr(str, i + 1, ft_strlen(str) - i);
	free(str);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*line;

	if ((fd < 0 || fd == 1 || fd == 2) || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = read_line(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = p1_line(str[fd]);
	str[fd] = last_line(str[fd]);
	return (line);
}
