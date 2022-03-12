/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 11:33:23 by jtrebes           #+#    #+#             */
/*   Updated: 2021/08/08 11:59:55 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	thread_data_init(t_z *z, int n)
{
	int				name;
	t_thread_data	*d;

	name = 0;
	while (name < n)
	{
		d = &z->thread_data[name];
		d->settings = &z->settings;
		d->name = name;
		d->left_fork = name;
		d->right_fork = (name + 1) % n;
		d->forks = z->forks;
		d->eat_count = 0;
		d->time_last_eat = 0;
		d->mutex = &z->mutex;
		d->over_eat_count = &z->over_eat_count;
		d->death = &z->death;
		name++;
	}
}

static int	init_mutex(t_z *z, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		if (pthread_mutex_init(&(z->forks[i]), NULL))
			return (1);
	if (pthread_mutex_init(&(z->mutex), NULL))
		return (1);
	return (0);
}

int	struct_init(t_z *z, int n)
{
	z->tid = NULL;
	z->forks = NULL;
	z->thread_data = NULL;
	z->death = 0;
	z->over_eat_count = 0;
	z->tid = malloc(sizeof(pthread_t) * n);
	if (!z->tid)
		return (exit_error(0, "Error: Malloc failed\n"));
	z->thread_data = malloc(sizeof(t_thread_data) * n);
	if (!z->thread_data)
		return (exit_error(z, "Error: Malloc failed\n"));
	z->forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!z->forks)
		return (exit_error(z, "Error: Malloc failed\n"));
	if (init_mutex(z, n))
		return (exit_error(z, "Error: Mutex init failed\n"));
	thread_data_init(z, n);
	return (0);
}
