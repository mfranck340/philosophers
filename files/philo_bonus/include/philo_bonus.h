/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:26:42 by ffierro-          #+#    #+#             */
/*   Updated: 2025/04/27 18:38:41 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/* ============================= SYSTEM HEADERS ============================= */
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <semaphore.h>

/* ============================ PROJECT HEADERS ============================= */
# define SEM_FORKS	"/sem_philo_forks"
# define SEM_WRITE	"/sem_philo_write"
# define SEM_DEAD	"/sem_philo_dead"
# define SEM_EAT	"/sem_philo_eat_"
# define SIZE_SEM_EAT 15

/* =============================== STRUCTURES =============================== */

typedef struct s_philo	t_philo;

typedef struct s_times
{
	long	time_die;
	int		time_eat;
	int		time_sleep;
	int		num_times_eat;
}	t_times;

typedef struct s_sem_philo
{
	sem_t	*sem_forks;
	sem_t	*sem_write;
	sem_t	*sem_dead;
}	t_sem_philo;

typedef struct s_core
{
	int				end;
	int				num_philo;
	pid_t			*pid;
	long long		start_time;
	t_philo			*philos;
	t_times			times;
	t_sem_philo		semaphores;
}	t_core;

typedef struct s_philo
{
	int				id;
	int				num_eat;
	long long		last_eat;
	char			*name_sem;
	sem_t			*sem_eat;
	t_core			*core;
}	t_philo;

/* =============================== PROTOTYPES =============================== */
// File: checks_bonus.c
int			check_args(int argc, char **argv);

// File: init_bonus.c
int			init_core(t_core *core, int argc, char **argv);

// File: clear_bonus.c
void		free_mem_core(t_core *core);
void		clear_semaphore(t_core *core, int flag);
void		clear_memory(t_core *core, int num_philo, int flag);

// File: utils_str_bonus.c
char		*get_sem_name(int id);
int			ft_atoi(const char *nptr);

// File: utils_bonus.c
long long	get_time(void);
void		ft_usleep(unsigned long time);
void		print_status(t_philo *philo, char *status);

// File: simulation_bonus.c
void		start_meal(t_core *core);

// File: philo_routine_bonus.c
void		philo_routine(t_philo *philo);

#endif
