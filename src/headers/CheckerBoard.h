//This is the header file for the CheckerBoard class

#ifndef CHECKER_BOARD_H
#define CHECKER_BOARD_H

#include "CommonResources.h"
using namespace CommonResources;

#include <string>
using std::string;

struct SquareStatus
{
	Availablity availablity;
	Occupation occupation;
	Players players;
	Checkers checkers;
};

class CheckerBoard
{
public:
	CheckerBoard();
	static void drawBoard( string, string );
	static void clearScreen();
	void initializeBoard();
	void printSquares();
	void moveChecker( Coordinates );
	void performJump( Coordinates );

	//returns true if coordinates are valid, false otherwise
	bool validateCoordinates( Coordinates, Players );
	bool validateCoordinates( int y, int x, Players );

	void lookForKings( Players );
	Coordinates* lookForJumps( Players, int *numElements );
	Coordinates* subsequentJumps( Coordinates, Players, int *numElements );

private:
	//Functions
	inline void setCheckers();
	void moveCheckerInSquareStatus( Coordinates );

	inline bool boundsCheck( Coordinates );
	inline bool boundsCheck( int y, int x );

	inline bool checkMoveValidity( Coordinates, Players, Checkers );

	inline void translateCoordinates( Coordinates& );
	inline void translateCoordinates( int&, int& );

	inline void grantKingship( Players, int y, int x );
	inline void findAvailableJumps( Coordinates*, Players, Checkers, int* );
	inline void moveCheckerToCapture( int x, int y, Players );

	//Data members
	static char xCoordinates[49];
	static char yCoordinates[25];

	static char border[49];
	static char checkerBoard[24][44];

	static char player1Capture[3][27];
	static char player2Capture[3][27];
	
	static const char PLAYER_1_PAWN;
	static const char PLAYER_1_KING;

	static const char PLAYER_2_PAWN;
	static const char PLAYER_2_KING;

	int p1PiecesCaptured;
	int p2PiecesCaptured;

	SquareStatus squareStatus[8][8];
	Coordinates coordinates;

};

#endif