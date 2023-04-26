/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:35:32 by arabenst          #+#    #+#             */
/*   Updated: 2023/04/26 12:43:21 by arabenst         ###   ########.fr       */
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

void	ft_free_stack(t_stack *stack)
{
	if (stack)
		free(stack->values);
	free(stack);
}

void	ft_exit(t_ps *data, bool error)
{
	ft_free_split(data);
	free(data->ops);
	ft_free_stack(data->a);
	ft_free_stack(data->b);
	free(data);
	if (error)
		ft_putendl_fd("Error", STDERR_FILENO);
	exit(error);
}
