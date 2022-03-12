/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 11:33:03 by jtrebes           #+#    #+#             */
/*   Updated: 2021/08/08 11:25:57 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>
# define FORK 		1
# define EAT 		2
# define SLEEP 		3
# define THINK 		4
# define OVER_EAT 	5
# define HE_ATE_IT_ALL	6
# define THEY_ATE_IT_ALL 7
# define DEATH 		666

typedef struct s_settings
{
	int			n;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			over_eat_limit;
}				t_settings;

typedef struct s_thread_data
{
	t_settings			*settings;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*mutex;
	int					name;
	int					left_fork;
	int					right_fork;
	int					eat_count;
	int					*over_eat_count;
	long long			start_time;
	long long			*launching_time;
	long long			time_last_eat;
	int					*death;
}					t_thread_data;

typedef struct s_z
{
	pthread_t			*tid;
	t_thread_data		*thread_data;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mutex;
	t_settings			settings;
	int					over_eat_count;
	int					death;
	long long			launching_time;
}					t_z;

//ROUTINE
int			philo_eat(t_thread_data *data, int time);
int			philo_sleep(t_thread_data *data, int time);
int			philo_think(t_thread_data *data);
int			unlock_forks(t_thread_data *d, int exitnum);
//UTILS
int			ft_isint_str(const char *str);
int			ft_atoi(const char *str);

//EXIT
void		clear(t_z *z);
int			exit_error(t_z *z, char *msg);
int			clear_pthreads(t_z *z, int n);
//PARSE SETTINGS
int			parse_settings(t_settings *x, int ac, char **av);
//STRUCT INIT
int			struct_init(t_z *z, int n);
//TIME UTILS
void		ft_usleep(int duration);
long		get_chrono(long time);
/// MAIN
int			philo_check(t_thread_data *d);
///STATE
int			philo_state(t_thread_data *args, int state);

#endif
