/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parce_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 22:44:01 by ujyzene           #+#    #+#             */
/*   Updated: 2019/08/12 13:24:45 by ujyzene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static unsigned int	n_from_format(char **format)
{
	int		n;
	char	*num;

	n = 0;
	while (**format && ft_isdigit(*(*format + n)))
		n++;
	num = ft_strsub(*format, 0, n);
	*format += n;
	n = ft_atoi(num);
	free(num);
	return (n);
}

inline int			pf_parce_flag(char **format, t_format *f)
{
	if (!ft_strchr("+- #0", **format))
		return (0);
	if (**format == '+')
		f->sign = 1;
	else if (**format == '-')
	{
		f->left = 1;
		f->pad = 32;
	}
	else if (**format == ' ' && !f->left)
		f->pad = 32;
	else if (**format == '#')
		f->alt = 1;
	else if (**format == '0' && !f->left)
	{
		if (f->pad == 32)
			f->opt |= 1;
		f->pad = 48;
	}
	(*format)++;
	return (1);
}

inline int			pf_parce_wp(char **format, va_list args, t_format *f)
{
	int tmp;

	if ((**format < '0' || **format > '9') &&
			**format != '*' && **format != '.')
		return (0);
	if (**format == '.')
	{
		(*format)++;
		tmp = **format == '*' ? va_arg(args, int) : n_from_format(format);
		f->prec = tmp >= 0 ? tmp : f->prec;
	}
	else
	{
		tmp = **format == '*' ? va_arg(args, int) : n_from_format(format);
		if (tmp >= 0)
			f->width = tmp;
		else
		{
			f->width = ABS(tmp);
			f->left = 1;
		}
	}
	if (**format == '*')
		(*format)++;
	return (1);
}

inline int			pf_parce_mod(char **format, t_format *f)
{
	t_uc	tmp;

	if (!(ft_strchr("lhLqzj", **format)))
		return (0);
	tmp = 0;
	if (**format == 'l')
		tmp = (*(*format + 1) == 'l') ? M_LLONG : M_LONG;
	else if (**format == 'h')
		tmp = (*(*format + 1) == 'h') ? M_HHALF : M_HALF;
	else if (**format == 'L' || **format == 'q')
		tmp = M_LDOUBLE;
	else if (**format == 'z')
		tmp = M_SIZET;
	else if (**format == 'j')
		tmp = M_MAXT;
	(*format) += 1 + (!!(tmp & M_LLONG) || !!(tmp & M_HHALF));
	f->mod = (tmp > f->mod) ? tmp : f->mod;
	return (1);
}
