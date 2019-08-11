/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 01:43:04 by ujyzene           #+#    #+#             */
/*   Updated: 2019/08/10 21:32:58 by ujyzene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static inline t_format	format_init(void)
{
	return (t_format){
		.prec = -1,
		.width = 0,
		.mod = 0,
		.base = 0,
		.alt = 0,
		.pad = 0,
		.sign = 0,
		.opt = 0,
		.left = 0,
	};
}

static inline int		isspec(char ch)
{
	return (!!ft_strchr("%sdibBoOuUxXfFcCnp", ch));
}

static inline int		get_base(char ch)
{
	return (ch == 'X' || ch == 'x' || ch == 'p' ? 16 :
		ch == 'O' || ch == 'o' ? 8 :
		ch == 's' || ch == 'c' || ch == '%' ? 0 : 10);
}

int						pf_parse(char **format, va_list args, t_pfs *out)
{
	t_format f;

	f = format_init();
	while (!isspec(**format))
	{
		if (!pf_parce_flag(format, &f) && (pf_parce_wp(format, args, &f) +
			pf_parce_mod(format, &f)) < 1)
			return (0);
	}
	return (pf_get_spec(format, &f, args, out));
}

int						pf_get_spec(char **conv, t_format *f, va_list args,
	t_pfs *out)
{
	const int	table[] = {[0] = 4, [2] = 3,3,3, [12] = 2, [16] = 5,
		[18] = 2, [21] = 2, [32] = 4, [33] = 1, [34] = 3,3,3, [38] = 1,
		[44] = 2, [45] = 2, [48] = 5, [50] = 2, [53] = 2
	};
	const int	(*handlers[7])(t_format*, va_list, t_pfs*) = {
		NULL,
		pf_int_handler,
		pf_uint_handler,
		pf_float_handler,
		pf_char_handler,
		pf_string_handler,
	};
	
	f->opt |= ft_islower(**conv) + (!!ft_strchr("epU%", **conv) << 1);
	f->base = get_base(**conv);
	if (**conv == '%')
		return (pf_char_handler(f, args, out));
	if (!**conv || !handlers[table[**conv - 67]])
		return (0);
	return (handlers[table[**conv - 67]](f, args, out));
}
