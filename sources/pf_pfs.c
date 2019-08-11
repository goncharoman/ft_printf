/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_pfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 01:07:59 by ujyzene           #+#    #+#             */
/*   Updated: 2019/08/07 19:52:35 by ujyzene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

t_pfs	pfs_init(void)
{
	t_pfs	tmp;

	if (!(tmp.s = ft_strnew(PF_BUFFSIZE)))
	{
		tmp.len = 0;
		tmp.last = 0;
	};
	tmp.len = PF_BUFFSIZE;
	tmp.last = 0;
	return (tmp);
}

static int		pfs_expand(t_pfs *buff)
{
	char	*tmp;

	if (!(tmp = ft_strnew(buff->len + PF_BUFFSIZE)))
		return (0);
	ft_strcpy(tmp, buff->s);
	free(buff->s);
	buff->s = tmp;
	buff->len += PF_BUFFSIZE;
	return (1);
}

inline int		pfs_write(t_pfs *buff, char *s, size_t len)
{
	if (len == (size_t)-1)
		len = ft_strlen(s);
	while (buff->len < buff->last + (int)len)
		if (!pfs_expand(buff))
			return (0);
	if (buff->len >= buff->last + (int)len)
	{
		ft_memcpy(buff->s + buff->last, s, len);
		buff->last += len;
	}
	return (1);
}

