#include "App.h"

#include "SceneLose.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Player.h"
#include "HUD.h"
#include "Physics.h"
#include "SceneManager.h"
#include "Animation.h"
#include "Planet.h"


#include "Defs.h"
#include "Log.h"

SceneLose::SceneLose() : SceneControl()
{
	active = true;
	name.Create("scene_lose");

	for (int i = 0; i < 12; i++)
	{
		expAnim.PushBack({ i * 128,0,128,128 });
	}
	expAnim.loop = false;
	expAnim.speed = 0.2f;

}

// Destructor
SceneLose::~SceneLose()
{}

// Called before render is available
bool SceneLose::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneLose::Start()
{

	expTex = app->tex->Load("Assets/Textures/explosion.png");
	bgTex = app->tex->Load("Assets/Textures/lose_bg.png");
	textTex = app->tex->Load("Assets/Textures/lose_text.png");

	loseFx = app->audio->LoadFx("Assets/Audio/Fx/lose.wav");
	app->audio->PlayFx(1, loseFx, 0);

	currentAnim = &expAnim;

	return true;
}

// Called each loop iteration
bool SceneLose::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneLose::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		return false;
	}

	return true;
}

// Called each loop iteration
bool SceneLose::PostUpdate()
{
	bool ret = true;

	app->render->DrawTexture(bgTex, 0, 0);

	app->render->DrawTexture(textTex, 0, 0);

	app->render->DrawTexture(expTex, 400, 300, &currentAnim->GetCurrentFrame());
	currentAnim->Update();

	return ret;
}

// Called before quitting
bool SceneLose::CleanUp()
{
	if (!active)
		return true;


	LOG("Freeing scene");
	active = false;

	return true;
}