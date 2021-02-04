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

	vDestination = { app->entityManager->entityList.At(1)->data->position.x - position.x, app->entityManager->entityList.At(1)->data->position.y - position.y};
	modDestination = sqrt(pow(vDestination.x, 2) + pow(vDestination.y, 2));
	normDestination = { vDestination.x / modDestination, vDestination.y / modDestination }; 

}

bool Gun::Start()
{
	return true;
}

bool Gun::Update(float dt)
{
	position.x += normDestination.x * 5.0f;
	position.y += normDestination.y * 5.0f;
	//collider->SetPos(position.x, position.y);
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
	
	
}

void Gun::CleanUp()
{

}