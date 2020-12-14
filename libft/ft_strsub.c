/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijanie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:20:46 by ijanie            #+#    #+#             */
/*   Updated: 2019/04/19 18:20:55 by ijanie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;

	if (!s)
		return (NULL);
	new_str = ft_strnew(len);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
		*(new_str + i++) = *(s + start++);
	return (new_str);
}
