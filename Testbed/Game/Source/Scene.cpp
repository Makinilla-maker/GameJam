#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "PlayerEntity.h"
#include "Collisions.h"
#include "EntityManager.h"
#include <time.h>
#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");	
}

// Destructor
Scene::~Scene()
{
}

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
	active = true;
	bckground = app->tex->Load("Assets/Textures/background.png");

	app->collisions->AddCollider({ 120,145,10,10 }, Collider::Type::TURNLEFT, this);
	app->collisions->AddCollider({ 43,145,10,10 }, Collider::Type::GODOWN, this);
	app->collisions->AddCollider({ 43,235,10,10 }, Collider::Type::TURNRIGHT, this);
	app->collisions->AddCollider({ 188,235,10,10 }, Collider::Type::GOUP, this);
	app->collisions->AddCollider({ 168,60,10,10 }, Collider::Type::TURNRIGHT, this);
	app->entityManager->Start();
	app->entityManager->AddEntity({217.0f,110.0f}, Entity::Type::PLAYER);
		
	waterBckGrnd = app->tex->Load("Assets/Textures/water.png");
	app->collisions->active = true;

	timer.Start();

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
	int miniGameTime = timer.ReadSec();

	if (miniGameTime == 1) 
	{
		app->entityManager->AddEntity({ 110.0f,0.0f }, Entity::Type::TARGET);
		miniGameTime = 0;
		timer.Start();
	}
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	ret = false;
	
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) app->collisions->debug = !app->collisions->debug;
	
	app->render->DrawTexture(bckground, 0, 0, NULL);

	return ret;
}
void Scene::OnCollision(Collider* a, Collider* b)
{
	
}

// Called before quitting
bool Scene::CleanUp()
{
	if (!active)return true;
	app->entityManager->CleanUp();
	app->scene->active = false;
	app->collisions->CleanUp();

	LOG("Freeing scene");
	return true;
}