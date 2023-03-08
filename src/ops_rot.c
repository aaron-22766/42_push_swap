/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:53:28 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/07 10:53:58 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_ra(t_push_swap *data)
{
	ft_rotate(data->a, 0);
	ft_printf("ra\n");
}

void	ft_rb(t_push_swap *data)
{
	ft_rotate(data->b, 0);
	ft_printf("rb\n");
}

void	ft_rr(t_push_swap *data)
{
	ft_rotate(data->a, 0);
	ft_rotate(data->b, 0);
	ft_printf("rr\n");
}
