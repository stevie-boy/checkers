//CheckerBoard.cpp

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <iomanip>
using std::setw;

#include <windows.h>

#include "CommonResources.h"
#include "CheckerBoard.h"
using namespace CommonResources;


char CheckerBoard::xCoordinates[49] = { "\t\t       0    1    2    3    4    5    6    7  \n" };
char CheckerBoard::yCoordinates[25] = { " 0  1  2  3  4  5  6  7" };
                                                                                         
char CheckerBoard::border[49] =	    "\t\t     ----------------------------------------\n";
char CheckerBoard::checkerBoard[24][44] = { "|     *****     *****     *****     *****|\n",
											"|     *****     *****     *****     *****|\n",
											"|     *****     *****     *****     *****|\n",
											"|*****     *****     *****     *****     |\n",
											"|*****     *****     *****     *****     |\n",
											"|*****     *****     *****     *****     |\n",
											"|     *****     *****     *****     *****|\n",
											"|     *****     *****     *****     *****|\n",
											"|     *****     *****     *****     *****|\n",
											"|*****     *****     *****     *****     |\n",
											"|*****     *****     *****     *****     |\n",
											"|*****     *****     *****     *****     |\n",
											"|     *****     *****     *****     *****|\n",
											"|     *****     *****     *****     *****|\n",
											"|     *****     *****     *****     *****|\n",
											"|*****     *****     *****     *****     |\n",
											"|*****     *****     *****     *****     |\n",
											"|*****     *****     *****     *****     |\n",
											"|     *****     *****     *****     *****|\n",
											"|     *****     *****     *****     *****|\n",
											"|     *****     *****     *****     *****|\n",
											"|*****     *****     *****     *****     |\n",
											"|*****     *****     *****     *****     |\n",
											"|*****     *****     *****     *****     |\n" };

char CheckerBoard::player1Capture[3][27] = { "--------------------------",
											 "|                        |",
											 "--------------------------" };
char CheckerBoard::player2Capture[3][27] = { "--------------------------",
											 "|                        |",
											 "--------------------------" };

const char CheckerBoard::PLAYER_1_PAWN = char(1);
const char CheckerBoard::PLAYER_1_KING = 'K';
const char CheckerBoard::PLAYER_2_PAWN = char(2);
const char CheckerBoard::PLAYER_2_KING = 'k';

//Constructor
CheckerBoard::CheckerBoard()
{
	p1PiecesCaptured = 0;
	p2PiecesCaptured = 0;
}

//Draws the checker board on the screen
void CheckerBoard::drawBoard( string name1, string name2 )
{
	//Draws the x coordinates at the top, followed by the border underneath it.
	cout << "\n\t\t\t\t        X" << "\n\n" << xCoordinates << border;

	//Draws a y coordinate, followed by 2 spaces and then a line of the checkerboard.
	for (  int i = 0; i < 24; ++i )
	{
		( i == 12 ) ? cout << "\tY       " : cout << "\t\t";
		cout << yCoordinates[i] << "   " << checkerBoard[i];
	}
	//Draws the bottom border.
	cout << border << endl;

	//prints the names above the capture pile
	cout << "\t       " << std::left << setw( 26 ) << name1 << " " << std::left << setw( 26 ) << name2 << endl;
	
	//Draws the capture piles.  The first is tabbed once and spaced over 7 spaces.
	//The second is spaced once.
	for ( int i = 0; i < 4; ++i )
	{ 
		cout << "\t       " << player1Capture[i] << " " << player2Capture[i] << endl; 
	}
}

void CheckerBoard::clearScreen()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {0, 0};
	DWORD count;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi);

	FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

	SetConsoleCursorPosition(hStdOut, coord);
}

//Puts the pieces on the board for the beginning of the game.
void CheckerBoard::initializeBoard()
{
	int y;
	int x;
	//Player 2 pieces on even rows.
	for ( y = 0; y < 3; y += 2 )
	{
		for ( x = 0; x < 8; x += 2 )
		{
			squareStatus[y][x].availablity = AVAILABLE;
			squareStatus[y][x].occupation = OCCUPIED;
			squareStatus[y][x].players = PLAYER2;
			squareStatus[y][x].checkers = PAWN;
		}// next x
	}// next y

	//Player 2 pieces on odd rows.
	for ( x = 1; x < 8; x += 2 )
	{
		squareStatus[1][x].availablity = AVAILABLE;
		squareStatus[1][x].occupation = OCCUPIED;
		squareStatus[1][x].players = PLAYER2;
		squareStatus[1][x].checkers = PAWN;
	}// next x
		
	// Unoccupied squares at game start.
	for ( x = 1; x < 8; x += 2 )
	{
		squareStatus[3][x].availablity = AVAILABLE;
		squareStatus[3][x].occupation = UNOCCUPIED;
	}// next x

	for ( x = 0; x < 8; x += 2 )
	{
		squareStatus[4][x].availablity = AVAILABLE;
		squareStatus[4][x].occupation = UNOCCUPIED;
	}// next x

	//Player 1 pieces on odd rows.
	for ( y = 5; y < 8; y += 2 )
	{
		for ( x = 1; x < 8; x += 2 )
		{
			squareStatus[y][x].availablity = AVAILABLE;
			squareStatus[y][x].occupation = OCCUPIED;
			squareStatus[y][x].players = PLAYER1;
			squareStatus[y][x].checkers = PAWN;
		}// next x
	}// next y

	//Player 1 pieces on even rows.
	for ( x = 0; x < 8; x += 2 )
	{
		squareStatus[6][x].availablity = AVAILABLE;
		squareStatus[6][x].occupation = OCCUPIED;
		squareStatus[6][x].players = PLAYER1;
		squareStatus[6][x].checkers = PAWN;
	}// next x

	//Unavailable squares on even numbered rows.
	for (  y = 0; y < 8; y += 2 )
	{
		for ( x = 1; x < 8; x += 2)
		{ squareStatus[y][x].availablity = UNAVAILABLE; }
	}

	//Unavailable squares on odd numbered rows.
	for ( y = 1; y < 8; y += 2 )
	{
		for ( x = 0; x < 8; x += 2)
		{ squareStatus[y][x].availablity = UNAVAILABLE; }
	}

	CheckerBoard::setCheckers();
}

void CheckerBoard::printSquares()
{
	for ( int y = 0; y < 4; ++y )
	{
		for ( int x = 0; x < 8; ++ x )
		{
			cout << y << ", " << x << endl
				 << squareStatus[y][x].availablity << endl
				 << squareStatus[y][x].occupation << endl
				 << squareStatus[y][x].players << endl
				 << squareStatus[y][x].checkers << endl << endl;
		}
	}
	char c;
	cin >> c;
	if ( c == 'y')
		return;

	for ( int y = 4; y < 8; ++y )
	{
		for ( int x = 0; x < 8; ++ x )
		{
			cout << y << ", " << x << endl
				 << squareStatus[y][x].availablity << endl
				 << squareStatus[y][x].occupation << endl
				 << squareStatus[y][x].players << endl
				 << squareStatus[y][x].checkers << endl << endl;
		}
	}
}
//Moves a checker.
void CheckerBoard::moveChecker( Coordinates c )
{
	char temp;
	moveCheckerInSquareStatus( c );

	translateCoordinates( c );

	temp = checkerBoard[ c.from.y ][ c.from.x ];
	checkerBoard[ c.from.y ][ c.from.x ] = ' ';
	checkerBoard[ c.to.y ][ c.to.x ] = temp;
}

void CheckerBoard::performJump( Coordinates c )
{
	int tempX, tempY; //Will hold the coordinates of the jumped piece.
	//Take the average of the 'x' and 'y' coordinates.  This should give you the coordinates of the jumped piece.
	tempX = ( c.from.x + c.to.x ) / 2;
	tempY = ( c.from.y + c.to.y ) / 2;
	//Move the checker.
	moveChecker( c );

	moveCheckerToCapture( tempX, tempY, squareStatus[ tempY ][ tempX ].players );

}
//Overloaded validateCoordinates that is used to validate one set of coordinates
//y and x values are copied to both "to" and "from" x and y values of the
//Coordinates structure because those values are required to validate the coordinates
//using validateCoordinates( Coordinates c, Players p )
//This overload is used in lookForJumps()
bool CheckerBoard::validateCoordinates( int y, int x, Players p )
{
	Coordinates c;
	//Assign values to both "from" and "to" members of Coordinates.
	c.from.x = x;
	c.from.y = y;
	c.to.x = x;
	c.to.y = y;

	return validateCoordinates( c, p );//return the result of this function
}
//returns "true" if coordinates are valid, and false otherwise.
bool CheckerBoard::validateCoordinates( Coordinates c, Players p )
{
	bool result = boundsCheck( c );

	if ( result )
	{
		// From coordinates
		if ( squareStatus[ c.from.y ][ c.from.x ].availablity == AVAILABLE ) // is the square available?
		{
			if ( squareStatus[ c.from.y ][ c.from.x ].occupation == OCCUPIED )// the square is available.  is it occupied?
			{
				if ( squareStatus[ c.from.y ][ c.from.x ].players == p )// the square is available and occupied. is it the current player's checker?
				{
					result = true;
				}

				else result = false; //from is invalid
			}

			else result = false; // from is invalid
		}

		else result = false; // from is invalid
	}

	// To coordinates : if result is still true
	if ( result )
	{
		// To coordinates
		if ( squareStatus[ c.to.y ][ c.to.x ].availablity == AVAILABLE ) // is the square available?
		{
			if ( squareStatus[ c.to.y ][ c.to.x ].occupation == UNOCCUPIED )// the square is available.  is it occupied?
			{
			
				result = checkMoveValidity( c, p, squareStatus[ c.from.y ][ c.from.x ].checkers );
			}

			else result = false; // to is invalid
		}

		else result = false; // to is invalid
	}

	return result;
}
//Looks for any checker that has made it to the other side and crowns it a king.
void CheckerBoard::lookForKings( Players p )
{
	int i, nothing; //nothing is used to fill a required parameter for translateCoordinates( int &x, int &y )
	//Player1 is crowned king on row 0
	if ( p == PLAYER1 )
	{
		for ( i = 0; i < 8; i += 2 )
			if ( squareStatus[ 0 ][ i ].occupation == OCCUPIED )
				if ( squareStatus[ 0 ][ i ].players == p )
					if ( squareStatus[ 0 ][ i ].checkers == PAWN )
					{
						squareStatus[ 0 ][ i ].checkers = KING;
						translateCoordinates( i, nothing );
						//The y coordinates is translated by the programmer because
						//the row number is known ( row 0 ) and the translation for
						//row 0 is 1.
						grantKingship( p, 1, i );
					}
	}
	//Player2 is crowned king on row 7
	else if ( p == PLAYER2 )
	{
		for ( i = 1; i < 8; i += 2 )
			if ( squareStatus[ 7 ][ i ].occupation == OCCUPIED )
				if ( squareStatus[ 7 ][ i ].players == p )
					if ( squareStatus[ 7 ][ i ].checkers == PAWN )
					{
						squareStatus[ 7 ][ i ].checkers = KING;
						translateCoordinates( i, nothing );
						//The y coordinates is translated by the programmer because
						//the row number is known ( row 7 ) and the translation for
						//row 7 is 22.
						grantKingship( p, 22, i );
					}
	}
}

/*This function looks for possible jumps for the current player.  It returns
* a pointer to a Coordinates structure that contains the coordinates for each
* jump.  It also accepts a reference to an integer value that will hold the 
* total number of elements the Coordinates structure has in it after all jumps
* have been discovered.  If this integer value is zero, then no jumps were discovered. */
Coordinates *CheckerBoard::lookForJumps( Players p, int *numElements )
{
	int row, col;
	Coordinates *cPtr = new Coordinates[ 10 ]; //Array of Coordinates that will hold the possible jumps.
	*numElements = 0; //numElements starts at zero.
	Checkers ch; //Contains the checker type at the current location.

	//First set of loops iterate through the rows where available squares are on even column numbers.
	//Iteration starts at the top of the board at row 0.
	for ( row = 0; row < 8; row += 2 )
		for ( col = 0; col < 8; col += 2 )
			if ( squareStatus[ row ][ col ].occupation == OCCUPIED ) //Inner loop iterates through each square on the current row
				if ( squareStatus[ row ][ col ].players == p )//If this is true, then we've found one of the current player's checkers.
				{
					//Assign the current coordinates of the checker to the current index of Coordinates array.
					cPtr[ *numElements ].from.y = row;
					cPtr[ *numElements ].from.x = col;
					//Assign the checker type at the current location to "ch" to pass it to isJumpAvailable
					ch = squareStatus[ row ][ col ].checkers;
					//Pass Coordinates array to isnJumpAvailable.
					findAvailableJumps( cPtr, p, ch, numElements );
				}

	//Second set of loops iterate through the rows where available squares are on odd column numbers.
	//Iteration starts at the top of the board at row 0.
	for ( row = 1; row < 8; row += 2 )
		for ( col = 1; col < 8; col += 2 )
			if ( squareStatus[ row ][ col ].occupation == OCCUPIED ) //Inner loop iterates through each square on the current row
				if ( squareStatus[ row ][ col ].players == p )//If this is true, then we've found one of the current player's checkers.
				{
					//Assign the current coordinates of the checker to the current index of Coordinates array.
					cPtr[ *numElements ].from.y = row;
					cPtr[ *numElements ].from.x = col;
					//Assign the checker type at the current location to "ch" to pass it to isJumpAvailable
					ch = squareStatus[ row ][ col ].checkers;
					//Pass Coordinates array to isnJumpAvailable.
					findAvailableJumps( cPtr, p, ch, numElements );
				}

	//If there were no jumps found, then delete the pointer.
	if ( *numElements == 0 )
	{
		delete [] cPtr;
		//Assign zero to cPtr so it won't reference anything.
		cPtr = 0;
	}

	return cPtr; //When we're finished, we return the address of our Coordinates array to be displayed to the Player.
}

Coordinates *CheckerBoard::subsequentJumps( Coordinates c, Players p, int *numElements )
{
	Coordinates *cPtr = new Coordinates[ 2 ]; //Array of Coordinates that will hold the possible jumps.
	*numElements = 0; //numElements starts at zero.
	/* Assign the 'to' coordinates of the c Coordinates structure that represent the current location of the piece that just
	 * made a jump to the 'from' coordinates of the first element of the Coordinates array in order to check for jumps at that location. */
	cPtr[ 0 ].from.x = c.to.x;
	cPtr[ 0 ].from.y = c.to.y;
	Checkers ch = squareStatus[ c.to.y ][ c.to.x ].checkers; //Contains the checker type at the current location.

	findAvailableJumps( cPtr, p, ch, numElements );

	if ( *numElements == 0 )
	{
		delete[] cPtr;
		//Assign zero to cPtr so it won't reference anything.
		cPtr = 0;
	}

	return cPtr; //When we're finished, we return the address of our Coordinates array to be displayed to the Player.
}
///////Private functions////////////////////////////////////
inline void CheckerBoard::setCheckers()
{
	//Set player 2's pieces on the board.
	//Row 0
	checkerBoard[1][3] = PLAYER_2_PAWN;
	checkerBoard[1][13] = PLAYER_2_PAWN;
	checkerBoard[1][23] = PLAYER_2_PAWN;
	checkerBoard[1][33] = PLAYER_2_PAWN;

	//Row 1
	checkerBoard[4][8] = PLAYER_2_PAWN;
	checkerBoard[4][18] = PLAYER_2_PAWN;
	checkerBoard[4][28] = PLAYER_2_PAWN;
	checkerBoard[4][38] = PLAYER_2_PAWN;

	//Row 2
	checkerBoard[7][3] = PLAYER_2_PAWN;
	checkerBoard[7][13] = PLAYER_2_PAWN;
	checkerBoard[7][23] = PLAYER_2_PAWN;
	checkerBoard[7][33] = PLAYER_2_PAWN;

	//Set player 1's pieces on the board.
	//Row 5
	checkerBoard[16][8] = PLAYER_1_PAWN;
	checkerBoard[16][18] = PLAYER_1_PAWN;
	checkerBoard[16][28] = PLAYER_1_PAWN;
	checkerBoard[16][38] = PLAYER_1_PAWN;

	//Row 6
	checkerBoard[19][3] = PLAYER_1_PAWN;
	checkerBoard[19][13] = PLAYER_1_PAWN;
	checkerBoard[19][23] = PLAYER_1_PAWN;
	checkerBoard[19][33] = PLAYER_1_PAWN;

	//Row 7
	checkerBoard[22][8] = PLAYER_1_PAWN;
	checkerBoard[22][18] = PLAYER_1_PAWN;
	checkerBoard[22][28] = PLAYER_1_PAWN;
	checkerBoard[22][38] = PLAYER_1_PAWN;
}

void CheckerBoard::moveCheckerInSquareStatus( Coordinates c )
{
	SquareStatus s;
	s = squareStatus[ c.to.y ][ c.to.x ];
	squareStatus[ c.to.y ][ c.to.x ] = squareStatus[ c.from.y ][ c.from.x ];
	squareStatus[ c.from.y ][ c.from.x ] = s;	
}

// returns true if all coordinates are in bounds and false if coordinates are out-of-bounds
inline bool CheckerBoard::boundsCheck( Coordinates c )
{
	bool result = true;
	//From
	if ( c.from.x > 7 || c.from.y < 0 )
		result = false;
	//To
	else if ( c.to.x > 7 || c.to.y < 0 )
		result = false;

	return result;
}

inline bool CheckerBoard::boundsCheck( int y, int x )
{
	//Returns true if x and y both fall between 0 and 7 and false otherwise.
	return ( ( x <= 7 && x >= 0 ) && ( y <= 7 && y >= 0 ) );
}

/* returns true if the move is valid and false otherwise. */
inline bool CheckerBoard::checkMoveValidity( Coordinates c, Players p, Checkers ch )
{
	bool result = true;
	int differenceX = c.from.x - c.to.x;
	int differenceY = c.from.y - c.to.y;

	//If you are either player and you are moving a king...
	if ( ch == KING )
	{
		// you can only move left or right one square and...
		if ( differenceX != 1 && differenceX != -1 )
			result = false;
		// you can only move up or down one square.
		else if ( differenceY > 1 )
			result = false;
	}

	//If you are PLAYER1...
	else if ( p == PLAYER1 )
	{
		// and you're moving a pawn...
		if ( ch == PAWN )
		{
			// you can only move left or right one square and...
			if ( differenceX != 1 && differenceX != -1 )
				result = false;
			// you can only move up one square ( you can not move down as a PLAYER1 pawn. )
			else if ( differenceY > 1 || differenceY < 1 )
				result = false;

			// the move is valid
			else result = true;
		}
	}

	else //You're Player2
	{
		// and you're moving a pawn...
		if ( ch == PAWN )
		{
			// you can only move left or right one square and...
			if ( differenceX != 1 && differenceX != -1 )
				result = false;
			// you can only move up one square ( you can not move down as a PLAYER2 pawn. )
			else if ( differenceY < -1 || differenceY > -1 )
				result = false;

			// the move is valid
			else result = true;
		}
	}

	return result; // return the news
}

//Translates coordinates in order to move the appropriate piece in the char array checkerBoard
inline void CheckerBoard::translateCoordinates( Coordinates &_c )
{
	_c.from.x = ( _c.from.x * 5 ) + 3;
	_c.from.y = ( _c.from.y * 3 ) + 1;

	_c.to.x = ( _c.to.x * 5 ) + 3;
	_c.to.y = ( _c.to.y * 3 ) + 1;
}
//Translates a set of x & y coordinates.  Used in lookForKings() and moveCheckerToCapture() functions.
inline void CheckerBoard::translateCoordinates( int &_x, int &_y )
{
	_x = ( _x * 5 ) + 3;
	_y = ( _y * 3 ) + 1;
}
//Changes char at specified coordinates to the correpsonding Player's king checker character.
inline void CheckerBoard::grantKingship( Players p, int y, int x )
{
	if ( p == PLAYER1 )
		checkerBoard[ y ][ x ] = PLAYER_1_KING;
	else
		checkerBoard[ y ][ x ] = PLAYER_2_KING;
}
//Determines whether or not there is a jump available for
inline void CheckerBoard::findAvailableJumps( Coordinates *_c, Players p, Checkers ch, int *elements )
{
	int tempX = 0, tempY = 0; //temporarily holds the modified coordinates to be checked.
	if ( ch == KING )
	{
		//upper left
		if ( boundsCheck( _c[ *elements ].from.y - 1, _c[ *elements ].from.x - 1 ) ) 
		{
			tempY = _c[ *elements ].from.y - 1;
			tempX = _c[ *elements ].from.x - 1;
			//Check to see if squareStatus contains an opposing Player's checker piece at these coordinates.
			if ( squareStatus[ tempY ][ tempX ].occupation == OCCUPIED )//If the square is occupied..
				if ( squareStatus[ tempY ][ tempX ].players != p )//and it is not occupied by the current player, it must be the opposing player...
					if ( boundsCheck( ( tempY - 1 ), ( tempX - 1 ) ) )//check to see if the coordinates of the landing square are in bounds
						if ( squareStatus[ tempY - 1 ][ tempX - 1 ].occupation == UNOCCUPIED )// check to see if the landing square is unoccupied.
						{
							_c[ *elements ].to.y = tempY - 1;
							_c[ *elements ].to.x = tempX - 1;
							( *elements )++;//increment the number of elements to access the next unassigned coordinate variable.
							//Assign the "to" coordinates from the previous element to the "to" coordinates of the new element.
							_c[ *elements ].from.y = _c[ ( *elements - 1 ) ].from.y;
							_c[ *elements ].from.x = _c[ ( *elements - 1 ) ].from.x;
						}
		}

		//upper right
		if ( boundsCheck( ( _c[ *elements ].from.y - 1 ), ( _c[ *elements ].from.x + 1 ) ) )
		{
			tempY = _c[ *elements ].from.y - 1;
			tempX = _c[ *elements ].from.x + 1;
			//Check to see if squareStatus contains an opposing Player's checker piece at these coordinates.
			if ( squareStatus[ tempY ][ tempX ].occupation == OCCUPIED )//If the square is occupied..
				if ( squareStatus[ tempY ][ tempX ].players != p )//and it is not occupied by the current player, it must be the opposing player...
					if ( boundsCheck( ( tempY - 1 ), ( tempX + 1 ) ) )//check to see if the coordinates of the landing square are in bounds
						if ( squareStatus[ tempY - 1 ][ tempX + 1 ].occupation == UNOCCUPIED )// check to see if the landing square is unoccupied.
						{
							_c[ *elements ].to.y = tempY - 1;
							_c[ *elements ].to.x = tempX + 1;
							( *elements )++;//increment the number of elements to access the next unassigned coordinate variable.
							//Assign the "to" coordinates from the previous element to the "to" coordinates of the new element.
							_c[ *elements ].from.y = _c[ ( *elements - 1 ) ].from.y;
							_c[ *elements ].from.x = _c[ ( *elements - 1 ) ].from.x;
						}
		}
		
		//lower left
		if ( boundsCheck( ( _c[ *elements ].from.y + 1 ), ( _c[ *elements ].from.x - 1 ) ) )
		{
			tempY = _c[ *elements ].from.y + 1;
			tempX = _c[ *elements ].from.x - 1;
			//Check to see if squareStatus contains an opposing Player's checker piece at these coordinates.
			if ( squareStatus[ tempY ][ tempX ].occupation == OCCUPIED )//If the square is occupied..
				if ( squareStatus[ tempY ][ tempX ].players != p )//and it is not occupied by the current player, it must be the opposing player...
					if ( boundsCheck( ( tempY + 1 ), ( tempX - 1 ) ) )//check to see if the coordinates of the landing square are in bounds
						if ( squareStatus[ tempY + 1 ][ tempX - 1 ].occupation == UNOCCUPIED )// check to see if the landing square is unoccupied.
						{
							_c[ *elements ].to.y = tempY + 1;
							_c[ *elements ].to.x = tempX - 1;
							( *elements )++;//increment the number of elements to access the next unassigned coordinate variable.
							//Assign the "to" coordinates from the previous element to the "to" coordinates of the new element.
							_c[ *elements ].from.y = _c[ ( *elements - 1 ) ].from.y;
							_c[ *elements ].from.x = _c[ ( *elements - 1 ) ].from.x;
						}
		}

		//lower right
		if ( boundsCheck( ( _c[ *elements ].from.y + 1 ), ( _c[ *elements ].from.x + 1 ) ) )
		{
			tempY = _c[ *elements ].from.y + 1;
			tempX = _c[ *elements ].from.x + 1;
			//Check to see if squareStatus contains an opposing Player's checker piece at these coordinates.
			if ( squareStatus[ tempY ][ tempX ].occupation == OCCUPIED )//If the square is occupied..
				if ( squareStatus[ tempY ][ tempX ].players != p )//and it is not occupied by the current player, it must be the opposing player...
					if ( boundsCheck( ( tempY + 1 ), ( tempX + 1 ) ) )//check to see if the coordinates of the landing square are in bounds
						if ( squareStatus[ tempY + 1 ][ tempX + 1 ].occupation == UNOCCUPIED )// check to see if the landing square is unoccupied.
						{
							_c[ *elements ].to.y = tempY + 1;
							_c[ *elements ].to.x = tempX + 1;
							( *elements )++;//increment the number of elements to access the next unassigned coordinate variable.
							//No need to assign the "to" coordinates from the previous element to the "to" coordinates of the new element.
							//There are no more jumps to look for for the current piece.
						}
		}
	}

	//If the checker piece is not a king, then it is a pawn
	//If it is a Player 1 pawn, then it can only jump to the upper left or the upper right
	else if ( p == PLAYER1 )
	{
		//upper left
		if ( boundsCheck( ( _c[ *elements ].from.y - 1 ), ( _c[ *elements ].from.x - 1 ) ) )
		{
			tempY = _c[ *elements ].from.y - 1;
			tempX = _c[ *elements ].from.x - 1;
			//Check to see if squareStatus contains an opposing Player's checker piece at these coordinates.
			if ( squareStatus[ tempY ][ tempX ].occupation == OCCUPIED )//If the square is occupied..
				if ( squareStatus[ tempY ][ tempX ].players != p )//and it is not occupied by the current player, it must be the opposing player...
					if ( boundsCheck( ( tempY - 1 ), ( tempX - 1 ) ) )//check to see if the coordinates of the landing square are in bounds
						if ( squareStatus[ tempY - 1 ][ tempX - 1 ].occupation == UNOCCUPIED )// check to see if the landing square is unoccupied.
						{
							_c[ *elements ].to.y = tempY - 1;
							_c[ *elements ].to.x = tempX - 1;
							( *elements )++; //increment the number of elements to access the next unassigned coordinate variable.
							//Assign the "to" coordinates from the previous element to the "to" coordinates of the new element.
							_c[ *elements ].from.y = _c[ ( *elements ) - 1 ].from.y;
							_c[ *elements ].from.x = _c[ ( *elements ) - 1 ].from.x;
						}
		}

		//upper right
		if ( boundsCheck( ( _c[ *elements ].from.y - 1 ), ( _c[ *elements ].from.x + 1 ) ) )
		{
			tempY = _c[ *elements ].from.y - 1;
			tempX = _c[ *elements ].from.x + 1;
			//Check to see if squareStatus contains an opposing Player's checker piece at these coordinates.
			if ( squareStatus[ tempY ][ tempX ].occupation == OCCUPIED )//If the square is occupied..
				if ( squareStatus[ tempY ][ tempX ].players != p )//and it is not occupied by the current player, it must be the opposing player...
					if ( boundsCheck( ( tempY - 1 ), ( tempX + 1 ) ) ) //check to see if the coordinates of the landing square are in bounds
						if ( squareStatus[ tempY - 1 ][ tempX + 1 ].occupation == UNOCCUPIED )// check to see if the landing square is unoccupied.
						{
							_c[ *elements ].to.y = tempY - 1;
							_c[ *elements ].to.x = tempX + 1;
							( *elements )++;//increment the number of elements to access the next unassigned coordinate variable.
							//No need to assign the "to" coordinates from the previous element to the "to" coordinates of the new element.
							//There are no more jumps to look for for the current piece.
						}
		}
	}

	//If the checker piece is not a king, then it is a pawn
	//If it is a Player 2 pawn, then it can only jump to the lower left or the lower right
	else if ( p == PLAYER2 )
	{
		//lower left
		if ( boundsCheck( ( _c[ *elements ].from.y + 1 ), ( _c[ *elements ].from.x - 1 ) ) )
		{
			tempY = _c[ *elements ].from.y + 1;
			tempX = _c[ *elements ].from.x - 1;
			//Check to see if squareStatus contains an opposing Player's checker piece at these coordinates.
			if ( squareStatus[ tempY ][ tempX ].occupation == OCCUPIED )//If the square is occupied..
				if ( squareStatus[ tempY ][ tempX ].players != p )//and it is not occupied by the current player, it must be the opposing player...
					if ( boundsCheck( ( tempY + 1 ), ( tempX - 1 ) ) ) //check to see if the coordinates of the landing square are in bounds
						if ( squareStatus[ tempY + 1 ][ tempX - 1 ].occupation == UNOCCUPIED )// check to see if the landing square is unoccupied.
						{
							_c[ *elements ].to.y = tempY + 1;
							_c[ *elements ].to.x = tempX - 1;
							( *elements )++;
							//Assign the "to" coordinates from the previous element to the "to" coordinates of the new element.
							_c[ *elements ].from.y = _c[ ( *elements ) - 1 ].from.y;
							_c[ *elements ].from.x = _c[ ( *elements ) - 1 ].from.x;
						}
		}

		//lower right
		if ( boundsCheck( ( _c[ *elements ].from.y + 1 ), ( _c[ *elements ].from.x + 1 ) ) )
		{
			tempY = _c[ *elements ].from.y + 1;
			tempX = _c[ *elements ].from.x + 1;
			//Check to see if squareStatus contains an opposing Player's checker piece at these coordinates.
			if ( squareStatus[ tempY ][ tempX ].occupation == OCCUPIED )//If the square is occupied..
				if ( squareStatus[ tempY ][ tempX ].players != p )//and it is not occupied by the current player, it must be the opposing player...
					if ( boundsCheck( ( tempY + 1 ), ( tempX + 1 ) ) ) //check to see if the coordinates of the landing square are in bounds
						if ( squareStatus[ tempY + 1 ][ tempX + 1 ].occupation == UNOCCUPIED )// check to see if the landing square is unoccupied.
						{
							_c[ *elements ].to.y = tempY + 1;
							_c[ *elements ].to.x = tempX + 1;
							( *elements )++; //increment the number of elements to access the next unassigned coordinate variable.
							//No need to assign the "to" coordinates from the previous element to the "to" coordinates of the new element.
							//There are no more jumps to look for for the current piece.
						}
		}
	}
}
//Moves a captured piece to the appropriate capture pile.
inline void CheckerBoard::moveCheckerToCapture( int x, int y, Players p )
{
	char temp;
	int offset; //will be used to calculate where the captured piece goes in the capture array.

	squareStatus[ y ][ x ].occupation = UNOCCUPIED;
	translateCoordinates( x, y );

	//Move character out of checkerBoard array.
	temp = checkerBoard[ y ][ x ];
	checkerBoard[ y ][ x ] = ' ';

	//Move the character into the appropriate capture pile.
	if ( p == PLAYER1 )
	{
		/*The offset equals the number of captured pieces multiplied by 2 plus one
		 * this will put the pieces in the capture pile with a space in between.
		 * the ( + 1 ) is used to compensate for the border ( | ) around the capture pile */
		offset = ( p1PiecesCaptured * 2 ) + 1;
		player2Capture[ 1 ][ offset ] = temp;
		++p1PiecesCaptured;
	}

	else
	{
		offset = ( p2PiecesCaptured * 2 ) + 1;
		player1Capture[ 1 ][ offset ] = temp;
		++p2PiecesCaptured;
	}
}

