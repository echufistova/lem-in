/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:33:27 by ychufist          #+#    #+#             */
/*   Updated: 2018/12/18 14:33:30 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "libft/ft_printf.h"

typedef struct 		s_point
{
	int x;
	int y;
}					t_point;

typedef struct		s_room
{
	char		*name;
	t_point		coord;
	char		**links;
	int         links_amount;
	int         level;
	int         flag;
}					t_room;

typedef struct		s_farm
{
	int				ants_amount;
	int             room_amount;
	int             flag;
	int             start_room_id;
	int             end_room_id;
	t_room			*rooms;
}					t_farm;

typedef struct      s_list_room
{
    char		*name;
    t_point		coord;
    char		**links;
    int         links_amount;
    int         level;
    int         flag;
}                   t_list_room;

void add_room(t_farm *farm);
void add_link(t_farm *farm, char *line, int i);
int is_room(t_farm farm, char *name);

#endif