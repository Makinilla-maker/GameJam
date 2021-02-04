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
#include "GuiButton.h"

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

	app->collisions->AddCollider({ 212,0,10,250 }, Collider::Type::PLAYERWALLLEFT, this);
	app->collisions->AddCollider({ 385,0,10,250 }, Collider::Type::PLAYERWALLRIGHT, this);
	app->collisions->AddCollider({ 200,15,250,10 }, Collider::Type::PLAYERWALLUP, this);
	app->collisions->AddCollider({ 200, 200,250,10 }, Collider::Type::PLAYERWALLDOWN, this);
	app->entityManager->Start();

	app->entityManager->AddEntity({90.0f,157.0f}, Entity::Type::PLAYER);
	app->entityManager->AddEntity({ 230.0f,115.0f }, Entity::Type::PLAYER2);
		
	waterBckGrnd = app->tex->Load("Assets/Textures/water.png");
	app->collisions->active = true;

	btn1 = new GuiButton(10, { 232, 207, 25, 25 }, "1");
	btn1->SetObserver((Scene*)this);
	btn1->SetTexture(app->tex->Load("Assets/Textures/button1.png"), app->tex->Load("Assets/Textures/button2.png"), app->tex->Load("Assets/Textures/button3.png"));

	btn2 = new GuiButton(11, { 290, 207, 25, 25 }, "2");
	btn2->SetObserver((Scene*)this);
	btn2->SetTexture(app->tex->Load("Assets/Textures/button1.png"), app->tex->Load("Assets/Textures/button2.png"), app->tex->Load("Assets/Textures/button3.png"));

	btn3 = new GuiButton(12, { 348, 207, 25, 25 }, "3");
	btn3->SetObserver((Scene*)this);
	btn3->SetTexture(app->tex->Load("Assets/Textures/button1.png"), app->tex->Load("Assets/Textures/button2.png"), app->tex->Load("Assets/Textures/button3.png"));

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

	if (miniGameTime > 1)
	{
		app->entityManager->AddEntity({ 110.0f,0.0f }, Entity::Type::TARGET);
		miniGameTime = 0;
		timer.Start();
	}
	btn1->Update(app->input, dt);
	btn2->Update(app->input, dt);
	btn3->Update(app->input, dt);

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
	btn1->Draw(app->render);
	btn2->Draw(app->render);
	btn3->Draw(app->render);

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

bool Scene::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		if (control->id == 10 && amelia == false)
		{
			amelia = true;
			letitia = false;
			ada = false;
		}
		if (control->id == 11 && letitia == false)
		{
			letitia = true;
			amelia = false;
			ada = false;
		}
		if (control->id == 12 && ada == false)
		{
			letitia = false;
			amelia = false;
			ada = true;
		}
	}
	}
    return true;
}