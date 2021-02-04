#include "Player.h"
#include "App.h"
#include "Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Collider.h"
#include "Scene.h"
#include "Audio.h"
#include "EntityManager.h"
#include "Windows.h"
#include <time.h>




Player::Player(Module* listener, fPoint position, SDL_Texture* texture, Type type) : Entity(listener, position, texture, type)
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

	jumpFx = app->audio->LoadFx("Assets/Audio/FX/jump.wav");
	doubleJumpFx = app->audio->LoadFx("Assets/Audio/FX/double_jump.wav");
	checkPointFx = app->audio->LoadFx("Assets/Audio/FX/checkpoint.wav");
	killingEnemyFx = app->audio->LoadFx("Assets/Audio/FX/enemy_death.wav");

	advice = false;


}

bool Player::Start()
{

	return true;
}

bool Player::Update(float dt)
{
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			position.y -= 1;
		}
		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			position.y += 1;
		}
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			position.x -= 1;
		}
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.x += 1;
		}
		if (debug == true)
		{
			app->collisions->DebugDraw();
		}


		collider->SetPos(position.x, position.y);
		cameraControl = true;
		currentAnimation->Update();
	return true;
}

bool Player::Draw()
{
	SDL_Rect playerRect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(texture, position.x, position.y, &playerRect);

	return true;
}

void Player::Collision(Collider* coll)
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
void Player::CleanUp()
{

}