#include "Coins.h"

#include "App.h"
#include"Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Collider.h"
#include "Audio.h"
#include "EntityManager.h"
#include "Scene.h"
#include "Font.h"
Coins::Coins(Module* listener, fPoint position, SDL_Texture* texture, Type type) : Entity(listener, position, texture, type)
{
	idleAnimation.loop = true;
	idleAnimation.PushBack({ 0, 0, 20, 20 });
	currentAnimation = &idleAnimation;

	collider = app->collisions->AddCollider(SDL_Rect{ (int)position.x,(int)position.y, 20, 20 }, Collider::Type::COINS, listener);
	health = 3;
}

bool Coins::Start()
{
	return true;
}

bool Coins::Update(float dt)
{
	collider->SetPos(position.x, position.y);
	currentAnimation->Update();

	return true;
}

bool Coins::Draw()
{
	SDL_Rect playerRect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(texture, position.x, position.y, &playerRect);

	char score[64] = { 0 };
	sprintf_s(score, 64, "Coins: %d", app->scene->moneyCont);
 	app->render->DrawText(app->render->font, score, 900, 0, 50, 5, { 255, 255, 43, 255 });

	return true;
}

void Coins::Collision(Collider* coll)
{
	if (coll->type == Collider::Type::PLAYER)
	{
		position.x = rand() % 140 + 200;
		position.y = rand() % 170 + 26;
		collected = !collected;
	}
	if (collected)
	{
		app->scene->moneyCont++;
	}
}

void Coins::CleanUp()
{

}