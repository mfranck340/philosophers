/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:26:20 by ffierro-          #+#    #+#             */
/*   Updated: 2025/02/09 00:26:22 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_error_usage(void)
{
	printf(
		"Usage: ./philo\t[INT] <number_of_philosophers>\n"
		"\t\t[INT] <time_to_die>\n"
		"\t\t[INT] <time_to_eat>\n"
		"\t\t[INT] <time_to_sleep>\n"
		"\t\t[INT] (OPTIONAL) <times_each_philosopher_must_eat>\n"
		);
	return (1);
}

int	free_memory(t_core *core)
{
	free(core->philos);
	free(core->forks);
	free(core->locks_eat);
	return (0);
}

int	clean_core(t_core *core, int limit)
{
	while (--limit >= 0)
	{
		pthread_mutex_destroy(&core->forks[limit]);
		pthread_mutex_destroy(&core->locks_eat[limit]);
	}
	pthread_mutex_destroy(&core->lock_write);
	return (free_memory(core));
}

int	main(int argc, char **argv)
{
	t_core	core;

	if (!check_args(argc, argv))
		return (ft_error_usage());
	if (!init_core(&core, argc, argv))
		return (1);
	start_meal(&core);
	clean_core(&core, core.num_philo);
	return (0);
}
