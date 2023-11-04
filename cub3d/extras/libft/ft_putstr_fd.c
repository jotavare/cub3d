/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:34:05 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/04 18:22:33 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes a null-terminated string to a file descriptor.
 *
 * @param s The null-terminated string to be written.
 * @param fd The file descriptor to write to.
 */
void	ft_putstr_fd(char const *s, int fd)
{
	int		i;

	if (fd < 0)
		return ;
	i = 0;
	if (s)
		while (s[i])
			write(fd, &s[i++], 1);
}
