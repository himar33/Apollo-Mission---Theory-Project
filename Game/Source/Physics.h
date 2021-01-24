#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Module.h"

#include "p2Point.h"
#include "List.h"


#define MOON_G_FROM_EARTH (9.807f * (6371 / 384400)^2)
#define EARTH_G_FROM_MOON ()


class Player;
class Planet;

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
	void AddPlanet(Planet* planet);
	void RemovePlanet(Planet* planet);

	bool CheckCollision(Planet* planet, Player* body);
	double distanceSquared(int x1, int y1, int x2, int y2);

	void AddPlayer(Player* player);
	void RemovePlayer(Player* player);
	// --------------------------- //
	
private:

	// ----- PHYSICS METHODS ----- //
	void VerletIntegrator(fPoint& x, fPoint& v, fPoint& a, float dt);
	// --------------------------- //

public:

	// ----- PHYSICS VARIABLES ----- //
	List<Planet*> planets;
	List<Player*> players;
	// ----------------------------- //

private:

	// ----- PHYSICS VARIABLES ----- //

	// ----------------------------- //
};


#endif // !__PHYSICS_H__