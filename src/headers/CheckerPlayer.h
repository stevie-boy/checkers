//CheckerPlayer.h file

#ifndef CHECKER_PLAYER_H
#define CHECKER_PLAYER_H

#include <string>
using std::string;

#include "CommonResources.h"
using namespace CommonResources;

class CheckerPlayer
{
public:
	CheckerPlayer();
	CheckerPlayer( Players, string );
	//public funtions
	void setPlayerID( int );
	void setPlayerID( Players );
	Players getPlayerID() const;

	void setPlayerName( string );
	string getPlayerName() const;

	int checkersRemaining();
	void checkerCaptured();

private:
	Players playerID; //Holds which player this is
	string playerName; //Holds the players name.
	int checkers;
};

#endif
