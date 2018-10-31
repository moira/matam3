#ifndef SERIES_H_
#define SERIES_H_

#include "mtm_ex3.h"

typedef struct series_t* Series;

Series seriesCreate (int episodesNum, Genre genre, int* ages, 
	int episodesDuration);
void seriesFree (Series series);
Series seriesCopy (Series series);
char* seriesGetGenre (Series series);
int compareSeriesByGenre(Series series_a, Series series_b);
int seriesGetEpisodeDuration(Series series);
int seriesGetMaxAge (Series series);
int seriesGetMinAge (Series series);

#endif /*SERIES_H_*/
