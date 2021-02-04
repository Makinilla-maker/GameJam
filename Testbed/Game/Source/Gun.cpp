#include "Gun.h"

#include "App.h"
#include"Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Collider.h"
#include "Audio.h"
#include "EntityManager.h"
#include "Log.h"

Gun::Gun(Module* listener, fPoint position, SDL_Texture* texture, Type type) : Entity(listener, position, texture, type)
{

	rightAnimation.loop = true;
	rightAnimation.PushBack({ 0, 0, 16, 23 });
	rightAnimation.speed = 0.1f;

	currentAnimation = &rightAnimation;
	for (int i = app->entityManager->entityList.Count(); i > 0; i--)
	{
		if(app->entityManager->entityList.At(i+1) != nullptr)
		{
			vDestination = { app->entityManager->entityList.At(i+1)->data->position.x - position.x, app->entityManager->entityList.At(i+1)->data->position.y - position.y };
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
		app->entityManager->entityList.At(0)->data->angle = acos(vDestination.x / modDestination) * (180 / 3.1415);
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