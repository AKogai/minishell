/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijanie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:20:46 by ijanie            #+#    #+#             */
/*   Updated: 2019/04/19 18:20:55 by ijanie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	has_whitespaces(char *str, int *i, size_t *j)
{
	while (ft_isspace(*(str + *i)))
		(*i)++;
	while (ft_isspace(*(str + *j)))
		(*j)--;
	if (*i || *j < ft_strlen(str))
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	size_t	j;
	int		k;
	char	*new_str;
	size_t	new_size;

	if (!s)
		return (NULL);
	i = 0;
	k = 0;
	j = ft_strlen(s) - 1;
	if (!has_whitespaces((char *)s, &i, &j) || !ft_strlen(s))
		return ((char *)s);
	new_size = (i == (int)ft_strlen(s)) ? 0 : ft_strlen(s) - (size_t)i - \
				(ft_strlen(s) - j);
	new_str = ft_strnew(new_size + 1);
	if (!new_str)
		return (NULL);
	while (i <= (int)j)
		*(new_str + k++) = *(s + i++);
	return (new_str);
}
