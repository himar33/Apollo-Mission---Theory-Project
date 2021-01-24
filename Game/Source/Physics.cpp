#include "App.h"

#include "Physics.h"

#include "Body.h"
#include "Planet.h"
#include "Player.h"

#include "Defs.h"
#include "Log.h"


// Constructor
Physics::Physics() : Module()
{
	name.Create("physics");
}

// Destructor
Physics::~Physics()
{

}


// Called before render is available
bool Physics::Awake(pugi::xml_node& config)
{
	LOG("Awake Physics Module");
	bool ret = true;



	return ret;
}
// Called before the first frame
bool Physics::Start()
{
	LOG("Start Physics");

	return true;
}


// Called each loop iteration
bool Physics::Update(float dt)
{

	return true;
}


// Called before quitting
bool Physics::CleanUp()
{
	LOG("Unloading Physics Module");


	return true;
}


// Verlet Integrator
void Physics::VerletIntegrator(fPoint& x, fPoint& v, fPoint& a, float dt)
{
	x.x += v.x * dt + 0.5f * a.x * dt * dt;
	v.x += a.x * dt;

	x.y += v.y * dt + 0.5f * a.y * dt * dt;
	v.y += a.y * dt;
}


void Physics::AddPlanet(Planet* planet)
{
	planets.Add(planet);
}

void Physics::RemovePlanet(Planet* planet)
{
	int i = planets.Find(planet);
	planets.Del(planets.At(i));
}


void Physics::AddPlayer(Player* player)
{
	players.Add(player);
}

void Physics::RemovePlayer(Player* player)
{
	int i = players.Find(player);
	players.Del(players.At(i));
}