/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:26:42 by ffierro-          #+#    #+#             */
/*   Updated: 2025/02/09 00:26:44 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_times
{
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		num_times_eat;
}	t_times;

typedef struct s_mtx
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*lock_write;
	pthread_mutex_t	*lock_eat;
}	t_mtx;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	unsigned long	last_eat;
	unsigned long	start_time;
	int				num_eat;
	t_mtx			locks;
	t_times			*times;
}	t_philo;

typedef struct s_core
{
	int				num_philo;
	t_times			times;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*locks_eat;
	pthread_mutex_t	lock_write;
}	t_core;

void			start_meal(t_core *core);
int				ft_atoi(const char *nptr);
int				init_core(t_core *core, int argc, char **argv);
int				clean_core(t_core *core, int limit);
int				free_memory(t_core *core);
unsigned long	get_time(void);
void			ft_usleep(unsigned long time);
void			print_status(t_philo *philo, char *status);
int				check_args(int argc, char **argv);

#endif
