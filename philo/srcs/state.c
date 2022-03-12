/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 11:32:41 by jtrebes           #+#    #+#             */
/*   Updated: 2021/08/08 15:34:07 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_state(t_thread_data *d, int state)
{
	long	time;

	time = get_chrono(*d->launching_time);
	if (state == OVER_EAT)
		return ;
	else if (state == FORK)
		printf("%ld\t%d\thas taken a fork\n", time, d->name + 1);
	else if (state == EAT)
		printf("%ld\t%d\tis eating\n", time, d->name + 1);
	else if (state == SLEEP)
		printf("%ld\t%d\tis sleeping\n", time, d->name + 1);
	else if (state == THINK)
		printf("%ld\t%d\tis thinking\n", time, d->name + 1);
	else if (state == DEATH)
		printf("%ld\t%d\tdied\n", time, d->name + 1);
}

int	philo_check(t_thread_data *d)
{
	if (*d->death)
		return (DEATH);
	if (d->settings->over_eat_limit != -1
		&& d->eat_count == d->settings->over_eat_limit)
		return (HE_ATE_IT_ALL);
	return (0);
}

int	philo_state(t_thread_data *d, int state)
{
	if (state != DEATH)
		pthread_mutex_lock(d->mutex);
	if (*d->death)
	{
		pthread_mutex_unlock(d->mutex);
		return (1);
	}
	if (state == EAT)
		d->time_last_eat = get_chrono(0);
	print_state(d, state);
	if (state == DEATH || state == OVER_EAT)
		return (unlock_forks(d, DEATH));
	pthread_mutex_unlock(d->mutex);
	return (0);
}
