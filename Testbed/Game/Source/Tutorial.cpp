#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Tutorial.h"
#include "Scene.h"
#include "Collisions.h"
#include "EntityManager.h"

#include "Defs.h"
#include "Log.h"

Tutorial::Tutorial() : Module()
{
	name.Create("scene");
	
}

// Destructor
Tutorial::~Tutorial()
{
}

// Called before render is available
bool Tutorial::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Tutorial::Start()
{
	active = true;
	bckground1 = app->tex->Load("Assets/Textures/tutorial1.png");
	bckground2 = app->tex->Load("Assets/Textures/tutorial2.png");

	x = 0;
	timer.Start();

	return true;
}

// Called each loop iteration
bool Tutorial::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Tutorial::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool Tutorial::PostUpdate()
{
	bool ret = true;
	int s1 = timer.ReadSec();
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	ret = false;
	
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) app->collisions->debug = !app->collisions->debug;
	
	if(s1 <= 8) SDL_RenderCopy(app->render->renderer,bckground1, 0,0);
	else if(s1 >8 && s1<= 16) SDL_RenderCopy(app->render->renderer, bckground2, 0, 0);
	else
	{
		CleanUp();
		app->scene->Start();
	}
	
	
	
	return ret;
}
void Tutorial::OnCollision(Collider* a, Collider* b)
{
	
}

// Called before quitting
bool Tutorial::CleanUp()
{
	if (!active)return true;
	app->entityManager->CleanUp();
	app->tutorial->active = false;

	LOG("Freeing scene");
	return true;
}