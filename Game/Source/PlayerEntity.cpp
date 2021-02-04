#include "PlayerEntity.h"
#include "App.h"
#include "Render.h"
#include "Collisions.h"
#include "Collider.h"
#include "FadeToBlack.h"
#include "Scene1.h"
#include "Title.h"
#include "Map.h"
#include "Audio.h"
#include "EntityManager.h"
#include "Fonts.h"


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

	collider = app->collisions->AddCollider(SDL_Rect({ (int)position.x, (int)position.y, 12, 11 }), Collider::Type::PLAYER, listener);
	footCollider = app->collisions->AddCollider(SDL_Rect({ (int)position.x + 1, (int)position.y + 10, 10, 7 }), Collider::Type::PLAYERFOOT, listener);

	advice = false;
	
}

bool PlayerEntity::Start()
{
	return true;
}

bool PlayerEntity::Update(float dt)
{
	if (!app->entityManager->playerData.pauseCondition)
	{
		app->render->camera.y = -app->entityManager->playerData.position.y + 50;
		//PlayerData Info Containers
		app->entityManager->playerData.position.x = position.x;
		app->entityManager->playerData.position.y = position.y;
	
		//Camera Update
		if (position.y <= 230 && position.y >= 20)
		{
			app->render->camera.y = -position.y + 50;
		}

		//Player States
		if (onGround == false && godMode == false)
		{
			vely += gravity;
			position.x += velx;
			position.y += vely;
		}
		if (onGround == true && godMode == false)
		{
			playerJumping = true;
		}

		//Player Movement
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE
			&& app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE
			&& app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE) 
		{
			currentAnimation = &idleAnimation;
		}
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			position.x -= 60 * dt;
			if (godMode == false)
			{
				onGround = false;
			}
			if (currentAnimation != &walkAnimationLeft) 
			{
				walkAnimationLeft.Reset();
				currentAnimation = &walkAnimationLeft;
			}
		}
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.x += 60 * dt;
			if (godMode == false)
			{
				onGround = false;
			}
			if (currentAnimation != &walkAnimationRight) 
			{
				walkAnimationRight.Reset();
				currentAnimation = &walkAnimationRight;
			}
		}
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && godMode == true)
		{
			position.y -= 120 * dt;
			app->render->camera.y += 180 * dt;
		}

		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && godMode == true)
		{
			position.y += 120 * dt;
			app->render->camera.y -= 180 * dt;
		}
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && godMode == false)
		{
			if (doubleJump == true && onGround == false)
			{
				vely = -4.5f;
				doubleJump = false;
				if (currentAnimation != &jumpAnimation)
				{
					jumpAnimation.Reset();
					currentAnimation = &jumpAnimation;
				}
			}
			if (playerJumping == true)
			{
				playerJumping = false;
				vely = -5.5f;
				position.y += vely;
				doubleJump = true;
				if (currentAnimation != &jumpAnimation)
				{
					jumpAnimation.Reset();
					currentAnimation = &jumpAnimation;
				}
				onGround = false;
			}
		}
		if (app->entityManager->playerData.footJump == true)
		{
			playerJumping = false;
			vely = -5.5f;
			position.y += vely;
			app->entityManager->playerData.footJump = false;
		}

		//Debug Keys
		/////////////////////////////////////////////////////////////////////////////////////////
		//F1 passes to Previous Level
		if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_REPEAT)
		{
			if (app->scene1->active == true)
			{
				position.x = app->entityManager->playerData.initPositionScene1.x;
				position.y = app->entityManager->playerData.initPositionScene1.y;
				app->render->camera.y = -app->entityManager->playerData.position.y + 50;
				app->render->camera.x = 0;
			}
		}
		//F2 passes to Next Level
		//F3 puts Player and Camera at Inital Position
		if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_REPEAT)
		{
			if (app->scene1->active == true)
			{
				position.x = app->entityManager->playerData.initPositionScene1.x;
				position.y = app->entityManager->playerData.initPositionScene1.y;
				app->render->camera.y = -app->entityManager->playerData.position.y + 50;
				app->render->camera.x = 0;
			}
		}
		//F5/F6 Save/Load Requests
		if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		{
			app->SaveGameRequest();
			app->fileSaved = true;
		}
		if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
			app->LoadGameRequest();
		//F9 DebugDraw
		if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		{
			if (debug == false) debug = true;
			else debug = false;
		}
		if (debug == true) {
			app->collisions->DebugDraw();
			app->map->DrawPath();
		}
		//GodMode
		if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		{
			if (godMode == true)
			{
				godMode = false;
				app->entityManager->playerData.godMode = false;
			}
			else
			{
				godMode = true;
				app->entityManager->playerData.godMode = true;
				collider->SetPos(-100, -100);
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////

		if (godMode == false)
		{
			collider->SetPos(position.x, position.y);
			footCollider->SetPos(position.x + 1, position.y + 12);
		}

		if ((app->scene1->active && app->scene1->time <= 0) && app->stop == false)
		{
			app->stop = true;
			app->fade->Fade((Module*)app->scene1, (Module*)app->deathScreen, 30);
		}
		if (advice == true)
		{
			app->render->DrawText(app->render->font, "Pisa al jefe en la cabeza", 400, 300, 50, 5, { 100, 100, 100, 255 });
			if ((app->entityManager->playerData.position.x <= 120.0f || app->entityManager->playerData.position.x >= 146.0f))
			{
				advice = false;
			}
		}

		if (((app->entityManager->playerData.position.x >= 120.0f && app->entityManager->playerData.position.x <= 146.0f) && (app->entityManager->playerData.position.y >= 266.0f && app->entityManager->playerData.position.y <= 278.0f)))
		{
			if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
			{
				advice = !advice;
			}
		}

		cameraControl = true;
		currentAnimation->Update();

	}
	

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
	if (coll->type == Collider::Type::LEFT_WALL)
	{
		position.x = coll->rect.x - coll->rect.w - 10;
		cameraControl = false;
	}
	if (coll->type == Collider::Type::RIGHT_WALL)
	{
		position.x = coll->rect.x + coll->rect.w + 1;
		cameraControl = false;
	}
	if (coll->type == Collider::Type::ROOF)
	{
		vely = 0;
		position.y = coll->rect.y + coll->rect.h;
		cameraControl = false;
	}

	if (coll->type == Collider::Type::ENEMY)
	{
		if (app->entityManager->playerData.lives != 0)
		{
			if (coll->rect.x > position.x)
			{
				position.x = coll->rect.x - coll->rect.w - 9;
			}
			if (coll->rect.x < position.x)
			{
				position.x = coll->rect.x + coll->rect.w + 6;
			}
		}
	}

	if (coll->type == Collider::Type::DEATH && deathCondition == false)
	{
		app->entityManager->playerData.lives -= 1;
		if (app->entityManager->playerData.lives > 0)
		{
			deathCondition = true;
			position.x = app->entityManager->playerData.initPositionScene3.x;
			position.y = app->entityManager->playerData.initPositionScene3.y;
			app->render->camera.y = -app->entityManager->playerData.position.y + 50;
			app->render->camera.x = 0;
		}
		
		deathCondition = false;
	}
}

void PlayerEntity::CleanUp()
{

}


