/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 11:31:25 by jtrebes           #+#    #+#             */
/*   Updated: 2021/08/07 21:49:30 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	clear_pthreads(t_z *z, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		if (pthread_join((z->tid[i]), NULL))
			return (exit_error(z, "Error: phtread_join failed\n"));
	return (0);
}

void	clear(t_z *z)
{
	if (z->tid)
	{
		free(z->tid);
		z->tid = NULL;
	}
	if (z->thread_data)
	{
		free(z->thread_data);
		z->thread_data = NULL;
	}
	if (z->forks)
	{
		free(z->forks);
		z->forks = NULL;
	}
}

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	exit_error(t_z *z, char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (z)
		clear(z);
	return (1);
}
