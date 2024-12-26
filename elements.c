/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-safi <hes-safi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:03:59 by hes-safi          #+#    #+#             */
/*   Updated: 2024/11/17 15:01:38 by hes-safi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	converter(t_game *cub, char **arr, char c)
{
	if (c == 'F')
	{
		cub->fl[0] = ft_atoi(arr[0]);
		cub->fl[1] = ft_atoi(arr[1]);
		cub->fl[2] = ft_atoi(arr[2]);
	}
	else if (c == 'C')
	{
		cub->cl[0] = ft_atoi(arr[0]);
		cub->cl[1] = ft_atoi(arr[1]);
		cub->cl[2] = ft_atoi(arr[2]);
	}
}

void	map_elements(t_game *cub, char **map)
{
	int	i;
	int	j;

	i = 0;
	if (!cub->no || !cub->so || !cub->ea || !cub->we
		|| cub->no[0] == '\0' || cub->so[0] == '\0'
		|| cub->ea[0] == '\0' || cub->we[0] == '\0'
		|| cub->fl[0] < 0 || cub->fl[1] < 0 || cub->fl[2] < 0
		|| cub->cl[0] < 0 || cub->cl[1] < 0 || cub->cl[2] < 0)
		ft_error(cub, "Invalid or Missing Element(s)!");
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_walkable(map[i][j]) && map[i][j] != '1' && map[i][j] != ' ')
				ft_error(cub, "Invalid Map Element(s)!");
			j++;
		}
		i++;
		if (cub->cols < j)
			cub->cols = j;
	}
	cub->rows = i;
}

int	color_setter(t_game *c, char *s)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!s[i] || !s[i + 1] || s[i + 1] != ' ' || (s[i] != 'F' && s[i] != 'C'))
		return (0);
	if ((s[i] == 'F' && c->fl[0] >= 0 && c->fl[1] >= 0 && c->fl[2] >= 0)
		|| (s[i] == 'C' && c->cl[0] >= 0 && c->cl[1] >= 0 && c->cl[2] >= 0))
		ft_error(c, "Duplicate Color(s)!");
	if (counter(s, ',') != 2)
		return (0);
	tmp = ft_split(&s[i + 1], ',');
	if (tmp && tmp[0] && tmp[1] && tmp[2] && tmp[3])
		return (free_array(tmp), 0);
	if (s[i] == 'F' && tmp && tmp[0] && tmp[1] && tmp[2])
		converter(c, tmp, 'F');
	else if (s[i] == 'C' && tmp && tmp[0] && tmp[1] && tmp[2])
		converter(c, tmp, 'C');
	free_array(tmp);
	if ((s[i] == 'F' && (c->fl[0] < 0 || c->fl[1] < 0 || c->fl[2] < 0))
		|| (s[i] == 'C' && (c->cl[0] < 0 || c->cl[1] < 0 || c->cl[2] < 0)))
		return (0);
	return (1);
}

int	path_setter(t_game *cub, char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (1);
	if ((str[i] == 'N' && str[i + 1] && str[i + 1] == 'O' && cub->no)
		|| (str[i] == 'S' && str[i + 1] && str[i + 1] == 'O' && cub->so)
		|| (str[i] == 'E' && str[i + 1] && str[i + 1] == 'A' && cub->ea)
		|| (str[i] == 'W' && str[i + 1] && str[i + 1] == 'E' && cub->we))
		ft_error(cub, "Duplicate Path(s)!");
	if (str[i] == 'N' && str[i + 1] && str[i + 1] == 'O' && !cub->no)
		cub->no = ft_strdup(&str[i + 2]);
	else if (str[i] == 'S' && str[i + 1] && str[i + 1] == 'O' && !cub->so)
		cub->so = ft_strdup(&str[i + 2]);
	else if (str[i] == 'E' && str[i + 1] && str[i + 1] == 'A' && !cub->ea)
		cub->ea = ft_strdup(&str[i + 2]);
	else if (str[i] == 'W' && str[i + 1] && str[i + 1] == 'E' && !cub->we)
		cub->we = ft_strdup(&str[i + 2]);
	else if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		return (1);
	else
		return (0);
	return (1);
}

void	get_elements(t_game *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->split[i])
	{
		j = 0;
		while (cub->split[i][j] && cub->split[i][j] == ' ')
			j++;
		if (!cub->split[i][j])
			i++;
		else if (is_map(&cub->split[i][j]))
			break ;
		else if (path_setter(cub, &cub->split[i][j]))
			i++;
		else if (color_setter(cub, &cub->split[i][j]))
			i++;
		else
			ft_error(cub, "Invalid Element(s)!");
	}
	cub->map_tmp = &cub->split[i];
	map_elements(cub, &cub->split[i]);
}
