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
#include "DeathCondition.h"

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
	livesText = app->tex->Load("Assets/Textures/heart.png");

	app->collisions->AddCollider({ 120,145,10,10 }, Collider::Type::TURNLEFT, this);
	app->collisions->AddCollider({ 43,145,10,10 }, Collider::Type::GODOWN, this);
	app->collisions->AddCollider({ 43,235,10,10 }, Collider::Type::TURNRIGHT, this);
	app->collisions->AddCollider({ 188,235,10,10 }, Collider::Type::GOUP, this);
	app->collisions->AddCollider({ 168,70,10,10 }, Collider::Type::TURNRIGHT, this);
	app->collisions->AddCollider({ 200,80,10,10 }, Collider::Type::SPRINT, this);

	app->collisions->AddCollider({ 212,0,10,250 }, Collider::Type::PLAYERWALLLEFT, this);
	app->collisions->AddCollider({ 400,0,10,250 }, Collider::Type::PLAYERWALLRIGHT, this);
	app->collisions->AddCollider({ 200,15,250,10 }, Collider::Type::PLAYERWALLUP, this);
	app->collisions->AddCollider({ 200, 200,250,10 }, Collider::Type::PLAYERWALLDOWN, this);

	app->entityManager->Start();

	app->entityManager->AddEntity({90.0f,157.0f}, Entity::Type::PLAYER);
	app->entityManager->AddEntity({ 230.0f,115.0f }, Entity::Type::PLAYER2);
	app->entityManager->AddEntity({ 250.0f,115.0f }, Entity::Type::COINS);
		
	waterBckGrnd = app->tex->Load("Assets/Textures/water.png");
	app->collisions->active = true;

	btn1 = new GuiButton(10, { 232, 207, 25, 25 }, "1");
	btn1->SetObserver((Scene*)this);
	btn1->SetTexture(app->tex->Load("Assets/Textures/button1.png"), app->tex->Load("Assets/Textures/button2.png"), app->tex->Load("Assets/Textures/button3.png"));

	btn2 = new GuiButton(11, { 290, 207, 25, 25 }, "2");
	btn2->SetObserver((Scene*)this);
	btn2->SetTexture(app->tex->Load("Assets/Textures/button21.png"), app->tex->Load("Assets/Textures/button22.png"), app->tex->Load("Assets/Textures/button23.png"));

	btn3 = new GuiButton(12, { 348, 207, 25, 25 }, "3");
	btn3->SetObserver((Scene*)this);
	btn3->SetTexture(app->tex->Load("Assets/Textures/button31.png"), app->tex->Load("Assets/Textures/button32.png"), app->tex->Load("Assets/Textures/button33.png"));

	lives = 3;

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

	for (int i = 0; i < lives; i++)
	{
		app->render->DrawTexture(livesText, 393, 20*i, NULL);
	}

	int x, y;

	app->input->GetMousePosition(x, y);

	if (amelia == true & (x > 239 && x < 257 && y>207 && y < 232))
	{
		app->render->DrawText(app->render->fonts, "1ra aviadora en atravesar el atlantico", 400, 50, 50, 5, { 0, 0, 0, 0 });
	}

	if (lives <= 0)
	{
		CleanUp();
		app->deathCondition->Start();
	}

	app->render->DrawText(app->render->fonts, "10 Coins", 690, 700, 20, 5, { 0, 0, 0, 0 });
	app->render->DrawText(app->render->fonts, "20 Coins", 860, 700, 20, 5, { 0, 0, 0, 0 });
	app->render->DrawText(app->render->fonts, "30 Coins", 1030, 700, 20, 5, { 0, 0, 0, 0 });

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
				change1 = true;
				change2 = false;
				change3 = false;
			}
			if (control->id == 11 && letitia == false)
			{
				letitia = true;
				amelia = false;
				ada = false;
				change1 = false;
				change2 = true;
				change3 = false;
			}
			if (control->id == 12 && ada == false)
			{
				letitia = false;
				amelia = false;
				ada = true;
				change1 = false;
				change2 = false;
				change3 = true;
			}
		}
	}
    return true;
}