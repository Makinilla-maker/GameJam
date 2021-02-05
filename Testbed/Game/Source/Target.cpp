#include "Target.h"

#include "App.h"
#include"Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Collider.h"
#include "Audio.h"
#include "EntityManager.h"
#include "Scene.h"

Target::Target(Module* listener, fPoint position, SDL_Texture* texture, Type type) : Entity(listener, position, texture, type)
{
	idleAnimation.PushBack({ 0, 0, 16, 17 });
	idleAnimation.PushBack({ 17, 0, 16, 18 });
	idleAnimation.PushBack({ 34, 0, 16, 19 });
	idleAnimation.PushBack({ 51, 0, 16, 20 });
	idleAnimation.PushBack({ 68, 0, 16, 19 });
	idleAnimation.PushBack({ 85, 0, 16, 18 });
	idleAnimation.speed = 0.05f;
	idleAnimation.loop = true; 
	currentAnimation = &idleAnimation;

	collider = app->collisions->AddCollider(SDL_Rect{ (int)position.x,(int)position.y, 20, 20 }, Collider::Type::TARGET, listener);
	health = 5;
}

bool Target::Start()
{
	return true;
}

bool Target::Update(float dt)
{
	if (!launch)
	{

		if (position.x > 427)
		{
			pendingToDelete = true;
		}
		if (goLeft)
		{
			position.y += 0;
			position.x -= 0.5;
		}
		if (goDown)
		{
			position.y += 0.5;
			position.x += 0;
		}
		if (goRight)
		{
			position.y += 0;
			position.x += 0.5;
		}
		if (goUp)
		{
			position.y -= 0.5;
			position.x += 0;
		}
	}
	else
	{
		position.x += normDestination.x*2.5f;
		position.y += normDestination.y*2.5;
	}
	collider->SetPos(position.x, position.y);
	currentAnimation->Update();
	if (health <= 0) 
	{
		pendingToDelete = true;
		collider->pendingToDelete = true;
	}
	hit = true;
	return true;
}

bool Target::Draw()
{
	SDL_Rect playerRect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(texture, position.x, position.y, &playerRect);

	return true;
}

void Target::Collision(Collider* coll)
{
	if (coll->type == Collider::Type::GUN)
	{
		if (hit == true && app->entityManager->powerfire == false)
		{
			health -= 1;
			hit = false;
		}
		if (hit == true && app->entityManager->powerfire == true)
		{
			health -= 2;
			hit = false;
		}
	}
	if (coll->type == Collider::Type::TURNLEFT)
	{
		goLeft = true;
		goDown = false;
		goRight = false;
		goUp = false;
	}
	if (coll->type == Collider::Type::GODOWN)
	{
		goLeft = false;
		goDown = true;
		goRight = false;
		goUp = false;
	}
	if (coll->type == Collider::Type::TURNRIGHT)
	{
		goLeft = false;
		goDown = false;
		goRight = true;
		goUp = false;
	}
	if (coll->type == Collider::Type::GOUP)
	{
		goLeft = false;
		goDown = false;
		goRight = false;
		goUp = true;
	}
	if (coll->type == Collider::Type::SPRINT)
	{
		launch = true;
		vDestination = { app->entityManager->entityList.At(1)->data->position.x - position.x, app->entityManager->entityList.At(1)->data->position.y - position.y };
		modDestination = sqrt(pow(vDestination.x, 2) + pow(vDestination.y, 2));
		normDestination = { vDestination.x / modDestination, vDestination.y / modDestination };
	}
	if (coll->type == Collider::Type::PLAYERWALLDOWN || coll->type == Collider::Type::PLAYERWALLRIGHT || coll->type == Collider::Type::PLAYERWALLUP)
	{
		pendingToDelete = true;
		collider->pendingToDelete = true;
	}
	if (coll->type == Collider::Type::PLAYER)
	{
		pendingToDelete = true;
		collider->pendingToDelete = true;
	}
}

void Target::CleanUp()
{

}