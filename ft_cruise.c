/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cruise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 11:56:51 by pcrosnie          #+#    #+#             */
/*   Updated: 2015/12/17 15:12:19 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_fill_sol_tab(t_noeud *ptr)
{
	int	i;

	i = ft_count_pieces(ref_tab);
	sol_tab = (int **)malloc(sizeof(int *) * i);
	while (i > 0)
	{
		sol_tab[i] = (int *)malloc(sizeof(int) * 8);
		sol_tab[i--] = ptr->coord_piece;
		ptr = ptr->prev;
	}
	sol_tab[ft_count_pieces(ref_tab) + 1] = NULL;
}

int		*ft_set_tab_vertical(int n)
{
	int *tab;
	int i;
	int j;

	i = 2;
	j = 1;
	tab = (int *)malloc(sizeof(int) * (n * 2));
	tab[0] = n - 1;
	tab[1] = 0;
	while (i < (n * 2))
	{
		tab[i] = 0;
		tab[i + 1] = j++;
		i += 2;
	}
	return (tab);
}

int		*ft_set_horizontal(int n)
{
	int	*tab;
	int i;
	int j;

	i = 2;
	j = 1;
	tab = (int *)malloc(sizeof(int) * (n * 2));
	tab[0] = 0;
	tab[1] = n - 1;
	while (i < (n * 2))
	{
		tab[i] = j++;
		tab[i + 1] = 0;
		i += 2;
	}
	return (tab);
}

int		ft_check_for_range_max(int *tab, int *str, int n)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (i < n)
	{
		j = 0;
		while (j < 8)
		{
			if (tab[i] == str[j] && tab[i + 1] == str[j + 1])
				return (0);
			j += 2;
		}
		i += 2;
	}
	return (1);
}

int		ft_check_sol(t_noeud *ptr)
{
	int		n;
	int 	*Vert_tab;
	int		*Hor_tab;

	n = ft_search_range(ft_count_pieces(ref_tab));
	Vert_tab = ft_set_tab_vertical(n);
	Hor_tab = ft_set_horizontal(n);
	while (ptr != NULL)
	{
		if (ft_check_for_range_max(Vert_tab, ptr->coord_piece) == 1
				|| ft_check_for_range_max(Hor_tab, ptr->piece) == 1)
			return (0);
		ptr = ptr->prev;
	}
	return (1);
}