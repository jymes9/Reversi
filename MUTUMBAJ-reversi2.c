#include <stdio.h>
#include <string.h>
#include "reversi.h"
/*Function prototypes*/
int valid_move( int current_player,int row, int col);
int count_scores(int current_player);
/*****************************************************************************
 * Get_Human_Move()
 *
 * Requests a valid move from the user for given <player>'s turn,
 *     either PLAYER1 or PLAYER2
 * Sets the x,y coordinates for the valid move by filling the <x> & <y>
 *     pointers
 * Returns the score for the chosen move, i.e. the number of squares converted
 *     from the opponent's colour to the player's colour, plus one for the
 *     move itself.
 *
 * Remember that the user types values in the range 1...MAX_BOARD_SIZE, but
 * the program should subtract 1 so that the x/y coordinates are in the
 * range 0...MAX_BOARD_SIZE-1. C likes numbers to start from 0!
 ****************************************************************************/
int Get_Human_Move(int player, int *x, int *y)
{
        int score;
        char move_arr[6];
        int row,i,column;
        char c;

        do {
                do {
                        fgets(move_arr,6,stdin);

                        for(i=0; i < strlen(move_arr); i++)
                        {
                                c = move_arr[i];
                                if(c == 'p')    /*check in range*/
                                        return 0;
                                if(c == 'q')    /*check in range*/
                                        return -1;
                        }
                } while (sscanf(move_arr,"%d%d",&column,&row)!=2
                         ||strcmp(move_arr,"")==0);
                row=row-1;
                column=column-1;
        }while(!(valid_move(player,row,column))); /*check for valid move*/

        score=Get_Score(player,row,column);
        *x=(row);
        *y=(column);

        return score;
}


/****************************************************************************
* Get_Score()
*
* Returns the score for the chosen move <x>, <y> by the given <player>,
*     i.e. the number of squares converted from the opponent's colour to the
*     player's colour, plus one for the move itself.
*
* Returns 0 if no squares are converted
****************************************************************************/
int Get_Score(int current_player, int x, int y)
{
        int i,j;
        int temp_board[size][size]; /* Local copy of board */
        int score = 0;
        int temp_score1=player1_score; /*local copy of current scores*/
        int temp_score2=player2_score;

        if(!(valid_move(current_player,x,y))) /* if move not valid return 0*/
                return 0;

        for(i = 0; i < size; i++)
        {
                for(j = 0; j < size; j++)
                {
                        temp_board[i][j]=board[i][j];
                }
        }


        Move( current_player,x, y );    /* Make move on the board */

        score = count_scores(current_player);   /* Get score for move */

        for(i = 0; i < size; i++)      /* restore the board and the scores*/
        {
                for(j = 0; j < size; j++)
                {
                        board[i][j]=temp_board[i][j];
                }
        }
        player1_score=temp_score1;
        player2_score=temp_score2;

        return score;
}

/***************************************************************************
 * Move()
 *
 * Updates the board with given <player>'s move at <x>,<y>
 *
 * Returns the score on a successful move, i.e. the number of squares converted
 *     from the opponent's colour to the player's colour, plus one for the
 *     move itself.
 *
 * Returns 0 on an invalid move
 **************************************************************************/
int Move(int current_player, int row, int col)
{
        int rowdelta = 0;
        int opposing_player;
        int coldelta = 0;
        int xpos = 0;
        int ypos = 0;


        if (!(valid_move(current_player,row,col)))
                return 0;

        board[row][col] = current_player; /* Place the player counter   */

        /* Identify opponent and increment score for added piece */
        if (current_player==1) {
                opposing_player=2;
                player1_score++;
        }
        else{
                opposing_player=1;
                player2_score++;
        }

        /* Check around the move for the opponents pieces to flip*/

        for(rowdelta = -1; rowdelta <= 1; rowdelta++)
        {
                for(coldelta = -1; coldelta <= 1; coldelta++)
                {
                        /* checking for the end of the board and skipping the passed move*/

                        if(row + rowdelta < 0 || row + rowdelta >= size ||

                           col + coldelta < 0 || col + coldelta >= size ||

                           (rowdelta==0 && coldelta== 0))

                                continue;



                        /* check to see next position has the opponent and if found and
                           keep going in that direction*/

                        if(board[row + rowdelta][col + coldelta] == opposing_player)

                        {

                                xpos = row + rowdelta;

                                ypos = col + coldelta;

                                /*move to the next position in the direction*/
                                for(;;)
                                {

                                        xpos += rowdelta;

                                        ypos += coldelta;

                                        /* stop when at the edge of the board*/

                                        if(xpos < 0 || xpos >= size || ypos < 0 || ypos >= size)

                                                break;

                                        /* If position is blank, break out*/

                                        if(board[xpos][ypos] == EMPTY_SPACE)
                                                break;

                                        /* If current player piece is found, go backwards while flipping all
                                           opponents pieces until initial position is found while
                                           updating scores and then break out after flipping*/
                                        if(board[xpos][ypos] == current_player)
                                        {
                                                while(board[xpos-=rowdelta][ypos-=coldelta]==opposing_player) {
                                                        board[xpos][ypos] = current_player;
                                                        if (current_player==1) {
                                                                player1_score++;
                                                                player2_score--;
                                                        }
                                                        else{
                                                                player2_score++;
                                                                player1_score--;
                                                        }
                                                }
                                                break; /*when all pieces are flipped, break out*/
                                        }
                                }
                        }
                }
        }
        if (current_player==1)  /*return the scores for the move*/
                return player1_score;
        else
                return player2_score;

}
/****************************************************************************
   This function checks if a move is valid for a current player.
   It takes in the current player and the move and first checks if the move is to
   an empty space, if not returns 0. It then moves around the move until an
   opponent is found, then moves in that direction until a current player
   piece is found then returns 1. stops moving in a direction when the edge
   of the board is found if no valid move, 0 is returned
****************************************************************************/
int valid_move( int current_player,int row, int col)

{

        int rowdelta = 0; /* direction positions for checking */
        int coldelta = 0;

        int x = 0;                    /*current positions*/
        int y = 0;

        int opposing_player;

/* Identify opponent */
        if (current_player==1)
                opposing_player=2;
        else
                opposing_player=1;

/* if the position isnt empty return 0 to indicate invalid move */
        if(board[row][col] != EMPTY_SPACE)
                return 0;

        /* Check around the blank position using direction moves  */
        for(rowdelta = -1; rowdelta <= 1; rowdelta++)
        {
                for(coldelta = -1; coldelta <= 1; coldelta++)

                {
                        /* check for board bounds and current position {0,0}*/

                        if(row + rowdelta < 0 || row + rowdelta >= size ||

                           col + coldelta < 0 || col + coldelta >= size ||

                           (rowdelta==0 && coldelta==0))

                                continue;

                        /* If opposing player is found in some direction adjacent to move
                           move in that direction checking for board bounds until the
                           current player is found then return 1 to indicate valid move*/

                        if(board[row + rowdelta][col + coldelta] == opposing_player)

                        {

                                x = row + rowdelta;

                                y = col + coldelta;

                                while (board[x][y] != EMPTY_SPACE) {
                                        x += rowdelta;
                                        y += coldelta;
                                        if(x < 0 || x >= size || y < 0 || y >= size)
                                                break;
                                        if(board[x][y] == current_player)
                                                return 1;
                                }

                        }

                }

        }

        return 0;   /*return 0 if no valid move*/
}
/***********************************************************************
   this function counts all the pieces of the current player on the
   board and returns them.
 ************************************************************************/
int count_scores(int current_player)

{
        int score = 0;
        int row,col;

        /* Check all board pieces counting the current players pieces*/
        for( row = 0; row < size; row++)

                for( col = 0; col < size; col++)

                {
                        if (board[row][col]==current_player)
                                score++;
                }

        return score;

}
