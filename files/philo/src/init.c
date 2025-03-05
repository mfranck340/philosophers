/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:34:45 by ffierro-          #+#    #+#             */
/*   Updated: 2025/02/09 00:34:47 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_args(t_core *core, int argc, char **argv)
{
	core->num_philo = ft_atoi(argv[1]);
	core->times.time_die = ft_atoi(argv[2]);
	core->times.time_eat = ft_atoi(argv[3]);
	core->times.time_sleep = ft_atoi(argv[4]);
	core->times.num_times_eat = -1;
	core->times.end = 0;
	if (argc == 6)
		core->times.num_times_eat = ft_atoi(argv[5]);
}

int	allocate_memory(t_core *core)
{
	core->philos = (t_philo *)malloc(sizeof(t_philo) * core->num_philo);
	if (!core->philos)
		return (0);
	core->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* core->num_philo);
	if (!core->forks)
	{
		free(core->philos);
		return (0);
	}
	core->locks_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* core->num_philo);
	if (!core->locks_eat)
	{
		free(core->philos);
		free(core->forks);
		return (0);
	}
	return (1);
}

int	create_philos(t_core *core)
{
	int	i;

	i = -1;
	while (++i < core->num_philo)
	{
		core->philos[i].id = i + 1;
		core->philos[i].times = &core->times;
		core->philos[i].num_eat = 0;
		core->philos[i].start_time = get_time();
		core->philos[i].last_eat = get_time();
		core->philos[i].locks.left_fork = &core->forks[i];
		core->philos[i].locks.right_fork = &core->forks[(i + 1)
			% core->num_philo];
		core->philos[i].locks.lock_write = &core->lock_write;
		core->philos[i].locks.lock_eat = &core->locks_eat[i];
		if (pthread_mutex_init(&core->forks[i], NULL) != 0)
			return (clean_core(core, i));
		if (pthread_mutex_init(&core->locks_eat[i], NULL) != 0)
		{
			pthread_mutex_destroy(&core->forks[i]);
			return (clean_core(core, i));
		}
	}
	return (1);
}

int	init_core(t_core *core, int argc, char **argv)
{
	init_args(core, argc, argv);
	if (!allocate_memory(core))
		return (0);
	if (pthread_mutex_init(&core->lock_write, NULL) != 0)
		return (free_memory(core));
	if (!create_philos(core))
		return (0);
	return (1);
}
