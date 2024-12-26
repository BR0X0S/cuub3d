/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-safi <hes-safi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:21:10 by hes-safi          #+#    #+#             */
/*   Updated: 2024/11/12 16:43:53 by hes-safi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**freearray(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_word(char *word, char const *s, int i, int wordlen)
{
	int	j;

	j = 0;
	while (wordlen > 0)
	{
		word[j] = s[i - wordlen];
		j++;
		wordlen--;
	}
	word[j] = '\0';
	return (word);
}

static char	**ft_split_words(char const *s, char c, char **words)
{
	int	i;
	int	word;
	int	wordlen;

	i = 0;
	word = 0;
	wordlen = 0;
	while (word < ft_wordcount(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			wordlen++;
		}
		words[word] = malloc(wordlen + 1);
		if (!words)
			return (freearray(words));
		ft_word(words[word], s, i, wordlen);
		wordlen = 0;
		word++;
	}
	words[word] = 0;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char			**words;

	if (!s)
		return (NULL);
	words = malloc(sizeof(char *) * ((ft_wordcount(s, c)) + 1));
	if (!words)
		return (NULL);
	words = ft_split_words(s, c, words);
	return (words);
}
