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
	idleAnimation.loop = true;
	idleAnimation.PushBack({ 0, 0, 20, 20 });
	currentAnimation = &idleAnimation;

	collider = app->collisions->AddCollider(SDL_Rect{ (int)position.x,(int)position.y, 20, 20 }, Collider::Type::TARGET, listener);
	health = 3;
}

bool Target::Start()
{
	return true;
}

bool Target::Update(float dt)
{
	
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
	collider->SetPos(position.x, position.y);
	currentAnimation->Update();
	if (health == 0) 
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
		if (hit == true)
		{
			health -= 1;
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
}

void Target::CleanUp()
{

}