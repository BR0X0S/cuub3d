/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:32:15 by hes-safi          #+#    #+#             */
/*   Updated: 2024/11/26 19:43:22 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map(char *str)
{
	int	i;

	i = 0;
	if (str[i] == 'F' || str[i] == 'C')
		return (0);
	if ((str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		&& str[i + 1])
	{
		if ((str[i] == 'N' && str[i + 1] == 'O')
			|| (str[i] == 'S' && str[i + 1] == 'O')
			|| (str[i] == 'E' && str[i + 1] == 'A')
			|| (str[i] == 'W' && str[i + 1] == 'E'))
			return (0);
	}
	return (1);
}

char	*read_file(int fd)
{
	char	buffer[2];
	char	*line;

	if (fd < 0)
		return (NULL);
	line = malloc(2);
	if (line == NULL)
		return (NULL);
	line[0] = '\0';
	line[1] = '\0';
	while (read(fd, buffer, 1) > 0)
	{
		buffer[1] = '\0';
		line = ft_strjoin(line, buffer, 1);
	}
	if (!ft_strlen(line))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_map(t_game *cub, char *str)
{
	int		fd;
	int		len;

	len = ft_strlen(str);
	if (!str || len < 4 || str[len - 1] != 'b' || str[len - 2] != 'u'
		|| str[len - 3] != 'c' || str[len - 4] != '.')
		ft_error(cub, "Invalid Map File!");
	fd = open(str, O_RDONLY);
	if (fd == -1)
		ft_error(cub, "Could not open Map!");
	cub->file = read_file(fd);
	close(fd);
	if (!cub->file)
		ft_error(cub, "Map is Empty!");
}

void	check_map(t_game *cub)
{
	int	i;
	int	flag;

	i = 0;
	while (cub->file && cub->file[i])
	{
		flag = 0;
		while (cub->file[i] && cub->file[i] == ' ')
			i++;
		if (cub->file[i] && (cub->file[i] == '\n' || !is_map(&cub->file[i])))
			flag = 1;
		while (cub->file[i] && cub->file[i] != '\n')
			i++;
		if (!flag && cub->file[i] && cub->file[i] == '\n' && (!cub->file[i + 1]
				|| (cub->file[i + 1] && cub->file[i + 1] == '\n')))
			ft_error(cub, "Invalid Map Scene!");
		while (cub->file[i] && cub->file[i] == '\n')
			i++;
	}
}

void	parsing(t_game *cub, char *str)
{
	read_map(cub, str);
	check_map(cub);
	cub->split = ft_split(cub->file, '\n');
	if (!cub->split)
		ft_error(cub, "Map is Empty!");
	ft_free(cub->file);
	cub->file = NULL;
	get_elements(cub);
	print_elements(cub);
	create_map(cub);
	print_array(cub->map);
	check_pathing(cub);
	get_player_pos(cub->map, &cub->player);
}
