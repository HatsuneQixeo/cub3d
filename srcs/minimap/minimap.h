/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIMAP_H
# define MINIMAP_H

# include "image.h"
# include "cubmap.h"

enum e_minimap_size
{
	MapCellSize = 32,
	MinimapCell = 7,
	MinimapSize = MapCellSize * MinimapCell
};

enum e_layer_index
{
	LayerPlayer,
	LayerRay,
	LayerInteract,
	LayerDoor,
	LayerMap,
	layer_count
};

typedef t_image	t_map_layers[layer_count];

/*
	Why isn't there a t_pointrange instead of this in case you wonder?
	This project is messy enough,
	and I feel really discouraged to add any more files.
*/
typedef struct s_minimapdata
{
	t_point	begin;
	t_point	player_pos;
	t_point	end;
}			t_minimapdata;

t_point	map_scale_point(t_point point);
void	map_draw_tile(t_image *map, t_colour colour, t_point pos);

void	map_layer_player(t_image *layer, t_point dir, t_minimapdata data);
void	map_layer_door(t_image *layer, t_door **arr_door, t_minimapdata data);
void	map_layer_interact(t_image *layer, t_point target, t_minimapdata data);

#endif
