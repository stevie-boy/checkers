//This file contains resources common to classes in this project.

#ifndef	COMMON_RESOURCES_H
#define COMMON_RESOURCES_H

namespace CommonResources
{
	enum Availablity { UNAVAILABLE, AVAILABLE };
	enum Occupation { OCCUPIED, UNOCCUPIED };
	enum Players { PLAYER1 = 1, PLAYER2 };
	enum Checkers { PAWN, KING };

	struct Location
	{
		int x;
		int y;
	};

	struct Coordinates
	{
		Location from;
		Location to;
	};
}// end namespace CommonResources

#endif
