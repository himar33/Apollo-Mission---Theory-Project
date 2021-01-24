#include "Body.h"

#include "Animation.h"


// ----- LINEAR MOVEMENT GETTERS ----- //
// Position Getter
fPoint Body::GetPosition() const
{
	return x;
}
// Velocity Getter
fPoint Body::GetVelocity() const
{
	return v;
}
// Acceleration Getter
fPoint Body::GetAcceleration() const
{
	return a;
}
// ----------------------------------- //


// ----- ANGULAR MOVEMENT GETTERS ----- //
// Angular Position Getter
float Body::GetAngularPosition() const
{
	return angularPosition;
}
// Angular Velocity Getter
float Body::GetAngularVelocity() const
{
	return angularVelocity;
}
// Angular Acceleration Getter
float Body::GetAngularAcceleration() const
{
	return angularAcceleration;
}
// ------------------------------------ //


// ----- LINEAR MOVEMENT SETTERS ----- //
// Position Setter
void Body::SetPosition(fPoint _x)
{
	x = _x;
}
// Velocity Setter
void Body::SetVelocity(fPoint _v)
{
	v = _v;
}
// Acceleration Setter
void Body::SetAcceleration(fPoint _a)
{
	a = _a;
}
// Stop linear velocity and acceleration
void Body::StopLinearMovement()
{
	v = { 0.0f, 0.0f };
	a = { 0.0f, 0.0f };
}
// ----------------------------------- //


// ----- ANGULAR MOVEMENT SETTERS ----- //
// Angular Position Setter
void Body::SetAgularPosition(float ax)
{
	angularPosition = ax;
}
// Angular Velocity Setter
void Body::SetAngularVelocity(float av)
{
	angularVelocity = av;
}
// Angular Acceleration Setter
void Body::SetAngularAcceleration(float aa)
{
	angularAcceleration = aa;
}
// Stop angular velocity and acceleration
void Body::StopAngularMovement()
{
	angularVelocity = 0.0f;
	angularAcceleration = 0.0f;
}
// ------------------------------------ //


// ----- MASS METHODS ----- //
// Mass Getter
float Body::GetMass() const
{
	return mass;
}
// Mass Setter
void Body::SetMass(float _mass)
{
	mass = _mass;
}
// ------------------------ //