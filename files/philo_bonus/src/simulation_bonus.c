/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:39:21 by ffierro-          #+#    #+#             */
/*   Updated: 2025/04/27 18:57:24 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*start_monitor(void *data)
{
	t_core	*core;
	int		i;

	core = (t_core *)data;
	sem_wait(core->semaphores.sem_dead);
	i = -1;
	while (++i < core->num_philo)
		kill(core->pid[i], SIGKILL);
	return (0);
}

void	wait_all(t_core *core, pthread_t thread_id)
{
	int		i;

	i = -1;
	while (++i < core->num_philo)
	{
		waitpid(core->pid[i], NULL, 0);
	}
	sem_post(core->semaphores.sem_dead);
	if (pthread_join(thread_id, NULL) != 0)
		return ;
}

void	start_meal(t_core *core)
{
	int			i;
	pid_t		pid;
	pthread_t	thread_id;

	if (pthread_create(&thread_id, NULL, &start_monitor, core) != 0)
		return ;
	i = -1;
	while (++i < core->num_philo)
	{
		pid = fork();
		if (pid == -1)
		{
			pthread_detach(thread_id);
			while (--i >= 0)
				kill(core->pid[i], SIGKILL);
			return ;
		}
		if (pid == 0)
			philo_routine(&core->philos[i]);
		else
			core->pid[i] = pid;
		usleep(10);
	}
	wait_all(core, thread_id);
}
