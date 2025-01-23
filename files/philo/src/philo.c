


#include "../include/philo.h"

int ft_error()
{
	printf("Usage:\t./philo number_of_philosophers time_to_die time_to_eat\n");
	printf("\ttime_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (1);
}

int main(int argc, char **argv)
{
	t_philo	*philo;
	
	if (argc != 5 && argc != 6)
		return (ft_error());
	return (0);
}