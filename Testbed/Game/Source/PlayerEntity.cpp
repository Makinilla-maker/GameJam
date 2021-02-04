#include "PlayerEntity.h"
#include "App.h"
#include "Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Collider.h"
#include "Scene.h"
#include "Audio.h"
#include "EntityManager.h"
#include "Windows.h"
#include <math.h>

PlayerEntity::PlayerEntity(Module* listener, fPoint position, SDL_Texture* texture, Type type) : Entity(listener, position, texture, type)
{

	planeAnimation.PushBack({ 0,0, 53, 51 });
	planeAnimation.PushBack({ 64,0, 53, 51 });
	planeAnimation.PushBack({ 128,0, 53, 51 });
	planeAnimation.PushBack({ 0,64, 53, 51 });
	planeAnimation.PushBack({ 64,64, 53, 51 });

	planeAnimation.PushBack({ 128,64, 53, 51 });
	planeAnimation.PushBack({ 0,128, 53, 51 });
	planeAnimation.PushBack({ 64,128, 53, 51 });

	planeAnimation.loop = true;
	planeAnimation.speed = 0.15f;

	letitiaXeringa.PushBack({ 0,179, 20, 58 });
	letitiaXeringa.PushBack({ 64,179, 20, 58 });
	letitiaXeringa.PushBack({ 128,179, 20, 58 });
	letitiaXeringa.PushBack({ 0,243, 20, 58 });
	letitiaXeringa.PushBack({ 64,243, 20, 58 });
	letitiaXeringa.PushBack({ 128,243, 20, 58 });
	letitiaXeringa.PushBack({ 0,303, 20, 58 });


	letitiaXeringa.loop = true;
	letitiaXeringa.speed = 0.15f;
	
	adaComputer.PushBack({ 205,0, 57, 56 });
	adaComputer.PushBack({ 269,0, 57, 56 });
	adaComputer.PushBack({ 333,0, 57, 56 });
	adaComputer.PushBack({ 205,64, 57, 56 });
	adaComputer.PushBack({ 269,64, 57, 56 });
	adaComputer.PushBack({ 333,64, 57, 56 });
	adaComputer.PushBack({ 205,128, 57, 56 });
	adaComputer.PushBack({ 269,128, 57, 56 });
	adaComputer.PushBack({ 333,128, 57, 56 });


	adaComputer.loop = true;
	adaComputer.speed = 0.3f;
	currentAnimation = &planeAnimation;

	collider = app->collisions->AddCollider(SDL_Rect({ (int)position.x, (int)position.y, 6, 5 }), Collider::Type::PLAYER, listener);

	jumpFx = app->audio->LoadFx("Assets/Audio/FX/jump.wav");
	doubleJumpFx = app->audio->LoadFx("Assets/Audio/FX/double_jump.wav");
	checkPointFx = app->audio->LoadFx("Assets/Audio/FX/checkpoint.wav");
	killingEnemyFx = app->audio->LoadFx("Assets/Audio/FX/enemy_death.wav");

	advice = false;

	timer.Start();

}

bool PlayerEntity::Start()
{

	return true;
}

bool PlayerEntity::Update(float dt)
{
	int miniGameTime = timer.ReadSec();
	if (miniGameTime == 5)
	{
		minigame = true;
	}
	if (miniGameTime == 25)
	{
		minigame = false;
	}
	if (!minigame)
	{
		int ballTime = timer.ReadSec();
		if (ballTime == 1 && app->entityManager->entityList.Count() > 1)
		{
			app->entityManager->AddEntity({ position.x+20, position.y+20 }, Entity::Type::GUN);
			ballTime = 0;
			timer.Start();

		}
		if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		{
			if (debug == false) debug = true;
			else debug = false;
		}
		if (debug == true)
		{
			app->collisions->DebugDraw();
		}

		collider->SetPos(position.x, position.y);
		cameraControl = true;
		currentAnimation->Update();
	}
	if (app->scene->amelia)
	{
		currentAnimation = &planeAnimation;
	}
	if (app->scene->letitia)
	{
		currentAnimation = &letitiaXeringa;
	}
	if (app->scene->ada)
	{
		currentAnimation = &adaComputer;
	}
	return true;
}

bool PlayerEntity::Draw()
{
	SDL_Rect playerRect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(texture, position.x, position.y, &playerRect,0,angle);

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