/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_range.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 15:06:27 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/01/08 18:35:30 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				ft_check_limits(int *tab, int n)
{
	n = n - 1;
	if ((tab[0] + tab[2] > n) || (tab[1] + tab[3] > n))
		return (0);
	if ((tab[0] + tab[2] < 0) || (tab[1] + tab[3] < 0))
		return (0);
	if ((tab[0] + tab[4] > n) || (tab[1] + tab[5] > n))
		return (0);
	if ((tab[0] + tab[4] < 0) || (tab[1] + tab[5] < 0))
		return (0);
	if ((tab[0] + tab[6] > n) || (tab[1] + tab[7] > n))
		return (0);
	if ((tab[0] + tab[6] < 0) || (tab[1] + tab[7] < 0))
		return (0);
	return (1);
}

int				ft_check_overlap(int *tmp, t_noeud *ptr)
{
	t_noeud *ptr2;

	ptr2 = ptr;
	if (ptr->coord_piece[0] == 100)
		return (1);
	while (ptr2 != NULL)
	{
		if (ft_strintstr(tmp, ptr2->coord_piece) == 0)
			return (0);
		ptr2 = ptr2->prev;
	}
	return (1);
}

struct s_noeud	*ft_fill_next_ptr(int *tmp, int nb, t_noeud *adr)
{
	t_noeud	*ptr;

	ptr = (t_noeud *)malloc(sizeof(t_noeud));
	ptr->coord_piece = ft_intstrcpy(tmp);
	ptr->etape = nb + 1;
	ptr->next = (t_noeud **)malloc(sizeof(t_noeud *) * 121);
	ptr->prev = adr;
	return (ptr);
}

void			ft_fill_next(t_noeud *ptr, int nb)
{
	int		i;
	int		j;
	int		index;
	int		*tmp;

	i = 0;
	index = 0;
	tmp = ft_intstrcpy(g_ref_tab[ptr->etape]);
	while (i < nb)
	{
		j = 0;
		tmp[0] = 0;
		while (j < nb)
		{
			if (ft_check_limits(tmp, nb) == 1 && ft_check_overlap(tmp, ptr)
					== 1)
				ptr->next[index++] = ft_fill_next_ptr(tmp, ptr->etape, ptr);
			j++;
			tmp[0]++;
		}
		i++;
		tmp[1]++;
	}
	ptr->next[index] = NULL;
}

t_noeud			*ft_def_start_possible_position(void)
{
	t_noeud	*ptr;
	int		i;
	int		nb;

	i = 0;
	nb = g_info[1];
	ptr = (t_noeud *)malloc(sizeof(t_noeud));
	ptr->etape = 0;
	ptr->coord_piece = (int *)malloc(sizeof(int) * 8);
	ptr->coord_piece[0] = 100;
	ptr->next = (t_noeud **)malloc(sizeof(t_noeud *) * nb * nb);
	ft_fill_next(ptr, nb);
	ptr->prev = NULL;
	return (ptr);
}
