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
	core->end = 0;
	core->num_philo = ft_atoi(argv[1]);
	core->times.time_die = ft_atoi(argv[2]);
	core->times.time_eat = ft_atoi(argv[3]);
	core->times.time_sleep = ft_atoi(argv[4]);
	core->times.num_times_eat = -1;
	if (argc == 6)
		core->times.num_times_eat = ft_atoi(argv[5]);
}

int	allocate_memory(t_core *core)
{
	core->philos = (t_philo *)malloc(sizeof(t_philo) * core->num_philo);
	if (!core->philos)
		return (0);
	core->pid = (pid_t *)malloc(sizeof(pid_t) * core->num_philo);
	if (!core->pid)
	{
		free(core->philos);
		return (0);
	}
	return (1);
}

int	init_semaphores(t_core *core)
{
	core->semaphores.sem_forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL,
		0644, core->num_philo);
	if (core->semaphores.sem_forks == SEM_FAILED)
	{
		free(core->philos);
		free(core->pid);
		return (0);
	}
	core->semaphores.sem_write = sem_open(SEM_WRITE, O_CREAT | O_EXCL,
			0644, 1);
	if (core->semaphores.sem_write == SEM_FAILED)
	{
		sem_close(core->semaphores.sem_forks);
		free(core->philos);
		free(core->pid);
		return (0);
	}
}

int	get_size_int(int n)
{
	int		i;

	i = 0;
	while (n >= 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*get_sem_name(int id)
{
	char	*name;
	char	*id_str;
	int		i;


	name = (char *)malloc(sizeof(char) * (SIZE_SEM_EAT + get_size_int(id) + 1));
	if (!name)
		return (0);
	i = 0;
	while (i < SIZE_SEM_EAT)
	{
		name[i] = SEM_EAT[i];
		i++;
	}
	id_str = ft_itoa(id);
	if (!id_str)
	{
		free(name);
		return (0);
	}
	
	
}

int	create_philos(t_core *core)
{
	int	i;

	i = -1;
	while (++i < core->num_philo)
	{
		core->philos[i].id = i + 1;
		core->philos[i].num_eat = 0;
		core->philos[i].start_time = get_time();
		core->philos[i].last_eat = get_time();
		core->philos[i].name_sem = get_sem_name(i + 1);
		core->philos[i].sem_eat = sem_open(SEM_EAT, O_CREAT | O_EXCL,
				0644, 1);
		if (core->philos[i].sem_eat == SEM_FAILED)
		{
			while (--i >= 0)
			{
				sem_close(core->philos[i].sem_eat);
				free(core->philos[i].sem_eat);
			}
			sem_close(core->semaphores.sem_write);
			sem_close(core->semaphores.sem_forks);
			free(core->philos);
			free(core->pid);
			return (0);
		}
	}
	return (1);
}

int	init_core(t_core *core, int argc, char **argv)
{
	init_args(core, argc, argv);
	if (!allocate_memory(core))
		return (0);
	if (!init_semaphores(core))
		return (0);
	if (!create_philos(core))
		return (0);
	return (1);
}
