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
	letitiaXeringa.speed = 0.120f;
	
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
	if (app->scene->amelia && app->scene->moneyCont >= 10)
	{
		if (app->scene->change1)
		{
			app->scene->moneyCont -= 10;
			currentAnimation = &planeAnimation;
		}
	}
	if (app->scene->letitia && app->scene->moneyCont >= 20)
	{
		if (app->scene->change2)
		{
			app->scene->moneyCont -= 20;
			currentAnimation = &letitiaXeringa;
		}
	}
	if (app->scene->ada && app->scene->moneyCont >= 30)
	{
		if (app->scene->change3)
		{
			app->scene->moneyCont -= 30;
			currentAnimation = &adaComputer;
		}
	}
	app->scene->change1 = false;
	app->scene->change2 = false;
	app->scene->change3 = false;
	return true;
}

bool PlayerEntity::Draw()
{
	SDL_Rect playerRect = currentAnimation->GetCurrentFrame();

	fPoint vDestination = { 0,0 };
	float modDestination = 0;
	fPoint normDestination = { 0,0 };

	fPoint pos = { 0,0 };
	if (collider!=nullptr)
	{
		SDL_Rect r = { 3*position.x,3*position.y,3*53,3*52 };
		pos = { float(r.x + (r.w / 2)), float(r.y + (r.h / 2)) };
	}

	for (int i = app->entityManager->entityList.Count(); i > 0; i--)
	{
		if (app->entityManager->entityList.At(i + 2) != nullptr)
		{
			vDestination = { app->entityManager->entityList.At(i + 2)->data->position.x - pos.x, app->entityManager->entityList.At(i + 2)->data->position.y - pos.y };
			modDestination = sqrt(pow(vDestination.x, 2) + pow(vDestination.y, 2));
			normDestination = { vDestination.x / modDestination, vDestination.y / modDestination };
		}
	}
	
	if (vDestination.y < 3 * pos.y)
	{
		app->entityManager->entityList.At(0)->data->angle = asin(vDestination.x / modDestination) * (180 / 3.1415);
	}
	else
	{
		app->entityManager->entityList.At(0)->data->angle = acos(vDestination.y / modDestination) * (180 / 3.1415);
	}

	app->render->DrawTexture(texture, position.x, position.y, &playerRect, 0, angle);

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