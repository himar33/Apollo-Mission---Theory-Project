#ifndef __PLANET_H__
#define __PLANET_H__

#include "Body.h"


class Planet : public Body
{
public:
	// Constructor
	Planet(float _gravity, float _radius, fPoint position, float mass);
	// Destructor
	virtual ~Planet();


	// ----- PLANET GETTERS ----- //
	float GetGravity() const;
	float GetRadius() const;
	// -------------------------- //

	// ----- PLANET SETTERS ----- //
	void SetGravity(float _gravity);
	void SetRadius(float _radius);
	// -------------------------- //



private:

	// ----- PLANET VARIABLES ----- //
	float gravity;
	float radius;
	// ---------------------------- //

};



#endif // !__PLANET_H__