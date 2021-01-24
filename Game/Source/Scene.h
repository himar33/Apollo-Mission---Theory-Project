#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "SceneControl.h"

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

	SDL_Texture* earthTex = nullptr;
	Animation* earthCurrentAnim = nullptr;
	Animation earthAnim;

	SDL_Texture* moonTex = nullptr;
	Animation* moonCurrentAnim = nullptr;
	Animation moonAnim;

};

#endif // __SCENE_H__