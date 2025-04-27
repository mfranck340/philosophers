/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:39:40 by ffierro-          #+#    #+#             */
/*   Updated: 2025/04/27 18:57:33 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(unsigned long time)
{
	unsigned long	start;
	unsigned long	current;

	start = get_time();
	current = start;
	while (current - start < time)
	{
		usleep(100);
		current = get_time();
	}
}

void	print_status(t_philo *philo, char *status)
{
	unsigned long	time;

	sem_wait(philo->core->semaphores.sem_write);
	time = get_time() - philo->core->start_time;
	printf("[%lu]\t%d %s\n", time, philo->id, status);
	sem_post(philo->core->semaphores.sem_write);
}
