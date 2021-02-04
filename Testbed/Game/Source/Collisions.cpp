#include "Collisions.h"

#include "App.h"
#include "Input.h"
#include "Log.h"
#include "Render.h"

Collisions::Collisions(bool startEnabled) : Module()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::PLAYERWALLLEFT] = true;
	matrix[Collider::Type::PLAYERWALLLEFT][Collider::Type::PLAYER] = true;

	matrix[Collider::Type::PLAYER][Collider::Type::PLAYERWALLRIGHT] = true;
	matrix[Collider::Type::PLAYERWALLRIGHT][Collider::Type::PLAYER] = true;

	matrix[Collider::Type::PLAYER][Collider::Type::PLAYERWALLUP] = true;
	matrix[Collider::Type::PLAYERWALLUP][Collider::Type::PLAYER] = true;

	matrix[Collider::Type::PLAYER][Collider::Type::PLAYERWALLDOWN] = true;
	matrix[Collider::Type::PLAYERWALLDOWN][Collider::Type::PLAYER] = true;

	matrix[Collider::Type::PLAYER][Collider::Type::COINS] = true;
	matrix[Collider::Type::COINS][Collider::Type::PLAYER] = true;
	
	matrix[Collider::Type::GUN][Collider::Type::TARGET] = true;
	
	matrix[Collider::Type::TARGET][Collider::Type::GUN] = true;

	matrix[Collider::Type::TARGET][Collider::Type::TURNLEFT] = true;

	matrix[Collider::Type::TURNLEFT][Collider::Type::TARGET] = true;

	matrix[Collider::Type::TARGET][Collider::Type::GODOWN] = true;

	matrix[Collider::Type::GODOWN][Collider::Type::TARGET] = true;

	matrix[Collider::Type::TARGET][Collider::Type::TURNRIGHT] = true;

	matrix[Collider::Type::TURNRIGHT][Collider::Type::TARGET] = true;

	matrix[Collider::Type::TARGET][Collider::Type::GOUP] = true;

	matrix[Collider::Type::GOUP][Collider::Type::TARGET] = true;
}

// Called before render is available
bool Collisions::Awake(pugi::xml_node&)
{
	return true;
}

// Called before the first frame
bool Collisions::Start()
{
	return true;
}

// Called each loop iteration
bool Collisions::PreUpdate()
{


	return true;
}

bool Collisions::Update(float dt)
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}

		}
	}

	return true;
}

bool Collisions::PostUpdate()
{
	if (debug)
		DebugDraw();


	return true;
}

// Called before quitting
bool Collisions::CleanUp()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* Collisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
			LOG("%d ", i);
		}
	}

	return ret;
}


void Collisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}

void Collisions::DebugDraw()
{
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case Collider::Type::NONE:
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;

		case Collider::Type::FLOOR:
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::PLAYER:
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::WATER:
			app->render->DrawRectangle(colliders[i]->rect, 20, 25, 100, alpha);
			break;
		case Collider::Type::AIR:
			app->render->DrawRectangle(colliders[i]->rect, 250, 25, 5, 0);
			break;
		case Collider::Type::GUN:
			app->render->DrawRectangle(colliders[i]->rect, 200, 100, 200, alpha);
			break;
		case Collider::Type::TARGET:
			app->render->DrawRectangle(colliders[i]->rect, 100, 155, 200, alpha);
			break;
		case Collider::Type::WIN:
			app->render->DrawRectangle(colliders[i]->rect, 100, 155, 0, alpha);
			break;
		case Collider::Type::TURNLEFT:
			app->render->DrawRectangle(colliders[i]->rect, 90, 255, 0, alpha);
			break;
		case Collider::Type::TURNRIGHT:
			app->render->DrawRectangle(colliders[i]->rect, 110, 20, 30, alpha);
			break;
		case Collider::Type::GOUP:
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case Collider::Type::GODOWN:
			app->render->DrawRectangle(colliders[i]->rect, 130, 10, 255, alpha);
			break;
		case Collider::Type::PLAYER2:
			app->render->DrawRectangle(colliders[i]->rect, 130, 10, 255, alpha);
			break;
		case Collider::Type::PLAYERWALLLEFT:
			app->render->DrawRectangle(colliders[i]->rect, 200, 200, 255, alpha);
			break;
		case Collider::Type::PLAYERWALLRIGHT:
			app->render->DrawRectangle(colliders[i]->rect, 200, 200, 255, alpha);
			break;
		case Collider::Type::PLAYERWALLUP:
			app->render->DrawRectangle(colliders[i]->rect, 200, 200, 255, alpha);
			break;
		case Collider::Type::PLAYERWALLDOWN:
			app->render->DrawRectangle(colliders[i]->rect, 200, 200, 255, alpha);
			break;
		case Collider::Type::COINS:
			app->render->DrawRectangle(colliders[i]->rect, 200, 200, 255, alpha);
			break;
		}
	}
}



void Collisions::DebugRequest() {

	debug = !debug;
}