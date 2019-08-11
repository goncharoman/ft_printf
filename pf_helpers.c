/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 21:59:19 by ujyzene           #+#    #+#             */
/*   Updated: 2019/08/07 12:47:54 by ujyzene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ft_printf.h>

char *pf_fill(t_format *f, char **str)
{
	size_t	slen;
	size_t	len;
	char	*tmp;
	int		j;

	len = f->width - (slen = ft_strlen(*str));
	if (!*str || !(tmp = ft_strnew(f->width)))
		return (NULL);
	if (!f->right)
	{
		*tmp = (j = f->pad == 48 && (**str == 43 || **str == 45)) ? **str : 0;
		ft_strcpy(ft_memset(tmp + j, f->pad, len) + len, *str + j);
	}
	else
		ft_memset(ft_strcpy(tmp, *str) + slen, f->pad, len);
	free(*str);
	return ((*str = tmp));
}

// static char *pf_hex_helper(char *str, char *add, t_format *f)
// {
// 	char	*tmp;
// 	int		ntmp;
// 	int		alen;
// 	int 	slen;

// 	alen = f->alt * ft_strlen(add);
// 	slen = (int)ft_strlen(str);
// 	if (!(tmp = ft_strnew(MAX((int)f->width, f->prec + alen))))
// 		return (NULL);
// 	if (!f->right)
// 	{
// 		if ((f->prec > slen && (ntmp = f->width - f->prec - alen) > 0) ||
// 		((ntmp = f->width - alen - slen) > 0 && f->pad != '0'))
// 			ft_memset(tmp, ' ', ntmp);
// 		if (f->alt && f->prec != 0)
// 			ft_strcat(tmp, add);
// 		if ((f->prec == -1 && (ntmp = f->width - alen - slen) > 0
// 		 && f->pad == '0') || (ntmp = f->prec - slen) > 0)
// 		 	ft_memset(tmp + ft_strlen(tmp), '0', ntmp);
// 		ft_strcat(tmp, str);
// 	}
// 	else
// 	{
// 		tmp = ft_strjoin(add, str);
// 		return (pf_fill(f, &tmp));

// 	}
// 	return (tmp);
// }

// char	*pf_hex(char **str, int base, int low, t_format *f)
// {
// 	char	*add;
// 	char	*tmp;

// 	add = f->alt && **str != '0' ? base == 16 ? low ? "0x" : "0X" : "0" : "";
// 	tmp = MAX(f->width, f->prec) > (int)(ft_strlen(*str) + ft_strlen(add)) ? 			pf_hex_helper(*str, add, f) : ft_strjoin(add, *str);
// 	free(*str);
// 	*str = tmp;
// 	return ((*str = tmp));
// }

static t_comp	get_comp(t_format *f, char *str, int low)
{
	t_comp c;

	c.str = *str;
}


static char *pf_prec(t_format *f, char **str)
{
	char	*tmp;
	int		i;
	int		len;

	if (f->prec == 0)
		return (f->width > 0 ? " " : f->base == 8 && f->alt ? "0" : "");
	if (f->prec == -1 || (len = f->prec - ft_strlen(*str)) < 0 ||
		!(tmp = ft_strnew(f->prec)))
		return (*str);
	*tmp = (i = SIGN(*str)) ? **str : 0;
	ft_strcpy(ft_memset(tmp + i, '0', len) + len, *str + i);
	free(*str);
	return ((*str = tmp));
}

char *pf_numfill(t_format *f, char **str, int low)
{
	char	*add;
	char	*tmp[2];
	int		len[3];
	int		i;

	add = f->alt && **str != '0' ? f->base == 16 ? low ? "0x" : "0X" : "0" : "";
	if (MAX(f->width, f->prec) < (len[0] = ft_strlen(*str)) ||
		!(tmp = ft_strnew(MAX(f->width, (len[1] = ft_strlen(add)) + f->prec))))
		return (*str);
	len[2] = f->width - f->prec > 0 ? f->width - len[0] - f->alt * len[1] : 0;
	if (!f->right)
	{
		*tmp = () ? **str : 0;
		// ft_strcpy(ft_memset(tmp + i, f->pad, len[2]) + len[2],
		// 	pf_prec(f, str) + i);
		STRCPY(MEMSET((LEFT(f) ? STRCAT(tmp, add) : tmp) + i, f->pad, len[2]), 		pf_prec(f, str));
	}
	else
		// ft_memset(ft_strcpy(tmp, pf_prec(f, str)) + len[0], f->pad, len[2]);
		MEMSET()
	free(*str);
	return ((*str = tmp));
}
