/*********************************
 * Reviewer: shani
 * Author: Sigal Tal
 * File Name: knight_tour.h
 * ******************************/

#ifndef __KNIGHT_TOUR_H__
#define __KNIGHT_TOUR_H__

#include "bit_array.h"

/* (0,0) = top left in the chess board */
typedef struct position
{
	int x;	/* horizontal axis */
	int y;	/* vertical axis */
} position_t;

void KnightTour(position_t position, int *path);

#endif /* __KNIGHT_TOUR_H__ */
