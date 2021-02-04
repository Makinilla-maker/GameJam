#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Module.h"
#include "Animation.h"
#include "Textures.h"
#include "Point.h"


class Body
{
public:
	enum class Type
	{
		UNKNOWN,
		PLAYER,
		GUN,
		TARGET
	};

	Body(Module* listener, fPoint position, float mass, float weight, float height, SDL_Texture* texture, Type type) : listener(listener), position(position), mass(mass), weight(weight), height(height), texture(texture), type(type)
	{}

	virtual bool Start()
	{
		return true;
	}

	virtual bool Update(float dt)
	{
		return true;
	}

	virtual bool Draw()
	{
		return true;
	}

	virtual void Collision(Collider* coll)
	{

	}

	virtual void CleanUp()
	{

	}

	Module* listener;

	Type type;
	fPoint position;

	float weight;
	float height;
	float mass;
	fPoint size = {weight, height};
	fPoint center = { size.x / 2, size.y / 2 };
	fPoint velocity;
	fPoint acceleration;
	fPoint force;
	float directionAngle;
	float rotationAngle;
	fPoint dirVelo;
	float surface;
	float cd;
	float velRelative;
	float volume;

	bool inWater;

	SDL_Texture* texture;

	Collider* collider = nullptr;

	bool pendingToDelete = false;
};

#endif // __ENTITY_H__