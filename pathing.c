/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-safi <hes-safi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:13:56 by hes-safi          #+#    #+#             */
/*   Updated: 2024/11/17 15:01:55 by hes-safi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_walkable(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	check_bounds(t_game *cub, char **arr, int i, int j)
{
	if (!i || !j || i == cub->rows - 1 || j == cub->cols - 1
		|| !arr[i + 1][j] || !arr[i - 1][j]
		|| !arr[i][j + 1] || !arr[i][j - 1])
		return (0);
	if (arr[i + 1][j] == ' ' || arr[i - 1][j] == ' '
		|| arr[i][j + 1] == ' ' || arr[i][j - 1] == ' ')
		return (0);
	return (1);
}

void	check_dupes(t_game *cub)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S'
				|| cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
			{
				if (flag == 1)
					ft_error(cub, "Duplicate Spawn Point(s)!");
				flag = 1;
			}
			j++;
		}
		i++;
	}
	if (flag == 0)
		ft_error(cub, "Missing Spawn Point!");
}

void	create_map(t_game *cub)
{
	int	i;
	int	j;

	i = 0;
	cub->map = malloc(sizeof(char *) * (cub->rows + 1));
	if (!cub->map)
		ft_error(cub, "Malloc() Failed!");
	while (cub->map_tmp[i])
	{
		cub->map[i] = malloc(cub->cols + 1);
		if (!cub->map[i])
			ft_error(cub, "Malloc() Failed!");
		j = -1;
		while (cub->map_tmp[i][++j])
			cub->map[i][j] = cub->map_tmp[i][j];
		while (j < cub->cols)
			cub->map[i][j++] = ' ';
		cub->map[i][j] = '\0';
		i++;
	}
	cub->map[i] = NULL;
	free_array(cub->split);
	cub->split = NULL;
	if (!cub->map[0])
		ft_error(cub, "Empty Map!");
}

void	check_pathing(t_game *cub)
{
	int	i;
	int	j;

	i = 0;
	check_dupes(cub);
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (is_walkable(cub->map[i][j])
				&& !check_bounds(cub, cub->map, i, j))
				ft_error(cub, "Map not Surrounded by Walls!");
			j++;
		}
		i++;
	}
}
