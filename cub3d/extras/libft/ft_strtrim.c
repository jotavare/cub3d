/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:34:19 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/04 18:30:24 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates a new string by trimming characters from the beginning and
 * end of an input string.
 *
 * @param s1 The input string to be trimmed.
 * @param set A set of characters to be removed from the input string.
 * @return A new string containing the trimmed version of the input
 * string, or NULL on failure.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s1)
		return (0);
	start = 0;
	while (s1[start] && char_in_set(s1[start], set))
		start ++;
	end = ft_strlen(s1);
	while ((end > start) && char_in_set(s1[end - 1], set))
		end--;
	i = 0;
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!str)
		return (0);
	while (start < end)
	{
		str[i++] = s1[start];
		start ++;
	}
	str[i] = 0;
	return (str);
}
