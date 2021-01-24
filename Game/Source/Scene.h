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

private:

	Planet* CreatePlanet(float gravity, float radius, fPoint position, float mass);
	void DeletePlanet(Planet* planet);
	Player* CreatePlayer(fPoint position, float mass);
	void DeletePlayer(Player* player);

private:

	Player* player = nullptr;

	SDL_Texture* earthTex = nullptr;
	Animation* earthCurrentAnim = nullptr;
	Animation earthAnim;
	Planet* earth = nullptr;

	SDL_Texture* moonTex = nullptr;
	Animation* moonCurrentAnim = nullptr;
	Animation moonAnim;
	Planet* moon = nullptr;
};

#endif // __SCENE_H__