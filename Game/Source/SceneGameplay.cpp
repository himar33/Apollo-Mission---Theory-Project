#include "SceneGameplay.h"

#include "EntityManager.h"

SceneGameplay::SceneGameplay()
{
}

SceneGameplay::~SceneGameplay()
{}

bool SceneGameplay::Load(Textures* tex)
{

	// Initialize player
	player = new Player();
	player->position = iPoint(200, 400);

    return false;
}

inline bool CheckCollision(SDL_Rect rec1, SDL_Rect rec2)
{
	if ((rec1.x < (rec2.x + rec2.w) && (rec1.x + rec1.w) > rec2.x) &&
		(rec1.y < (rec2.y + rec2.h) && (rec1.y + rec1.h) > rec2.y)) return true;
	else return false;
}

bool SceneGameplay::Update(Input *input, float dt)
{
	// Collision detection: map vs player
	iPoint tempPlayerPosition = player->position;

	player->Update(input, dt);

	return true;
}

bool SceneGameplay::Draw(Render* render)
{

	player->Draw(render);

    return false;
}

bool SceneGameplay::Unload()
{
	// TODO: Unload all resources

    return false;
}
