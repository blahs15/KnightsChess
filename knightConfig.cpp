// Russell Miller
/* Chess is played on an 8 × 8 board. A knight placed on one square can move to any unoccupied square that is at a distance of two squares horizontally and one square vertically, or else two squares vertically and one square horizontally. The complete move therefore looks like the letter L (in some orientation). A knight cannot move off the board. Unlike other chess pieces, the knight can “jump over” other pieces in going to its destination.
Consider a chess board on which we place any number m ∈ {0, 1, . . . , 64} of knights, at most one knight on each square. Call the configuration of knights valid if no knight can move to a square occupied by another knight.
Carefully specify a Boolean formula φ over 64 Boolean variables X where the number of truth assignments to φ is exactly the number of valid knight configurations. */

/* This program calculates the number of configurations that any number of knights can be in where no knight can capture any other knight on the board. */
/* It will also time how long the program takes to calculate the number of configurations. */
/* example output:
Configurations: 101693175442 // 8x8
Seconds: 3711.76 // 61 minutes on my computer, took ~2 hours in CSIF server
*/

#include <iostream>
#include <time.h>
#define ROW 8
#define COL 8
using namespace std;
void configure( bool board[ROW][COL], int i, int k, unsigned long long& configs );
bool valid( bool board[ROW][COL], int i, int k );

int main()
{
  clock_t t1,t2;
  t1 = clock();

  unsigned long long configs = 0;
  bool board[ROW][COL];
  for( int i = 0; i < ROW; i++ )
    for( int k = 0; k < COL; k++ )
      board[i][k] = false;
  configure( board, 0, 0, configs );
  cout << "Configurations: " << configs << endl;

  t2 = clock();
  double diff ( (double)t2 - (double)t1 );
  double seconds = diff / CLOCKS_PER_SEC;
  cout << "Seconds: " << seconds << endl;
} // main()

void configure( bool board[ROW][COL], int i, int k, unsigned long long& configs )
{ // Will check config(s) where knight is in current loc (if possible)
  // Then will check config(s) where knight is NOT in current loc
  if( valid( board, i, k ) )
  {
    board[i][k] = true;
    if( k < COL-1 )
      configure( board, i, k+1, configs );
    else if ( i < ROW-1 )
      configure( board, i+1, 0, configs );
    else // k == 7 && i == 7
      configs++;
  } // if valid location for knight
  board[i][k] = false;
  if( k < COL-1 )
    configure( board, i, k+1, configs );
  else if ( i < ROW-1 )
    configure( board, i+1, 0, configs );
  else // k == 7 && i == 7
    configs++;
  return;
} // configure()

bool valid( bool board[ROW][COL], int i, int k )
{ // i = row, k = column, not that it matters
  // half of tests unnecessary b/c loc hasn't been processed yet
  if( i-2 >= 0 && k-1 >= 0 && board[i-2][k-1] )
    return false;
  if( i-2 >= 0 && k+1 < COL && board[i-2][k+1] )
    return false;
  if( i-1 >= 0 && k-2 >= 0 && board[i-1][k-2] )
    return false;
  if( i-1 >= 0 && k+2 < COL && board[i-1][k+2] )
    return false;
  return true;
} // valid()