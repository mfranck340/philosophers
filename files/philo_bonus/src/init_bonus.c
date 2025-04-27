/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:34:45 by ffierro-          #+#    #+#             */
/*   Updated: 2025/04/27 18:56:50 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	init_args(t_core *core, int argc, char **argv)
{
	core->end = 0;
	core->num_philo = ft_atoi(argv[1]);
	core->start_time = get_time();
	core->times.time_die = ft_atoi(argv[2]);
	core->times.time_eat = ft_atoi(argv[3]);
	core->times.time_sleep = ft_atoi(argv[4]);
	core->times.num_times_eat = -1;
	if (argc == 6)
		core->times.num_times_eat = ft_atoi(argv[5]);
}

static int	allocate_memory(t_core *core)
{
	core->philos = (t_philo *)malloc(sizeof(t_philo) * core->num_philo);
	if (!core->philos)
		return (0);
	core->pid = (pid_t *)malloc(sizeof(pid_t) * core->num_philo);
	if (!core->pid)
	{
		free_mem_core(core);
		return (0);
	}
	return (1);
}

static int	init_semaphores(t_core *core)
{
	core->semaphores.sem_forks = sem_open(SEM_FORKS, O_CREAT,
			0644, core->num_philo);
	if (core->semaphores.sem_forks == SEM_FAILED)
	{
		perror("sem_open");
		free_mem_core(core);
		return (0);
	}
	core->semaphores.sem_write = sem_open(SEM_WRITE, O_CREAT,
			0644, 1);
	if (core->semaphores.sem_write == SEM_FAILED)
	{
		clear_semaphore(core, 1);
		free_mem_core(core);
		return (0);
	}
	core->semaphores.sem_dead = sem_open(SEM_DEAD, O_CREAT,
			0644, 0);
	if (core->semaphores.sem_dead == SEM_FAILED)
	{
		clear_semaphore(core, 1);
		free_mem_core(core);
		return (0);
	}
	return (1);
}

static int	create_philos(t_core *core)
{
	int	i;

	i = -1;
	while (++i < core->num_philo)
	{
		core->philos[i].id = i + 1;
		core->philos[i].num_eat = 0;
		core->philos[i].last_eat = get_time();
		core->philos[i].name_sem = get_sem_name(i + 1);
		if (!core->philos[i].name_sem)
			return (clear_memory(core, i, 1), 0);
		sem_unlink(core->philos[i].name_sem);
		core->philos[i].sem_eat = sem_open(core->philos[i].name_sem,
				O_CREAT, 0644, 1);
		if (core->philos[i].sem_eat == SEM_FAILED)
		{
			free(core->philos[i].name_sem);
			clear_memory(core, i, 1);
			return (0);
		}
		core->philos[i].core = core;
	}
	return (1);
}

int	init_core(t_core *core, int argc, char **argv)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DEAD);
	init_args(core, argc, argv);
	if (!allocate_memory(core))
		return (0);
	if (!init_semaphores(core))
		return (0);
	if (!create_philos(core))
		return (0);
	return (1);
}
