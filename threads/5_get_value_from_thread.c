/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_get_value_from_thread.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:26:29 by shadya            #+#    #+#             */
/*   Updated: 2026/08/23 19:44:07 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void	*roll_dice(void *)
{
	int	value;
	int	*result;

	value = (rand() % 6) + 1;
	result = malloc(sizeof(int));
	*result = value;
	return ((void *) result);
}

/*
	We can actually return values from the routines passed into our thread.
	In order to do so, we need to allocate a variable and pass it to the
	main process. This method does have implications with freeing the 
	memory later, which is not ideal. In the next lesson, we will
	discover how to use thread arguments to improve this method.
*/
int	main(int argc, char **argv)
{
	pthread_t	th;
	int			*res;

	srand(time(NULL));
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return (1);
	if (pthread_join(th, (void **)&res) != 0)
		return (1);
	printf("Result: %d\n", *res);
	free(res);
	return (0);
}
