/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:29:08 by tjarross          #+#    #+#             */
/*   Updated: 2024/10/19 14:50:29 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "world.h"
#include "parsing.h"

void	print_parsing(t_world world);

int	main(int argc, char **argv)
{
	t_world	world;
	int		parsing_ret;

	if (argc != 2)
		return (printf("Error\nProgram take only one argument\n"),
			EXIT_FAILURE);
	parsing_ret = parse_rt(argv[1], &world);
	if (parsing_ret != 0)
		return (EXIT_FAILURE);
	print_parsing(world);
	return (EXIT_SUCCESS);
}
