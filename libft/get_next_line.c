/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkozma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:43:48 by alkozma           #+#    #+#             */
/*   Updated: 2019/07/20 09:09:59 by alkozma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include "ft_printf.h"

static t_list	*ft_lstnew_gnl(void const *content, size_t fd, size_t sz)
{
	t_list	*ret;

	if (!(ret = (t_list*)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		ret->content = NULL;
		ret->content_size = 0;
	}
	else
	{
		if (!(ret->content = ft_memalloc(sz)))
			return (NULL);
		ft_memcpy(ret->content, content, sz);
		ret->content_size = fd;
	}
	ret->next = NULL;
	return (ret);
}

static t_list	*find_file(int fd, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (fd < 0)
		return (NULL);
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew_gnl("\0", fd, 1);
	ft_lstadd(lst, tmp);
	tmp = *lst;
	return (tmp);
}

static int		tokloc(char *str, char c)
{
	int i;

	i = 0;
	if (!ft_strchr(str, c))
		return (-1);
	while (str[i] != c)
		i++;
	return (i);
}

static void		strbecome(char **dst, char *src)
{
	char	*tmp;

	tmp = ft_strjoin(*dst, src);
	if (*dst)
	{
		free(*dst);
		*dst = NULL;
	}
	*dst = tmp;
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	int				i;
	int				read_bytes;
	char			buf[BUFF_SIZE + 1];
	t_list			*tst;

	MEMCHK((fd < 4865 && fd >= 0 && (tst = find_file(fd, &lst))));
	CONTENTCHK(((char*)tst->content) && *line);
	while (!ft_strchr((char*)tst->content, '\n') &&
			(read_bytes = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[read_bytes] = '\0';
		strbecome((char**)&tst->content, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (!ft_strlen((char*)tst->content))
		return (read_bytes);
	i = tokloc((char*)tst->content, '\n');
	*line = i >= 0 ? ft_strsub((char*)tst->content, 0, i)
		: ft_strdup((char*)tst->content);
	tst->content = i >= 0 ? ft_strslc((char*)tst->content, 0, i) : tst->content;
	if (i == -1 || ((char*)tst->content)[0] == '\0')
		free(tst->content);
	return (1);
}
