#include "Player.h"
#include "Audio.h"
#include "Render.h"
#include "Input.h"
#include "App.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Textures.h"
#include "Animation.h"

#include "Log.h"
#include "Defs.h"
#include "math.h"


Player::Player(fPoint position, float mass) : Body(position, mass)
{
	name.Create("player");

	engineOnAnim.PushBack({ 18,0,17,48 });
	engineOnAnim.PushBack({ 36,0,18,48 });
	engineOnAnim.PushBack({ 55,0,17,48 });
	engineOnAnim.loop = true;
	engineOnAnim.speed = 0.2f;

	engineOffAnim.PushBack({ 0,0,17,48 });
}

Player::~Player()
{}

bool Player::Start() 
{
	// Load textures and FX
	texture = app->tex->Load("Assets/Textures/rocket.png");

	SetPosition({ 0.0f, 0.0f });
	currentAnim = &engineOffAnim;

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
		SetPosition({ GetPosition().x + (float)sin(angleInRadian) * PLAYER_SPEED, GetPosition().y - (float)cos(angleInRadian) * PLAYER_SPEED });
		currentAnim = &engineOnAnim;
	}
	else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		float angleInRadian = angleDir / 180 * M_PI;
		SetPosition({ GetPosition().x - (float)sin(angleInRadian) * PLAYER_SPEED, GetPosition().y + (float)cos(angleInRadian) * PLAYER_SPEED });
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

	app->render->camera.x = (GetPosition().x - app->render->camera.w/2) * -1;
	app->render->camera.y = (GetPosition().y - app->render->camera.h / 2) * -1;

	return true;
}

bool Player::PostUpdate()
{
	int offSetX = currentAnim->GetCurrentFrame().w / 2;
	int offSetY = currentAnim->GetCurrentFrame().h / 2;
	app->render->DrawTexture(texture, GetPosition().x, GetPosition().y, &currentAnim->GetCurrentFrame(), 1.0f, angleDir, offSetX, offSetY);
	currentAnim->Update();

	return true;
}

bool Player::CleanUp()
{
	app->tex->UnLoad(texture);

	return true;
}