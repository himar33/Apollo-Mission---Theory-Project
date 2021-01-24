#include "Planet.h"

#include "p2Point.h"

// Constructor
Planet::Planet(float _gravity, float _radius, fPoint position, float mass) : Body(position, mass)
{
	gravity = _gravity;
	radius = _radius;

	StopLinearMovement();
	StopAngularMovement();
}
// Destructor
Planet::~Planet()
{

}


// Get gravity
float Planet::GetGravity() const
{
	return gravity;
}
// Get radius
float Planet::GetRadius() const
{
	return radius;
}

// Set gravity
void Planet::SetGravity(float _gravity)
{
	gravity = _gravity;
}
// Set radius
void Planet::SetRadius(float _radius)
{
	radius = _radius;
}