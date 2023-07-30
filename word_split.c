/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 02:29:42 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/07/30 04:42:13 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

static int	count_words(char const *s)
{
	int		num_words;
	int		in_word;
	char	in_quote;

	num_words = 0;
	in_word = 0;
	in_quote = 0;
	while (*s)
	{
		if (!ft_isspace(*s) && !in_word)
		{
			num_words++;
			in_word = 1;
		}
		if (in_quote && *s == in_quote)
			in_quote = 0;
		else if (!in_quote && (*s == 0x22 || *s == 0x27))
			in_quote = *s;
		else if (ft_isspace(*s) && !in_quote)
			in_word = 0;
		// printf("char %c, inquote: %c, inword: %d, n_words: %d\n", *s, in_quote, in_word, num_words);
		s++;
	}
	return (num_words);
}

static char	*next_word(char const **s)
{
	char	in_quote;
	char	*ret;
	int		counter;

	in_quote = 0;
	counter = -1;
	while ((*s)[++counter] && (!ft_isspace((*s)[counter]) || in_quote))
	{
		if (in_quote && (*s)[counter] == in_quote)
			in_quote = 0;
		else if (!in_quote && ((*s)[counter] == 0x22 || (*s)[counter] == 0x27))
			in_quote = (*s)[counter];
	}
	ret = ft_calloc(counter + 1, 1);
	in_quote = 0;
	counter = 0;
	while (ret && **s && (!ft_isspace(**s) || in_quote))
	{
		if (in_quote && **s == in_quote)
			in_quote = 0;
		else if (!in_quote && (**s == 0x22 || **s == 0x27))
			in_quote = **s;
		ret[counter++] = *((*s)++);
	}
	return (ret);
}

char	**word_split(char const *s)
{
	char	**ret;
	int		counter;

	if (!s || count_words(s) == 0)
		return (NULL);
	ret = ft_calloc((count_words(s) + 1), sizeof(char *));
	counter = -1;
	while (ret && *s)
	{
		if (!ft_isspace(*s))
		{
			ret[++counter] = next_word(&s);
			if (!(ret[counter]))
			{	
				while (counter > 0)
					free(ret[--counter]);
				free(ret);
				return (NULL);
			}
		}
		else
			s++;
	}
	return (ret);
}
