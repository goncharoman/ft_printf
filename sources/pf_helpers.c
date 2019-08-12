/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 12:46:22 by ujyzene           #+#    #+#             */
/*   Updated: 2019/08/12 18:53:15 by ujyzene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static inline int	preinx(t_format *f, char ch)
{
	if (f->base == 10 || f->base == 0)
		return (3);
	if ((f->alt && ch != 48) ||
		(!!(f->opt & 2) && f->base != 10 && f->base != 0))
		return (f->base == 16 ? !(f->opt & 1) : 2);
	else
		return (3);
}

static t_printf		print_init(t_format *f, char **str)
{
	t_printf	p;
	const char	*pre[] = {"0x", "0X", "0", ""};

	p.str_len = (int)ft_strlen(*str);
	p.add = (char*)pre[preinx(f, **str)];
	p.add_len = (int)ft_strlen(p.add);
	f->prec += (SIGN(**str) * f->sign) - (f->base == 8 && f->alt);
	p.all_len = !!f->base ? MAX(f->width, MAX(p.str_len, f->prec) + p.add_len) :
		f->width;
	p.p_part = MAX(f->prec - p.str_len, 0);
	p.w_part = MAX(p.all_len - (MAX(f->prec * !!f->base, p.str_len) +
		p.add_len), 0);
	return (p);
}

static char			*pf_prec(t_format *f, t_printf *p, char **str)
{
	char	*tmp;
	int		i;

	if (f->prec == 0 && **str == 48)
		tmp = ft_strdup(f->width > 0 ? " " : p->add);
	else if ((tmp = ft_strnew(p->all_len - p->w_part)))
	{
		i = (f->pad == 48 || f->prec > 0) && SIGN(**str);
		*tmp = i ? **str : 0;
		SCAT(MSET(SCAT(tmp + i, p->add), 48, p->p_part), *str + i);
	}
	else
		return (*str);
	free(*str);
	return ((*str = tmp));
}

char				*pf_fill(t_format *f, char **str)
{
	char		*tmp;
	t_printf	p;

	p = print_init(f, str);
	if (!(tmp = ft_strnew(p.all_len)))
		return (*str);
	if (f->base > 0)
		pf_prec(f, &p, str);
	if (!f->left)
		ft_strcpy(MSET(tmp, !f->base && !!f->pad ? f->pad : 32, p.w_part),
			*str);
	else
		ft_memset(SCPY(tmp, *str), !f->base && !!f->pad ? f->pad : 32,
			p.w_part);
	free(*str);
	return ((*str = tmp));
}
