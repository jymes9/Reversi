#include <stdio.h>
#include "reversi.h"

#define P1CHAR 'O'
#define P2CHAR '*'
#define EMPTYCHAR '.'

/*****************************************************************
 * Initialise_Board()                                            *
 *                                                               *
 * Initialises all squares on board to empty (zero)              *
 * Initialises central positions with two pieces for each player.*
 * Initialises the scores for each player at two points each     *
 ****************************************************************/
void Initialise_Board(void)
{
        int i, j;
        /* Goes through the elements of the board filling them with zeros,
           defined in EMPTY_SPACE*/
        for(i = 0; i < size; i++)
        {
                for(j = 0; j < size; j++)
                {
                        board[i][j] = EMPTY_SPACE;
                }
        }

        /* Initial setup of the board with the initial pieces placed central
           depending on the specified size of the board */
        board[(size - 2)/2][size/2]     = PLAYER1;
        board[size/2][(size - 2)/2]     = PLAYER1;
        board[(size - 2)/2][(size - 2)/2] = PLAYER2;
        board[size/2][size/2]         = PLAYER2;

        player1_score = player2_score = 2; /*Initial scores for both players*/

}


/*****************************************************************************
 * Print_Board()
 *
 * Prints the board to the screen in the format given
   in the assignment sheet    *
 ****************************************************************************/
void Print_Board(void)
{
        int i, j;
        printf("\n   ");
        /*Along with the for loop prints the upper line in the correct
           formatting using a field width of 2 for numbers */
        for(i = 0; i < size; i++)
                printf("%2i", i + 1);
        printf("\n   ");
        for(i = 0; i < size; i++)
                printf(" _");
        putchar(' ');
        printf("\n");

/*Nested for loop printing rows and columns and checks if the value
   in the 2 dim array is a PLAYER1 or PLAYER2 value and puts a
   character belonging to   these players and if its not any of these
   puts an empty character */
        for(i = 0; i < size; i++)
        {
                printf("%2i:", i+1);
                for(j = 0; j < size; j++)
                {
                        putchar(' ');

                        if (board[i][j] == PLAYER1)
                                putchar(P1CHAR);
                        else if (board[i][j] == PLAYER2)
                                putchar(P2CHAR);
                        else {
                                putchar(EMPTYCHAR);
                        }

                }
                putchar(' ');
                printf("\n");
        }
        printf("\n");
        /* writes the scores for both player in the specified formatting*/
        printf("Player 1 (");
        putchar(P1CHAR);
        printf(") score: %i", player1_score);
        printf("\n");
        printf("Player 2 (");
        putchar(P2CHAR);
        printf(") score: %i\n", player2_score);
}
