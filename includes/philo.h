/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:34:45 by Owen          #+#    #+#                 */
/*   Updated: 2023/06/17 15:44:29 by Owen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

/*Defines to make error messages easier and more readable. 
ERR = error I = input D = data*/
# define ERR_FND	"Error occured."
# define ERR_I_N	"Input incorrect, please use only numbers."
# define ERR_I_NN	"Input incorrect, please use positive numbers."
# define ERR_I_M	"Input incorrect. please use a value lower than max int."
# define ERR_I_C	"Input incorrect, please enter 4 or 5 digits."
# define ERR_M		"Initialization of mutex failed. Please try again."
# define ERR_D_NP	"Invalid amount of philosophers. At least one is needed."
# define ERR_D_DT	"Invalid time to die. Philosophers deserve at least 1ms\
 of life."
# define ERR_D_ET	"Invalid time to eat. Philosophers deserve at least 1ms\
 to eat."
# define ERR_D_ST	"Invalid time to sleep. Philosophers deserve at least 1\
ms to sleep."
# define ERR_D_MQ	"While 0 meals is valid, the simulation will end as\
 soon as it starts."
# define ERR_T_FND	"An issue occured during creation of the required \
threads."
# define ERR_T_F	"Failure occured during pthread_create. Please try again."
# define FIN		"Simulation succesful. All Philosophers are satisfied"

typedef struct s_philo	t_philo;

/*This struct contains all general data,
consisting of user input and other important metrics.*/
typedef struct s_data
{
	size_t			philo_nbr;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				meals_req;
	time_t			starttime;
	bool			stop;
	t_philo			*start;
	pthread_t		grim_reaper;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead;

}			t_data;

/*This struct contains all the information
necessary for a philosopher to function*/
typedef struct s_philo
{
	t_data			*data;
	size_t			tag;
	bool			finish;
	unsigned int	times_eaten;
	time_t			last_dinner;
	pthread_t		thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*meal_lock;
	struct s_philo	*prev;
	struct s_philo	*next;
}			t_philo;

typedef enum e_status
{
	DEATH = 0,
	EAT,
	SLEEP,
	THINK,
	FORK,
	FINISHED,
}	t_status;

/*Functions*/
/*Utils*/
int			ft_strlen(char *str);
int			ft_philoatoi(const char *str, int tmp);
t_philo		*search_first(t_philo *list);

/*Input_check*/
int			input_checker(int ac, char **av);
int			value_checker(t_data *data, int ac);

/*Cleanup*/
int			free_all(t_data *data, t_philo *philo, pthread_t *threads);
int			thread_error(t_data *d, pthread_t *t, size_t num);

/*Initialize*/
bool		init_mutex(t_data *data, t_philo *philo);
t_philo		*spawn_philos(t_data *data);
t_data		*init_data(char **av);
t_philo		*init_philo(t_data *data, size_t count);

/*Printing*/
int			err(char *str);
void		print_status(t_philo *philo, bool death, t_status status);

/*Eat_sleep_think*/
void		drop_forks(t_philo *philo);
void		think_time(t_data *data, t_philo *philo, bool start);
void		eat_sleep(t_data *data, t_philo *philo);

/*Symposium*/
bool		start_session(t_data *data);

/*Grim reaper*/
void		set_finish(t_data *data, int status);
bool		check_status(t_data *data);
bool		is_finished(t_data *data);
void		*grim_reaper(void *arg);

/*Threads*/
pthread_t	join_threads(pthread_t *threads, size_t amount);
pthread_t	*create_threads(t_data *data);

/*Time*/
time_t		get_current_time(void);
void		delay_start(t_data *data);
void		c_sleep(t_data *data, size_t sleeptime);

#endif