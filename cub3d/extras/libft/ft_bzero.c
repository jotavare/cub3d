/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:33:49 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/04 18:20:22 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Sets a block of memory to zero.
 *
 * @param b A pointer to the memory block to be zeroed.
 * @param n The number of bytes to set to zero.
 */
void	ft_bzero(void *b, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	dest = b;
	i = 0;
	while (i++ < n)
		*dest++ = 0;
}
