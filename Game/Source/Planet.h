#ifndef __PLANET_H__
#define __PLANET_H__

#include "Body.h"

#include "p2Point.h"



class Planet : public Body
{
public:
	// Constructor
	Planet();
	// Destructor
	~Planet();


	// ----- PLANET GETTERS ----- //
	float GetGravity() { return gravity; };
	// -------------------------- //


private:

	// ----- PLANET VARIABLES ----- //
	float gravity;
	// ---------------------------- //

};



#endif // !__PLANET_H__