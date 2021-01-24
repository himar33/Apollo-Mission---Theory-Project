#include "App.h"

#include "SceneIntro.h"

#include "Textures.h"
#include "Animation.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "SceneManager.h"



#include "Defs.h"
#include "Log.h"

SceneIntro::SceneIntro() : SceneControl()
{
	active = true;
	name.Create("sceneIntro");

	for (int i = 0; i < 50; i++)
	{
		earthAnim.PushBack({ i * 300,0,300,300 });
	}
	earthAnim.loop = true;
	earthAnim.speed = 0.1f;

	for (int i = 0; i < 50; i++)
	{
		moonAnim.PushBack({ i * 75,0,75,75 });
	}
	moonAnim.loop = true;
	moonAnim.speed = 0.1f;
}

SceneIntro::~SceneIntro()
{}

bool SceneIntro::Awake()
{
	LOG("Loading Scene Intro");
	bool ret = true;

	return ret;
}

bool SceneIntro::Start()
{
	earthTex = app->tex->Load("Assets/Textures/earth.png");
	moonTex = app->tex->Load("Assets/Textures/moon.png");
	introBg = app->tex->Load("Assets/Textures/intro_bg.png");
	introText = app->tex->Load("Assets/Textures/intro_text.png");

	app->audio->PlayMusic("Assets/Audio/Music/menu.wav");

	earthCurrentAnim = &earthAnim;
	moonCurrentAnim = &moonAnim;

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	return true;
}

bool SceneIntro::PreUpdate()
{
	return true;
}


bool SceneIntro::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		TransitionToScene(SceneType::LEVEL1);
	}
	return true;
}

bool SceneIntro::PostUpdate()
{
	bool ret = true;

	app->render->DrawTexture(introBg, 0, 0);

	app->render->DrawTexture(earthTex, 100, 350, &earthCurrentAnim->GetCurrentFrame());
	earthCurrentAnim->Update();

	app->render->DrawTexture(moonTex, 700, 100, &moonCurrentAnim->GetCurrentFrame());
	moonCurrentAnim->Update();

	app->render->DrawTexture(introText, 0, 0);

	return ret;
}

bool SceneIntro::CleanUp()
{
	if (!active)
		return true;

	app->audio->StopMusic();

	app->tex->UnLoad(earthTex);
	app->tex->UnLoad(moonTex);


	LOG("Freeing scene");
	active = false;

	return true;
}