/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:34:17 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/04 18:30:29 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Duplicates a limited portion of a null-terminated string.
 *
 * @param s1 The input string to be duplicated.
 * @param n The maximum number of characters to duplicate.
 * @return A new string containing a copy of the input string, up to
 * 'n' characters, or NULL on failure.
 */
char	*ft_strndup(const char *s1, size_t n)
{
	char	*heap_p;
	char	*p;

	heap_p = malloc(n + 1);
	if (!heap_p)
		return (0);
	p = heap_p;
	while ((*s1 != 0) && (n--))
		*p++ = *s1++;
	*p = '\0';
	return (heap_p);
}
