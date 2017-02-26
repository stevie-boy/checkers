//CheckerPlayer.cpp

#include "CheckerPlayer.h"

CheckerPlayer::CheckerPlayer()
{
	playerName = "";
	checkers = 12;
}

CheckerPlayer::CheckerPlayer( Players p, string _name )
: playerID( p ), playerName( _name ), checkers( 12 )
{
}

void CheckerPlayer::setPlayerID( int id )
{
	playerID = ( id >= 2 )? PLAYER2: PLAYER1;
}

void CheckerPlayer::setPlayerID( Players p )
{
	playerID = p;
}

Players CheckerPlayer::getPlayerID() const
{
	return playerID;
}

void CheckerPlayer::setPlayerName( string name )
{
	playerName = name;
}

string CheckerPlayer::getPlayerName()const
{
	return playerName;
}

void CheckerPlayer::checkerCaptured()
{
	checkers -= 1;
}

int CheckerPlayer::checkersRemaining()
{
	return checkers;
}