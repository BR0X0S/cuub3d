/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-safi <hes-safi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:24:48 by hes-safi          #+#    #+#             */
/*   Updated: 2024/11/17 15:04:36 by hes-safi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(t_game *cub, char *str)
{
	printf("%sError\n", RED);
	printf("%s%s\n", str, OFF);
	free_array(cub->split);
	free_array(cub->map);
	ft_free(cub->file);
	ft_free(cub->no);
	ft_free(cub->so);
	ft_free(cub->ea);
	ft_free(cub->we);
	exit(1);
}

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		ft_free(arr[i]);
		i++;
	}
	ft_free(arr);
}

void	print_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("arr[%d]	: {%s}\n", i, arr[i]);
		i++;
	}
}

void	print_elements(t_game *cub)
{
	printf("NO	: {%s}\n", cub->no);
	printf("SO	: {%s}\n", cub->so);
	printf("EA	: {%s}\n", cub->ea);
	printf("WE	: {%s}\n", cub->we);
	printf("FL	: {%d, %d, %d}\n", cub->fl[0], cub->fl[1], cub->fl[2]);
	printf("CL	: {%d, %d, %d}\n", cub->cl[0], cub->cl[1], cub->cl[2]);
	printf("ROWS	: %d\n", cub->rows);
	printf("COLS	: %d\n", cub->cols);
}

int	counter(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}
