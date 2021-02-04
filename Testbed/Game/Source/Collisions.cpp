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
	matrix[Collider::Type::PLAYER][Collider::Type::FLOOR] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WATER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::AIR] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WIN] = true;


	matrix[Collider::Type::FLOOR][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::FLOOR][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::GUN] = true;

	matrix[Collider::Type::GUN][Collider::Type::WATER] = true;
	matrix[Collider::Type::GUN][Collider::Type::TARGET] = true;
	matrix[Collider::Type::GUN][Collider::Type::FLOOR] = true;

	matrix[Collider::Type::TARGET][Collider::Type::GUN] = true;
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
		}
	}
}



void Collisions::DebugRequest() {

	debug = !debug;
}