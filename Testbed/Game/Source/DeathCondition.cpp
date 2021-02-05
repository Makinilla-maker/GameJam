#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "DeathCondition.h"
#include "Scene.h"
#include "Collisions.h"
#include "EntityManager.h"
#include "Logo.h"

#include "Defs.h"
#include "Log.h"

DeathCondition::DeathCondition() : Module()
{
	name.Create("scene");
	
}

// Destructor
DeathCondition::~DeathCondition()
{
}

// Called before render is available
bool DeathCondition::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool DeathCondition::Start()
{
	active = true;
	bckground = app->tex->Load("Assets/Textures/deathcondition.png");

		

	return true;
}

// Called each loop iteration
bool DeathCondition::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool DeathCondition::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool DeathCondition::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	ret = false;
	
	app->render->DrawTexture(bckground, 0,0, NULL);
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		CleanUp();
		app->logo->Start();
	}
	
	return ret;
}
void DeathCondition::OnCollision(Collider* a, Collider* b)
{
	
}

// Called before quitting
bool DeathCondition::CleanUp()
{
	if (!active)return true;
	//app->entityManager->CleanUp();
	app->deathCondition->active = false;

	LOG("Freeing scene");
	return true;
}