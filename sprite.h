
#ifndef SPRITE_H
#define SPRITE_H
#include "cubstruct.h"
#include "cub3d.h"

void add_sprite(t_sprite **sprites_list, int i, int j);
void saw_sprite(t_sprite *list, int i, int j);
void draw_sprite(t_game *game);

#endif
