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

bool Physics::CheckCollision(Planet* planet, Player* body)
{

	//Closest point on collision box
	int cX, cY;

	//Find closest x offset
	if (planet->GetPosition().x < body->GetPosition().x)
	{
		cX = body->GetPosition().x;
	}
	else if (planet->GetPosition().x > body->GetPosition().x + body->GetRect().w)
	{
		cX = body->GetPosition().x + body->GetRect().w;
	}
	else
	{
		cX = planet->GetPosition().x;
	}

	////Find closest y offset
	if (planet->GetPosition().y < body->GetPosition().y)
	{
		cY = body->GetPosition().x;
	}
	else if (planet->GetPosition().y > body->GetPosition().x + body->GetRect().h)
	{
		cY = body->GetPosition().y + body->GetRect().h;
	}
	else
	{
		cY = planet->GetPosition().y;
	}

	//If the closest point is inside the circle
	if (distanceSquared(planet->GetPosition().x, planet->GetPosition().y, cX, cY) < planet->GetRadius() * planet->GetRadius())
	{
		//This box and the circle have collided
		return true;
	}
	//If the shapes have not collided
	return false;
}

double Physics::distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
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