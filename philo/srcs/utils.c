/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 11:34:04 by jtrebes           #+#    #+#             */
/*   Updated: 2021/08/08 11:45:32 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	unsigned long long	res;
	int					sign;

	sign = 1;
	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return ((int)(sign * res));
}

static int	ft_atoi_err(const char *str, int *err)
{
	unsigned long long	res;
	int					sign;

	*err = 0;
	sign = 1;
	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (!*err && *str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		if ((sign == -1 && res > (unsigned long long)2147483648)
			|| (sign == 1 && res > (unsigned long long)INT_MAX))
			*err = 1;
		str++;
	}
	if (!*err && *str != '\0')
		*err = 2;
	return ((int)(sign * res));
}

int	ft_isint_str(const char *str)
{
	int	err;

	ft_atoi_err(str, &err);
	if (err == 1)
		return (1);
	if (err == 2)
		return (2);
	return (0);
}
