#include "Gun.h"

#include "App.h"
#include"Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Collider.h"
#include "Audio.h"
#include "EntityManager.h"
#include "Scene.h"
#include "Log.h"

Gun::Gun(Module* listener, fPoint position, SDL_Texture* texture, Type type) : Entity(listener, position, texture, type)
{

	bulet1.loop = true;
	bulet1.PushBack({ 0, 3, 16, 18 });
	bulet1.speed = 0.1f;

	bulet2.loop = true;
	bulet2.PushBack({ 0, 22, 16, 18 });
	bulet2.speed = 0.1f;

	bulet3.loop = true;
	bulet3.PushBack({ 0, 40, 16, 18 });
	bulet3.speed = 0.1f;

	currentAnimation = &bulet1;
	for (int i = app->entityManager->entityList.Count(); i > 0; i--)
	{
		if(app->entityManager->entityList.At(i+2) != nullptr)
		{
			vDestination = { app->entityManager->entityList.At(i+2)->data->position.x - position.x, app->entityManager->entityList.At(i+2)->data->position.y - position.y };
			modDestination = sqrt(pow(vDestination.x, 2) + pow(vDestination.y, 2));
			normDestination = { vDestination.x / modDestination, vDestination.y / modDestination };
		}
	}

	collider = collider = app->collisions->AddCollider(SDL_Rect{ (int)position.x,(int)position.y, 16, 16 }, Collider::Type::GUN, listener);
}

bool Gun::Start()
{
	return true;
}

bool Gun::Update(float dt)
{

	if (app->scene->amelia && app->scene->moneyCont >= 10)
	{
		if (app->scene->change1)
		{
			currentAnimation = &bulet1;
		}
	}
	if (app->scene->letitia && app->scene->moneyCont >= 20)
	{
		if (app->scene->change2)
		{
			currentAnimation = &bulet2;
		}
	}
	if (app->scene->ada && app->scene->moneyCont >= 30)
	{
		if (app->scene->change3)
		{
			currentAnimation = &bulet3;
		}
	}
	
	position.x += normDestination.x * 10.0f;
	position.y += normDestination.y * 10.0f;
	collider->SetPos(position.x, position.y);
	currentAnimation->Update();

	return true;
}

bool Gun::Draw()
{
	SDL_Rect GunRect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(texture, position.x, position.y, &GunRect);
	return true;
}

void Gun::Collision(Collider* coll)
{
	if (coll->type == Collider::Type::TARGET)
	{
		pendingToDelete = true;
		collider->pendingToDelete = true;
	}
}

void Gun::CleanUp()
{

}