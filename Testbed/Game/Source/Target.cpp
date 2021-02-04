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
	health = 2;
}

bool Target::Start()
{
	return true;
}

bool Target::Update(float dt)
{
	position.y += 1;
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
}

void Target::CleanUp()
{

}