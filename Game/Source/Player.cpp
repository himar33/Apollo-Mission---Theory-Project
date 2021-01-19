#include "Player.h"
#include "Audio.h"
#include "Render.h"
#include "Input.h"
#include "App.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Log.h"
#include "Defs.h"


Player::Player() : Module()
{
	name.Create("player");
}

Player::Player(iPoint pPosition, float pVelocity, SDL_Texture* pTexture): Module()
{
	name.Create("player");
}

Player::~Player()
{}

bool Player::Start() 
{
	active = true;
	// Create new ship

	// Load textures and FX
	texture = app->tex->Load("Assets/Textures/rocket.png");

	position.x = 0;
	position.y = 0;

	return true;
}

bool Player::Awake(pugi::xml_node& config)
{
	LOG("Loading Player Parser");
	bool ret = true;
	
	return true;
}

bool Player::PreUpdate() 
{
	return true;
}

bool Player::Update(float dt) 
{
	return true;
}

bool Player::PostUpdate()
{
	app->render->DrawTexture(texture, position.x, position.y);
	return true;
}

bool Player::CleanUp()
{
	if (!active)
		return true;

	app->tex->UnLoad(texture);
	active = false;

	return true;
}

