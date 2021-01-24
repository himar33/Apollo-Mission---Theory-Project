#include "Player.h"
#include "Audio.h"
#include "Render.h"
#include "Input.h"
#include "App.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Log.h"
#include "Defs.h"
#include "math.h"


Player::Player() : Module()
{
	name.Create("player");

	engineOnAnim.PushBack({ 18,0,17,48 });
	engineOnAnim.PushBack({ 36,0,18,48 });
	engineOnAnim.PushBack({ 55,0,17,48 });
	engineOnAnim.loop = true;
	engineOnAnim.speed = 0.2f;

	engineOffAnim.PushBack({ 0,0,17,48 });
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
	velocity = 2;
	currentAnim = &engineOffAnim;

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

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		float angleInRadian = angleDir / 180 * M_PI;
		position.x += sin(angleInRadian) * velocity;
		position.y -= cos(angleInRadian) * velocity;
		currentAnim = &engineOnAnim;
	}
	else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		float angleInRadian = angleDir / 180 * M_PI;
		position.x -= sin(angleInRadian) * velocity;
		position.y += cos(angleInRadian) * velocity;
		currentAnim = &engineOnAnim;
	}
	else
	{
		currentAnim = &engineOffAnim;
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		angleDir -= 5;
		currentAnim = &engineOffAnim;
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		angleDir += 5;
		currentAnim = &engineOffAnim;
	}

	app->render->camera.x = (position.x - app->render->camera.w/2) * -1;
	app->render->camera.y = (position.y - app->render->camera.h / 2) * -1;

	return true;
}

bool Player::PostUpdate()
{
	int offSetX = currentAnim->GetCurrentFrame().w / 2;
	int offSetY = currentAnim->GetCurrentFrame().h / 2;
	app->render->DrawTexture(texture, position.x, position.y, &currentAnim->GetCurrentFrame(), 1.0f, angleDir, offSetX, offSetY);
	currentAnim->Update();

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

