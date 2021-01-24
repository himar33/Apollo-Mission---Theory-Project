#ifndef __BODY_H__
#define __BODY_H__

#include "p2Point.h"
#include "Animation.h"


class Body
{
public:

	Body(fPoint position, float mass) : x(position), mass(mass) {}

	// ----- BODY GETTERS ----- //
	fPoint GetPosition() const;
	fPoint GetVelocity() const;
	fPoint GetAcceleration() const;
	float GetAngularPosition() const;
	float GetAngularVelocity() const;
	float GetAngularAcceleration() const;
	float GetMass() const;
	// ------------------------ //

	// ----- BODY SETTERS ----- //
	void SetPosition(fPoint _x);
	void SetVelocity(fPoint _v);
	void SetAcceleration(fPoint _a);
	void StopLinearMovement();
	void SetAgularPosition(float ax);
	void SetAngularVelocity(float av);
	void SetAngularAcceleration(float aa);
	void StopAngularMovement();
	void SetMass(float _mass);
	// ------------------------ //

private:

	// Linear movement properties
	fPoint x = { 0.0f, 0.0f };
	fPoint v = { 0.0f, 0.0f };
	fPoint a = { 0.0f, 0.0f };

	// Angular movement properties
	float angularPosition = 0;
	float angularVelocity = 0;
	float angularAcceleration = 0;

	float mass = 1.0f;

	Animation* animation = nullptr;
};

#endif // !__BODY_H__