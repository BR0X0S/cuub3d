/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:41:07 by hes-safi          #+#    #+#             */
/*   Updated: 2024/11/29 11:21:59 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = -1;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
	{
		if (res == -1)
			res = 0;
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] != '\0' || res > 255)
		return (-1);
	return (res);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*dest;

	if (!str || (str[0] != '\0' && str[0] != ' '))
		return (ft_strdup(""));
	while (str && *str == ' ')
		str++;
	i = ft_strlen(str);
	dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2, int flag)
{
	size_t	i;
	size_t	j;
	size_t	s1len;
	size_t	s2len;
	char	*toreturn;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	toreturn = malloc(s1len + s2len + 1);
	while (s1[i])
		toreturn[j++] = s1[i++];
	i = 0;
	while (s2[i])
		toreturn[j++] = s2[i++];
	toreturn[j] = '\0';
	if (flag == 1)
		free(s1);
	return (toreturn);
}

int	escape(t_game *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	exit(0);
}
