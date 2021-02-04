#include "Gun.h"

#include "App.h"
#include"Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Collider.h"
#include "Audio.h"
#include "EntityManager.h"
#include "Log.h"

Gun::Gun(Module* listener, fPoint position, float mass, float weight, float height, SDL_Texture* texture, Type type) : Body(listener, position, mass, weight, height, texture, type)
{

	rightAnimation.loop = true;
	rightAnimation.PushBack({ 0, 0, 16, 23 });
	rightAnimation.speed = 0.1f;

	currentAnimation = &rightAnimation;

	collider = collider = app->collisions->AddCollider(SDL_Rect{ (int)position.x,(int)position.y, 16, 16 }, Collider::Type::GUN, listener);

	dirVelo = { 1.0f,0 };
	surface = 1;
	cd = 1;
	velRelative = 20;
	volume = 0;
	inWater = false;

	app->input->GetMousePosition(x, y);	
	app->render->ScreenToWorld(x,y);

	vDestination = { x - (float)50, y - (float)190};
	modDestination = sqrt(pow(vDestination.x, 2) + pow(vDestination.y, 2));
	normDestination = { vDestination.x / modDestination, vDestination.y / modDestination }; 

}

bool Gun::Start()
{
	return true;
}

bool Gun::Update(float dt)
{
	/////////////////////////////////////////PHYSICS LOGIC/////////////////////////////////////////
	

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
	if (coll->type == Collider::Type::FLOOR)
	{
		pendingToDelete = true;
		collider->pendingToDelete = true;
	}
	if (coll->type == Collider::Type::WATER)
	{
		inWater = true;
	}
	if (coll->type == Collider::Type::TARGET)
	{
		pendingToDelete = true;
		collider->pendingToDelete = true;
		
	}
}

void Gun::CleanUp()
{

}