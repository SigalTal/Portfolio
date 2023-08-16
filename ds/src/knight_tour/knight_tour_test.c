/*********************************
 * Reviewer:  
 * Author: Sigal Tal
 * File Name: knight_tour_test.c
 * ******************************/

#include <stdio.h>
#include "knight_tour.h"

int main()
{
	int path[64]={-1};
	int i=0;
	position_t position={0,1};

	KnightTour(position, path);

	for(i=0; i<64; ++i)
	{
		printf("move number %d to place %d\n",i , path[i]);
	}
	
	return 0;
}
