/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 02:29:42 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/11 21:01:41 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

//if in_quote != 0, we have unclosed quotes
static int	count_words(char const *s, char *in_quote)
{
	int		num_words;
	int		in_word;

	num_words = 0;
	in_word = 0;
	*in_quote = 0;
	while (*s)
	{
		if (!ft_isspace(*s) && !in_word)
		{
			num_words++;
			in_word = 1;
		}
		if (*in_quote && *s == *in_quote)
			*in_quote = 0;
		else if (!*in_quote && (*s == 0x22 || *s == 0x27))
			*in_quote = *s;
		else if (ft_isspace(*s) && !*in_quote)
			in_word = 0;
		s++;
	}
	// printf("char %c, inquote: %c, inword: %d, n_words: %d\n", *s, *in_quote, in_word, num_words);
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

// splits by quotes and spaces
// status indentifies unclosed quotes
static char	**word_split(char const *s, char *status)
{
	char	**ret;
	int		counter;

	if (!s || count_words(s, status) == 0)
		return (*status = 3, NULL);
	if (*status)
		return (*status = 1, NULL);
	ret = ft_calloc((count_words(s, status) + 1), sizeof(char *));
	counter = -1;
	while (ret && *s)
	{
		if (!ft_isspace(*s))
		{
			ret[++counter] = next_word(&s);
			if (!(ret[counter]))
			{	
				free_arr_2((void **) ret);
				return (NULL);
			}
		}
		else
			s++;
	}
	return (ret);
}

//must have a way to identify invalid tokens and return them
static char	**token_split(char **word_s)
{
	(void) word_s;
	return (NULL);
}

//return NULL means error
//status = 0 malloc fail
//status = 1 unclosed quotes
//status = 2 unexpected token
//status = 3 empty string
char	**splitter(char const *s, char *status)
{
	char	**wordly_splitted;
	char	**tokenly_splitted;

	wordly_splitted = word_split(s, status);
	if (!wordly_splitted)
		return (NULL);
	return wordly_splitted;
	tokenly_splitted = token_split(wordly_splitted);
	if (!tokenly_splitted)
	{
		free_arr_2((void **) wordly_splitted);
		return (NULL);
	}
	return (tokenly_splitted);
}
