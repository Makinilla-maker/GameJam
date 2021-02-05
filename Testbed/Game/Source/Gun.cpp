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

	bullet1.loop = true;
	bullet1.PushBack({ 0, 3, 16, 18 });
	bullet1.speed = 0.1f;

	bullet2.loop = true;
	bullet2.PushBack({ 0, 22, 16, 18 });
	bullet2.speed = 0.1f;

	bullet3.loop = true;
	bullet3.PushBack({ 0, 40, 16, 18 });
	bullet3.speed = 0.1f;

	currentAnimation = &bullet1;

	if (app->scene->change1)	currentAnimation = &bullet1;
	if (app->scene->change2)	currentAnimation = &bullet3;
	if (app->scene->change3)	currentAnimation = &bullet2;
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
	
	if (app->scene->amelia && app->scene->moneyCont >= 10 && stopu == false)
	{
		
		if (app->scene->change1)
		{
			currentAnimation = &bullet1;
			stopu = true;
		}
	}
	if (app->scene->letitia && stopu == false)
	{
		
		if (app->scene->moneyCont >= 20)
		{
			
			if (app->scene->change2)
			{
				app->scene->moneyCont -= 20;
				currentAnimation = &bullet2;
				stopu = true;
			}
		}
	}
	if (app->scene->ada && app->scene->moneyCont >= 30 && stopu == false)
	{
		
		if (app->scene->change3)
		{
			app->scene->moneyCont -= 30;
			currentAnimation = &bullet3;
			stopu = true;
		}
	}
	stopu = false;
	app->scene->letitia = false;
	app->scene->amelia = false;
	app->scene->ada = false;
	/*app->scene->change1 = false;
	app->scene->change2 = false;
	app->scene->change3 = false;*/
	
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