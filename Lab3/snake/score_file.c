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

// modification of header location for CPE2600 - DER 9/10/2023 
#include "score_file.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <sys/stat.h>

/*
 * Return the amount of scores in the CSV file. Returns -1 on error
 */
static int
count_scores(char *csv)
{
	int num_scores;
	FILE *file;
	char buffer;

	if ((file = fopen(csv, "r")) == NULL)
	{
		warn("%s", csv);
		return (-1);
	}

	num_scores = -1;  /* To not count the header (first line) */
	while (fread(&buffer, sizeof(char), 1, file) > 0)
	{
		if (buffer == '\n')
			num_scores++;
	}

	fclose(file);

	return (num_scores);
}

/*
 * Parse a score_mark_t from a FILE* to the CSV file. Return NULL if there's
 * no registry available
 */
static score_mark_t*
parse_registry(FILE *file)
{
	score_mark_t *score_mark;
	char buffer;
	int line_length, player_name_length;
	char *line, *aux;

	/* Measure line length */
	line_length = 0;
	while (fread(&buffer, sizeof(char), 1, file) > 0)
	{
		line_length++;
		if (buffer == '\n')
			break;
	}
	if (line_length == 0)
		return (NULL);

	fseek(file, -line_length, SEEK_CUR);  /* Go back to the beginning of line */
	line = calloc(line_length + 1, sizeof(char));

	/* Read line */
	fread(line, sizeof(char), line_length, file);

	score_mark = malloc(sizeof(score_mark_t));

	/* Parse score */
	score_mark->score = atoi(line);

	/* Advance to the player name */
	aux = strchr(line, CSV_SEPARATOR);
	aux++;

	/* Parse player name */
	player_name_length = strchr(aux, CSV_SEPARATOR) - aux;
	score_mark->player_name = calloc(player_name_length + 1, sizeof(char));
	memcpy(score_mark->player_name, aux, player_name_length);

	/* Advance to date */
	aux = strchr(aux, CSV_SEPARATOR);
	aux++;

	/* Parse date */
	score_mark->date = atol(aux);

	free(line);

	return (score_mark);
}

/*
 * Read the CSV file and return a score_array_t with its contents. Return NULL
 * if there's an error or there are no scores stored
 */
static score_array_t*
read_scores(char *csv)
{
	score_array_t *score_array;
	FILE *file;
	char buffer;

	score_array = malloc(sizeof(score_array_t));
	score_array->length = access(csv, F_OK) != -1 ? count_scores(csv) : 0;

	/* Exit if the file is empty or there was an error */
	if (score_array->length <= 0)
	{
		free(score_array);
		return (NULL);
	}

	score_array->array = calloc(score_array->length, sizeof(score_mark_t*));

	if ((file = fopen(csv, "r")) == NULL)
	{
		free(score_array->array);
		free(score_array);
		warn("%s", csv);
		return (NULL);
	}

	/* Skip header */
	while (fread(&buffer, sizeof(char), 1, file) > 0)
	{
		if (buffer == '\n')
			break;
	}

	for (int i = 0; i < score_array->length; i++)
		score_array->array[i] = parse_registry(file);

	fclose(file);

	return (score_array);
}

/*
 * Deallocate an score_array_t
 */
static void
delete_score_array(score_array_t *score_array)
{
	for (int i = 0; i < score_array->length; i++)
	{
		free(score_array->array[i]->player_name);
		free(score_array->array[i]);
	}

	free(score_array->array);
	free(score_array);
}

/*
 * Return the number of digits of an unsigned int
 */
static unsigned int
count_digits(unsigned long n)
{
	unsigned int digits = 0;

	if (n == 0)
		return (1);

	while (n)
	{
		n /= 10;
		digits++;
	}

	return (digits);
}

/*
 * Create all the directories in the specified path if they don't exist
 */
static void
mkdir_parents(char *path)
{
	const int SIZE_DIR = strlen(path);
	char dir[SIZE_DIR];
	char *cur_separator = path;

	while ((cur_separator = strchr(cur_separator+1, '/')))
	{
		memset(dir, '\0', SIZE_DIR);
		memcpy(dir, path, cur_separator - path);

		/* Create dir if it doesn't exists */
		if (access(dir, F_OK) == -1)
		{
			if (mkdir(dir, 0755) == -1)
			{
				warn("%s", dir);
				break;
			}
		}
	}
}

void
get_csv_info(char *csv_file, unsigned int *number_scores, unsigned int *lower_score)
{
	score_array_t *score_array;

	if ((score_array = read_scores(csv_file)) == NULL)
	{
		*number_scores = 0;
		*lower_score = 0;
	}
	else
	{
		*number_scores = score_array->length;

		*lower_score = score_array->array[0]->score;
		for (int i = 1; i < score_array->length; i++)
		{
			if ((unsigned int)score_array->array[i]->score < *lower_score)
				*lower_score = score_array->array[i]->score;
		}

		delete_score_array(score_array);
	}
}

char
validate_player_name(char *player_name)
{
	return (strchr(player_name, CSV_SEPARATOR) ? CSV_SEPARATOR : '\0');
}

void
add_score_mark(char *csv_file, unsigned int max_stored_scores, score_mark_t *score_mark)
{
	FILE *file;
	score_array_t *score_array;
	unsigned int new_added, n_inserted;
	score_mark_t *current;

	mkdir_parents(csv_file);  /* Create directory for the CSV file */

	score_array = read_scores(csv_file);

	if ((file = fopen(csv_file, "w")) == NULL)
	{
		warn("%s", csv_file);
		return;
	}

	/* Write header */
	fwrite(CSV_HEADER, strlen(CSV_HEADER), 1, file);

	if (score_array == NULL)
	{
		/* If the file was empty */
		fprintf(file, "%d%c%s%c%ld\n", score_mark->score, CSV_SEPARATOR,
				score_mark->player_name, CSV_SEPARATOR, score_mark->date);
	}
	else
	{
		new_added = 0;
		n_inserted = 0;
		for (int i = 0; i < score_array->length && n_inserted < max_stored_scores; i++)
		{
			current = score_array->array[i];
			/* Insert new one if it's bigger than the current one */
			if (!new_added && score_mark->score > current->score)
			{
				fprintf(file, "%d%c%s%c%ld\n", score_mark->score, CSV_SEPARATOR,
						score_mark->player_name, CSV_SEPARATOR, score_mark->date);
				new_added = 1;
				n_inserted++;
			}

			/* Insert current one */
			if (n_inserted < max_stored_scores)
			{
				fprintf(file, "%d%c%s%c%ld\n", current->score, CSV_SEPARATOR,
						current->player_name, CSV_SEPARATOR, current->date);
				n_inserted++;
			}
		}
		/* If is the smaller score of the top and still has space */
		if (!new_added && n_inserted < max_stored_scores)
			fprintf(file, "%d%c%s%c%ld\n", score_mark->score, CSV_SEPARATOR,
					score_mark->player_name, CSV_SEPARATOR, score_mark->date);

		delete_score_array(score_array);
	}

	fclose(file);
}

void
print_scores(char *csv_file)
{
	score_array_t *score_array;
	unsigned int size_longest_score, size_longest_name, width_table;
	char date_buffer[17];

	if ((score_array = read_scores(csv_file)) == NULL)
		return;

	/* Find the longest sizes of score and player names */
	size_longest_score = count_digits(score_array->array[0]->score);
	size_longest_name = strlen(score_array->array[0]->player_name);
	for (int i = 1; i < score_array->length; i++)
	{
		if (count_digits(score_array->array[i]->score) > size_longest_score)
			size_longest_score = count_digits(score_array->array[i]->score);

		if (strlen(score_array->array[i]->player_name) > size_longest_name)
			size_longest_name = strlen(score_array->array[i]->player_name);
	}
	/* Mind the length of table headers */
	if (size_longest_score < strlen("Score"))
		size_longest_score = strlen("Score");
	if (size_longest_name < strlen("Player Name"))
		size_longest_name = strlen("Player Name");

	width_table = size_longest_score + size_longest_name + 32;
	/* Centered table title */
	printf("\n%*s\n", (int)(width_table/2 + strlen("TOP SCORES")/2), "TOP SCORES");
	/* Print table header */
	for (unsigned int i = 0; i < width_table; i++)
		putchar('-');
	putchar('\n');

	printf("| Top | %-*s | %-*s | Date             |\n", size_longest_score, "Score",
			size_longest_name, "Player Name");

	for (unsigned int i = 0; i < width_table; i++)
		putchar('-');
	putchar('\n');

	/* Print scores */
	for (int i = 0; i < score_array->length; i++)
	{
		strftime(date_buffer, 17, "%d-%m-%Y %H:%M",
				localtime(&score_array->array[i]->date));
		printf("| %3d | %-*d | %-*s | %-s |\n", i + 1, size_longest_score,
				score_array->array[i]->score,
				size_longest_name, score_array->array[i]->player_name,
				date_buffer);
	}

	/* Close table */
	for (unsigned int i = 0; i < width_table; i++)
		putchar('-');
	putchar('\n');

	delete_score_array(score_array);
}
