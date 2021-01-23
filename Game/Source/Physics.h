#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Module.h"

#include "p2Point.h"


class Physics : public Module
{
public:

	// Constructor
	Physics();
	// Destructor
	~Physics();


	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt); // Apply current physics & integrate & solve collisions


	// Called before quitting
	bool CleanUp();


public:

	// ----- PHYSICS METHODS ----- //

	// --------------------------- //
	
private:

	// ----- PHYSICS METHODS ----- //
	void VerletIntegrator(fPoint& x, fPoint& v, fPoint& a, float dt);
	// --------------------------- //

public:

	// ----- PHYSICS VARIABLES ----- //

	// ----------------------------- //

private:

	// ----- PHYSICS VARIABLES ----- //

	// ----------------------------- //
};


#endif // !__PHYSICS_H__