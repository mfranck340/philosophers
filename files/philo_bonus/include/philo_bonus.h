/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:26:42 by ffierro-          #+#    #+#             */
/*   Updated: 2025/02/09 00:26:44 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ============================= SYSTEM HEADERS ============================= */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

/* ============================ PROJECT HEADERS ============================= */
# define SEM_FORKS	"/sem_philo_forks"
# define SEM_WRITE	"/sem_philo_write"
# define SEM_EAT	"/sem_philo_eat_"
# define SIZE_SEM_EAT 15

/* =============================== STRUCTURES =============================== */
typedef struct s_times
{
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		num_times_eat;
}	t_times;

typedef struct s_philo
{
	int				id;
	int				num_eat;
	unsigned long	last_eat;
	unsigned long	start_time;
	char			*name_sem;
	sem_t			*sem_eat;
}	t_philo;

typedef struct s_semphilo
{
	sem_t	*sem_forks;
	sem_t	*sem_write;
}	t_semphilo;

typedef struct s_core
{
	int			end;
	int			num_philo;
	pid_t		*pid;
	t_times		times;
	t_philo		*philos;
	t_semphilo	semaphores;
}	t_core;

/* =============================== PROTOTYPES =============================== */
// File: checks.c
int	check_args(int argc, char **argv);

// File: init.c
int	init_core(t_core *core, int argc, char **argv);

#endif
