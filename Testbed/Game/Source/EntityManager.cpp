#include "EntityManager.h"

#include "App.h"
#include "Log.h"
#include "Textures.h"
#include "Render.h"
#include "Input.h"
#include "PlayerEntity.h"
#include "Target.h"
#include "Gun.h"

#include "Scene.h"


EntityManager::EntityManager() : Module()
{
	name.Create("entitymanager");
}

bool EntityManager::Awake()
{
	return true;
}

bool EntityManager::Start()
{
	texPlayer = app->tex->Load("Assets/Textures/player.png");
	texTarget = app->tex->Load("Assets/Textures/target.png");
	texGun = app->tex->Load("Assets/Textures/hgranade.png");

	
	playerData.resetCamera = false;

	return true;
}

bool EntityManager::PreUpdate()
{
	return true;
}

bool EntityManager::Update(float dt)
{
	ListItem<Entity*>* entity = entityList.start;

	while (entity != nullptr)
	{
		if (entity->data->pendingToDelete)
		{
			delete entity->data;
			entityList.Del(entity);
			entity = entity->next;
			continue;
		}

		entity->data->Update(dt);
		entity = entity->next;
	}

	
	return true;
}

bool EntityManager::PostUpdate()
{
	
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && (app->scene->active == true ))
	{
		//app->SaveGameRequest();
		if (app->entityManager->playerData.pauseCondition == false)	app->entityManager->playerData.cameraBckUp = app->render->camera;
		if (app->entityManager->playerData.pauseCondition == true)	app->render->camera = app->entityManager->playerData.cameraBckUp;
		app->entityManager->playerData.pauseCondition = !app->entityManager->playerData.pauseCondition;
		app->entityManager->playerData.resetCamera = true;

	}
	if (app->entityManager->playerData.pauseCondition)
	{
		app->render->camera.x = 0;
		app->render->camera.y = 0;
		app->render->DrawTexture(playerData.pauseMenu, 0, -20, NULL);

	}

	for (int i = 0; i < entityList.Count(); i++)
	{
		ListItem<Entity*>* entity = entityList.At(i);
		entity->data->Draw();
	}

	playerData.hit = false;

	return true;
}

bool EntityManager::CleanUp()
{
	for (int i = 0; i < entityList.Count(); i++)
	{
		ListItem<Entity*>* entity = entityList.At(i);
		entity->data->pendingToDelete = true;
	}

	entityList.Clear();

	return true;
}

void EntityManager::AddEntity(fPoint position, Entity::Type type)
{
	switch (type)
	{
	
	case Entity::Type::PLAYER:
		playerEntity = (Entity*)(new PlayerEntity((Module*)this, position, texPlayer, type));
		entityList.Add(playerEntity);
		break;
	case Entity::Type::TARGET:
		targetEntity = (Entity*)(new Target((Module*)this, position, texTarget, type));
		entityList.Add(targetEntity);
		break;
	case Entity::Type::GUN:
		gunEntity = (Entity*)(new Gun((Module*)this, position, texGun, type));
		entityList.Add(gunEntity);
		break;
	}


}

void EntityManager::OnCollision(Collider* a, Collider* b)
{
	for (int i = 0; i < entityList.Count(); i++)
	{
		ListItem<Entity*>* entity = entityList.At(i);

		if (entity->data->collider == a && b != nullptr)
		{
			entity->data->Collision(b);
		}

		if (entity->data->collider == b && a != nullptr)
		{
			entity->data->Collision(a);
		}
	}
}