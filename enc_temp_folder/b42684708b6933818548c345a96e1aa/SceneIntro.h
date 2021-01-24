#ifndef __SCENEINTRO_H__
#define __SCENEINTRO_H__

#include "SceneControl.h"

#include "Animation.h"

struct SDL_Texture;

class SceneIntro : public SceneControl
{
public:
	SceneIntro();

	virtual ~SceneIntro();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

private:

	SDL_Texture* earthTex = nullptr;
	Animation* earthCurrentAnim = nullptr;
	Animation earthAnim;

	SDL_Texture* moonTex = nullptr;
	Animation* moonCurrentAnim = nullptr;
	Animation moonAnim;

	SDL_Texture* introBg = nullptr;
	SDL_Texture* introText = nullptr;
};

#endif // !__SCENEINTRO_H__
