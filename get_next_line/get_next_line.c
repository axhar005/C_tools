/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:30:18 by anboisve          #+#    #+#             */
/*   Updated: 2023/06/19 17:11:52 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*Ct_tiny_split(char *s, size_t *cut)
{
	char	*new;
	size_t	i;

	i = 0;
	while (s[i])
		if (s[i++] == '\n')
			break ;
	new = Ct_calloc(i + 1, sizeof(char));
	if (!new)
		return (new = Ct_sfree(new));
	*cut = i;
	while (i--)
		new[i] = s[i];
	return (new);
}

char	Ct_find(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return ('\n');
		i++;
	}
	return ('0');
}

char	*get_next_line(int fd)
{
	static char	*book;
	t_info		t_val;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 500)
		return (book = Ct_sfree(book));
	if (!book)
		book = Ct_calloc(1, sizeof(char));
	t_val.tmp = Ct_calloc(BUFFER_SIZE + 1, sizeof(char));
	t_val.rv = 0;
	while (Ct_find(book) == '0')
	{
		Ct_bzero(t_val.tmp, BUFFER_SIZE + 1);
		t_val.rv = read(fd, t_val.tmp, BUFFER_SIZE);
		if (t_val.rv <= 0)
			break ;
		book = Ct_strjoin(book, t_val.tmp);
	}
	t_val.tmp = Ct_sfree(t_val.tmp);
	if (t_val.rv == -1 || (t_val.rv <= 0 && *book == 0))
		return (book = Ct_sfree(book), NULL);
	t_val.tmp = Ct_tiny_split(book, &t_val.cut);
	t_val.tmp2 = book;
	book = Ct_strjoin(NULL, book + t_val.cut);
	return (Ct_sfree(t_val.tmp2), t_val.tmp);
}
