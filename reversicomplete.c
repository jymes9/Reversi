#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reversi.h"
#define HUMAN    1
#define COMPUTER 2
#define TRUE 1
#define FALSE 0
#define PLAYABLE 3
#define P1CHAR 'O'
#define P2CHAR '*'
#define EMPTYCHAR '.'
#define PLAYABLE_MARKER 'p'


int size=8;
int player1_score;
int player2_score;
int wrong_move = FALSE;
int has_valid_move = FALSE;
int playable_direction[MAX_BOARD_SIZE][MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int read_line ( FILE *fp, char *line, int max_length );

int main(){
 int r,m,player=1;
 int i,j;
 Initialise_Board();
 Print_Board();

int chosenx, choseny;
    for(;;){
    Print_Board();
    printf("player is now %i\n",player);
    //Best_Move(player,&chosenx,&choseny);
    Get_Human_Move(player,&chosenx,&choseny);
    Move(player,chosenx,choseny);
    if (player==1)
        player=2;
    else
        player=1;
     Print_Board();
//    r=printf("score for get move is %i\n",r);
//    Move(player,chosenx,choseny);
//    if (player==1)
//        player=2;
//    else
//        player=1;

}



 return;
}
int Get_Human_Move(int player, int *x, int *y)
{   int score,current_player=player;
    int dirx,diry;
    char move_arr[6];
    int row,i,column;
     char c;
        do {
            do {
                fgets(move_arr,6,stdin);

                for(i=0;i < strlen(move_arr);i++)
                {
                    c = move_arr[i];
                    if(c == 'p')                /*check in range*/
                        return 0;
                    if(c == 'q')                /*check in range*/
                        return -1;
                }
        } while (sscanf(move_arr,"%d%d",&column,&row)!=2||strcmp(move_arr,"")==0);

        row=row-1;
        column=column-1;
        }while(!(is_valid_move(player,row,column,&dirx,&diry)));

    score=Get_Score(current_player,row,column);
    *x=(row);
    *y=(column);

   return score ;
}


int Get_Score(int player, int row, int col)
{
    int xdir,ydir;
    int score=0;
    int opposing_player;
        if (player==1)
            opposing_player=2;
        else
            opposing_player=1;

    if (valid_move(player,row,col,&xdir,&ydir)){
        score++;
        printf("i and j are now %i %i \n",xdir ,ydir);
        while (board[row+=xdir][col+=ydir]==opposing_player){
            score++;
            printf("count is now %i\n",score);
        }
    }

  return score;
}

int Move(int player,int row,int col){
    int xdir,ydir;
    int count=0;
    int opposing_player;
        if (player==1)
            opposing_player=2;
        else
            opposing_player=1;

    if (valid_move(player,row,col,&xdir,&ydir)){
        count++;
        board[row][col] = player;
        printf("i and j are now %i %i \n",xdir ,ydir);
        while (board[row+=xdir][col+=ydir]==opposing_player){
            board[row][col]=player;
            count++;
            printf("count is now %i\n",count);
        }
    }

return count;

}



int valid_move( int current_player,int row, int col,int *movedirx,int *movediry)

{
  int correct_move=0;
  int rowdelta = 0;                   /* Row increment around a square    */

  int coldelta = 0;                   /* Column increment around a square */

  int x = 0;                          /* Row index when searching         */

  int y = 0;                          /* Column index when searching      */

  int opposing_player;


/* Identify opponent */
  if (current_player==1)
        opposing_player=2;
    else
        opposing_player=1;


  /* Find squares for valid moves.                           */

  /* A valid move must be on a blank square and must enclose */

  /* at least one opponent square between two player squares */


      if(board[row][col] != EMPTY_SPACE)      /* Is it a blank square?  */

        return 0;                     /* No - so on to the next */



      /* Check all the squares around the blank square  */

      /* for the opponents counter                      */

      for(rowdelta = -1; rowdelta <= 1; rowdelta++){
        for(coldelta = -1; coldelta <= 1; coldelta++)

        {

          /* Don't check outside the array, or the current square */

            if (!(board_bounds(row+rowdelta,col+coldelta))||(coldelta==0&&rowdelta==0)){
                continue;


          /* Now check the square */

          if(board[row + rowdelta][col + coldelta] == opposing_player)

          {

            /* If we find the opponent, move in the delta direction  */

            /* over opponent counters searching for a player counter */

            x = row + rowdelta;       /* Move to          */

            y = col + coldelta;       /* opponent square  */



            /* Look for a player square in the delta direction */

            while (board[x][y] != EMPTY_SPACE) {
                     x+=rowdelta;
                     y += coldelta;
                     if(!(board_bounds(x,y)))
                        break;
                    if (board[x][y] == current_player){
                        *movedirx=rowdelta;
                        *movediry=coldelta;
                        correct_move=1;
                        printf("playable direction found is %i %i",rowdelta,coldelta);
                    }

                }

            }

          }

        }

      }

    return correct_move;

}

int count_scores(int current_player)

{

  int score = 0;                      /* Score for current position */
  int opposing_player;
  int row,col;

  /* Identify opponent */

  if (current_player==1)
        opposing_player=2;
    else
        opposing_player=1;


  /* Check all board squares */

  for( row = 0; row < size; row++)

    for( col = 0; col < size; col++)

    {
        if (board[row][col]==current_player)
            score++;
//      score -= board[row][col] == opposing_player; /* Decrement for opponent */
//
//      score += board[row][col] == current_player;   /* Increment for player   */

    }

  return score;

}

int board_bounds(int row, int col){
    if ((row < 0 || col < 0 || row >= size || col >= size))
        return 0;
    else
        return 1;
}



void Initialise_Board(void)
{
   int i, j;
    /* Goes through the elements of the board filling them with zeros, defined in EMPTY_SPACE*/
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			board[i][j] = EMPTY_SPACE;
		}
	}

	/* Initial setup of the board with the initial pieces placed central depending on the specified size of the board */
	board[(size - 2)/2][size/2]     = PLAYER1;
	board[size/2][(size - 2)/2]     = PLAYER1;
	board[(size - 2)/2][(size - 2)/2] = PLAYER2;
	board[size/2][size/2]         = PLAYER2;

	player1_score = player2_score = 2;                      /*Initial scores for both players*/

}

/*********************************************************************************
 * Print_Board()                                                                 *
 *                                                                               *
 * Prints the board to the screen in the format given in the assignment sheet    *
 ********************************************************************************/
void Print_Board(void)
{
   int i, j;
	printf("\n   ");                 	/*Along with the for loop prints the upper line in the correct formatting using a field width of 2 for numbers */
	for(i = 0; i < size; i++)
		printf("%2i", i + 1);
	printf("\n   ");
	for(i = 0; i < size; i++)
		printf(" _");
	printf("\n");

/*Nested for loop printing rows and columns and checks if the value in the 2 dim array is a PLAYER1 or PLAYER2 value and puts a character belonging to
these players and if its not any of these puts an empty character */
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

	printf("\nthis part of the board has %i\n",board[0][3]);
}


int flips(int current_player)
{
    if (current_player==1){
        player1_score++;player2_score--;
        return player1_score;
            }

    else if (current_player==2){
        player2_score++;player1_score--;
        return player2_score;
    }
}
int Best_Move(int player, int *xposition, int *yposition)
{
	int i, j, bestPlace[2], bestScore = 0, score; /*set up counters*/
	for(j = 0; j < size; j++) /*loop for x*/
	{
		for(i = 0; i < size; i++) /*loop for y*/
		{
			score = Get_Score(player, j, i); /*find the score for (i,j) */

			if(score > bestScore) /*if it is the new best*/
			{
				bestScore = score; /*update bestScore*/
				bestPlace[0] = j;  /*save coordinates*/
				bestPlace[1] = i;
			}
		}
	}
	if(bestScore == 0)
		return 0;
	*xposition = bestPlace[0];
	*yposition = bestPlace[1];

	return bestScore;
}

