#ifndef __BODY_H__

#include "p2Point.h"


class Body
{
public:

	// ----- BODY GETTERS ----- //
	fPoint GetPosition() { return x; };
	fPoint GetVelocity() { return v; };
	fPoint GetAcceleration() { return a; };
	float GetAngularPosition() { return angularPosition; };
	float GetAngularVelocity() { return angularVelocity; };
	float GetAngularAcceleration() { return angularAcceleration; };
	// ------------------------ //

	// ----- BODY SETTERS ----- //
	void SetPosition(fPoint _x) { x = _x; };
	void SetVelocity(fPoint _v) { v = _v;};
	void SetAcceleration(fPoint _a) { a = _a; };
	void SetAgularPosition(float ax) { angularPosition = ax; };
	void SetAngularVelocity(float av) { angularVelocity = av; };
	void SetAngularAcceleration(float aa) { angularAcceleration = aa; };
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
};


#endif // !__BODY_H__