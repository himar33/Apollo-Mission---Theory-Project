#ifndef __SCENE_H__
#define __SCENE_H__

#include "SceneControl.h"

#include "Animation.h"


class Player;
class Planet;
struct SDL_Texture;

class Scene : public SceneControl
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();


	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	Player* player = nullptr;
	Planet* earth = nullptr;

private:

	Planet* CreatePlanet(float gravity, float radius, fPoint position, float mass);
	void DeletePlanet(Planet* planet);
	Player* CreatePlayer(fPoint position, float mass, SDL_Rect rect);
	void DeletePlayer(Player* player);

private:

	SDL_Texture* earthTex = nullptr;
	Animation* earthCurrentAnim = nullptr;
	Animation earthAnim;

	SDL_Texture* moonTex = nullptr;
	Animation* moonCurrentAnim = nullptr;
	Animation moonAnim;
	Planet* moon = nullptr;

	SDL_Texture* bgTex = nullptr;
};

#endif // __SCENE_H__