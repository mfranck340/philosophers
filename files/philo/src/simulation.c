/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:12:31 by ffierro-          #+#    #+#             */
/*   Updated: 2025/02/10 15:12:36 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	do_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->locks.left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->locks.right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->locks.lock_eat);
	philo->last_eat = get_time();
	philo->num_eat++;
	pthread_mutex_unlock(philo->locks.lock_eat);
	ft_usleep(philo->times->time_eat);
	pthread_mutex_unlock(philo->locks.left_fork);
	pthread_mutex_unlock(philo->locks.right_fork);
	print_status(philo, "is sleeping");
	ft_usleep(philo->times->time_sleep);
	print_status(philo, "is thinking");
}

void	*start_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	pthread_mutex_lock(philo->locks.lock_eat);
	philo->start_time = get_time();
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->locks.lock_eat);
	while (1)
		do_routine(philo);
	return (0);
}

int	all_eat(t_core *core)
{
	int	i;
	int	count;

	if (core->times.num_times_eat == -1)
		return (0);
	i = -1;
	count = 0;
	while (++i < core->num_philo)
	{
		pthread_mutex_lock(core->philos[i].locks.lock_eat);
		if (core->philos[i].num_eat >= core->times.num_times_eat)
			count++;
		pthread_mutex_unlock(core->philos[i].locks.lock_eat);
	}
	if (count == core->num_philo)
	{
		pthread_mutex_lock(core->philos[0].locks.lock_write);
		return (1);
	}
	return (0);
}

void	*start_monitor(void *data)
{
	int		i;
	t_core	*core;

	core = (t_core *)data;
	while (1)
	{
		i = -1;
		while (++i < core->num_philo)
		{
			pthread_mutex_lock(core->philos[i].locks.lock_eat);
			if (get_time() - (unsigned long)core->philos[i].last_eat
				> (unsigned long)core->philos[i].times->time_die)
			{
				pthread_mutex_unlock(core->philos[i].locks.lock_eat);
				pthread_mutex_lock(core->philos[i].locks.lock_write);
				printf("[%lu]\t%d died\n", get_time() - core->philos[i].start_time,
					core->philos[i].id);
				return (0);
			}
			pthread_mutex_unlock(core->philos[i].locks.lock_eat);
		}
		if (all_eat(core))
			return (0);
	}
}

void	start_meal(t_core *core)
{
	int			i;
	pthread_t	thread_id;

	if (pthread_create(&thread_id, NULL, &start_monitor, core) != 0)
		return ;
	i = -1;
	while (++i < core->num_philo)
	{
		if (pthread_create(&core->philos[i].thread_id, NULL, &start_routine,
				&core->philos[i]) != 0)
			return ;
		usleep(1);
	}
	if (pthread_join(thread_id, NULL) != 0)
		return ;
	i = -1;
	while (++i < core->num_philo)
	{
		if (pthread_detach(core->philos[i].thread_id) != 0)
			return ;
	}
}
