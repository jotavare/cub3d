/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:34:13 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/04 18:30:16 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Search for a character in a limited portion of a string.
 *
 * @param s The input string to search.
 * @param c The character to search for.
 * @param n The maximum number of characters to search.
 * @return A pointer to the first occurrence of the character or NULL
 * if not found.
 */
char	*ft_strnchr(const char *s, int c, size_t n)
{
	char	byte;

	byte = (char) c;
	while (*s && *s != byte && n)
	{
		s++;
		n--;
	}
	if (*s == byte)
		return ((char *)s);
	return (0);
}
