/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 11:51:48 by jtrebes           #+#    #+#             */
/*   Updated: 2021/08/08 10:35:03 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_chrono(long time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + tv.tv_usec / 1000) - time);
}

void	ft_usleep(int duration)
{
	long	start;
	long	current;

	start = get_chrono(0);
	current = start;
	while (duration > current - start)
	{
		usleep(100);
		current = get_chrono(0);
	}
}
