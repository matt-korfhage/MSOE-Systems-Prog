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

#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

typedef struct arguments_s
{
	/* Value -1 means no specified */
	int height, width;
	int use_terminal_dimensions;
	int permill_obstacles;
	int starting_delay, minimum_delay, step_delay;
	int two_players;
	int duration_shortener, duration_decelerator, duration_extra_points;
	int probability_shortener, probability_decelerator, probability_extra_points;
	int score_step_map_change, disable_map_change;
	int disable_keys_help;
	int disable_top_scores;
	char *scorefile_path;
	int max_stored_scores;
} arguments_t;

/*
 * Parses command line arguments returning an arguments_t
 */
arguments_t*
parse_arguments(int argc, char *argv[]);

/*
 * Deallocates arguments_t
 */
void
delete_arguments(arguments_t *args);

#endif /* ARGUMENT_PARSER_H */
