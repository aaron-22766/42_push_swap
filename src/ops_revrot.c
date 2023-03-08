/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_reverse_rotate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:54:46 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/07 10:54:53 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_rra(t_push_swap *data)
{
	ft_rotate(data->a, 1);
	ft_printf("rra\n");
}

void	ft_rrb(t_push_swap *data)
{
	ft_rotate(data->b, 1);
	ft_printf("rrb\n");
}

void	ft_rrr(t_push_swap *data)
{
	ft_rotate(data->a, 1);
	ft_rotate(data->b, 1);
	ft_printf("rrr\n");
}
