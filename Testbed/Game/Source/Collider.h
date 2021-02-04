#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 1500

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		FLOOR,
		PLAYER,
		WATER,
		AIR,
		GUN,
		TARGET,
		WIN,
		TURNLEFT,
		TURNRIGHT,
		GOUP,
		GODOWN,
		PLAYER2,

		MAX
	};

	enum Height
	{
		UNDEFINED
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Height height;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__
