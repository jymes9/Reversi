#include <stdio.h>
#include "reversi.h"

/***************************************************************************
 * Best_Move()
 *
 * This function finds the best move that given <player> can make
 *
 * Returns the score of the best move that given player can make, i.e. the
 *     number of squares converted from the opponent's colour to the player's
 *     colour by the best move, plus one for the move itself.
 * Returns 0 if no move can be made
 *
 * Fills <xposition> and <yposition> pointers to the best move in the grid
 * If several moves give the same best score, uses the first move when
 * scanning the board in "raster scan" order (see image processing assignment
 **************************************************************************/
int Best_Move(int player, int *xposition, int *yposition)
{
	int i, j, bestPosition[2], bestScore = 0, score;
/*loop through column then row (raster scan)*/
	for(j = 0; j < size; j++){
		for(i = 0; i < size; i++){
			score = Get_Score(player, j, i); /*find the score for (i,j) */
			if(score > bestScore) /*if it is the new bestscore*/
			{
				bestScore = score; /*update bestScore*/
/*only update score if the new score is bigger, otherwise if the scores are
   the same keep the previous position in the raster scan*/
				bestPosition[0] = j;
				bestPosition[1] = i;
			}
		}
	}
	if(bestScore == 0)
		return 0;
/*updates the pointers to the positions with the best score*/
	*xposition = bestPosition[0];
	*yposition = bestPosition[1];
	return bestScore;
}
