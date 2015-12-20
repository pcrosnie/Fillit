/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/05 16:42:08 by pcrosnie          #+#    #+#             */
/*   Updated: 2015/12/20 14:41:46 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

int		ft_sol_range()
{
	int nbp;
	int i;
	int range;

	range = 0;
	i = 0;
	nbp = 0;
	while (nbp < ft_count_pieces(sol_tab))
	{
		i = 0;
		while (i < 6)
		{
			if ((sol_tab[nbp][0] + sol_tab[nbp][i + 2]) > range)
				range = (sol_tab[nbp][0] + sol_tab[nbp][i + 2]);
			i++;
			if ((sol_tab[nbp][1] + sol_tab[nbp][i + 2]) > range)
				range = (sol_tab[nbp][1] + sol_tab[nbp][i + 2]);
			i++;
		}
		nbp++;
	}
	return (range + 1);
}

char	**ft_convert()
{
	char	**tmp;
	int i;
	int j;
	int srange;
	char lettre;

	i = 0;
	j = 2;
	srange = ft_sol_range();
	lettre = 'A';
	tmp = ft_newc2d(srange, srange, '.');
	i = 0;
	while (i < ft_count_pieces(sol_tab))
	{
		tmp[sol_tab[i][1]][sol_tab[i][0]] = lettre;
		j = 2;
		while (j < 8)
		{
			tmp[sol_tab[i][j + 1] + sol_tab[i][1]]
				[sol_tab[i][j] + sol_tab[i][0]] = lettre;
			j += 2;
		}
		i++;
		lettre++;
	}
	return (tmp);
}

void	ft_display(char **tab)
{
	int i;
	int j;
	int		srange;

	i = 0;
	j = 0;
	srange = ft_sol_range();
	while (i < srange)
	{
		while (j < srange)
		{
			ft_putchar(tab[i][j]);
			j++;
		}
		ft_putchar('\n');
		j = 0;
		i++;
	}
	exit(0);
}

void	ft_parkour(t_noeud *tree, int i)
{
	if (tree->etape == ft_count_pieces(ref_tab))
	{
		if ((ft_check_sol(tree) == 0) && sol_tab == NULL)
		{
			ft_fill_sol_tab(tree);
		}
		else if (ft_check_sol(tree) == 1)
		{
			ft_fill_sol_tab(tree);
			ft_display(ft_convert());
		}
	}
	else
		ft_fill_next(tree, ft_search_range(ft_count_pieces(ref_tab)));
	while (tree->next[i])
	{
		ft_parkour(tree->next[i], 0);
		i++;
	}
	ft_display(ft_convert());
}

int		main(int argc, char **argv)
{
	int fd;
	t_noeud *tree;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		ref_tab = ft_get_tetriminos(fd);
		if (ref_tab)
		{
			tree = ft_def_start_possible_position();
			ft_parkour(tree, 0);
		}
	}
	else
		write(1, "error", 5);
	return (0);
}
