#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Logo.h"
#include "Win.h"
#include "Player.h"
#include "Collisions.h"
#include "EntityManager.h"

#include "Defs.h"
#include "Log.h"

Win::Win() : Module()
{
	name.Create("scene");
	
}

// Destructor
Win::~Win()
{
}

// Called before render is available
bool Win::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Win::Start()
{
	active = true;
	bckground = app->tex->Load("Assets/Textures/win.png");

		

	return true;
}

// Called each loop iteration
bool Win::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Win::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool Win::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	ret = false;
	
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) app->collisions->debug = !app->collisions->debug;
	
	app->render->DrawTexture(bckground, 0,-48, NULL);
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		CleanUp();
		app->logo->Start();
	}
	
	return ret;
}
void Win::OnCollision(Collider* a, Collider* b)
{
	
}

// Called before quitting
bool Win::CleanUp()
{
	if (!active)return true;
	app->entityManager->CleanUp();
	app->winCondition->active = false;

	LOG("Freeing scene");
	return true;
}