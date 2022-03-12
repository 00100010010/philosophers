/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_linux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 11:31:03 by jtrebes           #+#    #+#             */
/*   Updated: 2021/08/08 15:31:29 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	reaper(t_z *z)
{
	long	time;
	int		i;

	ft_usleep(z->settings.time_to_die);
	i = -1;
	while (++i < z->settings.n)
	{
		if (z->over_eat_count >= z->settings.n)
			return (philo_state(&(z->thread_data[i]), OVER_EAT));
		time = get_chrono(z->thread_data[i].time_last_eat);
		if (time > z->settings.time_to_die)
		{
			pthread_mutex_lock(&(z->mutex));
			time = get_chrono(z->thread_data[i].time_last_eat);
			if (time > z->settings.time_to_die)
				return (philo_state(&(z->thread_data[i]), DEATH));
			pthread_mutex_unlock(&(z->mutex));
		}
	}
	return (0);
}

static void	*routine(void *data)
{
	t_thread_data	*d;
	int				i;

	d = (t_thread_data *) data;
	d->start_time = get_chrono(0);
	d->time_last_eat = d->start_time;
	i = 0;
	while (philo_check(d) != DEATH)
	{
		if (i == 3)
			i = 0;
		if (i == 0 && philo_eat(d, d->settings->time_to_eat))
			break ;
		else if (i == 1 && philo_sleep(d, d->settings->time_to_sleep))
			break ;
		else if (i == 2 && philo_think(d))
			break ;
		i++;
	}
	return (NULL);
}

static int	start_threads(t_z *z, int i, int n)
{
	z->launching_time = get_chrono(0);
	while (i < n)
	{
		z->thread_data[i].launching_time = &(z->launching_time);
		if (pthread_create(&(z->tid[i]), NULL, &routine,
				(void *)&(z->thread_data[i])))
			return (exit_error(z, "Error: threads failed to start\n"));
		i += 2;
	}
	ft_usleep(1);
	i = 1;
	while (i < n)
	{
		z->thread_data[i].launching_time = &(z->launching_time);
		if (pthread_create(&(z->tid[i]), NULL, &routine,
				(void *)&(z->thread_data[i])))
			return (exit_error(z, "Error: threads failed to start\n"));
		i += 2;
		usleep(20);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_z	z;

	if (parse_settings(&z.settings, ac, av))
		return (1);
	if (struct_init(&z, z.settings.n))
		return (1);
	if (start_threads(&z, 0, z.settings.n))
		return (1);
	while (666)
		if (reaper(&z))
			break ;
	clear_pthreads(&z, z.settings.n);
	clear(&z);
	return (0);
}
