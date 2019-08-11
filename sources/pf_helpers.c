/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 12:46:22 by ujyzene           #+#    #+#             */
/*   Updated: 2019/08/11 07:18:44 by ujyzene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static t_printf		print_init(t_format *f, char **str)
{
	t_printf	p;
	const char	*pre[] = {"0x", "0X", "0", ""};

	p.str = *str;
	p.str_len = (int)ft_strlen(*str);
	p.add = pre[preinx(f, **str)];
	p.add_len = (int)ft_strlen(p.add);
	p.all_len = MAX(p.str_len, f->prec) + p.add_len;
	p.w_part = 
}

static inline int	preinx(t_format *f, char ch)
{
	if ((f->alt && ch != 48) || (f->opt >= 2 && f->base != 10))
		return (f->base == 16 ? (f->opt & 1) : 2);
	else
		return (3);
}

static char	*pf_prec(t_format *f, char **str)
{
	char		*tmp;
	// char		*add;
	// int			lother;
	int			i;

	// lother = MAX((int)ft_strlen(*str), f->prec) + (int)ft_strlen(add);
	if (f->prec == 0 && **str == 48)
		tmp = ft_strdup(f->width > 0 ? " " : f->base == 8 && f->alt ?
			"0" : add);
	else if ((tmp = ft_strnew(lother)))
	{
		i = (f->pad == 48 || f->prec > 0);
		*tmp = (i && SIGN(**str)) ? **str : 0;
		SCAT(MSET(SCAT(tmp + i, add), 48, MAX(f->prec - (int)ft_strlen(*str),
		0)), *str + i);
	}
	else
		return (*str);
	free(*str);
	return ((*str = tmp));
}

char		*pf_fill(t_format *f, char **str)
{
	char	*tmp;
	int		len;
	int		lstr;

	lstr = (int)ft_strlen(*str);
	len = lstr < MAX(f->width, f->prec) ?
		MAX(f->width, !!f->base * (MAX(f->prec, lstr) + 2)) :
		lstr + f->alt * 2;
	if (!(tmp = ft_strnew(len)))
		return (*str);
	f->prec += (SIGN(**str) * f->sign) - (f->base == 8 && f->alt);
	if (f->base > 0)
		pf_prec(f, str);
	len = MAX(f->width - (int)ft_strlen(*str), 0);
	if (!f->left)
		ft_strcpy(MSET(tmp, !!f->pad && !f->base ? f->pad : 32, len), *str);
	else
		ft_memset(SCPY(tmp, *str), !!f->pad && !f->base ? f->pad : 32, len);
	free(*str);
	return ((*str = tmp));
}
