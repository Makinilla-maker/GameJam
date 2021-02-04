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

	app->entityManager->Start();
	app->entityManager->AddEntity({217.0f,110.0f}, Entity::Type::PLAYER);

	app->entityManager->AddEntity({ 100.0f,50.0f }, Entity::Type::TARGET);
	app->entityManager->AddEntity({ 300.0f,50.0f }, Entity::Type::TARGET);
	
	waterBckGrnd = app->tex->Load("Assets/Textures/water.png");
	app->collisions->active = true;

	

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

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	ret = false;
	
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) app->collisions->debug = !app->collisions->debug;
	
	app->render->DrawTexture(bckground, 0, -40, NULL);
	app->render->DrawTexture(waterBckGrnd, 183, 200, NULL);

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