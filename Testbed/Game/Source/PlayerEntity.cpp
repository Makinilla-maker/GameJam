#include "PlayerEntity.h"
#include "App.h"
#include "Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Collider.h"
#include "Scene.h"
#include "Audio.h"
#include "EntityManager.h"



PlayerEntity::PlayerEntity(Module* listener, fPoint position, SDL_Texture* texture, Type type) : Entity(listener, position, texture, type)
{
	idleAnimation.loop = true;
	idleAnimation.PushBack({ 0, 0, 12, 11 });

	walkAnimationRight.PushBack({ 13,0, 12, 11 });
	walkAnimationRight.PushBack({ 26,0, 12, 11 });
	walkAnimationRight.PushBack({ 39,0, 12, 11 });
	walkAnimationRight.PushBack({ 53,0, 14, 11 });
	walkAnimationRight.loop = true;
	walkAnimationRight.speed = 0.1f;

	walkAnimationLeft.PushBack({ 13,12, 12, 11 });
	walkAnimationLeft.PushBack({ 26,12, 12, 11 });
	walkAnimationLeft.PushBack({ 39,12, 12, 11 });
	walkAnimationLeft.PushBack({ 53,12, 14, 11 });
	walkAnimationLeft.loop = true;
	walkAnimationLeft.speed = 0.1f;

	jumpAnimation.PushBack({ 1, 23, 12, 12 });
	jumpAnimation.loop = true;

	currentAnimation = &idleAnimation;

	jumpFx = app->audio->LoadFx("Assets/Audio/FX/jump.wav");
	doubleJumpFx = app->audio->LoadFx("Assets/Audio/FX/double_jump.wav");
	checkPointFx = app->audio->LoadFx("Assets/Audio/FX/checkpoint.wav");
	killingEnemyFx = app->audio->LoadFx("Assets/Audio/FX/enemy_death.wav");

	advice = false;

}

bool PlayerEntity::Start()
{
	return true;
}

bool PlayerEntity::Update(float dt)
{
	if (a)
	{
		app->entityManager->AddEntity({ position.x, position.y }, Entity::Type::GUN);
		a = false;
	}
	
	
	
	cameraControl = true;
	currentAnimation->Update();

	return true;
}

bool PlayerEntity::Draw()
{
	SDL_Rect playerRect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(texture, position.x, position.y, &playerRect);

	return true;
}

void PlayerEntity::Collision(Collider* coll)
{
	if (coll->type == Collider::Type::FLOOR)
	{
		onGround = true;
		position.y = coll->rect.y - coll->rect.h - 9;
		vely = 0;
		position.y = position.y;
		cameraControl = true;
	}
	
}

void PlayerEntity::CleanUp()
{

}


