/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:47:43 by ffierro-          #+#    #+#             */
/*   Updated: 2025/04/27 18:56:42 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	free_mem_core(t_core *core)
{
	if (core->philos)
		free(core->philos);
	if (core->pid)
		free(core->pid);
}

void	clear_semaphore(t_core *core, int flag)
{
	if (core->semaphores.sem_forks)
	{
		sem_close(core->semaphores.sem_forks);
		if (flag == 1)
			sem_unlink(SEM_FORKS);
	}
	if (core->semaphores.sem_write)
	{
		sem_close(core->semaphores.sem_write);
		if (flag == 1)
			sem_unlink(SEM_WRITE);
	}
	if (core->semaphores.sem_dead)
	{
		sem_close(core->semaphores.sem_dead);
		if (flag == 1)
			sem_unlink(SEM_DEAD);
	}
}

static void	clear_philo_semaphores(t_core *core, int num_philo, int flag)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		if (core->philos[i].sem_eat)
		{
			sem_close(core->philos[i].sem_eat);
			if (flag == 1)
				sem_unlink(core->philos[i].name_sem);
			free(core->philos[i].name_sem);
		}
		i++;
	}
}

void	clear_memory(t_core *core, int num_philo, int flag)
{
	clear_philo_semaphores(core, num_philo, flag);
	clear_semaphore(core, flag);
	free_mem_core(core);
}
