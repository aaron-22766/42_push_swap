/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:47:46 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/07 10:53:25 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sa(t_push_swap *data)
{
	ft_swap(data->a);
	ft_printf("sa\n");
}

void	ft_sb(t_push_swap *data)
{
	ft_swap(data->b);
	ft_printf("sb\n");
}

void	ft_ss(t_push_swap *data)
{
	ft_swap(data->a);
	ft_swap(data->b);
	ft_printf("ss\n");
}

void	ft_pa(t_push_swap *data)
{
	ft_push(data->b, data->a);
	ft_printf("pa\n");
}

void	ft_pb(t_push_swap *data)
{
	ft_push(data->a, data->b);
	ft_printf("pb\n");
}
