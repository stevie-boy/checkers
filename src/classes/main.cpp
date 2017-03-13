
#include <vector>
#include <iostream>
#include <cctype> //provides isalpha function.

using namespace std;

#include <stdlib.h>
using ::atoi;

#include "CheckerBoard.h"
#include "CheckerPlayer.h"


void clear_istream(istream& isIn); // Clears istream object
void switchPlayer();
Coordinates enterCoordinates();
inline void redrawBoard();
inline bool checkForJumps();
inline void enter_player_names();
inline void displayMessage();

//Global variables
CheckerBoard cBoard;
vector< CheckerPlayer >checkerPlayers(2);
int currentPlayer = 0, waitingPlayer = 1; //Represents the current player and the other player.

int main()
{
	char ans = 'y';

	checkerPlayers[0].setPlayerID( 1 );
	checkerPlayers[1].setPlayerID( 2 );

	displayMessage();
	cin.get();
	cBoard.clearScreen();

	enter_player_names(); //Allow the players to enter their names.

	Coordinates coord;
	cBoard.initializeBoard();
	CheckerBoard::drawBoard( checkerPlayers[0].getPlayerName(), checkerPlayers[1].getPlayerName() );
	cout << checkerPlayers[ currentPlayer ].getPlayerName() << "'s turn\n";

	do
	{
		//If there are jumps, the Player must take them,
		//then we check for kings.
		if ( checkForJumps() )
			cBoard.lookForKings( checkerPlayers[ currentPlayer ].getPlayerID() );

		else
		{
			coord = enterCoordinates();
			cBoard.moveChecker( coord );
			cBoard.lookForKings( checkerPlayers[ currentPlayer ].getPlayerID() );	
		}
		//The Player is switched.
		switchPlayer();
		redrawBoard();

	//continue the game as long as someone has checkers remaining.
	}while ( checkerPlayers[ 0 ].checkersRemaining() && checkerPlayers[ 1 ].checkersRemaining() );
}

inline void enter_player_names()
{
	string name;

	//Enter player 1 name.
	cout << "\n\n\tEnter a name for Player 1.\n\t===> ";
	cin >> name;
	checkerPlayers[0].setPlayerName( name );
	clear_istream( cin );
	cBoard.clearScreen();
	
	//Enter player 2 name.
	cout << "\n\n\tEnter a name for Player 2.\n\t===> ";
	cin >> name;
	checkerPlayers[1].setPlayerName( name );
	clear_istream( cin );
	cBoard.clearScreen();
}

void clear_istream(istream& isIn)        // Clears istream object
{
   streambuf*  sbpThis;
   char        szTempBuf[20];
   int         nCount;
    
   isIn.clear();                 // Clear error flags
   sbpThis = isIn.rdbuf();       // Get streambuf pointer
   nCount = sbpThis->in_avail(); // Number of characters in buffer
   while (nCount)                // Extract them to szTempBuf
   {
		if  (nCount > 20)
		{
			sbpThis->sgetn(szTempBuf, 20);
			nCount -= 20;
		}
   
		else
		{
			sbpThis->sgetn(szTempBuf, nCount);
			nCount = 0;
		}
   }
}

//Switches the value of currentPlayer and waitingPlayer from 0 - 1 and 1 - 0.  These ints are used as the index for the
//checkerPlayer vector and activates the player whose turn it is and identifies the waiting player.
void switchPlayer()
{
	if ( currentPlayer == 1 )
	{
		currentPlayer = 0;
		waitingPlayer = 1;
	}
	else 
	{
		currentPlayer = 1;
		waitingPlayer = 0;
	}
}

Coordinates enterCoordinates()
{
	Coordinates coord = { 0, 0 };
	bool result = true;
	char c = 'y';
	char coordinates[3];

	if ( c == 'y' || c == 'Y' )
	{
		do
		{
			//From
			cout << "\nEnter the coordinates of the piece you would like to move.\nEnter x coordinate===>  ";
	
			cin.getline( coordinates, 2 );
			coord.from.x = ::atoi( coordinates );
			clear_istream( cin );

			cout << "Enter y coordinate===>  ";
			cin.getline( coordinates, 2 );
			clear_istream( cin );
			coord.from.y = ::atoi( coordinates );

			redrawBoard();
				
			//To
			cout << "\nEnter the coordinates of the square to which you would like to move.\nEnter x coordinate===>  ";

			cin.getline( coordinates, 2 );
			clear_istream( cin );
			coord.to.x = ::atoi( coordinates );

			cout << "Enter y coordinate===>  ";
			cin.getline( coordinates, 2 );
			clear_istream( cin );
			coord.to.y = ::atoi( coordinates );

			result = cBoard.validateCoordinates( coord, checkerPlayers[ currentPlayer ].getPlayerID() );

			if ( !result )
			{
				cout << "\nInvalid coordinates.";
				cin.get();
				redrawBoard();
			}
		}while( !result );// while result is false
	}
	return coord;
}
//Clears the screen then draws the board
inline void redrawBoard()
{
	CheckerBoard::clearScreen();
	CheckerBoard::drawBoard( checkerPlayers[0].getPlayerName(), checkerPlayers[1].getPlayerName() );
	cout << checkerPlayers[ currentPlayer ].getPlayerName() << "'s turn\n";
}
//Checks for available jumps
inline bool checkForJumps()
{
	bool successful = false; //loop continuation variable.
	int numElements = 0; //contains the number of elements in the array
	int choice;  //Represents the choice made by the player
	char chc[ 3 ]; //used to get the choice as a char string in order to validate it.
	Players current = checkerPlayers[ currentPlayer ].getPlayerID(); //Current player
	Coordinates coord;

	//Will access the dynamically created array of Coordinate's elements created in lookForJumps
	Coordinates *cPtr;
	cPtr = cBoard.lookForJumps( current, &numElements );

	//If the pointer equals zero, then there are no jumps to take
	if ( cPtr == 0 )
		return false;

	else
	{
		do
		{
			cout << "\nThere are jumps that can be made.  You must choose one set of jump coordinates."
				 << "\n\tFROM ( x, y )\tTO ( x, y )";
			//Loop to printout the coordinates of the jumps.
			for ( int i = 0; i < numElements; ++i )
			{
				cout << endl << ( i + 1 ) << ":\t   " << "( " << cPtr[ i ].from.x << ", " << cPtr[ i ].from.y << " )"
					 << "\t  ( " << cPtr[ i ].to.x << ", " << cPtr[ i ].to.y << " )";
			}

			cout << "\n\nEnter your choice.\n===>  ";
			cin.getline( chc, 2 );
			clear_istream( cin );
			choice = ::atoi( chc );

			if ( choice <= 0 || choice > numElements )
			{	
				cout << "\nPlease choose a number between 1 and " << numElements
					 << "\nPress Enter to continue.";
				cin.get(); //Pauses execution so the player can see the reprimand.
				clear_istream( cin );//clear the istream object in case someone's been playing with the keyboard.
				redrawBoard();
				successful = false;
			}

			else 
			{
				//Assign the value of the chosen coordinates to a new Coordinates object so we can delete and then reassign cPtr.
				//This is necessary in order to get the coordinates of the piece that made the jump so we can call the
				//subsequentJumps function.
				coord = cPtr[ choice - 1 ];
				delete[] cPtr;
				cBoard.performJump( coord );
				//Take a checker away from the opposing player
				checkerPlayers[ waitingPlayer ].checkerCaptured();
				successful = true;
			}
		}while ( !successful );
	}

	redrawBoard();
	//Check for jumps for the piece that just jumped.
	cPtr = cBoard.subsequentJumps( coord, current, &numElements );
	
	while ( cPtr != 0 )
	{
		//This loop executes until a valid choice is made
		do
		{
			cout << "\nThere is another jump that can be made.\nYou must choose one set of jump coordinates."
			     << "\n\tFROM ( x, y )\tTO ( x, y )";
			//Loop to printout the coordinates of the jumps.
			for ( int i = 0; i < numElements; ++i )
			{
				cout << endl << ( i + 1 ) << ":\t   " << "( " << cPtr[ i ].from.x << ", " << cPtr[ i ].from.y << " )"
					 << "\t  ( " << cPtr[ i ].to.x << ", " << cPtr[ i ].to.y << " )";
			}
			
			cout << "\n\nEnter your choice.\n===>  ";
			cin.getline( chc, 2 );
			clear_istream( cin );
			choice = ::atoi( chc );

			if ( choice <= 0 || choice > numElements )
			{	
				cout << "\nPlease choose a number between 1 and " << numElements
					 << "\nPress Enter to continue.";
				cin.get(); //Pauses execution so the player can see the reprimand.
				clear_istream( cin );//clear the istream object in case someone's been playing with the keyboard.
				redrawBoard();
				successful = false;
			}
	
			else 
			{
				coord = cPtr[ choice - 1 ];
				cBoard.performJump( cPtr[ choice - 1 ] );
				//Take away a checker from the opposing player
				checkerPlayers[ waitingPlayer ].checkerCaptured();
				successful = true;
				delete[] cPtr;
			}

		}while ( !successful );

		redrawBoard();
		//Check for jumps for the piece that just jumped.
		cPtr = cBoard.subsequentJumps( coord, current, &numElements );
	}// end while
		
	delete[] cPtr;
	return true; //We've taken a jump
}

void displayMessage()
	{
		cout << "			    Welcome to C++ Checkers!!!" << endl;
		cout << endl;
		cout << endl;
		cout << "	  Welcome to C++ Checkers, the rules are the same but the " << endl;
		cout <<	"    gameplay is a little different.  This is an exciting time " << endl;
		cout <<	"    because my class is able to offer you such an exclusive game." << endl;
		cout <<	"    This probably has been done before, but we can proudly say this" << endl;
		cout <<	"    is an experience you will not forget!" << endl;
		cout << endl;
		cout << "	  Alright let's get started, first the game is a little different" << endl;
		cout <<	"    as I mentioned above.  The game is based on cordinates, that both" << endl;
		cout <<	"    players will be using.  The cordinates will remain the same throughout" << endl;
		cout <<	"    the entire game.  Player one will be the first to move and player one's" << endl;
		cout << "    will be the ones on the top, and player two will move second and this" << endl;
		cout << "    player's pieces will be on the bottom.  With our ability to error check" << endl;
		cout << "    both players will not be able to move in a direction that is invalid to" << endl;
		cout << "    that player.  Like ordinary checkers there can be only one winner and no" << endl;
		cout << "    ties.  The players are able to play until one player wins.  The players" << endl;
		cout << "    can only move on the black squares so choose cordinates that are within" << endl;
		cout << "    the squares.  With that said we are sure you will have fun with our game!" << endl;
		cout << endl;
		cout << endl;
		cout << "			 Thank You For Playing Our Game!!!" << endl;
		cout << endl;
	}