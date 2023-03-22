/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:35:32 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/22 10:34:00 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_free_split(t_ps *data)
{
	int	i;

	i = 0;
	while (data->split && data->split[i])
		free(data->split[i++]);
	free(data->split);
	data->split = 0;
}

void	ft_free_data(t_ps *data)
{
	if (!data)
		return ;
	ft_free_split(data);
	free(data->ops);
	free(data->a->values);
	free(data->a);
	free(data->b->values);
	free(data->b);
	free(data);
	data = 0;
}

void	ft_exit(t_ps *data, int error)
{
	ft_free_data(data);
	if (error)
		ft_putstr_fd("Error\n", STDERR_FILENO);
	// system("leaks push_swap");
	exit(!!error);
}
