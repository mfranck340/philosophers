/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:25:57 by ffierro-          #+#    #+#             */
/*   Updated: 2025/02/09 00:25:59 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb * sign);
}

unsigned long	get_time(void)
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

int	print_status(t_philo *philo, char *status)
{
	unsigned long	time;

	pthread_mutex_lock(philo->locks.lock_write);
	if (philo->times->end)
	{
		pthread_mutex_unlock(philo->locks.lock_write);
		return (0);
	}
	time = get_time() - philo->start_time;
	printf("%lu %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(philo->locks.lock_write);
	return (1);
}
