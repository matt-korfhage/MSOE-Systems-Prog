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

#ifndef SCOREFILE_H
#define SCOREFILE_H

#include <time.h>

#define CSV_SEPARATOR ';'
#define CSV_HEADER "score;player_name;date\n"

typedef struct
{
	int score;
	char *player_name;
	time_t date;
} score_mark_t;

typedef struct
{
	score_mark_t **array;
	int length;
} score_array_t;

/*
 * Stores in the specified pointers the number of marks contained in
 * the CSV file and the stored lower score
 */
void
get_csv_info(char *csv_file, unsigned int *number_scores, unsigned int *lower_score);

/*
 * Returns '\0' if the name is valid. Otherwise, returns the illegal
 * character
 */
char
validate_player_name(char *player_name);

/*
 * Add score mark to the specified CSV file if is has a better score than
 * the worst one already registered or there's still space (max_stored_scores)
 */
void
add_score_mark(char *csv_file, unsigned int max_stored_scores, score_mark_t *score_mark);

/*
 * Read the CSV file and print a table with its contents
 */
void
print_scores(char *csv_file);

#endif /* SCOREFILE_H */
