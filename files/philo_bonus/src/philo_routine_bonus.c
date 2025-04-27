/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:53:39 by ffierro-          #+#    #+#             */
/*   Updated: 2025/04/27 18:57:14 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	*check_status(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		sem_wait(philo->sem_eat);
		if (philo->core->times.num_times_eat != -1
			&& philo->num_eat >= philo->core->times.num_times_eat)
		{
			sem_post(philo->sem_eat);
			break ;
		}
		if (get_time() - philo->last_eat >= philo->core->times.time_die)
		{
			sem_wait(philo->core->semaphores.sem_write);
			printf("[%llu]\t%d died\n", get_time() - philo->core->start_time,
				philo->id);
			sem_post(philo->core->semaphores.sem_dead);
			sem_post(philo->sem_eat);
			break ;
		}
		sem_post(philo->sem_eat);
		usleep(5000);
	}
	return (0);
}

static void	do_routine(t_philo *philo)
{
	sem_wait(philo->core->semaphores.sem_forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->core->semaphores.sem_forks);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	sem_wait(philo->sem_eat);
	philo->last_eat = get_time();
	philo->num_eat++;
	sem_post(philo->sem_eat);
	usleep(philo->core->times.time_eat * 1000);
	sem_post(philo->core->semaphores.sem_forks);
	sem_post(philo->core->semaphores.sem_forks);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	thread_id;

	philo->last_eat = get_time();
	if (pthread_create(&thread_id, NULL, &check_status, philo) != 0)
	{
		clear_memory(philo->core, philo->core->num_philo, 0);
		return ;
	}
	while (1)
	{
		if (philo->id % 2 != 0)
			usleep(100);
		do_routine(philo);
		if (philo->core->times.num_times_eat != -1
			&& philo->num_eat >= philo->core->times.num_times_eat)
		{
			pthread_join(thread_id, NULL);
			clear_memory(philo->core, philo->core->num_philo, 0);
			exit(0);
		}
		print_status(philo, "is sleeping");
		usleep(philo->core->times.time_sleep * 1000);
		print_status(philo, "is thinking");
	}
}
