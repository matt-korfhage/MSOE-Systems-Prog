/*
 * Copyright (C) 2020 Esteban López Rodríguez <gnu_stallman@protonmail.ch>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef FIELD_H
#define FIELD_H

#include <stdlib.h>
#include <time.h>

typedef int coord_t;
typedef enum
{
	EMPTY,
	SNAKE,
	HEAD,
	HEAD2,
	FOOD,
	BORDER,
	OBSTACLE,
	SHORTENER,
	DECELERATOR,
	EXTRA_POINTS,
} cell_t;

typedef struct temp_item_s
{
	coord_t y, x;
	time_t scheduled_destruction;
	struct temp_item_s *next;
} temp_item_t;

typedef temp_item_t* temp_item_list_t;

typedef struct
{
	int width, height;
	cell_t **matrix;  /* [height][width] */
	temp_item_list_t til;
} field_t;


/*
 * Initialize a field with empty (incl. borders) matrix
 */
field_t*
init_field(int height, int width, int permill_obstacles);

/*
 * Changes the ubication of the obstacles to a new one
 */
void
change_obstacles(field_t *field);

/*
 * Add a random cell with food into the matrix. Return 0 if there wasn't
 * space for it. Return 1 in success
 */
int
add_food(field_t *field);

/*
 * Add a random cell with "type" into the matrix. Return 0 if there wasn't
 * space for it. Return 1 in success
 */
int
add_temp_item(field_t *field, cell_t type, time_t duration);

/*
 * Add extra_seconds to all the temporal items in the map
 */
void
prolong_temp_items(field_t *field, time_t extra_seconds);

/*
 * Take away expired items from the map
 */
void
remove_expired_items(field_t *field);

/*
 * Deallocate field
 */
void
delete_field(field_t *field);

#endif /* FIELD_H */
