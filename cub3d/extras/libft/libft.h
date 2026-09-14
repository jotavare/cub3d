/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:34:39 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/04 18:26:03 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// [LIBRARIES] //
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

// [FUNCTIONS] //
int		ft_atoi(const char *str);
void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isdigit(int str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_putstr_fd(char const *s, int fd);
char	**ft_split(char const *s, char c);
void	ft_split_free(char **ptr);
char	*ft_strdup(char *src);
size_t	ft_strlen(const char *str);
char	*ft_strnchr(const char *s, int c, size_t n);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
int		char_in_set(char c, char const *set);
char	*get_next_line(int fd);

#endif
