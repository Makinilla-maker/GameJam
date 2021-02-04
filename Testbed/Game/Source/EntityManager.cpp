#include "EntityManager.h"

#include "App.h"
#include "Log.h"
#include "Textures.h"
#include "Render.h"
#include "Player.h"
#include "Gun.h"
#include "Target.h"


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

    return true;
}

bool EntityManager::PreUpdate()
{
    return true;
}

bool EntityManager::Update(float dt)
{
    ListItem<Body*>* entity = entityList.start;

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
    for (int i = 0; i < entityList.Count(); i++)
    {
        ListItem<Body*>* entity = entityList.At(i);
        entity->data->Draw();
    }
    return true;
}

bool EntityManager::CleanUp()
{
    for (int i = 0; i < entityList.Count(); i++)
    {
        ListItem<Body*>* entity = entityList.At(i);
        entity->data->pendingToDelete = true;
    }

    entityList.Clear();

    return true;
}

void EntityManager::AddEntity(fPoint position, float mass, float weight, float height, Body::Type type)
{
    switch (type)
    {
    case Body::Type::PLAYER:
        playerEntity = (Body*)(new Player((Module*)this, position, mass, weight, height, texPlayer, type));
        entityList.Add(playerEntity);
        break;
    case Body::Type::GUN:
        bulletEntity = (Body*)(new Gun((Module*)this, position, mass, weight, height, app->tex->Load("Assets/Textures/hgranade.png") , type));
        entityList.Add(bulletEntity);
        break;
    case Body::Type::TARGET:
        targertEntity = (Body*)(new Target((Module*)this, position, mass, weight, height, texTarget, type));
        entityList.Add(targertEntity);
        break;
    }

}


void EntityManager::OnCollision(Collider* a, Collider* b)
{
    for (int i = 0; i < entityList.Count(); i++)
    {
        ListItem<Body*>* entity = entityList.At(i);

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