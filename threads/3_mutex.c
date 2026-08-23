/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_mutex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 18:51:28 by shadya            #+#    #+#             */
/*   Updated: 2026/08/23 19:09:01 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <unistd.h>

int				mails = 0;
pthread_mutex_t mutex;

void	*routine(void *)
{
	int	i;

	i = 0;
	while (i < 100000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
}

/*
	To fix the issue with race condtions, we can add a mutex by using the functions
	pthread_mutex_init() and pthread_mutex_destroy() inside the main process.
	Then, inside the threads we can use a lock with pthread_mutex_lock(&mutex) and
	unlock it pthread_mutex_unlock(&mutex).
	Notice how only the shared variable mails needs a mutex lock, since the issue
	is caused by multiple threads trying to access the same shared data but failing.
	Mutex are slow and heavy so we should only use them if necessary.
*/
int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_join(t1, NULL) != 0)
		return (1);
	if (pthread_join(t2, NULL) != 0)
		return (1);
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}
