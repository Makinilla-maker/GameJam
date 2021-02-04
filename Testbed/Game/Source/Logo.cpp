#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Logo.h"
#include "Scene.h"
#include "Player.h"
#include "Collisions.h"
#include "EntityManager.h"

#include "Defs.h"
#include "Log.h"

Logo::Logo() : Module()
{
	name.Create("scene");
	
}

// Destructor
Logo::~Logo()
{
}

// Called before render is available
bool Logo::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Logo::Start()
{
	active = true;
	bckground = app->tex->Load("Assets/Textures/logo.png");

		

	return true;
}

// Called each loop iteration
bool Logo::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Logo::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool Logo::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	ret = false;
	
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) app->collisions->debug = !app->collisions->debug;
	
	app->render->DrawTexture(bckground, 0,-48, NULL);
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		CleanUp();
		app->scene->Start();
	}
	
	return ret;
}
void Logo::OnCollision(Collider* a, Collider* b)
{
	
}

// Called before quitting
bool Logo::CleanUp()
{
	if (!active)return true;
	app->entityManager->CleanUp();
	app->logo->active = false;

	LOG("Freeing scene");
	return true;
}