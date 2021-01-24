#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Body.h"

#include "p2Point.h"
#include "Animation.h"

#define PLAYER_SPEED 10.0f


struct SDL_Rect;
struct SDL_Texture;

class Player : public Body
{
public:

	Player(fPoint position, float mass);
	virtual ~Player();

	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

	SDL_Rect GetRect() { return rect; };

private:

	SDL_Rect rect = { 0, 0, 0, 0 };

	SDL_Texture* texture = nullptr;
	Animation* currentAnim = nullptr;
	float angleDir = 0.0f;

	Animation engineOnAnim;
	Animation engineOffAnim;

	uint motorFx;

};

#endif // _PLAYER_H_