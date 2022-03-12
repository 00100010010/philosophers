/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 11:32:07 by jtrebes           #+#    #+#             */
/*   Updated: 2021/08/08 14:53:57 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	unlock_forks(t_thread_data *d, int exitnum)
{
	int	i;

	if (exitnum != DEATH)
	{
		pthread_mutex_unlock(&(d->forks[d->right_fork]));
		pthread_mutex_unlock(&(d->forks[d->left_fork]));
	}
	else
	{
		i = 0;
		*d->death = 1;
		while (i < d->settings->n)
			pthread_mutex_unlock(&d->forks[i++]);
		pthread_mutex_unlock(d->mutex);
	}
	return (exitnum);
}

static int	take_fork(t_thread_data *d, pthread_mutex_t *f, pthread_mutex_t *f2)
{
	pthread_mutex_lock(f);
	if (philo_state(d, FORK))
	{
		pthread_mutex_unlock(f);
		if (f2)
			pthread_mutex_unlock(f2);
		return (1);
	}
	return (0);
}

int	philo_eat(t_thread_data *d, int time)
{
	if (philo_check(d) == HE_ATE_IT_ALL)
		return (1);
	if (take_fork(d, &d->forks[d->left_fork], 0))
		return (1);
	if (take_fork(d, &d->forks[d->right_fork], &d->forks[d->left_fork]))
		return (1);
	++d->eat_count;
	if (philo_state(d, EAT))
		return (1);
	ft_usleep(time);
	if (d->settings->over_eat_limit != -1
		&& d->eat_count == d->settings->over_eat_limit)
	{
		pthread_mutex_lock(d->mutex);
		*(d)->over_eat_count += 1;
		pthread_mutex_unlock(d->mutex);
	}
	return (0);
}

int	philo_sleep(t_thread_data *d, int time)
{
	if (philo_state(d, SLEEP))
		return (unlock_forks(d, 1));
	unlock_forks(d, 0);
	ft_usleep(time);
	return (0);
}

int	philo_think(t_thread_data *d)
{
	if (philo_state(d, THINK))
		return (1);
	return (0);
}
