#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mtmflix.h"
#include "series.h"

//this type defines a series
//episodesNum is a number of episodes in the series,
//genre is its genre,
//ages is an array of two integers: minimal and maximal age to watch this series
//episodeDuration is an average episode duration
struct series_t {
	int episodesNum;
	Genre genre;
	int* ages;
	int episodesDuration;
};

//creates a series instance given the number of episodes, the ages array,
//and the average episode duration
Series seriesCreate (int episodesNum, Genre genre, int* ages, 
	int episodesDuration) {
	Series series = (Series)malloc(sizeof(*series));
	if (series == NULL) {
		return NULL;
	}
	series->episodesNum = episodesNum;
	series->genre = genre;
	if (ages == NULL) {
		series->ages = NULL;
	} else {
		series->ages = (int*)malloc(sizeof(*ages)*2);
		if (series->ages == NULL) {
		    seriesFree(series);
			return NULL;
		}
		memcpy(series->ages, ages, sizeof(*ages)*2);
		if (series->ages[0] < MTM_MIN_AGE) {
			series->ages[0] = MTM_MIN_AGE;
		}
		if (series->ages[1] > MTM_MAX_AGE) {
			series->ages[1] = MTM_MAX_AGE;
		}
	}
	series->episodesDuration = episodesDuration;
	return series;
}

//frees a series instance
void seriesFree (Series series) {
	free(series->ages);
	series->ages = NULL;
	free(series);
	series = NULL;
}

//copies a series instance
Series seriesCopy (Series series) {
	if (series == NULL) {
		return NULL;
	}
	Series new_series = seriesCreate(series->episodesNum, series->genre, 
		series->ages, series->episodesDuration);
	if (new_series == NULL) {
		return NULL;//added for readability
	}
	seriesFree(series);
	return new_series;
}

//helper function used to sort series alphabetically by genre
int compareSeriesByGenre(Series series_a, Series series_b) {
	return strcmp(seriesGetGenre(series_a), seriesGetGenre(series_b));
}

//given a series instance returns its genre as astring
char* seriesGetGenre (Series series) {
	if (series == NULL) {
		return NULL;
	}
	switch (series->genre) {
		case SCIENCE_FICTION: return "SCIENCE FICTION";
        case DRAMA : return "DRAMA";
        case COMEDY : return "COMEDY";
        case CRIME : return "CRIME";
        case MYSTERY : return "MYSTERY";
        case DOCUMENTARY : return "DOCUMENTARY";
        case ROMANCE : return "ROMANCE";
        case HORROR : return "HORROR";
	}
	// Unreachable
	assert(false);
	return NULL;
}

//given a series instance returns episode duration
int seriesGetEpisodeDuration(Series series){
    assert (series != NULL); //we check this before calling the function
    return series->episodesDuration;
}

//given a series instance returns the minimal age to watch the series
//when there are no age restrictions, returns MTM_MIN_AGE
int seriesGetMinAge (Series series) {
	assert (series != NULL); //we check this before calling the function
	if (series->ages == NULL) {
		return MTM_MIN_AGE;
	}
	return series->ages[0];
}

//given a series instance returns the maximal age to watch the series
//when there are no age restrictions, returns MTM_MAX_AGE
int seriesGetMaxAge (Series series) {
	assert (series != NULL); //we check this before calling the function
	if (series->ages == NULL) {
		return MTM_MAX_AGE;
	}
	return series->ages[1];
}
