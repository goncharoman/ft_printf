/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_num_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 02:13:58 by ujyzene           #+#    #+#             */
/*   Updated: 2019/08/11 13:44:02 by kbins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

inline static intmax_t	get_int_value(t_format p, va_list args)
{
	if (p.mod == 0)
		return (va_arg(args, int));
	if (p.mod == M_LONG)
		return (va_arg(args, long));
	if (p.mod == M_LLONG)
		return (va_arg(args, long long));
	if (p.mod == M_HALF)
		return ((short)va_arg(args, int));
	if (p.mod == M_HHALF)
		return ((char)va_arg(args, int));
	if (p.mod == M_SIZET)
		return (va_arg(args, size_t));
	if (p.mod == M_MAXT)
		return (va_arg(args, intmax_t));
	else
		return (0);
}

inline static uintmax_t	get_uint_value(t_format p, va_list args)
{
	if (p.mod == 0)
		return (va_arg(args, unsigned int));
	if (p.mod == M_LONG)
		return (va_arg(args, unsigned long));
	if (p.mod == M_LLONG)
		return (va_arg(args, unsigned long long));
	if (p.mod == M_HALF)
		return ((unsigned short)va_arg(args, unsigned int));
	if (p.mod == M_HHALF)
		return ((unsigned char)va_arg(args, unsigned int));
	if (p.mod == M_SIZET)
		return (va_arg(args, size_t));
	if (p.mod == M_MAXT)
		return (va_arg(args, uintmax_t));
	else
		return (0);
}

int						pf_int_handler(t_format *f, va_list args, t_pfs *out)
{
	char		*tmp;

	tmp = ft_itoa_base(get_int_value(*f, args), f->base, f->sign);
	f->width += (!f->width && f->prec == -1 && !f->alt && !f->sign &&
		f->pad == 32 && !SIGN(*tmp)) * ((int)ft_strlen(tmp) + 1);
	f->sign = 1;
	f->alt = 0;
	if (f->pad == 48 && f->prec == -1 && f->width > 0)
	{
		f->prec = f->width - f->alt * (f->base == 16 ? 2 : f->base == 8);
		f->width = 0;
		f->pad = 32;
		f->sign = 0;
	}
	pfs_write(out, pf_fill(f, &tmp), -1);
	free(tmp);
	return (1);
}

int						pf_uint_handler(t_format *f, va_list args, t_pfs *out)
{
	char		*tmp;

	if (!!(f->opt & 2))
		f->mod = M_LLONG;
	tmp = ft_uitoa_base(get_uint_value(*f, args), f->base);
	if (f->pad == 48 && f->prec == -1 && f->width > 0)
	{
		f->prec = f->width - f->alt * (f->base == 16 ? 2 : f->base == 8);
		f->width = 0;
		f->sign = 0;
	}
	if (!*tmp)
		return (0);
	if (!!(f->opt & 1))
		ft_chcase(&tmp, ft_tolower);
	pfs_write(out, pf_fill(f, &tmp), -1);
	free(tmp);
	return (1);
}
