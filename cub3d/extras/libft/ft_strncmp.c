/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:34:15 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/04 18:24:50 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Compares two null-terminated strings within a limited portion.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @param n The maximum number of characters to compare.
 * @return An integer less than, equal to, or greater than 0, indicating
 * whether the first string is less than, equal to, or greater than the
 * second string, respectively.
 */
int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
