#ifndef __SCENELOSE_H__
#define __SCENELOSE_H__

#include "SceneControl.h"

#include "Animation.h"


struct SDL_Texture;

class SceneLose : public SceneControl
{
public:

	SceneLose();

	// Destructor
	virtual ~SceneLose();

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

	SDL_Texture* expTex = nullptr;
	SDL_Texture* bgTex = nullptr;
	SDL_Texture* textTex = nullptr;
	Animation expAnim;
	Animation* currentAnim = nullptr;

	uint loseFx;
};

#endif // __SCENELOSE_H__