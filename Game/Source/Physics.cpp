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
	for (ListItem<Player*>* item = players.start; item != NULL; item = item->next)
	{
		AddWorldForces(item->data, dt);
		NewtonSecondLaw(item->data, dt);
		VerletIntegrator(item->data, dt);
		item->data->ResetForces();
		item->data->ResetTorques();
	}

	return true;
}


// Called before quitting
bool Physics::CleanUp()
{
	LOG("Unloading Physics Module");


	return true;
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
		cY = body->GetPosition().y;
	}
	else if (planet->GetPosition().y > body->GetPosition().y + body->GetRect().h)
	{
		cY = body->GetPosition().y + body->GetRect().h;
	}
	else
	{
		cY = planet->GetPosition().y;
	}

	double distance = distanceSquared(planet->GetPosition().x, planet->GetPosition().y, cX, cY);
	float rad = planet->GetRadius() * KM_TO_PX * planet->GetRadius() * KM_TO_PX;
	//If the closest point is inside the circle
	if (distanceSquared(planet->GetPosition().x, planet->GetPosition().y, cX, cY) < planet->GetRadius()*KM_TO_PX * planet->GetRadius()*KM_TO_PX)
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


// Add World Forces to the player
void Physics::AddWorldForces(Player* player, float dt)
{
	for (ListItem<Planet*>* planet = planets.start; planet != NULL; planet = planet->next)
	{
		fPoint force = CalculateGravity(player, planet->data, dt);
		player->AddForce(force);
	}
}
// Apply Newton's Second Law
void Physics::NewtonSecondLaw(Player* player, float dt)
{
	fPoint acceleration;
	acceleration.x = player->GetTotalForces().x / player->GetMass();
	acceleration.y = player->GetTotalForces().y / player->GetMass();
	player->SetAcceleration(acceleration);

	float angularAcceleration = player->GetTotalTorques() / player->GetInertia();
	player->SetAngularAcceleration(angularAcceleration);
}
// Verlet Integrator
void Physics::VerletIntegrator(Player* player, float dt)
{
	float posX = player->GetPosition().x + player->GetVelocity().x * dt + 0.5f * player->GetAcceleration().x * dt * dt;
	float posY = player->GetPosition().y + player->GetVelocity().y * dt + 0.5f * player->GetAcceleration().y * dt * dt;
	float velX = player->GetVelocity().x + player->GetAcceleration().x * dt;
	float velY = player->GetVelocity().y + player->GetAcceleration().y * dt;
	player->SetPosition({ posX, posY });
	player->SetVelocity({ velX, velY });


	player->SetAgularPosition(player->GetAngularPosition() + player->GetAngularVelocity() * dt + 0.5f * player->GetAngularAcceleration() * dt * dt);
	player->SetAngularVelocity(player->GetAngularVelocity() + player->GetAngularAcceleration() * dt);
}


fPoint Physics::CalculateGravity(Player* player, Planet* planet, float dt)
{
	float distance = CalculateDistance(player->GetPosition(), planet->GetPosition()) * PX_TO_KM;
	fPoint gravityForce = { 0.0f, 0.0f };

	if (distance >= planet->GetRadius())
	{
		float gravityModule = CalculateGravityRelativeToDistance(planet, distance);

		fVector direction = { player->GetPosition().x - planet->GetPosition().x, player->GetPosition().y - planet->GetPosition().y };
		direction.Normalize();
		

 		if (player->GetPosition().x > planet->GetPosition().x &&
			player->GetPosition().y < planet->GetPosition().y)
		{
			fVector xAxis = { 0.0, 1.0f };
			float cosAng = direction.dot(xAxis) / direction.Length() * xAxis.Length();
			float angle = acos(cosAng);
			gravityForce = { - (float)sin(angle) * gravityModule, - (float)cos(angle) * gravityModule };
		}
		else if(player->GetPosition().x < planet->GetPosition().x &&
			player->GetPosition().y < planet->GetPosition().y)
		{
			fVector xAxis = { 0.0f, -1.0f };
			float cosAng = direction.dot(xAxis) / direction.Length() * xAxis.Length();
			float angle = acos(cosAng);
			gravityForce = { (float)sin(angle) * gravityModule, - (float)cos(angle) * gravityModule };
		}
		else if (player->GetPosition().x < planet->GetPosition().x  &&
			player->GetPosition().y > planet->GetPosition().y)
		{
			fVector xAxis = { 0.0f, -1.0f };
			float cosAng = direction.dot(xAxis) / direction.Length() * xAxis.Length();
			float angle = acos(cosAng);
			gravityForce = { (float)sin(angle) * gravityModule, (float)cos(angle) * gravityModule };
		}
		else if (player->GetPosition().x > planet->GetPosition().x &&
			player->GetPosition().y > planet->GetPosition().y)
		{
			fVector xAxis = { 0.0f, 1.0f };
			float cosAng = direction.dot(xAxis) / direction.Length() * xAxis.Length();
			float angle = acos(cosAng);
			gravityForce = { - (float)sin(angle) * gravityModule, (float)cos(angle) * gravityModule };
		}
	}

	gravityForce.x *= PX_TO_KM;
	gravityForce.y *= PX_TO_KM;

	return gravityForce;
}
float Physics::CalculateGravityRelativeToDistance(Planet* planet, float distance)
{
	float g = planet->GetGravity() / pow(distance / (planet->GetRadius()), 2);

	return g;
}
float Physics::CalculateDistance(fPoint pos1, fPoint pos2)
{
	float res = sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2));

	return res;
}