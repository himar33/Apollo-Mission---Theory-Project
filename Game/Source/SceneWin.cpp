#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "SceneWin.h"
#include "SceneManager.h"

#include <SDL_mixer\include\SDL_mixer.h>

#include "Defs.h"
#include "Log.h"

SceneWin::SceneWin()
{
	active = true;
	name.Create("sceneWin");
}

SceneWin::~SceneWin()
{
}

bool SceneWin::Awake()
{
	LOG("Loading SceneWin");
	bool ret = true;
	return ret;
}

bool SceneWin::Start()
{
	winFx = app->audio->LoadFx("Assets/Audio/Fx/win.wav");
	img = app->tex->Load("Assets/Textures/win_text.png");
	bgText = app->tex->Load("Assets/Textures/win_bg.png");
	trophyText = app->tex->Load("Assets/Textures/trophy.png");

	app->audio->PlayFx(1, winFx, 0);

	return true;
}

bool SceneWin::PreUpdate()
{
	return true;
}

bool SceneWin::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		return false;
	}

	return true;
}

bool SceneWin::PostUpdate()
{
	bool ret = true;

	app->render->DrawTexture(bgText, 0, 0);
	app->render->DrawTexture(img, 0, 0);
	app->render->DrawTexture(trophyText, 400, 300);

	return ret;
}

bool SceneWin::CleanUp()
{
	if (!active)
		return true;

	LOG("Freeing scene");
	Mix_HaltMusic();

	active = false;
	return true;
}