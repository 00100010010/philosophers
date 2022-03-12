/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 11:31:40 by jtrebes           #+#    #+#             */
/*   Updated: 2021/08/08 12:00:23 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_error_in_arguments(t_settings *s, int ac)
{
	if (s->time_to_die < 0 || s->time_to_eat < 0
		|| s->time_to_sleep < 0 || (ac == 6 && s->over_eat_limit < 0))
		return (exit_error(0, "Error: no negative int allowed\n"));
	if (s->n <= 0 || s->n > 200)
		return (exit_error(0, "Error: num of philosophers (1-200)\n"));
	return (0);
}

static int	check_args_type(int ac, char **av)
{
	if (ft_isint_str(av[1]) || ft_isint_str(av[2])
		|| ft_isint_str(av[3]) || ft_isint_str(av[4]))
		return (1);
	if (ac == 6 && ft_isint_str(av[5]))
		return (1);
	return (0);
}

int	parse_settings(t_settings *s, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (exit_error(0, "Error: number of arguments\n"));
	if (check_args_type(ac, av))
		return (exit_error(0, "Error: not int in arguments\n"));
	s->n = ft_atoi(av[1]);
	s->time_to_die = ft_atoi(av[2]);
	s->time_to_eat = ft_atoi(av[3]);
	s->time_to_sleep = ft_atoi(av[4]);
	s->over_eat_limit = -1;
	if (ac == 6)
		s->over_eat_limit = ft_atoi(av[5]);
	return (check_error_in_arguments(s, ac));
}
