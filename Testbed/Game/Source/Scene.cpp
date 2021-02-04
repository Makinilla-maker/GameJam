#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
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
	app->entityManager->AddEntity({50.0f,100.0f}, 60.0f, 22.0f, 25.0f, Body::Type::PLAYER);

	app->entityManager->AddEntity({ 300.0f, 100.0f }, 15.0f, 20.0f, 20.0f, Body::Type::TARGET);
	app->entityManager->AddEntity({ 480.0f, 70.0f }, 15.0f, 20.0f, 20.0f, Body::Type::TARGET);
	app->entityManager->AddEntity({ 540.0f, 30.0f }, 15.0f, 20.0f, 20.0f, Body::Type::TARGET);
	app->entityManager->AddEntity({ 700.0f, 90.0f }, 15.0f, 20.0f, 20.0f, Body::Type::TARGET);
	app->entityManager->AddEntity({ 820.0f, 120.0f }, 15.0f, 20.0f, 20.0f, Body::Type::TARGET);
	app->entityManager->AddEntity({ 900.0f, 55.0f }, 15.0f, 20.0f, 20.0f, Body::Type::TARGET);
	app->entityManager->AddEntity({ 1020.0f, 75.0f }, 15.0f, 20.0f, 20.0f, Body::Type::TARGET);
	app->entityManager->AddEntity({ 1160.0f, 85.0f }, 15.0f, 20.0f, 20.0f, Body::Type::TARGET);
	app->entityManager->AddEntity({ 1320.0f, 30.0f }, 15.0f, 20.0f, 20.0f, Body::Type::TARGET);
	app->entityManager->AddEntity({ 1520.0f, 60.0f }, 15.0f, 20.0f, 20.0f, Body::Type::TARGET);

	waterBckGrnd = app->tex->Load("Assets/Textures/water.png");
	app->collisions->active = true;

	app->collisions->AddCollider({ 0,0,2000,174 }, Collider::Type::AIR, this);

	app->collisions->AddCollider({ 0,200,183,50 }, Collider::Type::FLOOR, this);
	app->collisions->AddCollider({ 337,200,1800,50 }, Collider::Type::FLOOR, this);

	app->collisions->AddCollider({ 183,200,154,500 }, Collider::Type::WATER, this);

	app->collisions->AddCollider({ 1930,180,26,26 }, Collider::Type::WIN, this);

	app->entityManager->score = 0;

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
	if (app->entityManager->entityList.At(0)->data->position.x > 100.0f && app->entityManager->entityList.At(0)->data->position.x < 1620.0f) app->render->camera.x = -(app->entityManager->entityList.At(0)->data->position.x * 3) +300;
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