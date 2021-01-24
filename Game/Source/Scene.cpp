#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Font.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
#include "HUD.h"
#include "Physics.h"
#include "SceneManager.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : SceneControl()
{
	active = true;
	name.Create("scene");

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

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	earth = CreatePlanet(9.807, 6371, { 100, 100 }, 5000);
	moon = CreatePlanet(1.62, 1737, { earth->GetPosition().x + 100 + 384400 * KM_TO_PX , 100 }, 2000);

	earthTex = app->tex->Load("Assets/Textures/earth.png");
	moonTex = app->tex->Load("Assets/Textures/moon.png");

	earthCurrentAnim = &earthAnim;
	moonCurrentAnim = &moonAnim;

	app->audio->PlayMusic("Assets/Audio/Music/ambient.wav");

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	int offSetX = earthCurrentAnim->GetCurrentFrame().w / 2;
	int offSetY = earthCurrentAnim->GetCurrentFrame().h / 2;
	app->render->DrawTexture(earthTex, earth->GetPosition().x, earth->GetPosition().y, &earthCurrentAnim->GetCurrentFrame(), 1.0f, 0.0f, offSetX, offSetY);
	earthCurrentAnim->Update();

	offSetX = moonCurrentAnim->GetCurrentFrame().w / 2;
	offSetY = moonCurrentAnim->GetCurrentFrame().h / 2;
	app->render->DrawTexture(moonTex, moon->GetPosition().x, moon->GetPosition().y, &moonCurrentAnim->GetCurrentFrame(), 1.0f, 0.0f, offSetX, offSetY);
	moonCurrentAnim->Update();

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	if (!active)
		return true;

	DeletePlanet(earth);
	DeletePlanet(moon);


	LOG("Freeing scene");
	active = false;

	return true;
}


Planet* Scene::CreatePlanet(float gravity, float radius, fPoint position, float mass)
{
	Planet* planet = new Planet(gravity, radius, position, mass);

	app->physics->AddPlanet(planet);

	return planet;
}

void Scene::DeletePlanet(Planet* planet)
{
	app->physics->RemovePlanet(planet);
	delete planet;
	planet = nullptr;
}